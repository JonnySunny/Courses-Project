Author: Zhongyi Sun
ID: 5320262
//
	For this socket programming assignment, I tested it with two website. 
The first one is facebook.com, the address for it is 157.240.2.35; the second one is www.google.com, the address for it is 216.58.216.228. When using these codes, must run DNSSeverV3.py first, then run DNSClientV3.py to make sure that works fine.
//
	In the server code, first of all is to make a socket and bind with its host and port number since we want to receive the request from client. And also we should notice that the maximum number of connections queued is 20. Then we decode and want to see the connection socket to check if it is valid (check this by is_valid_hostname() function) and if it exists in local file, if not valid, we return Invalid format to Client; if it doesn't exit, we should use gethostbyname() to get its address from Root DNS and it is written to file immediately (cached), then send related information to Client as encode format. But pay attention that before we check them, we should check if the local DNS file exits, if not we should make a new file called DNS_mapping first!  
	the server needs multiple 2 sockts since it wants to handle the more than one socket in the queue, so we want to them be setup differently and keep the program running without stopping
	When there are more than one clients send request informtaion to sever, the server is listening for the new client, after the new connections created, a new thread is created to handle this specific client's request. 

