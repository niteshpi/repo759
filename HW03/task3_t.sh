#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -N 1
#SBATCH --cpus-per-task=20
#SBATCH -J HW03_task3_t
#SBATCH -o HW03_task3_t.out -e HW03_task3_t.err
#SBATCH --mem=8G

# The ts value that gave the best result in the threshold sweep.
BEST_TS=1024

# Compile the OpenMP task-based merge sort
g++ task3.cpp msort.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

echo "Compilation complete"

: > task3_t_scaling.dat

for ((t=1; t<=20; t++)); do
    TIME_MS=$(./task3 1000000 "$t" "$BEST_TS" | tail -n 1)
    echo "$t $TIME_MS" >> task3_t_scaling.dat
done

# plot using Python
python - <<'PY'
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

data = []
with open("task3_t_scaling.dat", "r") as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        t, time_ms = map(float, line.split())
        data.append((int(t), float(time_ms)))

if not data:
    raise SystemExit("No timing data found")

t_vals = [t for t, _ in data]
time_vals = [time_ms for _, time_ms in data]

plt.figure(figsize=(8, 5))
plt.plot(t_vals, time_vals, marker='o', linewidth=2)
plt.xlabel('t')
plt.ylabel('Time (ms)')
plt.title('Merge sort scaling for n = 10^6, ts = 64')
plt.grid(True, which='major', linestyle='--', alpha=0.5)
plt.tight_layout()
plt.savefig('task3_t.pdf')
print('Saved task3_t.pdf')
PY
