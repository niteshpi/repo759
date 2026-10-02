#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH -c 2
#SBATCH -J HW02_task2
#SBATCH -o HW02_task2.out -e HW02_task2.err
#SBATCH --mem=1G

# Compile the code
g++ -O2 -o task2 task2.cpp convolution.cpp

# Run with different input sizes
echo "Running convolution with n=100, m=5"
./task2 100 5

echo "Running convolution with n=500, m=7"
./task2 500 7

echo "Running convolution with n=1000, m=3"
./task2 1000 3