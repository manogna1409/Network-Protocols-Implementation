# Network-Protocols-Implementation
Provides implementation of two network protocols named Stop and wait protocol and sliding window protocol using CRC(cyclic redundancy check) error detection algorithm

This project uses SOcket programming. 
It contains two file for each protocol:
Server side file: It contains connection part and sends message by adding crc bits to the message.
Client side file: It connects with the server and receives the message and uses crc algorithm for error detection.
				  If the message is corrupted, It sends acknowledgement that message should be sent again
				  If the message is not corrupted, It sends acknowledgement to send the next message
We use 64-message and 8-bit crc				  
				  
How to run the files, 
First run the Server side file which establishes a connection and waits for the reply, 
Then , run the client file.