Okay, d'accord ! Le document décrit très bien les mécanismes internes d'un appel de fonction en C, en se concentrant sur la gestion de la pile (stack). Voici une explication détaillée basée sur les pages 17 à 19 (et les diagrammes associés, y compris celui de la page 25).

**Concepts Clés (Rappel de la Page 17)**

1.  **Stack Frame / Activation Record**:
    *   Lorsqu'une fonction est appelée, une nouvelle zone de mémoire est allouée sur la pile. Cette zone est appelée "stack frame" (cadre de pile) ou "activation record" (enregistrement d'activation).
    *   Ce cadre contient :
        *   Les paramètres passés à la fonction.
        *   L'adresse de retour (où retourner dans la fonction appelante après l'exécution de la fonction appelée).
        *   L'état sauvegardé de la fonction appelante (par exemple, l'ancienne valeur du pointeur de base de pile).
        *   Les variables locales de la fonction appelée.
    *   Ce cadre est détruit lorsque la fonction retourne, libérant ainsi la mémoire et rendant les variables locales inaccessibles. C'est ce qui contrôle la **portée (scope)** des variables locales.

2.  **Registres Importants (Page 18)**:
    *   **EBP (Base Pointer / Frame Pointer)** : Pointeur de base de pile. Il pointe vers un emplacement fixe *à l'intérieur* du cadre de pile de la fonction actuelle. Il sert de référence stable pour accéder aux paramètres et aux variables locales.
    *   **ESP (Stack Pointer)** : Pointeur de sommet de pile. Il pointe toujours vers le sommet actuel de la pile (la dernière donnée empilée). La pile grandit généralement vers les adresses mémoire inférieures.
    *   **EIP (Instruction Pointer)** : Pointeur d'instruction. Il contient l'adresse de la prochaine instruction CPU à exécuter.

**Étapes d'un Appel de Fonction (Pages 18-19 et diagramme p. 25)**

Prenons l'exemple de l'appel `z = add(10, 20);` où `add` est une fonction.

**Avant l'appel (dans la fonction appelante, ex: `main`)**

1.  **Étape 1: Empiler les Paramètres (Page 18)**
    *   Les paramètres de la fonction `add` (10 et 20) sont poussés sur la pile.
    *   En convention C (cdecl), les paramètres sont poussés de droite à gauche. Donc, `20` est poussé en premier, puis `10`.
    *   Le diagramme (page 18) montre `param #2 (20)` puis `param #1 (10)` sur la pile. `ESP` pointe maintenant vers `10`.

    ```
    ...
    | 20 (param #2) |  <-- ESP pointe ici après push 20
    | 10 (param #1) |  <-- ESP pointe ici après push 10 (sommet actuel)
    +---------------+
    ```

**L'instruction `CALL`**

