# 🧠 Arithmétique des pointeurs en langage C
## 📝 Best online compilers : jdoodle c, online-cpp.com

## ✅ Principe fondamental

> En C, l’arithmétique des pointeurs est faite **en nombre d’éléments**, **pas en octets**.

---

## 🧱 Exemple mémoire (avec `int`)

```c
int data[4] = {1, 2, 3, 4};
int *p1 = &data[0]; // Adresse supposée : 0x1000
int *p2 = &data[1]; // Adresse supposée : 0x1004 (si int = 4 octets)
int diff = p2 - p1; // Résultat : 1 (élément), pas 4 (octets)

```
> On peut faire des opérations arithmétiques sur les pointeurs. comme la soustraction, addition.
> Quand on définit un array, le nom de l'arrauy est un pointeur vers le premier élément de l'array (store l'adresse du premier élément). 
> On peut alors faire : &array[i] = array + i, *array = array[0], array[i] = *(array + i).
