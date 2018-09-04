import os, sys, time, socket, threading, random, select
import argparse
import hashlib
import socket

TIMEOUT = 5 # Wait for five seconds.
SIZE = 512


# Using "SYN" "ACK" "SAK" "RST" "FIN" "AKF" to represent SYN, ACK, SYNACK, RST, FIN, ACKFIN.
# Using 1 represent the last sign is activited and otherwise 0

def check_valid_packet(packet):
	valided = False
	key = packet[:20]
	check = packet[20:]
	# get key to check
	compare_key = hashlib.sha1(check.encode()).hexdigest()
	compare_key = compare_key[:20]
	if(key == compare_key):
		valided = True
	print("After packet check, the result is "+str(valided))
	return valided

# check_sum = packet[:20] syn = packet[20], sizedata = packet[21:23],  last_sign = packet[24], data = packet[25:]
def generate_a_packet(seq_No, data, last_Sign):

	# 3 byte total size of the data, use 0 to complete it.

	packet = str(seq_No) + "%03d"%(len(data)) + str(last_Sign) + data
	# give data to packet, total size is 487
	packet +=  "\x00" *(487 - len(data))
	# hexdigest
	check_sum_num = hashlib.sha1(packet.encode()).hexdigest()
	# make check_sum+num to be 20-Byte
	check_sum_num = check_sum_num[:20]
	# creat packet
	packet = check_sum_num + packet
	return packet


def monitorQuit():
	while 1:
		sentence = input()
		if sentence == "exit":
			os.kill(os.getpid(),9)

def Client(host, port, filename):
	try:
		cSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		cSock.connect((host, port))
		print("Hello Sever! ")
	except err as msg:
		print(msg)
	try:
		# open file
		f = open(filename, 'r')
		print ("Sending...")
		file_data = f.read()
		file_len = len(file_data)
		f.close()
		# record the position
		file_start = 0
		file_end = 0
	except err as msg:
		print(msg)
	# begin to hand shake
	seq_No = 0
	print("Client : Send packet with SYN to Server..")
	packet = generate_a_packet(seq_No, "SYN", 0)
	cSock.send(packet.encode())
	first = True
	while True:
		#Following part is how to handle timeout event. Please pay attention!
		ready = select.select([cSock], [], [], TIMEOUT)
		if ready[0]:
			print("Client : Recevied a Packet from Server..")
			packet_ = cSock.recv(SIZE).decode()
		else:
			print("Client : Timeout! Retransmitting...")
			cSock.send(packet.encode())
			continue
# check_sum = packet[:20] seq = packet[20], sizedata = packet[21:23],  last_sign = packet[24], data = packet[25:]
		if(len(packet_)<512):
			break
		if(not check_valid_packet(packet_)):
			print("Client : Transmitting "+ str(seq_No) + "th packet")
			print("Client : Opps, receiving a invalid packet! Ignore it... ")
			cSock.send(packet.encode())
			continue
		seq = int(packet_[20])
		sizedata =int(packet_[21:24])
		last_sign = int(packet_[24])
		data = packet_[25:]
		if(seq_No != seq and last_sign == 0):
			print("Client : Can't match with squence number, retransmitting...")
			# resend packet
			cSock.send(packet.encode())
			continue

		if (first):
			# if the packet sent by server is SYNACK, then the hand shake has done halfly
			if(data[:3] == "SAK"):
				first = False
				print("Client : Receiving SYNACK from Server, connection established...")
				print("Client : Transmitting filename...")
				seq_No = (seq_No+1)%10
				packet = generate_a_packet(seq_No, "ACK"+filename, 0)
				cSock.send(packet.encode())
				continue
			else:
				# Problem 2: SYNACK lost, waittinf for new one
				print("Client : Do not Receive SYNACK from Server...")
				cSock.send(packet.encode())
				continue

		if(data[:3] == "AKF"):
			print("Client : Receive ACKFIN. Half close, waitting for FIN sent from server")
			seq_No = (seq_No+1)%10
			packet = generate_a_packet(seq_No,"AKF",1)
			cSock.send(packet.encode())

		if(data[:3] == "ACK"):
			print("Client : Start transmitting file...")
			seq_No = (seq_No+1)%10
			file_end = min(file_start+487,file_len) #add 487 bytes of data to the starting position
			content = file_data[file_start:file_end]
			file_start = file_end
			packet = generate_a_packet(seq_No,content,0)

			if(len(content) == 0):
				print("Client : Transmission process is done, send FIN to server")
				packet = generate_a_packet(seq_No,"FIN",0)
			cSock.send(packet.encode())
		else:
			print("Client : invaild ACK packet, retransmitting...")
			cSock.send(packet.encode())
	print("Client : Connection Canceled" )
	cSock.shutdown(1)
	cSock.close()


