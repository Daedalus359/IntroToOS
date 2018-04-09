#!/bin/sh
#SBATCH --nodes=1
#SBATCH --cpus-per-task=6 # 6 cores
#SBATCH --time=0-00:05:00  # 5 minutes
#SBATCH --output=p1_output.txt 

cp p1.c $PFSDIR/.
cd $PFSDIR
gcc p1.c -o p1 -fopenmp -lm
./p1