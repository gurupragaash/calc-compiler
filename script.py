# To run: python script.py <optimizer_output_file>
#
# This creates a directory called passes which contains the output of passes that
# appear to have changed the IR because LLVM's debugging output sometimes only
# prints basic blocks rather than a full function. Not all of the passes with files
# will have actually changed anything.

import os
import re
import sys

with open(sys.argv[1]) as file:
    data = file.read()

split_data = re.split("\*\*\* IR Dump After ([ \w'-/]+) \*\*\*", data)
del split_data[0]
passes = zip(split_data[0::2],split_data[1::2])

def unchanged_passes(passes):
    res = []
    last = passes[0][1]
    remaining = passes[1:]

    for name, after in remaining:
        if after != last:
            last = after
            res.append((name, after))

    return res

def remove_junk(stuff):
    return "\n".join([line for line in stuff.split("\n")
        if not(line.startswith(";") or line.startswith("declare") or line.startswith("attributes")
        or line.startswith("target triple") or line.startswith("source_filename") or line.isspace()
        or line == "")])

unchanged = unchanged_passes([(name, remove_junk(after)) for name, after in passes])

passesdir = "passes"

os.mkdir(passesdir)

for idx, (name, after) in enumerate(unchanged):
    filename = str(idx).zfill(2) + "_" + "_".join(name.replace('/',' ').split(" "))
    with open(os.path.join(passesdir, filename), "w") as f:
        f.write(after)


