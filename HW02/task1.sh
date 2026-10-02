#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 2
#SBATCH -J HW02_task1
#SBATCH -o HW02_task1.out -e HW02_task1.err
#SBATCH --mem=8G
echo "$(hostname)"
g++ scan.cpp task1.cpp -Wall -O3 -std=c++17 -o task1
echo "Compilation complete"

# create a file to store results: n, time_ms
: > task1_scaling.dat

for ((n=10; n<=30; n++)); do
    N=$((2 ** n))
    TIME_MS=$(./task1 "$N" | head -n 1)
    echo "$N $TIME_MS" >> task1_scaling.dat
done

# plot using Python
python - <<'PY'
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

data = []
with open("task1_scaling.dat", "r") as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        n, t = map(float, line.split())
        data.append((int(n), float(t)))

if not data:
    raise SystemExit("No timing data found")

n_vals = [n for n, _ in data]
t_vals = [t for _, t in data]

plt.figure(figsize=(8, 5))
plt.plot(n_vals, t_vals, marker='o', linewidth=2)
plt.xscale('log', base=2)
plt.yscale('log')
plt.xlabel('n')
plt.ylabel('Time (ms)')
plt.title('Scaling Analysis')
plt.grid(True, which='both', linestyle='--', alpha=0.5)
plt.tight_layout()
plt.savefig('task1.pdf')
print('Saved task1.pdf')
PY

