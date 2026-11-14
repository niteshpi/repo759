#!/bin/bash
#SBATCH --job-name=HW05_Task2
#SBATCH --output=task2_%j.out
#SBATCH --error=task2_%j.err
#SBATCH --partition=instruction
#SBATCH --time=00:10:00
#SBATCH --mem=16G
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --gpus-per-task=1

module load nvidia/cuda

nvcc task2.cu -Xcompiler -O3 -Xcompiler -Wall -Xptxas -O3 -std=c++17 -o task2
./task2
