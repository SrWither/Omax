#ifndef _KERNEL_SERIAL_H
#define _KERNEL_SERIAL_H

#include <stdint.h>
#include <stdlib.h>

#define SERIAL_COM1_BASE                0x3F8

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

#define SERIAL_LINE_ENABLE_DLAB         0x80

void serial_configure_baud_rate(unsigned short, unsigned short);
void serial_configure_line(unsigned short);
void serial_configure_buffers(unsigned short);
void serial_configure_modem(unsigned short);

int serial_is_transmit_fifo_empty(unsigned int);

void serial_initialize(unsigned int);
void serial_write(unsigned int, char);

int serial_received(unsigned short);

char read_serial(unsigned short);

#endif