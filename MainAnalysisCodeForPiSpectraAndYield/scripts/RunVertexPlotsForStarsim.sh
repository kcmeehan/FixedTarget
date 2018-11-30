#!/bin/bash

# This runs the RunVertexPlotsForStarsim.C macro which generates the vertex distribution plots needed as 
# input to Starsim when running the background simulations. The path to the davisdsts (the dataDirectory) 
# and the output directory need to be set by the user. The rest of the code is already set to the proper 
# configuration.

###########################################################
#SET THE DATA DIRECTORY HERE
dataDirectory=/scratch_menkar/FixedTargetData/AuAu_4_5GeV_2015/

#SET THE OUTPUT DIRECTORY HERE
outputDirectory=../userfiles/background/

#SET THE NUMBER OF EVENTS HERE (USE -1 FOR ALL)
nEvents=-1 

#SET THE STAR LIBRARY VERSION
starlib=SL16a

#SET THE COLLISION ENERGY HERE
energy=4.5

#SET THE EVENT CONFIGURATION HERE
eventConfig=FixedTarget2015

########################################################### 

#Array containing all of the dataFiles
dataFiles=( $dataDirectory/*.root )
#dataFiles=AuAu_4_5GeV_2015_0.root
processID=()
numberOfFiles=${#dataFiles[@]}
#numberOfFiles=1
outFiles=()
#i=$dataDirectory
#i+=$dataFiles

for i in ${dataFiles[@]}
do
    echo "Running on dataFile: " $i
    outFile=$(basename $i .root)

    outFile=$outputDirectory"$outFile"_Processed.root
 
    outFiles+=($outFile)

    root -l -q -b ../macros/RunVertexPlotsForStarsim.C\(\"$i\",\"$outFile\",\"$starlib\",$nEvents,$energy,\"$eventConfig\"\) 

    processID+=($!)
    echo ${processID[@]}
done

wait ${processID[@]}

suffix=vertexHistosForStarsim

hadd $outputDirectory/$suffix.root ${outFiles[@]}

wait

rm ${outFiles[@]}

exit
