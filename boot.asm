bits 32

section .multiboot
    dd 0x1BADB002
    dd 0x0

section .text
global start
extern main

start:
    cli
    mov esp, stack_space
    call main
    hlt

section .bss
resb 16000
stack_space: