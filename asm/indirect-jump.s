# Fichier: jump_table.asm
# Assemble avec: nasm -f elf32 jump_table.asm && ld -m elf_i386 -o jump_table jump_table.o

section .data
    jump_table dd case0, case1, case2     # table de pointeurs (adresses)
    val        dd 1                       # valeur testée (changer ici : 0, 1, 2, 3...)
    y          dd 0                       # résultat

section .text
    global _start

_start:
    mov eax, [val]        # charger val dans eax
    cmp eax, 2
    ja default_case       # si val > 2 → default

    # saut indirect via la jump table
    jmp dword [jump_table + eax*4]

case0:
    mov dword [y], 10
    jmp end

case1:
    mov dword [y], 20
    jmp end

case2:
    mov dword [y], 30
    jmp end

default_case:
    mov dword [y], 99

end:
    # fin du programme : on sort proprement
    mov eax, 1      # syscall: exit
    mov ebx, 0      # code de sortie
    int 0x80
