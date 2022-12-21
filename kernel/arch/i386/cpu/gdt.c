#include <cpu/gdt.h>
#include <stdint.h>
#include <stdio.h>

struct gdt_ptr GDTStruct;

__attribute__((aligned(0x1000))) struct GDT defaultGDT = {
	{0, 0, 0, 0x00, 0x00, 0},
	{0, 0, 0, 0x9a, 0xcf, 0},
	{0, 0, 0, 0x92, 0xcf, 0},
};

void init_gdt(){
	GDTStruct.Limit = (sizeof(struct GDT)) - 1;
	GDTStruct.Base = (uint32_t) &defaultGDT;
	gdt_load(&GDTStruct);
	printf(" Finished initializing the GDT. ");
}