2.  **Étape 2: Appeler la Fonction (Page 18, `CALL INSTR`)**
    *   L'instruction `CALL add` effectue deux actions principales :
        *   **Empiler l'adresse de retour**: L'adresse de l'instruction *immédiatement après* l'instruction `CALL` dans la fonction appelante (par exemple, l'adresse de `z++;` dans le diagramme, `0x200000108`) est poussée sur la pile. C'est là que l'exécution reprendra après le retour de `add`.
        *   **Sauter à la fonction**: Le contrôle est transféré à la première instruction de la fonction `add`. `EIP` est mis à jour pour pointer vers le début de `add`.
    *   `ESP` pointe maintenant vers l'adresse de retour (`OLD EIP`).

    ```
    ...
    | 20 (param #2)   |
    | 10 (param #1)   |
    | 0x200000108 (OLD EIP) | <-- ESP pointe ici (sommet actuel)
    +-----------------+
    ```

**Dans la fonction appelée (ex: `add`) - Le Prologue de la fonction**

3.  **Étape 3: Sauvegarder et Mettre à Jour EBP (Page 18, confirmé p. 19 et p. 25)**
    *   **Sauvegarder l'ancien EBP**: La première chose que la fonction `add` fait (généralement) est de sauvegarder la valeur actuelle de `EBP` (qui appartient au cadre de pile de `main`) en le poussant sur la pile.
        `push ebp`
    *   `ESP` pointe maintenant vers l'ancien EBP (`OLD EBP`).

        ```
        ...
        | 20 (param #2)       |
        | 10 (param #1)       |
        | 0x200000108 (OLD EIP) |
        | Valeur EBP de main (OLD EBP) | <-- ESP pointe ici
        +---------------------+
        ```
    *   **Établir le nouveau EBP**: `EBP` est ensuite mis à jour pour pointer vers le sommet actuel de la pile (`ESP`).
        `mov ebp, esp`
        `EBP` devient ainsi le pointeur de base du cadre de pile pour la fonction `add`. Il restera fixe pendant l'exécution de `add`, servant de référence.

    *   **Accès aux paramètres (Page 19)**:
        *   À partir de ce `EBP` (nouveau `EBP` de `add`), les paramètres sont accessibles à des offsets positifs :
            *   `OLD EBP` (EBP de main) est à `[EBP]` (ou `EBP+0` si `EBP` pointe directement dessus après le `mov`).
            *   L'adresse de retour (`OLD EIP`) est à `[EBP + 4]` (en supposant des adresses de 4 octets).
            *   Le premier paramètre (`10`) est à `[EBP + 8]`.
            *   Le deuxième paramètre (`20`) est à `[EBP + 12]`.
        *   C'est ce que signifient les notations comme `8(%ebp)` (pour le premier paramètre) dans l'assembleur.

    *   **Allouer de l'espace pour les variables locales (Page 19 et p. 25)**:
        *   De l'espace est réservé sur la pile pour les variables locales de la fonction `add` en décrémentant `ESP`. Par exemple, si `add` a une variable locale `int z_local;`, `ESP` serait diminué de 4 octets.
        *   Les variables locales sont accessibles à des offsets négatifs par rapport à `EBP`.
            *   `z_local` serait à `[EBP - 4]`.
        *   Le diagramme de la page 25 montre `Local var #1 (z)` à un offset négatif de `current EBP`.

    *   **(Optionnel) Sauvegarder les registres callee-saved**: Si la fonction `add` utilise des registres qui doivent être préservés pour l'appelant (registres "callee-saved" comme EBX, ESI, EDI selon certaines conventions), elle les empile ici. Le diagramme p.25 montre "Saved %reg".

**Exécution de la fonction `add`**

La fonction `add` exécute son code, utilisant `EBP` pour accéder à ses paramètres et variables locales.

**Fin de la fonction `add` - L'Épilogue de la fonction**

4.  **Étape 4: Retourner de l'Appel de Fonction (Page 25, implicite)**
    *   **(Optionnel) Restaurer les registres callee-saved**: Si des registres ont été sauvegardés, ils sont dépilés dans l'ordre inverse.
    *   **Libérer l'espace des variables locales**: `ESP` est ramené à la valeur de `EBP`.
        `mov esp, ebp`
        Ceci annule l'allocation des variables locales.
    *   **Restaurer l'ancien EBP**: L'ancien `EBP` (celui de `main`) qui avait été sauvegardé est dépilé et restauré dans le registre `EBP`.
        `pop ebp`
        `ESP` pointe maintenant vers l'adresse de retour (`OLD EIP`).
    *   **Retourner à l'appelant**: L'instruction `RET` est exécutée.
        *   Elle dépile l'adresse de retour de la pile et la charge dans `EIP`.
        *   L'exécution reprend dans la fonction `main` à l'instruction qui suivait `CALL add`.

**Retour dans la fonction appelante (`main`)**

*   **Nettoyage des paramètres (si nécessaire)**: Dans la convention d'appel cdecl (utilisée par défaut par de nombreux compilateurs C), c'est à la fonction *appelante* (`main`) de nettoyer les paramètres qu'elle avait poussés sur la pile. Cela se fait généralement en ajoutant à `ESP` la taille totale des paramètres (par exemple, `add esp, 8` pour deux entiers de 4 octets).

**En résumé, le cadre de pile pour `add` ressemblerait à ceci (la pile grandit vers le bas):**

```
        Adresse Mémoire
        Inférieure
        ^
        |
        +---------------------+
        | ... variables locales de add ... | <-- [EBP - offset_local_N]
        | variable locale 1 de add       | <-- [EBP - 4] (par ex.)
        +---------------------+
        | Valeur EBP de main (OLD EBP) | <-- EBP (pointeur de cadre de 'add') pointe ici après "mov ebp, esp"
        +---------------------+
        | Adresse Retour (OLD EIP)       | <-- [EBP + 4]
        +---------------------+
        | Paramètre 1 (10)               | <-- [EBP + 8]
        +---------------------+
        | Paramètre 2 (20)               | <-- [EBP + 12] (ESP pointait ici avant le CALL)
        +---------------------+
        | ... cadre de pile de main ...  |
        v
        Adresse Mémoire
        Supérieure
```

Ce mécanisme assure que chaque fonction a son propre espace de travail isolé, que les paramètres sont correctement transmis, et que l'exécution peut retourner proprement à l'appelant. Le pointeur `EBP` est crucial car il fournit un point de référence fixe pour accéder aux données du cadre de pile, même si `ESP` change (par exemple, pour allouer plus de variables locales ou faire des appels de fonction imbriqués).


Vous avez raison de souligner ce point, c'est une étape cruciale et il est important qu'elle soit claire. Reprenons l'étape 3 en détail, en clarifiant le rôle de `ESP` et `EBP`.

**Situation avant l'Étape 3 (juste après l'instruction `CALL`)**

