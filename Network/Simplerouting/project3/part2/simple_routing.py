from pox.core import core
import pox.openflow.libopenflow_01 as of


# Even a simple usage of the logger is much nicer than print!
log = core.getLogger()


#use this table to add the needed entries
table = {}

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

	# parse the packet, get src, dst, and port number
	packet = event.parsed
	src_mac = packet.src
	dst_mac = packet.dst
	switch = event.connection
	port_number = event.port


	# update the table, key is mac address, value is port number
	table[(event.connection, src_mac)] = port_number
	dst_port = table.get((event.connection, dst_mac))

	if dst_port != None:
		# set table entry for source
		msg = of.ofp_flow_mod()
		msg.match.dl_dst = src_mac
		msg.match.dl_src = dst_mac
		msg.actions.append(of.ofp_action_output(port = port_number))
		switch.send(msg)

		# set table entry for destination
		msg = of.ofp_flow_mod()
		# Forward the packet
		msg.data = event.ofp 
		msg.match.dl_src = src_mac
		msg.match.dl_dst = dst_mac
		msg.actions.append(of.ofp_action_output(port = dst_port))
		switch.send(msg)
    
	else:
		msg = of.ofp_packet_out()
		msg.data = event.ofp 
		msg.actions.append(of.ofp_action_output(port = of.OFPP_FLOOD )) 
		switch.send(msg)
		

def launch ():
	core.openflow.addListenerByName("PacketIn", _handle_PacketIn)
	log.info("Pair-Learning switch running.")