def Server(host, port):
	sSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sSock.bind((host, port))
	sSock.listen(20)
	monitor = threading.Thread(target=monitorQuit, args=[])
	monitor.start()
	print("Server is listening...")
	while 1:
		connectionSock, addr = sSock.accept()
		server = threading.Thread(target=file_trans, args=[connectionSock, addr[0]])
		server.start()



def file_trans(sSock, srcAddress):
	seq_No = 0
	packet = ""
	first = True # differenciated the first ACK packet
	SYN_record = True
	ACK_record = True
	packet_ = ""
	while True:
		ready = select.select([sSock], [], [], TIMEOUT)
		if ready[0]:
			print("Server : Recevied a Packet from client")
			packet_ = sSock.recv(SIZE).decode()
			print(packet_)
		else:
			if(packet!= ""):
				print("Server : not receive a SYN packet from client ")
				print("Server : Timeout! Retransmitting...")
				sSock.send(packet.encode())
		if(len(packet_)<512):
			break
		if(not check_valid_packet(packet_)):
			print("Server : Transmitting "+ str(seq_No) + "th packet")
			print("Server : Opps, receiving a invalid packet! Ignore it ")
			sSock.send(packet.encode())
			continue
# check_sum = packet[:20] seq = packet[20], sizedata = packet[21:23],  last_sign = packet[24], data = packet[25:]
		seq = int(packet_[20])
		sizedata =int(packet_[21:24])
		last_sign = int(packet_[24])
		data = packet_[25:]
		if(last_sign == 1):
			print("Server : Closing ... ")
			break
		if(seq_No != seq and last_sign == 0):
			print("Server : Can't match with squence number, retransmitting...")
			# resend packet
			sSock.send(packet.encode())
		if(SYN_record):
			if(data[:3] == "SYN"):
				SYN_record  = False
				print("Server : Receving SYN from Client, and send SYNACK back...")
				seq_No = (seq + 1)%10
				packet = generate_a_packet(seq,"SAK",0)
				sSock.send(packet.encode())
				continue
			else:
				print("Server : receiving packet which is not valid for SYN, retransmitting...")
				sSock.send(packet.encode())

			# first to use to differenciated SYNACK and normal ACK
		if(first and data[:3] == "ACK"):
			first = False
			print("Server : Receive filename and waitting transmitting file...")
			filename = data[3:sizedata]
			print("Server : Building the file ...")
			f = open(filename, "w")
			seq_No = (seq + 1)%10
			packet = generate_a_packet(seq,"ACK",0)
			sSock.send(packet.encode())
			continue
		if(not first and data[:3] != "FIN" and data[:3] != "AKF" and seq_No == seq ):
			filedata = data[:sizedata]
			if(len(filedata) > 0):
				print("Server : Writing file...")
				f.write(filedata)
				seq_No = (seq + 1)%10
				packet = generate_a_packet(seq,"ACK",0)
				sSock.send(packet.encode())
		if(data[:3] == "FIN"):
			print("Server : receiving FIN from client, and send ACKFIN back ")
			seq_No = (seq + 1)%10
			packet = generate_a_packet(seq,"AKF",0)
			sSock.send(packet.encode())
			continue
		if(data[:3] == "AKF"):
			print("Server : receiving ACKFIN from client, and fully close")
			print("Server : Connection Canceled" )
			f.close()
			break


	sSock.shutdown(1)
	sSock.close()



def parser():
	parser = argparse.ArgumentParser()
	parser.add_argument('-ho',  type = str , default = 'localhost',
	 help = "specify a host")
	parser.add_argument('-spo',  type = int , default = 5001,
	help = "specify a portnumber used by server, default portnumber for server is 5001")
	# parser.add_argument('-cpo',  type = int , default = 5002,
	# help = "specify a portnumber used by client, default portnumber for client is 5002")
	parser.add_argument('-fi',  type = str , default = '',
	help = "specify a file waitting for transfering")
	args = parser.parse_args()
	return (args.ho, args.spo, args.fi)



def main():
	(ho,spo,fi) = parser()
	if(fi == ""):
		# No file this time, run server
		return Server(ho,spo)
	else:
		return Client(ho,spo,fi)


main()
