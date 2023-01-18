#!/usr/bin/env python

import csv
import os
import sys
import subprocess
import tempfile


LYCEES_FILE = os.path.join(os.path.dirname(__file__), "../data/lycees.csv")
ELEVES_FILE = os.path.join(os.path.dirname(__file__), "../data/voeux_zones.csv")

lycees = []
eleves = []


class Lycee:
    def __init__(self, id: int, capacity: int):
        self.id = id
        self.capacity = capacity
        self.eleves = []  # always sorted by score (descending)

    @staticmethod
    def get_lycee(lycee_id):
        if lycees[lycee_id].id == lycee_id:
            return lycees[lycee_id]
        else:
            for lycee in lycees:
                if lycee.id == lycee_id:
                    return lycee
            raise ValueError(f"Lycee {lycee_id} not found")

    def add_eleve(self, eleve):
        self.eleves.append(eleve)

    def sort(self):
        self.eleves.sort(key=lambda e: e.get_score(self.id), reverse=True)

    def delete(self, eleve):
        self.eleves.remove(eleve)

    def accept_students(self):
        eleves_accepted = self.eleves[: self.capacity]
        edit = False
        for eleve in eleves_accepted:
            edit = eleve.delete_after(self.id) or edit
        return edit

    def __repr__(self):
        return f"Lycee {self.id} ({self.capacity})"


class Eleve:
    def __init__(self, id: int, scores: list[int] = None, wishes: list[int] = None):
        self.id = id
        if wishes is None:
            wishes = []
        if scores is None:
            scores = []
        self.wishes = wishes
        self.scores = scores

    def get_score(self, lycee_id):
        return self.scores[self.wishes.index(lycee_id)]

    def add_wish(self, lycee_id, score):
        self.wishes.append(lycee_id)
        self.scores.append(score)

    def delete_after(self, lycee_id) -> bool:
        index = self.wishes.index(lycee_id)
        edit = False
        for _ in range(index + 1, len(self.wishes)):
            Lycee.get_lycee(self.wishes.pop()).delete(self)
            self.scores.pop()
            edit = True

        return edit

    def __repr__(self):
        return f"Eleve {self.id} ({self.wishes})"


def read_lycees():
    with open(LYCEES_FILE, "r") as f:
        reader = csv.reader(f, delimiter=",", lineterminator="\n")
        lycees = [Lycee(int(i), int(c)) for i, c in reader]
    return lycees


def read_eleves():
    eleves = []
    with open(ELEVES_FILE, "r") as f:
        reader = csv.reader(f, delimiter=",", lineterminator="\n")
        for row in reader:
            line = (n for n in row)
            eleve = Eleve(next(line))
            for lycee_id, score in zip(line, line):
                eleve.add_wish(int(lycee_id), int(score))
            eleves.append(eleve)
    return eleves


def eiffelnet():
    global lycees, eleves
    lycees = read_lycees()
    eleves = read_eleves()

    for eleve in eleves:
        for lycee_id in eleve.wishes:
            lycees[lycee_id].add_eleve(eleve)

    for lycee in lycees:
        lycee.sort()

    while True:
        edit = False
        for lycee in lycees:
            edit = lycee.accept_students() or edit
        if not edit:
            break

    output = tempfile.NamedTemporaryFile(mode="w")
    for lycee in lycees:
        print(lycee.id, end=" ", file=output)
        for eleve in lycee.eleves[: lycee.capacity]:
            print(eleve.id, end=" ", file=output)
        print(file=output)

    return output


def main():
    assert len(sys.argv) == 2
    assert os.path.isfile(sys.argv[1])
    program_path = sys.argv[1]

    program_out = tempfile.NamedTemporaryFile(mode="w")
    subprocess.run(
        [program_path],
        stdout=program_out,
        cwd=os.path.dirname(program_path),
    )

    eiffelnet_out = eiffelnet()

    # make the files readable
    program_out = open(program_out.name, "r")
    eiffelnet_out = open(eiffelnet_out.name, "r")
    program_out.seek(0)
    eiffelnet_out.seek(0)

    if program_out.read() == eiffelnet_out.read():
        exit(0)
    else:
        print("Program output does not match EiffelNet output")
        exit(1)


if __name__ == "__main__":
    main()
else:
    raise RuntimeError("This file should not be imported")
