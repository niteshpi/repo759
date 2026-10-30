#!/bin/bash
#SBATCH -p instruction
#SBATCH -N 1
#SBATCH --cpus-per-task=20
#SBATCH -J HW04_task2
#SBATCH -o HW04_task2.out -e HW04_task2.err
#SBATCH --mem=8G
#SBATCH --time=00:10:00

# Compile:
g++ task2.cpp -Wall -O3 -std=c++17 -o task2

# Run the program; keep the values fixed at 100 particles and 10 seconds.
./task2 100 10
