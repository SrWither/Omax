#include <common.h>
#include <cpu/isr.h>
#include <stdio.h>
#include <kernel/tty.h>

void isr_handler(registers_t regs)
{
   printf("recieved interrupt: ");
   printf("%d", regs.int_no);
   terminal_putchar('\n');
}