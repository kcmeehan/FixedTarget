#!/bin/bash
lowPtTag=4x5GeVFemto_lowPt
highPtTag=4x5GeVFemto_highPt
# tag=4x5GeVFemto_widePt_excludeHighMult

# Loop over centrality bins
for((i=0; i<=5; i++))
do
    star-submit-template -template submitFxtFemtoAnalysis.xml -entities multBin=$i,fileTag=$lowPtTag,minPt=0.1,maxPt=0.3
    star-submit-template -template submitFxtFemtoAnalysis.xml -entities multBin=$i,fileTag=$highPtTag,minPt=0.15,maxPt=0.8
done
