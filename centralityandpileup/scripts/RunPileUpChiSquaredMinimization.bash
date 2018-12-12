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

#bin where all bins beyond are pileup
lastBin=240

#Negative Binomial Parameters
p=0.82081
n=0.890602

#Number of histograms to be generated
numberOfPercentages=15

#Starting and ending percentages describing how often a pileup event occurs
percentBeg=0.1
percentEnd=1.5

#number of Simulated Events
nSimulatedEvents=1000000

#arrays
fitFiles=($fitDirectory/CentralityBins.root)
processID=()
numberOfFiles=${#fitFiles[@]}
outFiles=()

for i in ${fitFiles[@]}
do
	echo "Running on file: " $i

	outFile=$(basename $i .root)
	outFile=$outputDirectory/"$outFile"_pileupChiSquaredMinimization.root

	outFiles+=($outFile)

	root -l -q -b ../macros/RunPileUpChiSquaredMinimization.C\(\"$i\",$fitNumber,\"$dataFile\",\"$glauberFile\",\"$outFile\",$normStartBin,$normEndBin,$lastBin,$p,$n,$numberOfPercentages,$percentBeg,$percentEnd,$nSimulatedEvents\) #> /dev/null 2>&1 &

	processID+=($!)
	echo ${processID[@]}
done
wait ${processID[@]}

exit

