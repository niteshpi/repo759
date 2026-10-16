#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -N 1
#SBATCH --cpus-per-task=20
#SBATCH -J HW03_task2
#SBATCH -o HW03_task2.out -e HW03_task2.err
#SBATCH --mem=8G

# Compile the OpenMP implementation
# Required command: g++ task2.cpp convolution.cpp -Wall -O3 -std=c++17 -o task2 -fopenmp
g++ task2.cpp convolution.cpp -Wall -O3 -std=c++17 -o task2 -fopenmp

echo "Compilation complete"

# create a file to store results: t, time_ms
: > task2_scaling.dat

for ((t=1; t<=20; t++)); do
    TIME_MS=$(./task2 1024 "$t" | tail -n 1)
    echo "$t $TIME_MS" >> task2_scaling.dat
done

# plot using Python
python - <<'PY'
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

data = []
with open("task2_scaling.dat", "r") as f:
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
plt.title('OpenMP convolution scaling for n = 1024')
plt.grid(True, which='major', linestyle='--', alpha=0.5)
plt.tight_layout()
plt.savefig('task2.pdf')
print('Saved task2.pdf')
PY