1.  Les paramètres ont été poussés sur la pile par la fonction appelante (`main`).
2.  L'instruction `CALL add` a poussé l'adresse de retour (`OLD EIP`) sur la pile.
3.  `EIP` pointe maintenant vers la première instruction de la fonction `add`.
4.  `ESP` (Stack Pointer) pointe vers l'adresse de retour (`OLD EIP`) qui est actuellement au sommet de la pile.
5.  `EBP` (Base Pointer) pointe toujours vers le **bas du cadre de pile de la fonction appelante (`main`)**. Il n'a pas encore été modifié par la fonction `add`.

Voici l'état de la pile à ce moment précis :

```
        Adresse Mémoire Inférieure
        ^
        |
        +-----------------+
        | ... (espace vide) ... |
        +-----------------+ <-- ESP pointe ici (vers OLD EIP)
        | Adresse Retour (OLD EIP) |
        +-----------------+
        | Paramètre 1 (10)         |
        +-----------------+
        | Paramètre 2 (20)         |
        +-----------------+
        | ... cadre de pile de main ...  | <-- EBP (de main) pointe quelque part ici
        v
        Adresse Mémoire Supérieure
```

**Étape 3: Le Prologue de la fonction `add`**

Le "prologue" est une séquence standard d'instructions au début d'une fonction pour configurer son cadre de pile.

**3.a. Sauvegarder l'ancien `EBP` (celui de `main`)**

*   **Instruction : `push ebp`**
*   **Action :**
    1.  La valeur actuelle du registre `EBP` (qui est le pointeur de base du cadre de pile de `main`) est poussée sur la pile.
    2.  `ESP` est décrémenté (la pile grandit vers les adresses inférieures) pour pointer vers ce `EBP` sauvegardé.

    État de la pile *après* `push ebp` :

    ```
            Adresse Mémoire Inférieure
            ^
            |
            +---------------------+
            | ... (espace vide) ... |
            +---------------------+ <-- ESP pointe ici (vers OLD EBP)
            | EBP de main (OLD EBP) |
            +---------------------+
            | Adresse Retour (OLD EIP) |
            +---------------------+
            | Paramètre 1 (10)         |
            +---------------------+
            | Paramètre 2 (20)         |
            +---------------------+
            | ... cadre de pile de main ...  | <-- La valeur qui était dans EBP (de main) est maintenant sur la pile. Le registre EBP lui-même n'a pas encore changé.
            v
            Adresse Mémoire Supérieure
    ```
    À ce moment, vous avez raison, `ESP` pointe vers l'emplacement où l'ancien `EBP` (celui de `main`) vient d'être sauvegardé. Le *registre* `EBP` lui-même contient toujours le pointeur de base du cadre de `main`.

**3.b. Établir le nouveau `EBP` pour la fonction `add`**

