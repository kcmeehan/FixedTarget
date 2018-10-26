#!/bin/bash

dir="../urqmd_outputfiles/root/"           #Directory with root files to process
outStarsimDir="../STARSIM/inputfiles/"     #Directory where the .tx files should be stored
vertexHistoFile="../STARSIM/vertexHistosForStarsim.root"         #path to and name of root file with vertex histos
vertexHistoBaseName="AuAu4pt5"     #base name of the histos (histos need to be named something like: basename_zVertex)
maxEventsPerOutputFile=10  #if there are more than this many events in the urqmd file they will be split 
                           #across multiple starsim files
nDesiredEventsPerJob=10    #the number of desired events you would like from each job (e.g. because not all
                           #events in the root file will be valid events for the tx file)

#Check that the input Directory exists
if [ ! -d $dir ];then
    echo "ERROR: Input file directory $dir does not exist!"
    exit 1
fi

#Check that the output starsim directory exists
if [ ! -d $outStarsimDir ]; then
    echo "ERROR: The output STARSIM directory $outStarsimDir does not exist"
    exit 1
fi

#Check that the Vertex Histo File exists
if [ ! -e $vertexHistoFile ]; then
    echo "WARNING: The vertex histogram file $vertexHistoFile does not exist!"
    echo "         Event vertices will all be defined as (0,0,0)"
fi

fileArray=( $dir/*.root )
processIDs=()

maxJobs=6
currentJobs=0
completedJobs=0

while [ $completedJobs -lt ${#fileArray[@]} ]
do

    if [[ $currentJobs -lt $maxJobs ]]
    then
	root -l ../macros/RunMakeStarsimTxFiles.C\(\"${fileArray[$completedJobs]}\",\"$outStarsimDir\",\"$vertexHistoFile\",\"$vertexHistoBaseName\",$maxEventsPerOutputFile,$nDesiredEventsPerJob\) &

	processIDs+=($!)
	echo "Submitting Job $completedJobs"
	completedJobs=$(($completedJobs + 1))
    
    #else
	#sleep 15
	
    fi
        
    currentJobs=`ps --no-headers -o pid --ppid=$$ | wc -w`
    
done

#Make sure all the jobs have completed
wait ${processIDs[@]}


