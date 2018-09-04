# Fall 2016 CSci4211: Introduction to Computer Networks
# This program serves as the server of DNS query.
# Written in Python v3.

import sys, threading, os, re
from socket import *

def main():
	host = "localhost" # Hostname. It can be changed to anything you desire.
	port = 5001 # Port number.

	#create a socket object, SOCK_STREAM for TCP

	#bind socket to the current address on port 5001

	#Listen on the given socket maximum number of connections queued is 20:
				#blocked until a remote machine connects to the local port 5001

	try:
		sSock = socket(AF_INET, SOCK_STREAM)
	except error as msg:
		sSock = None
	try:
		sSock.bind((host, port))
	except error as msg:
		sSock = None

	sSock.listen(20)

	monitor = threading.Thread(target=monitorQuit, args=[])
	monitor.start()


	print("Server is listening...")

	while 1:
		connectionSock, addr = sSock.accept()
		server = threading.Thread(target=dnsQuery, args=[connectionSock, addr[0]])
		server.start()


def dnsQuery(connectionSock, srcAddress):
	#check the DNS_mapping.txt to see if the host name exists
	#set local file cache to predetermined file.
		 #create file if it doesn't exist
		 #if it does exist, read the file line by line to look for a
		 #match with the query sent from the client
	#If no lines match, query the local machine DNS lookup to get the IP resolution
	#write the response in DNS_mapping.txt
	#print response to the terminal
	#send the response back to the client
	#Close the server socket.
	host = connectionSock.recv(1024).decode().lower()
	file_exit = os.path.isfile("DNS_mapping.txt")

	if(file_exit):
		#file exit then jsut read and write things in it.
		file_ = open("DNS_mapping.txt", "r+")
		d  = file_.readlines()
		response = ""
		#check the inoput if is valid, if it not valid return Invalid format
		format_correct = is_valid_hostname(host)

		if(format_correct):
			#use a for loop to check if the input in the file
			find = False
			for line in d:
				if(host.replace("www.","") in line):
					find = True
					response = "Local DNS:"+line
					print(response)
					response = response.replace('\n','')
					break
			#If not find in the exited file, using gethostbyname to get ip address from Root DNS, then write it to in the file
			if(find == False):
				try:
					ip = gethostbyname(host)
					response = "Root DNS:"+str(host)+":"+str(ip)
					print(response)
					file_.write(str(host)+":"+str(ip)+ "\n")
				except Exception as esponse:
					response = "Host not found"
					print(response)
					file_.close()
		else:
			response = "Invalid format"
			print(response)
	else:
		#file doesn't exit. Creat a new one and look for the ip address from the root DNS
		file_ = open("DNS_mapping.txt", "w")
		try:
			ip = gethostbyname(host)
			response = "Root DNS:"+str(host)+":"+str(ip)
			print(response)
			file_.write(str(host)+":"+str(ip)+ "\n")
		except Exception as response:
			response = "Host not found"
			print(response)
		file_.close()

	connectionSock.send(response.encode())
	connectionSock.close()



def monitorQuit():
	while 1:
		sentence = input()
		if sentence == "exit":
			os.kill(os.getpid(),9)

#This function is used to check if the host is valid
def is_valid_hostname(hostname):
	reserved = [";","/","?",":","@","&","=","+","$",","]
	valid = True
	if len(hostname) > 255:
		valid = False
	else:
		for c in reserved:
			if c in hostname:
				valid = False
	return valid

main()
