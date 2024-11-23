ENTRY(main)
SECTIONS
{
    . = 0x100000; /* Higher image base address */

    .text : {
        *(.multiboot) /* Ensure the Multiboot header is included */
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }

    /DISCARD/ : {
        *(.comment)
    }
}