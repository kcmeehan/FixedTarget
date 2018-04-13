#! /usr/bin/tcsh


# Make scratch directories
set scratchRoot=/gpfs/mnt/gpfs01/star/scratch/$USER/fxtHbt

mkdir -p $scratchRoot/output
mkdir -p $scratchRoot/logs
mkdir -p $scratchRoot/schedulerFiles

# Switch to the right STAR library and compile the source code
starver SL16a
cons
