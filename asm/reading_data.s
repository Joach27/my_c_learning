.intel_syntax noprefix
.global _start
#Notons que nous avons utilisé une adresse mémoire générique (1337000)
_start:
    mov rax, 0
    mov rdi, 0
    mov rsi, 1337000
    mov rdx, 8
    syscall
    
    mov rax, 1
    mov rdi, 1
    mov rsi, 1337000
    mov rdx, 8
    syscall
    
    mov rax, 60
    mov rdi, 42
    syscall