(a)
part1 and part2 are handled in _handle_PacketIn function, which listening to event "PacketIn". We first detect if the receiving packet is an arp request; if it is, then we mapping the the arp request's destnation IP addresss to its MAC address according to our arp table. After that, we create an arp response message containing destnation host's MAC address and send it back to request host. arp table's entries are determined beforehand.

If the receiving packet is not an arp request, we simply forward it according to the switch table at each switch. Switch tables' rules are determined beforehand since the topology and the link details are known beforehand.

part3 is handled in _link_Failure function, which listening to the event "PortStatus". In this function, we declared 6 global flag, and each time we detect a link is down, we check the incoming port number and set the flag of that link to true. After flags for all 3 links in one spine switch are set to true (which means all three links are down), we update all switch tables so the packet will follow another way to its destnation.

(b)
For link failure part, we only handled the situation that all 3 links in a spine switch are down, when there is only 1 or 2 links down, the program won't work.

Also, when you shut down more than 3 links at one time, the pinall command will show some "X".

mininet> link s4 l1 down
mininet> link s4 l2 down
mininet> link s4 l3 down
mininet> pingall
*** Ping: testing ping reachability
h1 -> h2 h3 h4 h5 h6 
h2 -> h1 h3 h4 h5 h6 
h3 -> h1 h2 h4 h5 h6 
h4 -> h1 h2 h3 h5 h6 
h5 -> h1 h2 h3 h4 h6 
h6 -> h1 h2 h3 h4 h5 
*** Results: 0% dropped (30/30 received)
mininet> link s5 l3 down
mininet> pingall
*** Ping: testing ping reachability
h1 -> h2 h3 h4 X X 
h2 -> h1 h3 h4 X X 
h3 -> h1 h2 h4 X X 
h4 -> h1 h2 h3 X X 
h5 -> X X X X h6 
h6 -> X X X X h5 
*** Results: 53% dropped (14/30 received)


(c)
Zhongyi Sun(sunx0725): Worked on part1.
Dawei Luo(luoxx417): Worked on part2.
Yuanzong Zhang(zhan3790): Worked on part3.
All team members worked together on debugging and documents.
