this is the implementation of server ECU code.

Server ECU :
- receives data packet from dummy ECU via serial interface.
- validate these data,
- add the received time to the packet
- Send the packet to ECU-2 via Ethernet Socket communication.   

If ECU-1 terminates,
- It closes socket connections.
- It closes serial connections.

to run it correctly :
execute the .out file with passing the USB device file path which the Linux OS has create it
for example, if your USB read as a file in "/dev/ttyUSB0" you must execute it as

$ sudo ./worspace/Server_ECU/Debug/Server_ECU /dev/ttyUSB0
