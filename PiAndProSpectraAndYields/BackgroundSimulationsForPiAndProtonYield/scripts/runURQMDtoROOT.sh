#!/bin/bash

dir=../urqmd_outputfiles/f13/          #Directory with .f13 files to process
outRootDir=../urqmd_outputfiles/root/  #Directory where the resulting root files should be stored
reflect=1                              #reflects the z values (only needed if you are doing fixed target sims)

#Check that the input Directory exists
if [ ! -d $dir ];then
    echo "ERROR: Input file directory $dir does not exist!"
    exit 1
fi

#Check that the input Directory has files to process
if [ "$(ls -1 $dir/*.f13 | wc -l)" -eq 0 ];then
    echo "ERROR: No .f13 files were found in $dir"
    exit 1
fi

#Check that the input Directory exists
if [ ! -d $outRootDir ]; then
    echo "ERROR: The output ROOT directory $outRootDir does not exist"
    exit 1
fi

#Check that the reflect is either 0 or 1
if [ "$reflect" -ne 0 -a "$reflect" -ne 1 ]; then
    echo "ERROR: Please choose either 0 (do not reflect) or 1 (do reflection) for the reflect variable."
    exit 1
fi


fileArray=( $dir/*.f13 )
processIDs=()

maxJobs=6
currentJobs=0
completedJobs=0

while [ $completedJobs -lt ${#fileArray[@]} ]
do

    if [[ $currentJobs -lt $maxJobs ]]
    then
	root -l -q -b ../macros/ConvertURQMDToROOT.C\(\"${fileArray[$completedJobs]}\",\"$outRootDir\",$reflect\) &

	processIDs+=($!)
	echo "Submitting Job $completedJobs"
	completedJobs=$(($completedJobs + 1))
    
    else
	sleep 15
	
    fi
        
    currentJobs=`ps --no-headers -o pid --ppid=$$ | wc -w`
    
done

#Make sure all the jobs have completed
wait ${processIDs[@]}

