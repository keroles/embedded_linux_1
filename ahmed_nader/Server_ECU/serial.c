
#include "serial.h"

int serial_fd;/*File Descriptor*/

void serial_init(const char * serial_path) {

	/*------------------------------- Opening the Serial Port -------------------------------*/

	/* Change /dev/ttyUSB0 to the one corresponding to your system */
	serial_fd = open(serial_path, O_RDWR | O_NOCTTY); /* ttyS0 is the FT232 based USB2SERIAL Converter   */
	/* O_RDWR   - Read/Write access to serial port       */
	/* O_NOCTTY - No terminal will control the process   */
	/* Open in blocking mode,read will wait              */


	if(serial_fd == -1) /* Error Checking */
	{
		printf("Error! in Opening serial_fd \n");
		exit(0);
	}
	else
	printf("serial_fd Opened Successfully\n");

	/*---------- Setting the Attributes of the serial port using termios structure --------- */

	struct termios SerialPortSettings; /* Create the structure                          */

	tcgetattr(serial_fd, &SerialPortSettings); /* Get the current attributes of the Serial port */

	/* Setting the Baud rate */
	cfsetispeed(&SerialPortSettings, B115200); /* Set Read  Speed as 115200                       */
	cfsetospeed(&SerialPortSettings, B115200); /* Set Write Speed as 115200                     */

	/* 8N1 Mode */
	SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */
	SerialPortSettings.c_cflag &= ~PARENB; /* Disables the Parity Enable bit(PARENB),So No Parity   */
	SerialPortSettings.c_cflag &= ~CSTOPB; /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
	SerialPortSettings.c_cflag &= ~CSIZE; /* Clears the mask for setting the data size             */
	SerialPortSettings.c_cflag |= CS8; /* Set the data bits = 8                                 */

	SerialPortSettings.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);

	SerialPortSettings.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK
			| INPCK | ISTRIP | IXON); /* Disable XON/XOFF flow control both i/p and o/p */

	SerialPortSettings.c_oflag &= ~(OCRNL | ONLCR | ONLRET | ONOCR | OFILL
			| OPOST);/*No Output Processing*/

	/* Setting Time outs */
#ifndef BLOCKING_SERIAL
	SerialPortSettings.c_cc[VMIN] = 255;  /* non-blocking mode */
	SerialPortSettings.c_cc[VTIME] = 1; /* Wait 0.5 seconds   */

#elif  BLOCKING_SERIAL
	SerialPortSettings.c_cc[VMIN] = 0;
	SerialPortSettings.c_cc[VTIME] = 5;
#endif // BLOCKING_SERIAL


	tcsetattr(serial_fd, TCSANOW, &SerialPortSettings);


	if((tcsetattr(serial_fd,TCSANOW,&SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
	{
		printf("\n  ERROR ! in serial_fd Setting attributes\n");
		exit(0);
	}



	/*------------------------------- Read data from serial port -----------------------------*/
	fcntl(serial_fd, F_SETFL, 0);
	tcflush(serial_fd, TCIOFLUSH); /* Discards old data in the tx/rx buffer */
}
