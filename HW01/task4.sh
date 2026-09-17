#!/usr/bin/env zsh
#SBATCH -c n
#SBATCH -J FirstSlurm
#SBATCH -o FirstSlurm-%j.out -e FirstSlurm-%j.err
echo "The hostname is: $(hostname)"
