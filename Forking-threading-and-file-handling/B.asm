section .bss
        text1 resb 8 

section .data
        text db "Present in B.asm file",10

section .text
        global B
        extern C

B:
        pop r10
        push C
        mov [text1], rdi

        mov rax, 1
        mov rdi, 1
        mov rsi, text
        mov rdx, 22
        syscall

        mov rax, 1
        mov rdi, 1
        mov rsi, text1
        mov rdx, 8
        syscall

        ret

