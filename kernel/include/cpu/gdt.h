#ifndef _CPU_GDT_H
#define _CPU_GDT_H
#include <stdint.h>

struct gdt_ptr{
	uint16_t Limit;
	uint32_t Base; 
}__attribute__((packed));

struct gdt_entry{
	uint16_t Limit0;
	uint16_t Base0;
	uint8_t Base1;
	uint8_t AccessByte;
	uint8_t Flags;
	uint8_t Base2;
} __attribute__((packed));

struct GDT{
	struct gdt_entry null;
	struct gdt_entry kernel_code;
	struct gdt_entry kernel_data;
} __attribute__((packed)) __attribute__((aligned(0x1000)));

void init_gdt();

extern void gdt_load(uint64_t);

#endif