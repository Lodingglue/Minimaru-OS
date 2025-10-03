ENTRY(_start)

PHDRS
{
  text PT_LOAD FLAGS(5); /* Read + Exec */
  data PT_LOAD FLAGS(6); /* Read + Write */
}

SECTIONS
{
  . = 0x00100000; /* Kernel load address */

  .text : {
    *(.multiboot)
    *(.text*)
    *(.ctors)
    *(.init)
    *(.fini)
  } :text

  .rodata ALIGN(0x1000) : {
    *(.rodata*)
    PROVIDE(__rodata_start = .);
  } :text

  .data ALIGN(0x1000) : {
    PROVIDE(__data_start = .);
    *(.data*)
    *(.sdata*)
  } :data

  .bss (NOLOAD) : {
    PROVIDE(__bss_start = .);
    *(.bss*)
    *(COMMON)
    PROVIDE(__bss_end = .);
  } :data
}
