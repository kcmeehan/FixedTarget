#!/bin/bash

#Run UrQMD Simulations
inputFileDir=../urqmd_inputfiles/  #Path to the directory containing the input files
outDir=../urqmd_outputfiles/f13/        #Path to the directory where the output files should be stored
energyName=AuAu4pt5FXT    #Name to be used as a prefix in the output file names
maxJobs=6       #Maximum number of parallel jobs to run at a time

#Check to make sure the input file directory exists
if [ ! -d $inputFileDir ]; then
    echo "ERROR: Input file directory $inputFileDir does not exist!"
    exit 1
fi

#Check to make sure the output file directory exists
if [ ! -d $outDir ]; then
    echo "ERROR: Output directory $outDir does not exist!"
    exit 1
fi

#Check to make sure there are input files to run on
if [ $(ls -1 $inputFileDir/*.input | wc -l) -eq 0 ]; then
    echo "ERROR: Did not find any UrQMD input files in $inputFileDir!"
    exit 1
fi

inputFileArray=( $inputFileDir/*.input )
nJobs=${#inputFileArray[@]}

currentJobs=0
submittedJobs=0

while [ $submittedJobs -lt $nJobs ]
do
    
    if [[ "$currentJobs" -lt "$maxJobs" ]] 
    then
	echo "There are this many jobs running" $currentJobs
	echo "Submitting job $x: " ${inputFileArray[$submittedJobs]} $outDir $energyName $submittedJobs
	./runURQMD.sh ${inputFileArray[$submittedJobs]} $outDir $submittedJobs >/dev/null &
	submittedJobs=$(($submittedJobs + 1))
    fi
	
    currentJobs=$(ps -u kmeehan | grep -c "urqmd.x86_64")
    
    sleep 2

done
