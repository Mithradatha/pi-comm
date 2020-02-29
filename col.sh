#!/bin/bash

#SBATCH --job-name COL-S-1
#SBATCH --ntasks 1
#SBATCH --partition class
#SBATCH --time 00:10:00
#SBATCH --error=COL-S-1.%J.err
#SBATCH	--output=COL-S-1.%j.out
# module load mpich
# module load gcc

mpiexec ~/pi-mpi/col 800000000
