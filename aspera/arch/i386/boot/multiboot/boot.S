.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
movl $stack_top, %esp
movl $stack_top, %ebp
pushl %ebx
pushl %eax
call boot_check
popl %eax
popl %ebx
call _init
call kernel_entry
cli
loop:
hlt
jmp loop
.size _start, . - _start
