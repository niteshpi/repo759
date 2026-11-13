#!/bin/bash
#SBATCH -p instruction
#SBATCH -N 1
#SBATCH --cpus-per-task=8
#SBATCH -J HW05_task1
#SBATCH -o HW05_task1.out -e HW05_task1.err
#SBATCH --mem=8G
#SBATCH --time=00:10:00
#SBATCH --gpus-per-task=1

module load nvidia/cuda

nvcc task1.cu -Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17 -o task1
./task1
