#include <stdio.h>
#include <kernel/tty.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>

void kernel_main(void) {
  // Init gdt and idt
  init_gdt();
  idt_install();
  
  // Init term
  terminal_initialize();
  printf("Kernel: Omax\nFilesystem: NULL\nLibc: Minimal\nLibc++: NULL");
}
