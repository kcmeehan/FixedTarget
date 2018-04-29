#/bin/bash

scratchRoot=/gpfs/mnt/gpfs01/star/scratch/$USER/fxtHbt

star-submit-template -template submitHadd.xml -entities scratchRoot=$scratchRoot,fileGlob=4x5GeVFemto_narrowPt

for((i=0; i<=5; i++)); do
    star-submit-template -template submitHadd.xml -entities scratchRoot=$scratchRoot,fileGlob=4x5GeVFemto_widePt_multBin_${i}
done
