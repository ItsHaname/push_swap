*This project has been created as part of the 42 curriculum by haait-ba, sael-mgh.*

# push_swap

> *Because Swap_push doesn't feel as natural.*

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![42](https://img.shields.io/badge/42-push__swap-000000?style=for-the-badge&logo=42&logoColor=white)
![Norminette](https://img.shields.io/badge/Norminette-OK-00BABC?style=for-the-badge)
![Équipe](https://img.shields.io/badge/Équipe-2%20personnes-00BABC?style=for-the-badge)

---

## 📖 Description

**push_swap** est un projet d'algorithmique du cursus 42, réalisé en binôme.

On dispose de deux piles, `a` et `b`. Au départ, `a` contient une liste d'entiers
(positifs et/ou négatifs, sans doublon) et `b` est vide. Le programme doit afficher sur
la sortie standard **la plus petite suite d'opérations possible** qui trie `a` par ordre
croissant (le plus petit en haut), en n'utilisant que les opérations suivantes :

| Opération | Effet |
|:---:|---|
| `sa` / `sb` / `ss` | Échange les 2 premiers éléments de `a` / `b` / les deux |
| `pa` / `pb` | Prend le sommet de `b` et le met sur `a` / l'inverse |
| `ra` / `rb` / `rr` | Rotation vers le haut (le premier devient le dernier) |
| `rra` / `rrb` / `rrr` | Rotation vers le bas (le dernier devient le premier) |

Le binaire embarque **quatre stratégies** de tri, choisies à l'exécution :

| Flag | Stratégie | Complexité (en nombre d'opérations) |
|---|---|:---:|
| `--simple` | Tri simple (extraction du min / sélection) | O(n²) |
| `--medium` | Tri par chunks « butterfly » (fenêtre ≈ 1,5·√n) | O(n√n) |
| `--complex` | Quicksort à deux pivots sur les deux piles | O(n log n) |
| `--adaptive` *(défaut)* | Choix selon le **désordre** mesuré | dépend du régime |

### Objectifs de performance

| Taille | Minimum | Bon | Excellent |
|:---:|:---:|:---:|:---:|
| 100 nombres | < 2000 | < 1500 | < 700 |
| 500 nombres | < 12000 | < 8000 | < 5500 |

---

## 👥 Répartition des tâches

Le sujet exige que **les deux membres contribuent réellement et comprennent
l'intégralité du code**. Chacune est responsable de sa partie, mais tout le code est
relu et expliqué à l'autre avant d'être fusionné (pull request + relecture croisée).

La charge est **équilibrée** : chacune a une partie « fondations » et **deux vrais
algorithmes** de tri. Les deux peuvent commencer en même temps — Sanae travaille
d'abord sur un simple tableau d'entiers pendant que Hanane construit les piles.

### 🟦 Hanane — `haait-ba`

**Fondations : piles, opérations, parsing — algorithmes simple et medium**

- [ ] `Makefile` (règles `$(NAME)`, `all`, `clean`, `fclean`, `re`, `bonus`, sans relink) et intégration de la `libft`
- [ ] Structure de données des piles (liste chaînée ou tableau circulaire) + libération mémoire
- [ ] Les 11 opérations (`sa` … `rrr`) avec affichage et compteur pour le bench
- [ ] Parsing des arguments : nombres séparés ou dans une même chaîne (`"3 2 1"`)
- [ ] Gestion d'erreurs → `Error\n` sur stderr : non-entiers, dépassement `INT_MIN`/`INT_MAX`, doublons, argument vide
- [ ] **Stratégie simple — O(n²)** (`--simple`)
- [ ] **Stratégie medium — O(n√n)** (`--medium`) : tri par chunks
- [ ] Mode `--bench` (sur stderr) : désordre en %, stratégie + complexité, total et détail des opérations

### 🟪 Sanae — `sael-mgh`

**Fondations : analyse de l'entrée — algorithmes complex et adaptive**

- [ ] Lecture des flags (`--simple`, `--medium`, `--complex`, `--adaptive`, `--bench`)
- [ ] Indexation des valeurs (remplacer chaque nombre par son rang `0..n-1`)
- [ ] Calcul du **désordre** (`compute_disorder`) avant toute opération
- [ ] Tris spéciaux pour les petites tailles (2, 3 et 5 éléments)
- [ ] **Stratégie complexe — O(n log n)** (`--complex`) : quicksort à deux pivots
- [ ] **Stratégie adaptative** (`--adaptive`, défaut) : sélection selon le désordre

### 🤝 Ensemble

- [ ] **Bonus** : programme `checker` (lecture de stdin, `OK` / `KO` / `Error`) — réutilise le parsing et les opérations
- [ ] Optimisations pour atteindre les objectifs de performance (fusion `ra`+`rb` → `rr`, suppression des paires inutiles, etc.)
- [ ] Choix des seuils de l'algorithme adaptatif et leur justification
- [ ] Scripts de test : erreurs, cas limites, 100 / 500 nombres aléatoires, `checker_linux`
- [ ] Vérification `norminette` et fuites mémoire (`valgrind`)
- [ ] Rédaction de ce README (algorithmes, justifications, ressources)
- [ ] Préparation de la soutenance : chacune doit savoir expliquer **tout** le code

### Organisation Git

- `main` : version stable, toujours compilable
- Une branche par tâche : `hanane/parsing`, `sanae/radix`, …
- Fusion dans `main` uniquement via pull request relue par l'autre

---

## 🗂️ Structure du projet

> Structure prévue — elle évoluera au fil du projet (la Norme impose au plus
> 5 fonctions par fichier et 25 lignes par fonction).

```
push_swap/
├── Makefile                  ← compile libft puis push_swap / checker      (Hanane)
├── README.md
├── includes/
│   └── push_swap.h           ← structures et prototypes                    (ensemble)
├── libft/                    ← notre libft (sources + Makefile)
├── srcs/
│   ├── 00_main.c             ← enchaîne parsing, tri et bench              (Sanae)
│   ├── 01_stack.c            ← créer / ajouter / libérer la pile           (Hanane)
│   ├── 02_parsing.c          ← argv → nombres                              (Hanane)
│   ├── 03_parsing_utils.c    ← atoi avec dépassement, doublons             (Hanane)
│   ├── 04_ops_swap.c         ← sa  sb  ss                                  (Hanane)
│   ├── 05_ops_push.c         ← pa  pb                                      (Hanane)
│   ├── 06_ops_rotate.c       ← ra  rb  rr                                  (Hanane)
│   ├── 07_ops_rev_rotate.c   ← rra rrb rrr                                 (Hanane)
│   ├── 08_index.c            ← indexation des valeurs                      (Sanae)
│   ├── 09_disorder.c         ← calcul du désordre, pile déjà triée ?       (Sanae)
│   ├── 10_sort_utils.c       ← min / max, amener un élément en haut        (ensemble)
│   ├── 11_sort_small.c       ← tris pour 2, 3 et 5 éléments                (Sanae)
│   ├── 12_sort_simple.c      ← --simple    O(n²)                           (Hanane)
│   ├── 13_sort_medium.c      ← --medium    O(n√n)                          (Hanane)
│   ├── 14_sort_complex.c     ← --complex   O(n log n)                      (Sanae)
│   ├── 14_complex_utils.c    ← helpers du quicksort (pivots, petits cas)   (ensemble)
│   ├── 15_flags.c            ← lecture des flags (--simple, --bench…)      (Sanae)
│   ├── 16_sort_adaptive.c    ← --adaptive                                  (Sanae)
│   └── 17_bench.c            ← --bench                                     (Hanane)
└── bonus/
    ├── checker_bonus.c       ← programme checker                           (ensemble)
    └── checker_utils_bonus.c
```

---

## ⚙️ Instructions

### Compilation

```bash
make          # compile push_swap
make bonus    # compile checker
make clean    # supprime les fichiers objets
make fclean   # supprime objets + binaires
make re       # recompile tout
```

### Utilisation

```bash
./push_swap 2 1 3 6 5 8                     # stratégie adaptative par défaut
./push_swap --simple 5 4 3 2 1              # force O(n²)
./push_swap --medium 4 67 3 87 23           # force O(n√n)
./push_swap --complex 4 67 3 87 23          # force O(n log n)

ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l          # nombre d'opérations
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_linux $ARG   # vérification

./push_swap --bench $ARG 2> bench.txt > /dev/null     # métriques seulement
```

### Erreurs

```bash
$> ./push_swap 0 one 2 3
Error
$> ./push_swap 3 2 3
Error
```

---

## 🧠 Algorithmes

> ⚠️ Section à compléter au fur et à mesure de l'implémentation.
> Toutes les complexités sont exprimées en **nombre d'opérations push_swap générées**.

### Mesure du désordre

Proportion de paires `(i, j)` avec `i < j` et `a[i] > a[j]` parmi toutes les paires :
`0` = déjà trié, `1` = trié à l'envers. Calculé avant toute opération.

### 1. Simple — O(n²)

*À compléter : principe (ex. extraction répétée du minimum vers `b` puis `pa`),
pourquoi chaque extraction coûte au plus O(n) rotations → O(n²) au total.*

### 2. Medium — O(n√n)

**Envoi vers `b` (« butterfly ») :** un compteur `i` démarre à 0 et une fenêtre
de largeur `r ≈ 1,5·√n` (15 pour 100 nombres, 33 pour 500). Pour le sommet `v` de `a` :
- `v ≤ i` → `pb` puis `rb` (les petits vont en bas de `b`), `i++` ;
- `v ≤ i + r` → `pb` (reste en haut de `b`), `i++` ;
- sinon → `ra`.

`b` se retrouve presque trié, les plus grands près du sommet.

**Retour vers `a` :** `b` contient exactement les index `0 … b.size−1`. On compare
le coût pour amener le maximum et le 2ᵉ maximum au sommet ; si le 2ᵉ est moins
cher, on l'envoie d'abord, puis le maximum, puis `sa`.

**Borne :** un élément est rotaté tant qu'il est hors de la fenêtre, soit au plus
O(n / r) tours de `a` de O(n) chacun → O(n²/r) = O(n√n). Au retour, chaque élément
est à O(r) positions de sa place dans `b` → O(n·r) = O(n√n). Mémoire : O(n).

### 3. Complex — O(n log n)

Quicksort récursif « à trois tiers » sur des plages d'index contiguës
`[lo, lo+len)` (`srcs/14_sort_complex.c`, helpers dans `srcs/14_complex_utils.c`).
Deux pivots `p1 = lo + len/3` et `p2 = lo + 2·len/3` :

- **`sort_a`** (plage au sommet de `a`) : grands (`≥ p2`) → `ra`, moyens → `pb` + `rb`,
  petits → `pb`. Puis on annule les rotations (`rrr` quand les deux piles en ont
  besoin), on trie les grands dans `a`, puis on renvoie les moyens et les petits.
- **`sort_b`** (plage au sommet de `b`) : grands → `pa`, moyens → `pa` + `ra`,
  petits → `rb`. On trie les grands, on remonte les moyens et on trie les petits.
- Un `rb` (ou `ra`) en attente suivi d'un `ra` (ou `rb`) est fusionné en `rr`.
- Plages de 3 éléments ou moins, ou déjà triées : traitées directement.

**Borne :** à chaque niveau de récursion, chaque élément subit O(1) opérations
(un push ou une rotation, plus au plus une rotation inverse), et la taille des plages
est divisée par 3 → log₃(n) niveaux → **O(n log n)** opérations.
Mémoire : O(n) pour les piles + O(log n) de récursion.

**Mesures** (aléatoire, vérifié avec `checker_linux`) : ≈ 655 opérations pour 100
nombres (max 680), ≈ 4250 pour 500 nombres.

### 4. Adaptive

| Désordre | Régime | Méthode utilisée | Complexité |
|:---:|---|---|:---:|
| `< 0.2` | faible | *à compléter* | O(n²) |
| `0.2 ≤ d < 0.5` | moyen | *à compléter* | O(n√n) |
| `≥ 0.5` | fort | *à compléter* | O(n log n) |

*À compléter : justification des seuils, techniques internes, bornes en temps et
en mémoire.*

---

## 📚 Ressources

- [Sujet officiel push_swap (42)](https://projects.intra.42.fr/projects/42cursus-push_swap)
- [Quicksort — Wikipédia](https://fr.wikipedia.org/wiki/Tri_rapide)
- [Notation Big-O — Wikipédia](https://fr.wikipedia.org/wiki/Comparaison_asymptotique)
- [Inversions (mesure du désordre) — Wikipedia](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics))
- Visualiseur push_swap utilisé pour les tests

### Utilisation de l'IA

*À compléter honnêtement par chacune* : pour quelles tâches l'IA a été utilisée
(ex. structure du README, idées de tests, explications de concepts) et pour quelles
parties du projet. Tout contenu généré a été relu, compris et testé par nous deux.
