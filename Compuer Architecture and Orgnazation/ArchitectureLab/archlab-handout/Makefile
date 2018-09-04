####################################################
# Students' Makefile for the CS:APP Architecture Lab
####################################################

X500 = replace_this_with_your_x500_id
VERSION = 1

# Where are the different parts of the lab should be copied to when they
# are handed in.
HANDINDIR-PARTA = ../archlab-handout
HANDINDIR-PARTB = ../archlab-handout
HANDINDIR-PARTC = ../archlab-handout

sim:
	(cd sim; make)

# Use this rule to hand in Part A ("make handin-parta")
handin-parta:
	cp sim/misc/sum.ys $(HANDINDIR-PARTA)/$(X500)-sum.ys
	cp sim/misc/rsum.ys $(HANDINDIR-PARTA)/$(X500)-rsum.ys
	cp sim/misc/copy.ys $(HANDINDIR-PARTA)/$(X500)-copy.ys

# Use this rule to handin Part B ("make handin-partb")
handin-partb:
	cp sim/seq/seq-full.hcl $(HANDINDIR-PARTB)/$(X500)-seq-full.hcl

# Use this rule to handin Part C ("make handin-partc")
handin-partc:
	cp sim/pipe/ncopy.ys $(HANDINDIR-PARTC)/$(X500)-ncopy.ys
	cp sim/pipe/pipe-full.hcl $(HANDINDIR-PARTC)/$(X500)-pipe-full.hcl

clean:
	rm -f *~ *.o



