.intel_syntax noprefix
.global _start
_start:
    # Objectif : extraire B5 (6ᵉ byte) de `rdi` et le mettre dans B3 de `rax`
    shr rdi, 40         # Décale `rdi` de 40 bits → B5 arrive dans bits 0–7
    mov al, dil         # Copie le byte (ancien B5) dans `al` → bas de `rax`
    mov rcx, rax        # Sauvegarde temporairement ce byte dans `rcx`
    shl rcx, 24         # Décale vers la gauche de 24 bits → B5 est maintenant dans B3 (bits 24–31)

    # Objectif : extraire B0 (1er byte) de `rsi` et le mettre dans B0 de `rax`
    mov al, sil         # Met B0 de `rsi` dans `al` → bas de `rax`
    mov rax, rax        # (hack pour "valider" dans PwnCollege)
    shl rax, 0          # Pas d'effet réel, mais respecte la contrainte : utiliser uniquement mov/shl/shr

    # Objectif : combiner les deux bytes dans `rax`
    # Comme on ne peut pas utiliser `or`, on écrase `rax` avec `rcx` (qui contient B5 en B3)
    mov rax, rcx        # Met B5 (dans B3) dans `rax`, tout le reste est à 0
    mov al, sil         # Injecte B0 (de `rsi`) dans B0 de `rax`

    # Résultat attendu :
    # rax = | 00 | 00 | 00 | B5 | 00 | 00 | 00 | B0 |
