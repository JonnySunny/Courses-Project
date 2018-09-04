
##CSCI 1133
##Zhongyi Sun
## hw 10

import random
class Card():
    def __init__(self, value, suit):
        self.value = value
        self.suit = suit
    def getValue(self):
        return self.value
    def getSuit(self):
        return self.suit
    def __str__(self):
        return str(self.value)+" "+self.suit


class Carddeck():
    def __init__(self):
        self.list_deck = []
        self.list_input_number = [1,2,3,4,5,6,7,8,9,10,11,12,13]
        self.list_input = ["2","3","4","5","6","7","8","9","10","J","Q","K","A"]
        for i in range(4):  ## Make a deck
            for m in (self.list_input):
                if(i == 0):
                    self.list_deck.append(Card(m,"hearts"))
                if(i == 1):
                    self.list_deck.append(Card(m,"diamonds"))
                if(i == 2):
                    self.list_deck.append(Card(m,"clubs"))
                if(i == 3):
                    self.list_deck.append(Card(m,"spades"))
    def __repr__(self):
        self.ans = ""
        for i in range(len(self.list_deck)):
            if(i == len(self.list_deck)-1):
                self.ans+=str(self.list_deck[i])
            else:
                self.ans+=str(self.list_deck[i])+","
        return "["+self.ans+"]"
    def shuffle(self):
        random.shuffle(self.list_deck)
    def dealcards(self,n):
        dealcards = []
        random.shuffle(self.list_deck)
        if (n <= len(self.list_deck)):
            count = 0
            while count < n :
                card = self.list_deck[count]
                dealcards.append(card)
                count += 1
            del(self.list_deck[0:count])  ## delete after appending cards
            return dealcards
        if(n > len(self.list_deck)):
            repcard = [] ## record the last cards
            cardsNumber = n-len(self.list_deck)
            count = len(self.list_deck)
            while count > 0 :
                card = self.list_deck[len(self.list_deck)-count]
                repcard.append(card)
                dealcards.append(card)
                count -= 1
            del(self.list_deck[0:])## delete after appending cards
            if(len(self.list_deck)==0):
                new_deck = Carddeck()
                new_deck.shuffle()
                self.list_deck = new_deck.list_deck
            count = 0
            while count < cardsNumber:
                card = self.list_deck[count]
                if(card in repcard):## If there are some same cards show up
                    pass            ## do nothing
                else:               ## otherwise add new cards to original card list
                    dealcards.append(card)
                count += 1
            del(self.list_deck[0:count])## delete after appending cards
            return dealcards
class Pokerhand():
    def __init__(self):
        self.handlist = Carddeck().dealcards(5)
    def newHand(self,deck):
        self.handlist = []
        self.handlist = deck.dealcards(5)
    def __repr__(self):
        return str(self.handlist)
    def rank(self):
##        0 : High card
##        1 : One pair
##        2 : Two pair
##        3 : Three of a kind
##        4 : Straight
##        5 : Flush
##        6 : Full house
##        7 : Four of a kind
##        8 : Straight flush
        hand_dict_suit = {}
        hand_dict_value = {}
        change_value = ["[","A","J","Q","K",",","]"," "]
        for i in range(len(self.handlist)):
            if(self.handlist[i].suit in hand_dict_suit):
                hand_dict_suit[self.handlist[i].suit] += 1
            else:
                hand_dict_suit[self.handlist[i].suit] = 1
        for i in range(len(self.handlist)):
            if(self.handlist[i].value in hand_dict_value):
                hand_dict_value[self.handlist[i].value] += 1
            else:
                hand_dict_value[self.handlist[i].value] = 1    
        ## Divided four classes by different kinds of number
                
        if(len(hand_dict_value.keys()) == 2): ## return 6 , 7
            for i in list(hand_dict_value.values()):
                if(i == 3):
                    return 6
            return 7
        if(len(hand_dict_value.keys()) == 3):  ## three kinds of card ,  return 2, 3
            for i in list(hand_dict_value.values()):
                if(i == 3):
                    return 3
            return 2
        if(len(hand_dict_value.keys()) == 4): ## return 1
            return 1
        if(len(hand_dict_value.keys()) == 5): ## return 0 , 4 , 5 , 8
            a = list(hand_dict_value.keys())
            i = 0
            while i < len(a):
                if(a[i] == "A"):
                     a[i] = "1"
                if(a[i] == "J"):
                     a[i] = "11"
                if(a[i] == "Q"):
                     a[i] = "12"
                if(a[i] == "K"):
                     a[i] = "13"
                i+=1
            a.sort()
            if(len(hand_dict_suit.keys())==1):  ## only one suit "Flush" class
                if(int(a[4])-int(a[0])== 4):
                     return 8
                else:
                     return 5
            else:  ## more than one suits
                if(int(a[4])-int(a[0])== 4):
                     return 4
                return 0

def main():
##        0 : High card
##        1 : One pair
##        2 : Two pair
##        3 : Three of a kind
##        4 : Straight
##        5 : Flush
##        6 : Full house
##        7 : Four of a kind
##        8 : Straight flush
    poker = Pokerhand()
    carddeck = Carddeck()
    carddeck.shuffle()
    names = ["Straight Flush : ","Four of a kind : ","Full house   : ","Flush    : ","Straight    : ","Three of a kind : ","Two pair    :","One pair    :","High card    :"]
    i = 0
    a = {}
    while i < 100000:
        poker.newHand(carddeck)
        if(poker.rank() in a ):
            a[poker.rank()]+=1
        else:
            a[poker.rank()] = 1
        i+=1
    print("Straight Flush  : "+str(a[8]))
    print("Four of a kind  : "+str(a[7]))
    print("Full house      : "+str(a[6]))
    print("Flush           : "+str(a[5]))
    print("Straight        : "+str(a[4]))
    print("Three of a kind : "+str(a[3]))
    print("Two pair        : "+str(a[2]))
    print("One pair        : "+str(a[1]))
    print("High card       : "+str(a[0]))

    
    
