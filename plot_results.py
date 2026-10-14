import csv
from collections import defaultdict
import matplotlib.pyplot as plt

data = defaultdict(dict)

with open("timings.csv", newline="") as file:
    for row in csv.DictReader(file):
        program = row["program"]
        processes = int(row["processes"])
        elapsed = float(row["time_seconds"])
        data[program][processes] = elapsed

for program, measurements in data.items():
    if 1 not in measurements or any(t <= 0 for t in measurements.values()):
        print(f"Skipping {program}: enter valid positive timings first.")
        continue

    processes = sorted(measurements)
    times = [measurements[p] for p in processes]
    speedups = [measurements[1] / measurements[p]
                for p in processes]

    plt.figure()
    plt.plot(processes, times, marker="o")
    plt.xlabel("Number of MPI processes")
    plt.ylabel("Execution time (seconds)")
    plt.title(f"{program}: Execution Time vs Processes")
    plt.xticks(processes)
    plt.grid(True)
    plt.savefig(f"{program}_time.png", dpi=150, bbox_inches="tight")
    plt.close()

    plt.figure()
    plt.plot(processes, speedups, marker="o")
    plt.xlabel("Number of MPI processes")
    plt.ylabel("Speedup")
    plt.title(f"{program}: Speedup vs Processes")
    plt.xticks(processes)
    plt.grid(True)
    plt.savefig(f"{program}_speedup.png", dpi=150, bbox_inches="tight")
    plt.close()

print("Graph generation complete.")
