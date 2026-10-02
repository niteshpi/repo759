#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 2
#SBATCH -J HW01_task6
#SBATCH -o HW01_task6.out -e HW01_task6.err
echo "$(hostname)"
g++ task6.cpp -Wall -O3 -std=c++17 -o task6
echo "Compilation complete"
./task6 9