#!/bin/sh 

particle=$1
filename=$2
blocksize="10"
title=`basename $filename .list`
outdir="output.${title}"
if [ ! -d $outdir ]; then
   mkdir $outdir
fi

nfile=`wc $filename | awk '{print $1}'` 
njob=$(($nfile/$blocksize))
rest=$(($nfile%$blocksize))
if [ $rest -gt "0" ] ; then
   njob=$(($njob+1))
fi

for (( i=0 ; $i - $njob ; i++ )) 
do
   echo $i
   qsub -l projectio=1,projectaio=1 -hard -o /dev/null -e /dev/null run2.csh $filename $i $blocksize $particle $outdir
   #condor_run "./run2.csh $filename $i $blocksize $particle $outdir > /dev/null" > /dev/null 2> /dev/null & 
   sleep 0.3
done
