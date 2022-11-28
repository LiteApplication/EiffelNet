import random
import csv
import sys, os

NB_VOEUX = 10
NB_LYCEES = 28
NB_ELEVES = 1327

MIN_EFFECTIF = 10
MAX_EFFECTIF = 100
MAX_SCORE = 255

used_scores = set()

lycees = []
for i in range(NB_LYCEES):
    lycees.append((i, random.randrange(MIN_EFFECTIF, MAX_EFFECTIF)))

eleves = []
for i in range(NB_ELEVES):
    score = 0
    while score == 0 or score in used_scores:
        score = random.randrange(1, MAX_SCORE)
    voeux = []
    available = list(range(NB_LYCEES))
    for _ in range(NB_VOEUX):
        voeux.append(random.choice(available))
        available.remove(voeux[-1])
    eleves.append((i, score, *voeux))

eleves_zones = []
for i in range(NB_ELEVES):
    voeux = [
        random.randrange(1, MAX_SCORE) if i % 2 else random.randrange(0, NB_LYCEES)
        for i in range(NB_VOEUX * 2)
    ]
    eleves_zones.append((i, *voeux))

os.chdir(os.path.dirname(sys.argv[1] if len(sys.argv) > 1 else "./"))


# Write everything
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
