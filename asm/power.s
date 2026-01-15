.intel_syntax noprefix
.global power
power:
  mov rax, 1         # initialiser résultat à 1
  cmp rsi, 0         # si exposant == 0
  je done            # on retourne 1 directement

loop:
  imul rax, rdi      # rax = rax * rdi
  sub rsi, 1         # b--
  cmp rsi, 0
  jg loop            # tant que b > 0, continuer

done:
  ret
