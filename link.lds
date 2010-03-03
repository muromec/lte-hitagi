TARGET(elf32-bigarm)

MEMORY {
  SRAM (RWX) : ORIGIN = 0x12000000, LENGTH = 32m
}

ENTRY(start)

SECTIONS {

  .data : {
    *(.startup)
    *(.data)
  } > SRAM

  .bss : {
    *(.bss)
  } > SRAM
}
