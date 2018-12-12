#!/bin/bash

#This script is used to find the centrality binning of data
#It needs a Glauber Simulation to have been completed first.

#USER DEFINED VARIABLES
dataFileName=../userfiles/AuAu_4_5GeV_2015/centralityVariableRuns/CentralityVariableDistributions.root #File containing histogram to be matched
dataHistoName=nGoodTracks                                               #Name of the histogram in the file from above
glauberFileName=../userfiles/AuAu_4_5GeV_2015/Glauber_197_197_30mb_WoodsSaxon.root        #Glauber file generated from runGlauberSimulation.sh
outputFileName=../userfiles/AuAu_4_5GeV_2015/centralityBins/CentralityBins.root                #outputfile (will get re-written if it already exists!)
normStartBinCenter=110 #60 auau  120                                                  #The bin center value to begin the chi^2 matching/optimization routine
normStopBinCenter=230 #177 auau    180                                               #The bin center value to end the chi^2 matching/optimization routine Use -1 to use the last bin of the data histogram. NOTE: This value must be larger than normStartBinCenter to make any sense.

root -l -b -q ../macros/RunCentralityDetermination.C\(\"$dataFileName\",\"$dataHistoName\",\"$glauberFileName\",\"$outputFileName\",$normStartBinCenter,$normStopBinCenter\)
