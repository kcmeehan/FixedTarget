#!/bin/bash
tag=4x5GeVFemto_narrowPt

# for((i=0; i<=5; i++))
for((i=0; i<=0; i++))
do
    star-submit-template -template submitFxtFemtoAnalysis.xml -entities multBin=$i,fileTag=$tag
done
