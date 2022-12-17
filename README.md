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

## Exécution
Pour exécuter le programme, vous pouvez lancer les commandes suivantes après avoir compilé le programme: (depuis le dossier build)
```bash
make run # Compile et exécute le programme
make valgrind # Execute avec valgrind
./eiffelnet # Execute directement
```
Pour générer les fichiers `lycees.csv`, `voeux.csv` et `voeux_zones.csv`, il faut éxécuter : (tout en étant dans le dossier build)
```bash
make genfiles
```

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
Pour choisir le mode d'affichage, il suffit de `#define` ou `#undef` `PRETTY_PRINT` dans le fichier [`includes/eiffelnet.h`](includes/eiffelnet.h#L8) (ligne 8). 

## Commentaires
Les commentaires de documentation sont situés dans les fichiers [`headers (.h)`](includes/).

Pour une fonction particulière, une description est indiquée par `@brief <description>`, les paramètres par `@param <name> <description>` et les valeurs de retour par `@return <description>`.

## Structure du projet
```bash
.
├── CMakeLists.txt # Fichier de configuration de CMake
├── main.c # Point d'entrée du programme
├── README.md # Ce fichier
├── includes # Headers
│   ├── eiffelnet.h
│   ├── eleve.h
│   ├── lecture.h
│   ├── lycee.h
│   ├── output.h
│   └── test.h
├── src # Sources et fonctions
│   ├── eiffelnet.c
│   ├── eleve.c
│   ├── exemple_lecture.c # Fourni par le sujet
│   ├── exemple_tri.c # Fourni par le sujet
│   ├── lecture.c
│   ├── lycee.c
│   └── output.c
├── data # Données d'entrée
│   ├── lycees.csv
│   ├── voeux.csv
│   └── voeux_zones.csv
├── tests # Fichiers de tests
│   ├── generate_values.py # Générateur de fichiers d'entrées
│   └── tests.c # Fichier de tests contenant les assertions, point d'entrée des tests
└── build # Dossier de compilation
    ├── eiffelnet # Éxécutable
    ├── libefnet # Bibliothèque statique contenant les fonctions de l'application
    ├── eiffelnet_test # Éxécutable pour les tests
    └── ...
```