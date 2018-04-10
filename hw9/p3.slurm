#!/bin/sh
#SBATCH --nodes=1
#SBATCH --cpus-per-task=6 # 6 cores
#SBATCH --time=0-00:05:00  # 5 minutes
#SBATCH --output=p3_output.txt 

cp p3.c $PFSDIR/.
cd $PFSDIR
gcc p3.c -o p3 -lrt -lpthread -lm
./p3 1
./p3 2
./p3 3
./p3 4
./p3 5