#!/usr/bin/env python

from mininet.cli import CLI
from mininet.net import Mininet
from mininet.link import TCLink
from mininet.topo import Topo
from mininet.log import setLogLevel
#from pox import POX

class AssignmentNetworks(Topo):
    def __init__(self, **opts):
        Topo.__init__(self, **opts)
        lvl1_bw = 100
        lvl2_bw = 40
        lvl3_bw = 10

        lvl1_delay = '30ms'
        lvl2_delay = '20ms'
        lvl3_delay = '10ms'

        #Start to build the tree here.
        h1 = self.addHost('h1')
        h2 = self.addHost('h2')
        h3 = self.addHost('h3')
        h4 = self.addHost('h4')
        h5 = self.addHost('h5')
        h6 = self.addHost('h6')
        h7 = self.addHost('h7')
        h8 = self.addHost('h8')

        c1 = self.addSwitch('c1')

        a1 = self.addSwitch('a1')
        a2 = self.addSwitch('a2')

        e1 = self.addSwitch('e1')
        e2 = self.addSwitch('e2')
        e3 = self.addSwitch('e3')
        e4 = self.addSwitch('e4')

        self.addLink(e1, h1, bw=lvl3_bw, delay=lvl3_delay)
        self.addLink(e1, h2, bw=lvl3_bw, delay=lvl3_delay)
        self.addLink(e2, h3, bw=lvl3_bw, delay=lvl3_delay)
        self.addLink(e2, h4, bw=lvl3_bw, delay=lvl3_delay)
        self.addLink(e3, h5, bw=lvl3_bw, delay=lvl3_delay)
        self.addLink(e3, h6, bw=lvl3_bw, delay=lvl3_delay)
        self.addLink(e4, h7, bw=lvl3_bw, delay=lvl3_delay)
        self.addLink(e4, h8, bw=lvl3_bw, delay=lvl3_delay)

        self.addLink(a1, e1, bw=lvl2_bw, delay=lvl2_delay)
        self.addLink(a1, e2, bw=lvl2_bw, delay=lvl2_delay)
        self.addLink(a2, e3, bw=lvl2_bw, delay=lvl2_delay)
        self.addLink(a2, e4, bw=lvl2_bw, delay=lvl2_delay)

        self.addLink(c1, a1, bw=lvl1_bw, delay=lvl1_delay)
        self.addLink(c1, a2, bw=lvl1_bw, delay=lvl1_delay)


      

       
 
        
if __name__ == '__main__':
    setLogLevel( 'info' )

    topo = AssignmentNetworks()
    net = Mininet(topo=topo, link=TCLink, autoSetMacs=True,
           autoStaticArp=True)

    # Run network
    net.start()
    CLI( net )
    net.stop()

