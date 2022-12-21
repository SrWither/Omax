#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include <kernel/vga.h>
#include <kernel/tty.h>
#include <kernel/serial.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_back(int);

void terminal_moveCursor(void){
  unsigned temp;

  temp = terminal_row * VGA_WIDTH + terminal_column;

  outb(0x3D4, 14);
  outb(0x3D5, temp >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, temp);
}

size_t terminal_getRow(){
  return terminal_row;
}

size_t terminal_getColumn(){
  return terminal_column;
}

void terminal_initialize(void){
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ ){
		for ( size_t x = 0; x < VGA_WIDTH; x++ ){
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
  terminal_moveCursor();
}

void terminal_setcolor(uint8_t color){
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y){
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_clearScreen(){
  terminal_initialize();
}

void scroll(void){
  uint16_t blank, temp;

	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	blank = make_vgaentry('.', terminal_color);
  blank = blank;

  if(terminal_row >= 25){

    temp = terminal_row - 25 + 1;
    memcpy (VGA_MEMORY, VGA_MEMORY + temp * 80, (25 - temp) * 80 * 2);

	  for(int i = 0; i < 80; i++){
		  terminal_putentryat(' ', terminal_color, i, 24);
    }
	  terminal_row = 25 - 1;
   }
}

void terminal_newLine(){
  terminal_column = -1;
  terminal_row++;
}

void terminal_putchar(char c){
	if(c == '\n'){
	  terminal_newLine();
  }else{
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	}
	
	if(++terminal_column == VGA_WIDTH){
		terminal_column = 0;
    terminal_row++;
	}
	scroll();
  terminal_moveCursor();
  serial_write(SERIAL_COM1_BASE, c);
}

void terminal_write(const char* data, size_t size){
	for ( size_t i = 0; i < size; i++ )
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data){
	terminal_write(data, strlen(data));
}

void terminal_backspace(void){
  terminal_back(1);
  terminal_putchar(' ');
  terminal_back(1);
  terminal_moveCursor();
}

void terminal_back(int x){
  if((int)terminal_column - x < 0){
    terminal_row--;
    terminal_column = VGA_WIDTH - (x - terminal_column);
  }else{
    terminal_column -= x;
  }
}