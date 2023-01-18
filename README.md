# EiffelNet
Par Martin Wattel et Alexis Rossfelder

## README.md
Ce fichier peut être visualisé en ligne sur [GitHub](https://gist.github.com/LiteApplication/34ac0ac5dce4024abc6c9fb8b5d7e417)

## Build
```bash
cmake -B build -S .
cd build
make
```

## Tests
Ce programme est compatible avec la suite de test CTest de CMake. Pour lancer les tests, il suffit de lancer la commande suivante :
```bash
ctest
# ou
make test
# ou 
./eiffelnet_test
```
après avoir compilé le programme à l'étape précédente.

CMake exécutera alors 5 tests sur le programme et ses fonctions:
 1. Teste si le fichier principal compile sans erreur
 2. Teste si le fichier de test compile sans erreur
 3. Execute le fichier de test et vérifie que le programme s'exécute sans erreur
 4. Teste si les fonctions sont bien définies dans les fichiers sources et headers
 5. Teste si la version C du programme produit les mêmes résultats que la version Python

## Exécution
Pour exécuter le programme, vous pouvez lancer les commandes suivantes après avoir compilé le programme: (depuis le dossier build)
```bash
make run # Compile et exécute le programme
make valgrind # Execute avec valgrind
./eiffelnet # Execute directement
```
Pour générer les fichiers `lycees.csv`, `voeux.csv` et `voeux_zones.csv`, il faut exécuter : (tout en étant dans le dossier build)
```bash
make genfiles
```
Cela générera les fichiers dans le dossier `data/`.


## Formatage
Le programme propose deux modes d'affichage : 
 - Le mode brut qui affiche les données exactement comme elles sont demandées dans le sujet 
```
<id lycee1> <id eleve1> <id eleve2> <id eleve3> ...
<id lycee2> <id eleve4> <id eleve5> <id eleve6> ...
...
```
 - Le mode formaté qui affiche les données de manière plus lisible
```
Lycée <id>
    Effectif actuel:    <effectif actuel> / <effectif max>
    Élèves:
        Eleve <id>:    Score: <score>   Voeux: <liste des voeux> 
        Eleve <id>:    Score: <score>   Voeux: <liste des voeux>
```
Pour choisir le mode d'affichage, il suffit de `#define` ou `#undef` `PRETTY_PRINT` dans le fichier [`includes/eiffelnet.h`](includes/eiffelnet.h#L9) (ligne 9). 

## Commentaires
Les commentaires de documentation sont situés dans les fichiers [`headers (.h)`](includes/).

Pour une fonction particulière, une description est indiquée par `@brief <description>`, les paramètres par `@param <name> <description>` et les valeurs de retour par `@return <description>`.

## Structure du projet
```bash
.
├── CMakeLists.txt # Fichier de configuration de CMake
├── README.md # Ce fichier
├── build # Dossier de compilation, créé par CMake
│   ├── Makefile # Fichier de compilation généré par CMake
│   ├── eiffelnet # Programme principal, point d'entrée
│   ├── eiffelnet_test # Programme de test
│   │   ... # Autres fichiers générés par CMake
│   └── libefnet.a # Librairie contenant les fonctions du projet
├── data # Dossier contenant les fichiers de données
│   ├── lycees.csv # Liste des lycées
│   ├── voeux.csv # Liste des voeux (pour une zone)
│   └── voeux_zones.csv # Liste des voeux (algo plusieurs zones)
├── includes # Dossier contenant les fichiers d'entête
│   ├── eiffelnet.h 
│   ├── eleve.h
│   ├── lecture.h
│   ├── lycee.h
│   ├── output.h
│   ├── test.h
│   └── voeux.h
├── main.c # Fichier principal, point d'entrée
├── src # Dossier contenant les fichiers sources
│   ├── eiffelnet.c
│   ├── eleve.c
│   ├── exemple_lecture.c
│   ├── exemple_tri.c
│   ├── lecture.c
│   ├── lycee.c
│   ├── output.c
│   └── voeux.c
└── tests # Dossier contenant les fichiers de tests
    ├── check_functions.py # Teste si les fonctions sont bien définies
    ├── generate_values.py # Génère des valeurs aléatoires pour les données
    ├── eiffelnet.py # Teste la sortie du programme principal
    └── tests.c # Teste les fonctions du projet
 
52 directories, 290 files
```