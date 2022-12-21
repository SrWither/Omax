#include <common.h>
#include <kernel/serial.h>

void serial_configure_baud_rate(unsigned short com, unsigned short divisor){
  outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
  outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void serial_configure_line(unsigned short com){
  outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_buffers(unsigned short com){
  outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com){
  outb(SERIAL_MODEM_COMMAND_PORT(com), 0x0B);
}

int serial_is_transmit_fifo_empty(unsigned int com){
  return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_initialize(unsigned int base){
  outb(base + 1, 0x00);
  serial_configure_baud_rate(base, 3);
  serial_configure_line(base);
  serial_configure_buffers(base);
  serial_configure_modem(base);
}

void serial_write(unsigned int com, char c){
  while(serial_is_transmit_fifo_empty(com) == 0);

  outb(com, c);
}

int serial_received(unsigned short com){
  return inb(SERIAL_LINE_STATUS_PORT(com)) & 1;
}

char read_serial(unsigned short com){
  while(serial_received(com) == 0);
  
  return inb(com);
}