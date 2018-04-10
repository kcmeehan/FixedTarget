#!/bin/bash

#This script takes a list of root files and hadds them into a smaller
#number of files such that no new file is larger than a maximum size.

#USEAGE (this is aliased to grouphadd
#  grouphadd <maxFileSizeInMB> <outputFileBaseName> <filesToAdd>

#EXAMPLE
#  grouphadd 3000 AuAl_3_0_2010 *.root

#The Array of all arguments
args=( $@ )

#Constants
maxFileSize=${args[0]}                 #Maximum files size of resulting hadded file in MB
fileBaseName=${args[1]}                #Basename to be used for the output file
fileList=( ${args[@]:2:${#args[@]}} )  #List of files to be considered for adding
nFilesInList=${#fileList[@]}

#Variables
totalFilesAdded=0                      #Count of total files added
groupCounter=0                         #The nth group of files to be added
fileSize=0                             #The total size of the files to be added
filesToAdd=()                          #List of files to be added
currentFileSize=0                      #The size of the current file

for file in ${fileList[@]}; do

    #Get the size of the current file
    currentFileSize=$(du -h --block-size=MB $file | cut -f1 | cut -d "M" -f1)

    #If the current file has a size which is greater than 80% of the maxFileSize
    #then simply rename it

    echo "currentFileSize: " $currentFileSize
    currentFilePercentage=$(echo "$currentFileSize*100/$maxFileSize" | bc -l | cut -d"." -f1)

    if [ -z "$currentFilePercentage" ]; then
	currentFilePercentage=0
    fi

    if [ $currentFilePercentage -ge 80 ]; then
	echo "copying $file to" "$fileBaseName"_$groupCounter.root $currentFileSize
	cp $file "$fileBaseName"_$groupCounter.root
	groupCounter=$(($groupCounter+1))
	continue
    fi
    
    #Add the current file to the list of files to be hadded
    filesToAdd=("${filesToAdd[@]}" "$file")

    #Check to see if the filesize of the list of files to be added is larger
    #than maxFileSize. If it is then hadd the files and reset the variables.
    #Add the file size of the current file to the total fileSize of the files to be added
    fileSize=$(($fileSize+$currentFileSize)) 
    totalFilesAdded=$(($totalFilesAdded+1))

    #Check if fileSize is greater than maxFileSize. If it is then hadd the current
    #list of filesToAdd, increment the group counter, and reset variables.
    if [[ $fileSize -ge $maxFileSize ]] || [[ $totalFilesAdded -eq $nFilesInList ]]; then
	echo "Adding now" "$fileBaseName"_$groupCounter.root $fileSize
	nice hadd "$fileBaseName"_$groupCounter.root "${filesToAdd[@]}"

	groupCounter=$(($groupCounter+1))
	fileSize=0
	unset filesToAdd
	filesToAdd=()
	
    fi

done
