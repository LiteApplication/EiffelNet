# EiffelNet
## Build
```bash
cmake -B build -S .
cd build
make
```

## Tests
Ce programme utilise la suite de test CTest de CMake. Pour lancer les tests, il suffit de lancer la commande suivante :
```bash
ctest
```
après avoir compilé le programme à l'étape précédente.

## Exécution
Pour exécuter le programme, vous pouvez lancer les commandes suivantes après avoir compilé le programme: (depuis le dossier build)
```bash
make run # Compile et exécute le programme
make valgrind # Execute avec valgrind
./eiffelnet # Execute directement
```