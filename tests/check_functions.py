# This will check the c files to ensure that each function defined in the header
# file is also defined in the c file.

# It will also check that each function defined in the c file is also defined
# in the header file.

# This will also print out the number of lines in all the project files.

import os, re

FUNCTION_REGEX = r"^(\w+( )?(\*){0,3}){2,3}\([^!@#$+%^]+?\)"
INCLUDE_DIR = "includes"
C_DIR = "src"

lines = 0

os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))  # Go to root

header_files = []
c_files = []

for root, dirs, files in os.walk("."):
    for file in files:
        if INCLUDE_DIR in root and file.endswith(".h"):
            header_files.append(os.path.join(root, file))
        elif C_DIR in root and file.endswith(".c"):
            c_files.append(os.path.join(root, file))

header_functions = {}
c_functions = {}

for file in header_files:
    with open(file, "r") as f:
        for i, line in enumerate(f):
            lines += 1
            if re.match(FUNCTION_REGEX, line):
                header_functions[
                    line.rstrip("\n; {")
                ] = f"{os.path.relpath(file)}:{i+1}"

for file in c_files:
    with open(file, "r") as f:
        for i, line in enumerate(f):
            lines += 1
            if re.match(FUNCTION_REGEX, line):
                c_functions[line.rstrip("\n; {")] = f"{os.path.relpath(file)}:{i+1}"


missing_functions = {k: v for k, v in header_functions.items() if k not in c_functions}
missing_headers = {k: v for k, v in c_functions.items() if k not in header_functions}

error = missing_functions or missing_headers

if missing_functions:
    print("Missing functions in c files:")
    for function, file in missing_functions.items():
        print(f"  {function} in {file}")

if missing_headers:
    print("Missing functions in header files:")
    for function, file in missing_headers.items():
        print(f"  {function} in {file}")

print(
    f"Total lines: {lines} in {len(header_files)} header files and {len(c_files)} c files"
)

if error:
    exit(1)
