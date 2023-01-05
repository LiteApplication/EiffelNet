import random
import csv
import sys, os

NB_VOEUX = 10
NB_LYCEES = 28
NB_ELEVES = 1327

MIN_EFFECTIF = 10
MAX_EFFECTIF = 100
MAX_SCORE = NB_ELEVES * 2

lycees = []
print("Génération des lycées ... ")
for i in range(NB_LYCEES):
    lycees.append((i, random.randrange(MIN_EFFECTIF, MAX_EFFECTIF)))

eleves = []
print("Génération des élèves ... ")
unused_scores = set(range(1, MAX_SCORE))
for i in range(NB_ELEVES):
    score = random.choice(list(unused_scores))
    unused_scores.remove(score)
    voeux = []
    available = list(range(NB_LYCEES))
    for _ in range(NB_VOEUX):
        voeux.append(random.choice(available))
        available.remove(voeux[-1])
    eleves.append((i, score, *voeux))

eleves_zones = []
print("Génération des élèves avec zones ... ")
unused_scores = list(range(1, MAX_SCORE * NB_VOEUX))
for i in range(NB_ELEVES):
    voeux = []
    available = list(range(NB_LYCEES))
    for _ in range(NB_VOEUX):
        voeux.append(random.choice(available))
        available.remove(voeux[-1])
        voeux.append(random.choice(unused_scores))
        unused_scores.remove(voeux[-1])
    eleves_zones.append((i, *voeux))

os.chdir(os.path.dirname(sys.argv[1] if len(sys.argv) > 1 else "./"))


# Write everything
print("Écriture des fichiers ... ")
with open("lycees.csv", "w") as f:
    for i, row in enumerate(lycees):
        csv.writer(f, lineterminator="").writerow(row)
        if i < len(lycees) - 1:
            f.write("\n")

with open("voeux.csv", "w") as f:
    for i, row in enumerate(eleves):
        csv.writer(f, lineterminator="").writerow(row)
        if i < len(eleves) - 1:
            f.write("\n")

with open("voeux_zones.csv", "w") as f:
    for i, row in enumerate(eleves_zones):
        csv.writer(f, lineterminator="").writerow(row)
        if i < len(eleves_zones) - 1:
            f.write("\n")
