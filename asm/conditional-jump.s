.intel_syntax noprefix
.global _start
# if [x] is 0x7f454c46:
#   y = [x+4] + [x+8] + [x+12]
# else if [x] is 0x00005A4D:
#    y = [x+4] - [x+8] - [x+12]
# else:
#    y = [x+4] * [x+8] * [x+12]

_start:
    cmp dword ptr [edi], 0x7f454c46
    jne check_elseif               # si ≠ ELF, tester l'autre

    # if block (ELF magic)
    mov ebx, [edi+4]
    add ebx, [edi+8]
    add ebx, [edi+12]
    mov eax, ebx
    jmp done

check_elseif:
    cmp dword ptr [edi], 0x00005A4D
    jne do_else                   # si ≠ MZ, on fait else

    # elseif block (MZ magic)
    mov ecx, [edi+4]
    sub ecx, [edi+8]
    sub ecx, [edi+12]
    mov eax, ecx
    jmp done

do_else:
    # else block
    mov edx, [edi+4]
    imul edx, [edi+8]
    imul edx, [edi+12]
    mov eax, edx

done:
    nop    # ou hlt / ret selon contexte
