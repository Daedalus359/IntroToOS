#!/bin/sh
#SBATCH --nodes=1
#SBATCH --cpus-per-task=6 # 6 cores
#SBATCH --time=0-00:05:00  # 5 minutes
#SBATCH --output=p2_output.txt 

cp p2.c $PFSDIR/.
cd $PFSDIR
gcc p2.c -o p2 -lrt -lpthread -lm
./p2