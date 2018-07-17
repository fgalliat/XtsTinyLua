#ifndef _SERIAL_H_
#define _SERIAL_H_ 1

    int set_interface_attribs (int fd, int speed, int parity);
    void set_blocking (int fd, int should_block);
    void uart_writestr(const char* string);
    void uart_write(void* data, size_t len);
    ssize_t uart_read(void* buffer, size_t charsToRead);
    int uart_open(const char* port, int baud, int blocking);

  class Serial {
      public:
        Serial(const char *portname);
        ~Serial();

        void writestr(const char* string);
        void write(void* data, size_t len);
        ssize_t read(void* buffer, size_t charsToRead);
  };


#endif