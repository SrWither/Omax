#ifndef _CPU_IDT_H
#define _CPU_IDT_H

#include <stdint.h>

void idt_install(void);
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

#endif
