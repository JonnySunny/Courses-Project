from pox.core import core
import pox
from pox.lib.packet.ethernet import ethernet, ETHER_BROADCAST
from pox.lib.packet.ipv4 import ipv4
from pox.lib.packet.arp import arp
from pox.lib.addresses import IPAddr, EthAddr
from pox.lib.util import dpid_to_str, str_to_bool
from pox.lib.recoco import Timer
import pox.openflow.libopenflow_01 as of
from pox.lib.revent import *
import time

# Even arp_request simple usage of the logger is much nicer than print!
log = core.getLogger()

#ARP table
arp_table = {"10.0.0.1":"00:00:00:00:00:01",
			 "10.0.0.2":"00:00:00:00:00:02",
			 "10.0.0.3":"00:00:00:00:00:03",
			 "10.0.0.4":"00:00:00:00:00:04",
			 "10.0.0.5":"00:00:00:00:00:05",
			 "10.0.0.6":"00:00:00:00:00:06"}
			 
#forwarding tables			 
l1 = {"00:00:00:00:00:01": 3,
	 "00:00:00:00:00:02": 4,
	 "00:00:00:00:00:03": 1,
	 "00:00:00:00:00:04": 2,
	 "00:00:00:00:00:05": 1,
	 "00:00:00:00:00:06": 2}
	 
l2 = {"00:00:00:00:00:01": 1,
	 "00:00:00:00:00:02": 2,
	 "00:00:00:00:00:03": 3,
	 "00:00:00:00:00:04": 4,
	 "00:00:00:00:00:05": 1,
	 "00:00:00:00:00:06": 2}
	 
l3 = {"00:00:00:00:00:01": 1,
	 "00:00:00:00:00:02": 2,
	 "00:00:00:00:00:03": 1,
	 "00:00:00:00:00:04": 2,
	 "00:00:00:00:00:05": 3,
	 "00:00:00:00:00:06": 4}
	 
s4 = {"00:00:00:00:00:01": 1,
	 "00:00:00:00:00:03": 2,
	 "00:00:00:00:00:05": 3}
	 
s5 = {"00:00:00:00:00:02": 1,
	 "00:00:00:00:00:04": 2,
	 "00:00:00:00:00:06": 3}
	 
l1_s4 = False
l2_s4 = False
l3_s4 = False
l1_s5 = False
l2_s5 = False
l3_s5 = False

# Handle messages the switch has sent us because it has no
# matching rule.

def _handle_PacketIn (event):
	# check if the entry is in the table or not
	# if it's not in the table, add an entry to the table
	# We don't know where the destination is yet.  So, we'll just
	# send the packet out all ports (except the one it came in on!)
	# and hope the destination is out there somewhere. :)
	# To send out all ports, we can use either of the special ports
	# OFPP_FLOOD or OFPP_ALL. 
	# if the appropriate entry is in the table, just forward the packet to that port

	# parse the packet

	packet = event.parsed
	src_mac = packet.src
	dst_mac = packet.dst
	switch = event.connection
	port_in = event.port
	switch = event.connection
	match = of.ofp_match.from_packet(packet)
	arp_request = packet.find('arp')
	#identify switch
	dpid = event.connection.dpid
	
	if not arp_request:
		#part 2
		if(dpid_to_str(dpid) == "00-00-00-00-00-01"):
			port_out = l1[str(dst_mac)]
		elif (dpid_to_str(dpid) == "00-00-00-00-00-02"):
			port_out = l2[str(dst_mac)]
		elif (dpid_to_str(dpid) == "00-00-00-00-00-03"):
			port_out = l3[str(dst_mac)]
		elif (dpid_to_str(dpid) == "00-00-00-00-00-04"):
			port_out = s4[str(dst_mac)]
		elif (dpid_to_str(dpid) == "00-00-00-00-00-05"):
			port_out = s5[str(dst_mac)]

		msg = of.ofp_packet_out()
		msg.data = event.ofp
		msg.actions.append(of.ofp_action_output(port = port_out))
		switch.send(msg)
	else:
		if arp_request.prototype == arp.PROTO_TYPE_IP:
			if arp_request.hwtype == arp.HW_TYPE_ETHERNET:
				if arp_request.protosrc != 0:
					if arp_request.opcode == arp.REQUEST:
					  dst_ip = arp_request.protodst
					  src_ip = arp_request.protosrc
					  res = arp()
					  res.hwtype = arp_request.hwtype
					  res.prototype = arp_request.prototype
					  res.hwlen = arp_request.hwlen
					  res.protolen = arp_request.protolen
					  res.opcode = arp.REPLY
					  res.hwdst = arp_request.hwsrc
					  res.protodst = src_ip
					  res.protosrc = dst_ip
					  mac = EthAddr(arp_table[str(dst_ip)])

					  res.hwsrc = mac
					  e = ethernet(type=packet.type, src=mac,
									dst=arp_request.hwsrc)
					  e.payload = res
					  msg = of.ofp_packet_out()
					  msg.data = e.pack()
					  msg.actions.append(of.ofp_action_output(port =
															  of.OFPP_IN_PORT))
					  msg.in_port = port_in
					  switch.send(msg)
					  

def _link_Failure (event):
	global l1_s4
	global l2_s4
	global l3_s4
	global l1_s5
	global l2_s5
	global l3_s5

	dpid = event.connection.dpid
	port_in = event.port
	#check if link got down (state == 1) 
	if event.modified:
		if event.ofp.desc.state == 1:
			if(dpid_to_str(dpid) == "00-00-00-00-00-04"):
				if port_in == 1:
					l1_s4 = True
				elif port_in == 2:
					l2_s4 = True
				elif port_in == 3:
					l3_s4 = True
			if(dpid_to_str(dpid) == "00-00-00-00-00-05"):
				if port_in == 1:
					l1_s5 = True
				elif port_in == 2:
					l2_s5 = True
				elif port_in == 3:
					l3_s5 = True
	
	#update the forwarding table so it can go another way	
	if(l1_s5 and l2_s5 and l3_s5):
		l1["00:00:00:00:00:04"] = 1 
		l1["00:00:00:00:00:06"] = 1 
		l2["00:00:00:00:00:02"] = 1 
		l2["00:00:00:00:00:06"] = 1 
		l3["00:00:00:00:00:02"] = 1 
		l3["00:00:00:00:00:04"] = 1 
		s4["00:00:00:00:00:02"] = 1 
		s4["00:00:00:00:00:04"] = 2
		s4["00:00:00:00:00:06"] = 3

	if(l1_s4 and l2_s4 and l3_s4):
		l1["00:00:00:00:00:03"] = 2
		l1["00:00:00:00:00:05"] = 2 
		l2["00:00:00:00:00:01"] = 2 
		l2["00:00:00:00:00:05"] = 2 
		l3["00:00:00:00:00:01"] = 2 
		l3["00:00:00:00:00:03"] = 2 
		s5["00:00:00:00:00:01"] = 1 
		s5["00:00:00:00:00:03"] = 2
		s5["00:00:00:00:00:05"] = 3


  
def launch ():
		core.openflow.addListenerByName("PacketIn", _handle_PacketIn)
		core.openflow.addListenerByName("PortStatus", _link_Failure)
		log.info("Pair-Learning switch running.")

