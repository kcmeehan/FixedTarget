# DavisDstMaker

***
Authors: This code was first written by Christopher Flores, UC Davis (https://bitbucket.org/chris_flores/davisdstanalysis/) and further edited by Kathryn Meehan, UC Davis (https://bitbucket.org/kmeehan713/kathryns-stdatacollector-version).
***


***
Use: Code that produces "davisdsts" from STAR mudsts. This code is currently configured for the 2015 Au + Au 4.5 GeV center-of-mass energy STAR fixed-target collisions. This code is meant to run on RCF by running:

star-submit AuAu_4_5_2015_kmeehan.xml

This xml file can be written so as to do a file query instead of taking a file list. When doing the query, care must be taken to only obtain the run numbers of interest since many of the earlier run numbers are bad. 

*IMPORTANT NOTE*: The library used when making the Davisdsts for the pi minus analysis was SL15e. At the time of this README this library is no longer on RCF, but SL15e_embed is still available. 
***


***
Other files in the repository:
The run number list is: AuAu_4_5_2015_official_runnumberSelected.list
It contains the paths to the 121 MuDsts used in this analysis. Note that the paths to these files might change, so to obtain their new location one might need to run a query:

get_file_list.pl -keys 'node,path,storage' -cond 'trgsetupname=fixedTarget2015,production=P16ia,filetype=daq_reco_MuDst,path~140, runnumber>16140032' -onefile -limit 0 | wc

Requiring the path to contain 140 removes files from the 2015 Al + Au dataset and the runnumber requirement removes bad runs. 
***


***
RunStDataCollectorMaker.C runs the chain of makers that produces Davisdsts from Mudsts. The RefMultCorr class mentioned in the macro is not used in the FXT analysis. None of the cuts that can be set in the .xml file are used so they are all set to their default values.
***


***
The StRoot directory containts the heart of the code used to make the DavisDsts in the StDataCollectionMaker class as well as three helper classes, EventInfo, PrimaryVertexInfo, and TrackInfo. The StRefMultCorr class was used for BES-I analyses and is not used in the FXT analysis. The function IsGoodEvent() is used when making the FXT Davisdsts to remove events with no primary vertices.
***





