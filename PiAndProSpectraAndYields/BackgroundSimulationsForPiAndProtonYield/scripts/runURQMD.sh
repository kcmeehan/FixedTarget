#!/bin/bash

inputFile=$1  #path and name of the input file
outDir=$2     #path to the output directory where the .f files will be saved
energyName=$3    #energy name that will be used as part of the output file name structure
extension=$4     #an additional parameter to distinguish between output files (usually an integer)

name="$energyName"_$extension

#Set up for UrQMD
export ftn09=$inputFile
export ftn13=$outDir/$name.f13
export ftn14=$outDir/$name.f14
export ftn15=$outDir/$name.f15
export ftn16=$outDir/$name.f16
export ftn19=$outDir/$name.f19
export ftn20=$outDir/$name.f20

if [ "$HOSTNAME" != "menkar" ]
then
    cd ../urqmd-3.4_SL/
else
    cd ../urqmd-3.4/

fi

time ./urqmd.x86_64

rm $ftn14 $ftn15 $ftn19 $ftn20 $ftn16

