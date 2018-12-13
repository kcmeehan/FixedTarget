#!/bin/sh
start=$(($3*$2))
end=$(($3*($2+1)))
for (( i=$start ; $i - $end ; i++ )) 
do
echo $i
./run.csh $1 $i $4 $5
sleep 1
done
