# 🧠 Notes – Écriture en mémoire avec registres 64 bits (x86-64, Intel syntax)

## 🧱 1. Rappel sur les tailles

- Un registre 64 bits (`rax`, `rbx`, etc.) contient **8 octets**.
- Pour écrire une valeur de 64 bits en mémoire, il faut :
  - Charger la valeur dans un registre 64 bits.
  - Puis utiliser `mov [adresse], registre` pour écrire en mémoire.

---

## 🧠 2. Endianness

- x86 utilise le format **Little Endian**.
- Cela signifie que les **octets sont stockés en mémoire du moins significatif au plus significatif**.

> Exemple :  
> Valeur : `0xdeadbeef00001337`  
> En mémoire : `37 13 00 00 ef be ad de`

---

## 📦 3. Réserver de la mémoire avec un label

```asm
section .data
my_buffer: times 16 db 0   ; réserve 16 octets initialisés à 0
```

* `my_buffer` est un **label** qui représente l’adresse de début de cette zone mémoire.
* `times 16 db 0` crée 16 octets de valeur 0.

---

## 🗺️ 4. Écrire plusieurs blocs de 64 bits

Chaque bloc de 64 bits occupe 8 octets :

```asm
lea rdi, [rel my_buffer]

mov rax, 0x1111111111111111
mov [rdi], rax              ; 1er bloc (offset +0)

mov rbx, 0x2222222222222222
mov [rdi+8], rbx            ; 2e bloc (offset +8)

mov rcx, 0x3333333333333333
mov [rdi+16], rcx           ; 3e bloc (offset +16)
```

---

## 🛑 5. On ne peut PAS faire :

```asm
mov [rdi], 0xdeadbeef00001337   ; ❌ interdit !
```

* L’assembleur **n’autorise pas** de déplacer une valeur immédiate de 64 bits directement en mémoire.
* Il faut passer par un registre :

```asm
mov rax, 0xdeadbeef00001337
mov [rdi], rax                  ; ✅
```

---

## ✅ 6. Exemple complet

```asm
.intel_syntax noprefix
section .data
my_array: times 24 db 0

section .text
.global _start 
_start:
  lea rdi, [rel my_array]

  mov rax, 0x1111111111111111
  mov [rdi], rax

  mov rbx, 0x2222222222222222
  mov [rdi+8], rbx

  mov rcx, 0x3333333333333333
  mov [rdi+16], rcx

  mov rax, 60        ; syscall: exit
  xor rdi, rdi       ; status: 0
  syscall
```

---

## 🧠 Astuce pour retenir

* **8 octets = 64 bits**
* Pour écrire à la suite : ajouter `+8` à l'adresse de base
* Toujours utiliser un registre pour écrire une valeur en mémoire
* Endian ≠ ordre d'écriture humain

---

Parfait ! Voici une section additionnelle à coller **à la suite** de ton fichier `.md` pour compléter tes notes avec `lea`, `rel` et le syscall `exit`.

---




## 🧭 7. Comprendre `lea` et `rel`

### 🔹 `lea` — Load Effective Address


lea rdi, [rel my_buffer]

* `lea` charge une **adresse mémoire** dans un registre, sans accéder à la mémoire.
* C’est comme dire : “rdi ← adresse de `my_buffer`”.

### 🔹 `rel` — Adresse relative

* `rel` signifie **relative** (par rapport à la position du code).
* Il permet de rendre le programme **position-indépendant** (PIE-compatible).
* Cela évite d’utiliser des adresses absolues, ce qui est **plus sûr et plus portable**.

---

## 🚪 8. Quitter proprement un programme avec syscall `exit`

### 🔸 Syscall `exit` sous Linux (x86-64)

```asm
mov rax, 60      ; code syscall pour exit (n°60)
xor rdi, rdi     ; code retour (ici 0)
syscall
```

* `rax = 60` → numéro du syscall `exit`
* `rdi = 0`  → status/exit code (0 = succès)
* `syscall` → invoque le syscall

Tu peux aussi retourner une autre valeur :

```asm
mov rdi, 1    ; exit(1)
```

---

## 🔁 Résumé rapide : Registres de syscall (Linux, x86-64)

| Registre | Rôle              |
| -------- | ----------------- |
| `rax`    | Numéro du syscall |
| `rdi`    | 1er argument      |
| `rsi`    | 2e argument       |
| `rdx`    | 3e argument       |
| `r10`    | 4e argument       |
| `r8`     | 5e argument       |
| `r9`     | 6e argument       |

---

```

Souhaites-tu aussi une section sur **debugging avec GDB**, ou sur comment **visualiser la mémoire** après écriture ?
```
