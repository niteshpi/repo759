#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 2
#SBATCH -J HW02_task3
#SBATCH -o HW02_task3.out -e HW02_task3.err
#SBATCH --mem=1G

# Compile the code
g++ task3.cpp matmul.cpp -Wall -O3 -std=c++17 -o task3

# Run the program
./task3