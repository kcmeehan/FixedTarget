#! /bin/bash

rcfName=$1
rcfDirectory=/star/u/$1/$2
rcfUrl=rftpexp.rhic.bnl.gov

# Copy the output files for each multiplicity bin
# AND convert from multiplicity bin to centrality bin
for((mult=0; mult<=5; mult++))
do
    cent=$((6-$mult))

    sourceFilename=4x5GeVFemto_lowPt_multBin_$mult.root
    destinationFilename=4x5GeVFemto_lowPt_cent_$cent.root
    scp $rcfName@$rcfUrl:$rcfDirectory/$sourceFilename output_histograms/$destinationFilename

    sourceFilename=4x5GeVFemto_highPt_multBin_$mult.root
    destinationFilename=4x5GeVFemto_highPt_cent_$cent.root
    scp $rcfName@$rcfUrl:$rcfDirectory/$sourceFilename output_histograms/$destinationFilename
done
