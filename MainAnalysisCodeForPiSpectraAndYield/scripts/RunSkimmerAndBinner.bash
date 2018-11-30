#!/bin/bash

#This runs the calls the RunSkimmerAndBinner.C macro which loads the necessary libraries
#and then runs skimmerAndBinner.cxx. The code is run for each root file in the data
# directory.

###########################################################
#SET THE DATA DIRECTORY HERE
dataDirectory=/scratch_menkar/FixedTargetData/AuAu_4_5GeV_2015/

#SET THE OUTPUT DIRECTORY HERE
outputDirectory=../userfiles/analysis/

#SET THE NUMBER OF EVENTS HERE (USE -1 FOR ALL)
nEvents=-1 #1000

#SET THE STAR LIBRARY VERSION
starlib=SL16a

#SET THE COLLISION ENERGY HERE
energy=4.5

#SET THE EVENT CONFIGURATION HERE
eventConfig=FixedTarget2015

########################################################### 

#Array containing all of the dataFiles
dataFiles=( $dataDirectory/*.root )
processID=()
numberOfFiles=${#dataFiles[@]}
outFiles=()

for i in ${dataFiles[@]}
do
    echo "Running on dataFile: " $i

    outFile=$(basename $i .root)
    outFile=$outputDirectory/"$outFile"_Processed.root

    outFiles+=($outFile)

    root -l -q -b ../macros/RunSkimmerAndBinner.C\(\"$i\",\"$starlib\",$nEvents,\"$outFile\",$energy,\"$eventConfig\"\) > /dev/null 2>&1 &

    processID+=($!)
    echo ${processID[@]}
done
wait ${processID[@]}

hadd $outputDirectory/YieldHistograms.root ${outFiles[@]}

wait

rm ${outFiles[@]}


exit
