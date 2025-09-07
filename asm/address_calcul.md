


# 🧠 Fiche Mémo : Registres en x86_64

## 1. Vue d'ensemble des registres généraux

| Registre     | Nom complet        | Utilisation typique                                |
|--------------|--------------------|-----------------------------------------------------|
| `rax`        | Accumulateur       | Résultat, retour de fonction, ID syscall            |
| `rbx`        | Base               | Sauvegarde de valeur, callee-saved                  |
| `rcx`        | Counter            | Compteur, boucle, 4e argument fonction C            |
| `rdx`        | Data               | Paramètre, E/S, 3e argument fonction C              |
| `rsi`        | Source Index       | 2e argument fonction C/syscall                      |
| `rdi`        | Destination Index  | 1er argument fonction C/syscall                     |
| `rsp`        | Stack Pointer      | Pointeur de pile (réservé)                          |
| `rbp`        | Base Pointer       | Cadre de pile (debug, stack frame)                 |
| `r8`         | Register 8         | 5e argument fonction C/syscall                      |
| `r9`         | Register 9         | 6e argument fonction C/syscall                      |
| `r10–r11`    | Temporaires        | Arguments syscall, scratch                          |
| `r12–r15`    | Sauvegardés        | Variables, callee-saved                             |

---

## 2. Appels Système Linux x86_64 (syscall)

| Argument           | Registre |
|--------------------|----------|
| Numéro du syscall  | `rax`    |
| 1er argument       | `rdi`    |
| 2e argument        | `rsi`    |
| 3e argument        | `rdx`    |
| 4e argument        | `r10`    |
| 5e argument        | `r8`     |
| 6e argument        | `r9`     |

---

## 3. Appels de fonctions C (convention ABI System V)

| Argument            | Registre |
|---------------------|----------|
| 1er argument        | `rdi`    |
| 2e argument         | `rsi`    |
| 3e argument         | `rdx`    |
| 4e argument         | `rcx`    |
| 5e argument         | `r8`     |
| 6e argument         | `r9`     |
| Retour de fonction  | `rax`    |

---

## 4. Remarques importantes

- Les registres peuvent contenir des entiers, des adresses mémoire ou des pointeurs.
- Certains registres sont *callee-saved* : une fonction appelée doit les restaurer si elle les modifie.
- `rsp` est réservé pour la pile. Ne jamais l’utiliser pour autre chose.
- `rax` est utilisé pour retourner une valeur de fonction ou le numéro d’un syscall.

---
# Résumé sur le calcul des adresses et accès

---


## 🧠 Calcul d'adresse mémoire en assembleur x86_64

## 📌 Pourquoi faire du calcul d'adresse ?

La mémoire est **linéaire**, c’est-à-dire qu’elle est vue comme un **grand tableau de bytes**.  
Pour accéder à un élément (dans un tableau, une structure, etc.), on doit **calculer l’adresse exacte** en fonction de sa position et de sa taille.

---

## 🧱 Forme générale du calcul d'adresse

Le processeur x86_64 permet de calculer une adresse mémoire sous cette forme :



\[base + index \* scale + offset]



| Élément   | Rôle                                             |
|-----------|--------------------------------------------------|
| `base`    | Registre contenant l’adresse de départ           |
| `index`   | Registre contenant un index (ex: position dans tableau) |
| `scale`   | Multiplicateur de taille (1, 2, 4 ou 8 uniquement) |
| `offset`  | Décalage constant (valeur immédiate)   


---

## 🧰 L’instruction `LEA` — Load Effective Address


lea destination, [base + index * scale + offset]
````

* Ne lit pas la mémoire ❌
* Ne copie pas de données ❌
* Fait uniquement un **calcul d’adresse** ✅

---

## ✅ Exemple simple : `lea rax, [arr + 2]`

```asm
lea rax, [arr + 2]  ; rax = adresse de arr + 2 octets
```

* `arr` = base
* `2` = offset
* Pas d’index ni de scale

---

## ✅ Exemple complet (base + index + scale + offset)

Accès au champ `y` du 2e élément d’un tableau de structures `Point {int x; int y;}` :

```asm
mov rdi, points     ; base = adresse du tableau
mov rsi, 1          ; index = 2e élément
lea rbx, [rdi + rsi*8 + 4]  ; adresse de points[1].y
mov eax, [rbx]            ; lecture de la valeur
```

* `scale = 8` car chaque structure `Point` fait 8 octets (2 x 4)
* `offset = 4` pour accéder au champ `y` (qui est après `x`)
* `eax` contiendra `points[1].y`

---

## 🧠 Pourquoi `scale` vaut 1, 2, 4 ou 8 ?

Parce que ce sont les tailles typiques des types de données :

* 1 → byte
* 2 → short
* 4 → int / float
* 8 → long / double / pointeur

---

## 🆚 `lea` vs `mov`

| Instruction        | Rôle                                 |
| ------------------ | ------------------------------------ |
| `mov eax, [rdi+4]` | Lit la valeur à l’adresse `rdi+4`    |
| `lea rax, [rdi+4]` | Calcule l’adresse `rdi+4`, sans lire |

---

## 🧠 À retenir

* La mémoire est **linéaire** → il faut **calculer l’adresse exacte**
* `lea` est utile pour : indexation, pointeurs, offset de champ, etc.
* Le format `[base + index*scale + offset]` est **très puissant**
* Il est utilisé aussi dans les accès mémoire : `mov`, `add`, etc.

---

## 💡 Exemples de cas typiques

| Cas                                 | Formule                                   |
| ----------------------------------- | ----------------------------------------- |
| Accès à un élément `arr[i]` (int)   | `[arr + i * 4]`                           |
| Accès à un champ dans une structure | `[base + i * struct_size + champ_offset]` |
| Adresse relative                    | `[rip + offset]`                          |

---