*   **Instruction : `mov ebp, esp`**
*   **Action :**
    1.  La valeur actuelle du registre `ESP` (qui pointe vers le `OLD EBP` sauvegardé sur la pile) est copiée dans le registre `EBP`.
    2.  **C'est ici que le registre `EBP` change !** Il ne pointe plus vers le cadre de pile de `main`. Il pointe maintenant vers le sommet actuel de la pile, qui est l'emplacement où l'ancien `EBP` a été sauvegardé.
    3.  Ce nouveau `EBP` devient le **pointeur de base du cadre de pile pour la fonction `add`**. Il servira de point de référence stable pour accéder aux paramètres et aux futures variables locales de `add`.
    4.  `ESP` n'est pas modifié par cette instruction `mov`. `ESP` et `EBP` pointent donc *momentanément* au même endroit : le `OLD EBP` sauvegardé sur la pile.

    État de la pile *après* `mov ebp, esp` :

    ```
            Adresse Mémoire Inférieure
            ^
            |
            +---------------------+
            | ... (espace vide) ... |
            +---------------------+ <-- EBP (nouveau, pour 'add') pointe ici
                                      <-- ESP pointe aussi ici
            | EBP de main (OLD EBP) |
            +---------------------+
            | Adresse Retour (OLD EIP) |
            +---------------------+
            | Paramètre 1 (10)         |
            +---------------------+
            | Paramètre 2 (20)         |
            +---------------------+
            | ... cadre de pile de main ...  |
            v
            Adresse Mémoire Supérieure
    ```
    **Clarification importante :**
    *   Quand on dit "`ESP` pointe maintenant vers cet ancien `EBP`", on parle de l'emplacement *sur la pile* où la valeur de l'ancien `EBP` a été stockée.
    *   Quand on dit "`EBP` est ensuite mis à jour pour pointer vers le sommet (`ESP`)", on veut dire que le *registre* `EBP` est chargé avec l'adresse contenue dans le *registre* `ESP`. Puisque `ESP` pointait vers l'ancien `EBP` sauvegardé sur la pile, le registre `EBP` pointera désormais aussi vers cet emplacement.

**Pourquoi faire cela ?**

*   **Référence stable :** Une fois `EBP` établi pour la fonction `add`, il ne changera plus pendant l'exécution de `add` (jusqu'à l'épilogue). `ESP`, en revanche, changera si des variables locales sont allouées ou si `add` appelle d'autres fonctions.
*   **Accès facile :**
    *   L'ancien `EBP` sauvegardé est accessible à `[EBP]` (ou `[EBP+0]`).
    *   L'adresse de retour (`OLD EIP`) est accessible à `[EBP+4]` (en supposant des adresses de 4 octets).
    *   Le premier paramètre (poussé en dernier par l'appelant) est accessible à `[EBP+8]`.
    *   Le deuxième paramètre est accessible à `[EBP+12]`, et ainsi de suite.

**3.c. Allouer de l'espace pour les variables locales (Optionnel mais typique)**

*   **Instruction : `sub esp, N` (où N est la taille totale des variables locales)**
*   **Action :**
    1.  `ESP` est décrémenté de `N` octets pour faire de la place sur la pile pour les variables locales de la fonction `add`.
    2.  `EBP` reste inchangé (il pointe toujours vers l'emplacement de `OLD EBP` sauvegardé).
    3.  Les variables locales sont maintenant accessibles via des offsets négatifs par rapport à `EBP` (par exemple, `[EBP-4]`, `[EBP-8]`, etc.).

    État de la pile *après* `sub esp, 4` (pour une variable locale `int z_local;`) :

    ```
            Adresse Mémoire Inférieure
            ^
            |
            +---------------------+ <-- ESP pointe ici (sommet de la pile)
            | z_local (non initialisée) |   [EBP - 4]
            +---------------------+ <-- EBP (pour 'add') pointe ici
            | EBP de main (OLD EBP) |   [EBP]
            +---------------------+
            | Adresse Retour (OLD EIP) |   [EBP + 4]
            +---------------------+
            | Paramètre 1 (10)         |   [EBP + 8]
            +---------------------+
            | Paramètre 2 (20)         |   [EBP + 12]
            +---------------------+
            | ... cadre de pile de main ...  |
            v
            Adresse Mémoire Supérieure
    ```

J'espère que cette décomposition plus fine et la distinction entre le contenu du registre et l'emplacement sur la pile clarifient pourquoi et comment `EBP` est mis à jour pour pointer vers ce qui était le sommet de la pile (`ESP`) après la sauvegarde de l'ancien `EBP`. C'est le pivot de la création du nouveau cadre de pile.