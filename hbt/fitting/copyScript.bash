#! /bin/bash

# Run this script using:
#    copyScript.bash [rcfName] [rcfDirectory]
# where [rcfName] is your user name on RCF and [rcfDirectory] is the directory
# on RCF where the output histograms are stored, most likely somewhere in your
# scratch space.
#
# This script will copy the files to the output_histograms directory.


rcfName=$1
rcfDirectory=/star/u/$1/$2
rcfUrl=rftpexp.rhic.bnl.gov

# Copy the output files for each multiplicity bin of the high-pt analysis
for((mult=0; mult<=5; mult++))
do
    fileName=4x5GeVFemto_widePt_multBin_$mult.root
    scp $rcfName@$rcfUrl:$rcfDirectory/$fileName output_histograms/$fileName
done

# Copy the output file for the 0-15% central widePt analysis
fileName=4x5GeVFemto_widePt_multBins_3to5.root
scp $rcfName@$rcfUrl:$rcfDirectory/$fileName output_histograms/$fileName

# Copy the output files for the low-pt analysis
fileName=4x5GeVFemto_narrowPt.root
scp $rcfName@$rcfUrl:$rcfDirectory/$fileName output_histograms/$fileName
