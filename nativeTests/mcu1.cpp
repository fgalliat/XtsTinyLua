#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* use omega UART1 */
const char *portname = "/dev/ttyS1";
int uartFd = -1; 


int set_interface_attribs (int fd, int speed, int parity);
void set_blocking (int fd, int should_block);
void uart_writestr(const char* string);
void uart_write(void* data, size_t len);
ssize_t uart_read(void* buffer, size_t charsToRead);
int uart_open(const char* port, int baud, int blocking);

// ===========================================

unsigned char rxBuff[1];

void flushRX() {
   uart_read( rxBuff, 1 ); // 0xFF ok -- 0xFE failed
}

unsigned char txBuff[32];
	

void lcd_cls() {
	// CLS	
	int len = 1; txBuff[0] = 0x22; 
	uart_write( txBuff, len );
	flushRX();
}

// not more than 30 chars
void _lcd_print30max(char* str) {
	int len = 1; txBuff[0] = 0x32; 
	uart_write( txBuff, len );
	uart_writestr( str );
	len = 1; txBuff[0] = 0x00; 
	uart_write( txBuff, len );
	flushRX();
}

void lcd_print(char* str) {
  _lcd_print30max(str);
}

void lcd_drawPCT(char* name, int x, int y) {

	int len = 1; txBuff[0] = 0x47; 
	uart_write( txBuff, len );
	
	len = 2; txBuff[0] = 0x00; txBuff[1] = 0x00;  // X
	uart_write( txBuff, len );

	len = 2; txBuff[0] = 0x00; txBuff[1] = 0x00;  // Y
	uart_write( txBuff, len );

	uart_writestr( "/CARO.PCT" ); // asset name
	
	len = 1; txBuff[0] = 0x00; 
	uart_write( txBuff, len );
	flushRX();
}



// ===========================================

int main(int argc, char* argv[] ) {

	if(!uart_open(portname, B115200, 0)) 
		return -1;

	printf("Start....\n");
	
if ( argc < 2 ) {
	lcd_cls();	
}
	
	// PRINT
if ( argc < 2 ) {
	lcd_print("Hello World from Omega\n");
} else if ( argc < 3 ) {
	lcd_print( argv[1] ); // argv[0] is PRGM name
	lcd_print("\n");
} else {
        lcd_drawPCT("/CARO.PCT", 0, 0);
}
	
	
	
	
	printf("Stop.....\n");
	
	return 0;
}

// ===========================================



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

