this is the implementation of Client ECU code.

Client ECU:
- is used to receive packets from ECU-1 via Ethernet Socket communication.   
- Add the received time to the packet.
- Dump the received packet into file in ECU-2’s system files.

If ECU-2 terminates,
It closes socket connection.
It creates a child process to show the dumped file to the user.

to run it correctly :
execute the .out file with passing the IP address for server.
for example

$ sudo ./worspace/Client_ECU/Debug/Client_ECU 127.0.0.1  ==> for running server and Client in the same PC 
$ sudo ./worspace/Client_ECU/Debug/Client_ECU <server-IP>  ==> for running server and Client in different PCs 

note: PORT number for establishing Ethernet socket connection is 5454
