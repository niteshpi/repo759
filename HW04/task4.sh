#!/bin/bash
#SBATCH -p instruction
#SBATCH -N 1
#SBATCH --cpus-per-task=8
#SBATCH -J HW04_task4
#SBATCH -o HW04_task4.out -e HW04_task4.err
#SBATCH --mem=8G
#SBATCH --time=00:20:00

# Compile once; the scheduling policy is chosen at runtime via OMP_SCHEDULE.
g++ task3.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

rm -f task4_timings.csv

for policy in static dynamic guided
do
    export OMP_SCHEDULE=$policy
    for t in 1 2 3 4 5 6 7 8
    do
        export OMP_NUM_THREADS=$t
        output=$(./task3 1000 100 $t)
        time_ms=$(printf '%s\n' "$output" | grep -oE '[0-9]+(\.[0-9]+)?' | head -n 1)
        echo "$policy,$t,$time_ms" >> task4_timings.csv
        echo "$policy threads=$t $output"
    done
done

python task4_plot.py task4_timings.csv task4.pdf
