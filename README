
This code was designed for use on PDSF to run over the embedding minimc files and produce embedding QA.
It also produces the histograms that code from the main davisdstanalysis repository needs to make the TPC acceptance + efficiency and energy loss correction curves. 
The output can be copied to menkar/nuclear and passed as input to RunMakeEmbeddingCorrectionCurves.C

Before running this code a CSV file with the centrality bin of each event must have been created using the RunCreateCentralityDatabaseCSV.sh script in the
main davisdstsanalysis repository. Execute the code with star-submit:

star-submit RunProcessEmbedding.xml

The user should set the path for the log, scheduler, and output files. In addition, the user should verify the path to the input list of minimc files, the path to the centrality database CSV, and the paths in the sandbox are correct. The rest of the xml script should already be properly configured.
