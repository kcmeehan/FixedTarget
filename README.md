# DavisDstMaker
Code that produces "davisdsts" from STAR mudsts. This code is currently configured for the 2015 Au + Au 4.5 GeV center-of-mass energy STAR fixed-target collisions. This code is meant to run on RCF by running:

star-submit AuAu_4_5_2015_kmeehan.xml

*NOTE: The library used when making the Davisdsts for the pi minus analysis was SL15e. At the time of this README this library is no longer on RCF, but SL15e_embed is still available. 

This xml file can be written so as to do a file query instead of taking a file list. When doing the query, care must be taken to only obtain the run numbers of interest since many of the earlier run numbers are bad. 
