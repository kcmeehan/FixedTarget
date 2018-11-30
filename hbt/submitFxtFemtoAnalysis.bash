#!/bin/bash
narrowPtTag=4x5GeVFemto_narrowPt
widePtTag=4x5GeVFemto_widePt
scratchRoot=/gpfs/mnt/gpfs01/star/scratch/$USER/fxtHbt

# Loop over multiplicity bins for low pt analysis
for((i=4; i<=5; i++))
do
    star-submit-template -template submitFxtFemtoAnalysis.xml -entities multBin=$i,fileTag=$narrowPtTag,minPt=0.1,maxPt=0.3,scratchRoot=$scratchRoot
done

# Loop over multiplicity bins for high pt analysis
for((i=0; i<=5; i++))
do
    star-submit-template -template submitFxtFemtoAnalysis.xml -entities multBin=$i,fileTag=$widePtTag,minPt=0.15,maxPt=0.8,scratchRoot=$scratchRoot
done
