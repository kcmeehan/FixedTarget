#! /bin/bash

fit() {

    inFile=$1
    outFile=$2
    multBin=$3

    ktBin=4
    pm=$4 # -1=piMinus, +1=piPlus, 0=both
    projRange=0.03

    declare -a initPars=(0.17 0.486 10 10 10 0 0 0)

root -b <<EOF
.x fitManager.C("$inFile","$outFile",$pm,$ktBin,$multBin,0.149,${projRange},${initPars[0]},${initPars[1]},${initPars[2]},${initPars[3]},${initPars[4]},${initPars[5]},${initPars[6]},${initPars[7]})
EOF

}

directory=output_histograms

# Fit highPt results for each multiplicity bin
fileTag=4x5GeVFemto_highPt
outFile=${fileTag}_FitResults.root

for((i=0; i <= 5; i++))
do
    inFile=$directory/${fileTag}_multBin_${i}.root
    logFile=${fileTag}_multBin_${i}.log
    echo "Fitting highPt multBin $i"
    fit $inFile $outFile $i 0 >& $logFile
done

# Fit lowPt results
fileTag=4x5GeVFemto_lowPt
inFile=$directory/${fileTag}.root
outFile=${fileTag}_FitResults.root
logFile=${fileTag}.log
echo "Fitting lowPt"
fit $inFile $outFile 0 -1 >& $logFile # Technically this assigns the lowPt fit
                                      # to the zeroth mult bin, which is incorrect.
                                      # But the mult bin is irrelevant for lowPT,
                                      # so it's fine.
