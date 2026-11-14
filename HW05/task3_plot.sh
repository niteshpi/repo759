#!/bin/bash
#SBATCH --job-name=HW05_Task3_Plot
#SBATCH --output=task3_plot_%j.out
#SBATCH --error=task3_plot_%j.err
#SBATCH --partition=instruction
#SBATCH --time=00:20:00
#SBATCH --mem=16G
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --gpus-per-task=1

module load nvidia/cuda

python3 task3_plot.py
