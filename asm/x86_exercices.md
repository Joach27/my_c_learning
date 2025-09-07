# Exercices x86

C'est génial que tu sois sur le **module Assembly Crash Course** et que tu sois presque à la fin ! Ça montre que tu as bien acquis les bases d'**assembly x86\_64** et des concepts clés comme la **stack**, les **registres**, et les **instructions fondamentales**.

Maintenant, pour solidifier tout ce que tu as appris, voici quelques exercices pratiques que tu peux essayer. Ils sont conçus pour te pousser à manipuler directement les concepts que tu as étudiés tout en approfondissant des aspects plus techniques.

---

### 🧩 **Exercice 1 : Implémentation d'une fonction `strcmp` en assembly**

**Objectif :** Écrire une fonction `strcmp` en assembly qui compare deux chaînes de caractères (sans utiliser de fonctions externes). La fonction renvoie 0 si les chaînes sont égales, une valeur négative si la première chaîne est lexicographiquement plus petite, et une valeur positive si la première chaîne est plus grande.

**Indications :**

* Utilise les registres pour parcourir les chaînes de caractères.
* Compare chaque caractère à l'aide de `cmp` et d’un saut conditionnel (`je`, `jl`, `jg`).
* N'oublie pas de gérer les cases où une des chaînes est plus courte que l'autre.

**Bonus :** Tester ta fonction avec différents jeux de chaînes, notamment celles de taille différente et contenant des caractères spéciaux.

---

### 🧩 **Exercice 2 : Implémentation de la fonction `strrev` (reverse une chaîne de caractères)**

**Objectif :** Écrire une fonction qui inverse une chaîne de caractères donnée.

**Indications :**

* Utilise deux pointeurs : un au début de la chaîne et un à la fin. Échange les caractères de ces pointeurs jusqu'à ce qu'ils se rencontrent.
* La chaîne d'entrée peut être modifiée en place.
* Utilise des registres pour manipuler la mémoire directement (en modifiant les caractères dans la chaîne).

**Bonus :** Si tu veux, essaie de le faire sans utiliser de variables temporaires, uniquement avec des échanges directs dans la mémoire.

---

### 🧩 **Exercice 3 : Implémentation d’un compteur de bits (popcount)**

**Objectif :** Écrire une fonction qui compte le nombre de bits à `1` dans un nombre donné. Cette opération s'appelle souvent **popcount**.

**Indications :**

* Utilise l'instruction `test` et `shr` (shift right) pour tester chaque bit de droite à gauche.
* Incrémente un compteur chaque fois que tu rencontres un `1`.
* Teste la fonction avec plusieurs entiers, y compris des entiers négatifs.

**Bonus :** Implémenter un **popcount parallèle** (techniques d’optimisation, si tu veux explorer la gestion des bits plus avancée).

---

### 🧩 **Exercice 4 : Gestion de la mémoire avec `malloc` et `free` en assembly**

**Objectif :** Écrire une fonction qui alloue de la mémoire avec `malloc` et la libère avec `free`.

**Indications :**

* Utilise les appels système `brk` ou `mmap` pour allouer de la mémoire manuellement (sans utiliser la libc).
* Fais attention aux alignements et à la gestion de la mémoire.
* Implémente une petite gestion des tailles de blocs de mémoire alloués, comme une forme simple de **heap management**.

**Bonus :** Implémenter un système de **libération de mémoire** pour simuler un comportement proche de `free()`.

---

### 🧩 **Exercice 5 : Débogage d'un crash en utilisant GDB**

**Objectif :** Lancer un programme en assembleur avec GDB, puis provoquer un crash (par exemple, via un **buffer overflow**). Ensuite, utilise GDB pour examiner la **stack** et identifier où le programme a échoué.

**Indications :**

* Écris un programme en assembleur qui prend une entrée utilisateur et copie cette entrée dans un buffer sans vérification de taille (pour créer un buffer overflow).
* Lance le programme dans GDB et active le **backtrace** (`bt`) pour inspecter les registres et la stack après le crash.
* Identifie le lieu précis du crash et la cause du débordement de mémoire.

**Bonus :** Utiliser des techniques comme le **NOP sled** pour pratiquer le concept de **shellcode**.

---

### 🧩 **Exercice 6 : Tracer une fonction récursive**

**Objectif :** Implémenter une fonction récursive (comme le calcul du **factoriel** ou de la **suite de Fibonacci**) en **assembleur**.

**Indications :**

* Prends l'exemple de `factorial(n)` ou `fibonacci(n)`.
* Gère les **paramètres** via la stack et les **retours de fonction** avec `ret`.
* Mets bien en évidence comment la stack est utilisée pour gérer les appels imbriqués.

**Bonus :** Observe comment la stack est modifiée à chaque appel récursif (en inspectant les valeurs de `rsp` et des **frames de pile**).

---

### 🧩 **Exercice 7 : Gestion des exceptions et des erreurs**

**Objectif :** Implémenter un mécanisme de gestion des erreurs en utilisant des **exceptions** basées sur la stack. Cela peut inclure des erreurs comme "division par zéro", "déréférencement d'un pointeur nul", etc.

**Indications :**

* Utilise des sauts conditionnels pour détecter des erreurs spécifiques.
* Sauvegarde l'état de la pile avant de sauter à une routine de gestion des erreurs.
* Imprime un message d’erreur et quitte proprement.

**Bonus :** Essaie d'utiliser des **return codes** et des appels à des fonctions de gestion des erreurs (en utilisant des mécanismes comme la **stack unwinding**).

---

### 🔑 Bonus général pour t’entraîner à l'assembly :

* **Créer des scripts pour analyser la mémoire :** Avec des outils comme **GDB**, fais des scripts pour analyser les buffers, les registres et la stack. Cela te donnera une idée de la gestion de la mémoire dans un programme.
* **Explorer les appels système** : Fais une série d'exercices où tu utilises les appels système directement (comme `write`, `exit`, `mmap`, `brk`, etc.) pour manipuler la mémoire et les entrées/sorties.

---

### 💭 Pourquoi ces exercices sont utiles :

Ces exercices combinent l’utilisation de la **stack**, des **registres**, et des **techniques de gestion de mémoire** avancées, tout en mettant en pratique des concepts essentiels de l’**architecture x86\_64**. En les pratiquant, tu vas renforcer ta compréhension des **vulnérabilités** (comme les débordements de mémoire, les erreurs de gestion des pointeurs, etc.), qui sont des compétences cruciales dans des domaines comme la **sécurité** et le **reverse engineering**.
