.intel_syntax noprefix
.global factorial

factorial:
    cmp rdi, 1
    jle base_case
    
    push rbx        # Sauvegarder rbx sur la pile pour le restaurer apres car callee saved
    mov rbx, rdi    # Sauvegarder la valeur de rdi pour ne pas pas ecraser n qui est dans rdi
    
    sub rdi, 1      # rdi = rdi - 1
    call factorial  # rax = factorial(n - 1)
    
    mov rdi, rbx    # restauration de n dans rdi 
    pop rbx         # restauration du registre rbx 
    mul rdi         # rax = rax * rdi (n * (n - 1)!)
    
    ret
        
base_case:
    mov rax, 1
    ret
    