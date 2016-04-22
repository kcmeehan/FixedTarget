#!/bin/bash
tag=4x5GeVFemto_widePt_excludeHighMult

for((i=5; i<=5; i++))
do
    star-submit-template -template submitFxtFemtoAnalysis.xml -entities multBin=$i,fileTag=$tag
done
