#!/bin/bash

#best fit histogram directory found from RunCentralityDetermination.sh
fitDirectory=../userfiles/AuAu_4_5GeV_2015/centralityBins/

#best fit histogram fit number
fitNumber=0

# UNNORMALIZED data sorted by run number with included cuts in UserCuts.cxx
dataFile=../userfiles/AuAu_4_5GeV_2015/centralityVariableRuns/CentralityVariableDistributions.root

#glauber directory
glauberFile=../userfiles/AuAu_4_5GeV_2015/Glauber_197_197_30mb_WoodsSaxon.root

#output directory
outputDirectory=../userfiles/AuAu_4_5GeV_2015/pileupLumi/

energy=4.5

eventConfig="FixedTarget2015"

starLibrary="SL16a"

#region where to normalize. *Should* match the bins used in RunCentralityDetermination.sh
normStartBin=110
normEndBin=230

#Negative Binomial Parameters
p=0.82081
n=0.890602

#Simulate how often a pileup event occurs between 0 and 1
pileUpEventOccurence=0.0073

#number of simulated events
nSimulatedEvents=10000000

#Draw canvas? Not needed for pile up study
drawCanvas=false


#arrays
fitFiles=($fitDirectory/CentralityBins.root)
processID=()
numberOfFiles=${#centralityFiles[@]}
outFiles=()

for i in ${fitFiles[@]}
do
	echo "Running on file: " $i

	outFile=$(basename $i .root)
	outFile=$outputDirectory/"$outFile"_pileupLumi.root

	outFiles+=($outFile)

	root -l -q -b ../macros/RunPileUpLuminosity.C\(\"$i\",$fitNumber,\"$dataFile\",\"$glauberFile\",\"$outFile\",$energy,\"$eventConfig\",\"$starLibrary\",$normStartBin,$normEndBin,$p,$n,$pileUpEventOccurence,$nSimulatedEvents,$drawCanvas\) #> /dev/null 2>&1 &

	processID+=($!)
	echo ${processID[@]}
done
wait ${processID[@]}

exit
