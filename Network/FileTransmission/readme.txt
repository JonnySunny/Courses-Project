

-Zhongyi Sun
-Sunx0725
-5320262


About this program, first of all, you should run the networklayer, and then input some arguments to run the server, lastly input relatively arguments to run client. 
Here is a example:
python3 programbackup-3.py -ho localhost -spo 5001 -fi "" to run server 
python3 programbackup-3.py -ho localhost -spo 5002 -fi filename to run client with filename

parse argument by a function
-ho  means the hostname
-spo means the port number, first time as server portnumber, second time as client portnumber 
-fi  means the file name which you want to transfer from client to server 


In the client side, it transfered a file to the server side. Basically, it reads 487 bytes every time since the packet structure also occupied by other flags to make sure packet accurate. Then handle some exceptions such as pocket lost, time out, and so on. To deal with those situations, I check the check sum and compare the sequence in both sides, and it they doesn't match, they will be chosen to retransmit by client. After reading processe is over, send FIN message to Server, ready to close the client side. Specially, I simpilyied process of closing between Client and Server, once the client received the ACKFIN, it will send back ACKFIN to server. 

In the server side, it received the file and build a same file as client's one. Similarly, it write 487 bytes every time and I print them out to see what is written by server. To deal with those unexpectation situations,I check the check sum and compare the sequence in both sides, and it they doesn't match, they will be chosen to retransmit by client. After receive FIN packet, the server side will send back a ACKFIN and close the file (stopping writing). Last packet will be received and then check the last sign of it. if the last sign is 1, then shut down the server.  

I used the packet structure as same as suggested in the file: 20-byte check sum; 1-byte packet number; 3-byte size of data; 1-byte last sign; 487-byte real data. I learned a lot in this one. I understand more well how they connected by three-way hand shake than before. The longer delay on the rate of retransmission, probablity of packet lost, probability of packet mangle, all of them   wil disorder the sequence number of packet on both sides, I retransmited the relative packet when I encountered those unexpected situtation when doing this assignment. 
