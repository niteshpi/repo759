#!/bin/bash
#SBATCH -p instruction
#SBATCH -N 1
#SBATCH --cpus-per-task=8
#SBATCH -J HW04_task3
#SBATCH -o HW04_task3.out -e HW04_task3.err
#SBATCH --mem=8G
#SBATCH --time=00:10:00

# Compile
 g++ task3.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

# Run the program with fixed values and a thread count
# Example: ./task3 100 10 4
./task3 100 10 4
