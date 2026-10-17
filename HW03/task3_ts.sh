#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -N 1
#SBATCH --cpus-per-task=20
#SBATCH -J HW03_task3_ts
#SBATCH -o HW03_task3_ts.out -e HW03_task3_ts.err
#SBATCH --mem=8G

# Compile the OpenMP task-based merge sort
g++ task3.cpp msort.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

echo "Compilation complete"

# Per the assignment: n = 10^6, t = 8, and ts = 2^1, 2^2, ..., 2^10.
: > task3_ts_scaling.dat

for ((ts=2; ts<=1024; ts*=2)); do
    TIME_MS=$(./task3 1000000 8 "$ts" | tail -n 1)
    echo "$ts $TIME_MS" >> task3_ts_scaling.dat
done

# plot using Python
python - <<'PY'
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

data = []
with open("task3_ts_scaling.dat", "r") as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        ts, time_ms = map(float, line.split())
        data.append((int(ts), float(time_ms)))

if not data:
    raise SystemExit("No timing data found")

ts_vals = [ts for ts, _ in data]
time_vals = [time_ms for _, time_ms in data]

plt.figure(figsize=(8, 5))
plt.plot(ts_vals, time_vals, marker='o', linewidth=2)
plt.xscale('log', base=2)
plt.xlabel('ts (log scale)')
plt.ylabel('Time (ms)')
plt.title('Merge sort threshold sweep (n = 10^6, t = 8)')
plt.grid(True, which='both', linestyle='--', alpha=0.5)
plt.tight_layout()
plt.savefig('task3_ts.pdf')
print('Saved task3_ts.pdf')
PY
