"""a utility to parse log and calculate average cpu usage"""
from typing import List
import sys

# python will remove 'python' for sys.argv so it's avg_cpu_use.py <log_path>
log_path: str = sys.argv[1]

with open(log_path, "r") as log_file:
    log: List[str] = log_file.readlines()

cpu_use: float = 0.0

for line in log:
    # this could help check if your log matches specified format :)
    # first separate with space
    tmp = line.strip("\n").split(" ")
    # have some additional test here but hidden
    assert tmp[-2] == "[cpu%]", "log not correct"
    cpu_use += float(tmp[-1].strip("%")) / 100

print("average cpu usage: {:.2%}".format(cpu_use / len(log)))