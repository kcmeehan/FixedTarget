#!/bin/bash

###########################################################
#SET THE DATA DIRECTORY HERE
dataDirectory=/scratch_menkar/FixedTargetData/AuAu_4_5GeV_2015/

#SET THE OUTPUT DIRECTORY HERE
outputDirectory=/scratch_menkar/kmeehan/RepoForThesis/davisdstanalysis/userfiles/embedding/

#SET THE NUMBER OF EVENTS HERE (USE -1 FOR ALL)
nEvents=-1

#Set the star library version here
starLib=SL16a

#SET THE ENERGY OF THE COLLISION HERE
energy=4.5

#SET THE EVENT CONFIGURATION HERE
eventConfig=FixedTarget2015

###########################################################

#Array containing all the datafiles
dataFiles=( $dataDirectory/*.root )
processID=()
numberOfFiles=${#dataFiles[@]}
outFiles=()

for i in ${dataFiles[@]}
do
    echo "Running on dataFile: " $i
    
    outFile=$(basename $i .csv)
    outFile=$outputDirectory/"$outFile"_Processed.csv

    outFiles+=($outFile)

    nice root -l -q -b ../macros/RunCreateCentralityDatabaseCSV.C\(\"$i\",\"$outFile\",$nEvents,\"$starLib\",$energy,\"$eventConfig\"\) > /dev/null 2>&1 & 
    
    processID+=($!)
    echo ${processID[@]}
done 
wait ${processID[@]}

exit
