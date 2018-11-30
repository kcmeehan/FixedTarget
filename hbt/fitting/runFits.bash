#! /bin/bash

fit() {

    inFile=$1
    outFile=$2
    pm=$3 # -1=piMinus, +1=piPlus, 0=both
    ktBin=$4 # 0.15-0.25, 0.25-0.35, 0.35-0.45, 0.45-0.6, Integrated (all in Gev)
    multBin=$5
    ktDifferential=$6 # Boolean for whether or not the fits are diff. in kt
    projRange=0.03 # Range in q-space to project correlation functions (in GeV)

    # Initial values for the fit parameters
    # Norm, lambda, R^2_o, R^2_s, R^2_l, R^2_os, R^2_ol, R^2_sl, 
    # declare -a initPars=(0.17 0.486 10 10 10 0 0 0)
    declare -a initPars=(0.17 0.486 20 20 20 0 0 0)


    # Build the argument string
    args='"'$inFile'","'$outFile'"',$pm,$ktBin,$multBin,0.149,$projRange
    args="$args,${initPars[0]},${initPars[1]},${initPars[2]},${initPars[3]}"
    args="$args,${initPars[4]},${initPars[5]},${initPars[6]},${initPars[7]}"
    args="$args,$ktDifferential"

    echo $args
    
root -b <<EOF
.x fitManager.C($args)
EOF

}

directory=output_histograms

####### Fitting widePt results ####### 
# Multiplicity differential - kt integrated
fileTag=4x5GeVFemto_widePt
outFile=${fileTag}_multiplicity_FitResults.root
pm=0
ktBin=4
ktDifferential=0

for((i=0; i <= 5; i++))
do
    inFile=$directory/${fileTag}_multBin_${i}.root
    logFile=${fileTag}_${i}.log
    multBin=$i
    echo "Fitting widePt multBin $i - kt integrated"
    fit $inFile $outFile $pm $ktBin $multBin $ktDifferential >& $logFile
done

# 0-5% central - lowest kt bin
outFile=${fileTag}_lowKt_FitResults.root
inFile=$directory/${fileTag}_multBin_5.root
logFile=${fileTag}.log
multBin=5
ktBin=0
ktDifferential=0
echo "Fitting widePt multBin 5 - lowKt"
fit $inFile $outFile $pm $ktBin $multBin $ktDifferential >& $logFile

# 0-15% central - kt differential
multbin=0
inFile=$directory/${fileTag}_multBins_3to5.root
outFile=${fileTag}_kt_FitResults.root
ktDifferential=1
for((i=0; i <= 3; i++))
do
    logFile=0to15percentCentral_widePt_kt_${i}.log
    ktBin=$i
    echo "Fitting widePt - 0-15% - ktBin $i"
    fit $inFile $outFile $pm $ktBin $multBin $ktDifferential >& $logFile
done


####### Fitting narrowPt results ####### 
fileTag=4x5GeVFemto_narrowPt
inFile=$directory/${fileTag}.root
outFile=${fileTag}_FitResults.root
logFile=${fileTag}.log
multBin=0   # Doesn't matter, since narrowPt isn't differential in multiplicity
ktBin=4
pm=-1       # Only pi- pairs
ktDifferential=0
echo "Fitting narrowPt - kt integrated"
fit $inFile $outFile $pm $ktBin $multBin $ktDifferential >& $logFile

# Fit narrowPt results for each kt bin
ktDifferential=1
pm=-1
outFile=${fileTag}_kt_FitResults.root
for((i=0; i <= 3; i++))
do
    logFile=${fileTag}_ktBin_${i}.log
    ktBin=$i
    echo "Fitting narrowPt - ktBin $i"
    fit $inFile $outFile $pm $ktBin $multBin $ktDifferential >& $logFile
done


