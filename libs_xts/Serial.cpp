#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "Serial.h"

/* use omega UART1 */
// const char *portname = "/dev/ttyS1";
char *portname = NULL;
int uartFd = -1; 


Serial::Serial(const char *_portname) {
  portname = (char*)_portname;
  if(!uart_open(portname, B115200, 0)) {
		//return -1;
        printf("FAILED TO OPEN 'Serial' !!! \n");
  }
}
Serial::~Serial() {

}

void Serial::writestr(const char* string) {
  uart_writestr(string);
}
void Serial::write(void* data, size_t len) {
  uart_write(data, len);
}
ssize_t Serial::read(void* buffer, size_t charsToRead) {
  return uart_read(buffer, charsToRead);
}


// ==============================================================================

int set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                fprintf (stderr, "error %d from tcgetattr", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                fprintf (stderr, "error %d from tcsetattr", errno);
                return -1;
        }
        return 0;
}

void set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                fprintf (stderr, "error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                fprintf (stderr, "error %d setting term attributes", errno);
}




void uart_writestr(const char* string) {
	write(uartFd, string, strlen(string));
}	

void uart_write(void* data, size_t len) {
	write(uartFd, data, len); 
}

ssize_t uart_read(void* buffer, size_t charsToRead) {
	return read(uartFd, buffer, charsToRead); 
}

int uart_open(const char* port, int baud, int blocking) {
	uartFd = open (port, O_RDWR | O_NOCTTY | O_SYNC);
	if (uartFd < 0)
	{
			fprintf (stderr, "error %d opening %s: %s", errno, port, strerror (errno));
			return -1;
	}
	set_interface_attribs (uartFd, baud, 0);  // set speed, 8n1 (no parity)
	set_blocking (uartFd, blocking); //set blocking mode
	printf("Port %s opened.\n", port); 
	return 1;
}

