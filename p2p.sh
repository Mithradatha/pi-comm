#!/bin/bash

#SBATCH --job-name P2P-S-1
#SBATCH --ntasks 1
#SBATCH --partition class
#SBATCH --time 00:10:00
#SBATCH --error=P2P-S-1.%J.err
#SBATCH	--output=P2P-S-1.%j.out
# module load mpich
# module load gcc

mpiexec ~/pi-mpi/p2p 800000000