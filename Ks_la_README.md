For K0s and Lambda Analysis

1) mudstv0xifinder:
The codes for K0s and Lambda reconstruction from MuDst for AuAu FXT at 4.5 GeV.
To compile, use 'starver SL16a_embed', 'cons'.
To submit the jobs, first create directories "batch", "log", "output",
then use 'star-submit Scheduler.xml', the "output" directory contains the picodst.root files for further offline analysis.

2) offlinecut:
The code for applying further offline cuts for K0s/Lambda on the picodst.root, and filling invariant mass histograms.
To run it, one needs to first generate the list of the picodst.root files, for example, the 'finished_ks.list/finished_ksrot.list' for K0s,
then 'starver SL16a_embed', 'cons' to compile the code under StRoot, finally use './runcuts.sh ks' to run the 'cuts_ks_cut0.C' script. The code for Lambda is 'cuts_la_cut0.C', use './runcuts.sh K0s' and './runcuts.sh la'  run them respectively. The output is the histogram root files under 'output' directory.

3) embedv0xifinder:
The codes for K0s and Lambda reconstruction from embedding data.
To run it, one needs to first generate the list of embedding .geant.root files, find examples in 'lists' sub-directory for AuAu FXT at 4.5 GeV,
one also needs to generate a root tree for each daq file to record the reference multiplicity of the embedded events from real data mudst.  Then, logon to PDSF farm, run 'starver SL16a_embed', 'cons' to compile the code under StRoot. Finally use './submit.sh k0s lists/k0sfp_100_119.list' to submit the jobs for the list of 'k0sfp_100_124.list', the jobs for other lists should be submitted to PDSF farm in similar way.
The output picodst can be found in 'output.k0sfp_100_119',... One can use hadd to merge them into one pico.root file for further efficiency analysis.

4) embedpicocut:
The code for applying further offline cuts for K0s/Lambda (for AuAu FXT at 4.5 GeV) on the embedding pico.root, and obtain the quantities for efficiency calculation.
To run it, one needs to first generate the list of the pico.root files, for example, the 'k0sfp_100_119.pico.list' for K0s flat pT sample,
then 'starver SL16a_embed', 'cons' to compile the code, finally use './runcuts.sh ks' to run the 'cuts_ks_cut0.C' script. The code for Lambda is 'cuts_la_cut0.C', use './runcuts.sh la to run. The output is the .txt files under 'output' directory.

5) spectra:
'ks' directory is the code for Ks AuAu FXT at 4.5 GeV, one needs to download both the histo.root (from step 2) and weight*txt (from step 4) to 'output' subdirectory. The script 'draws_ks_cut0.C' is for invariant mass fitting and signal yield extraction. The scripts 'spectra_ks_corr_low_cut0.C', 'spectra_ks_corr_high_cut0.C', and 'spectra_ks_corr_all_cut0.C' is for obtaining the pT spectra and yields, one should run them one after another.
'la' directory is the code for Lambda at 39 GeV, one needs to download both the histo.root (from step 2) and weight*txt (from step 4) to 'output' subdirectory. The script 'draws_la_cut0.C' is for invariant mass fitting and signal yield extraction. The scripts 'spectra_la_corr_low_cut0.C', 'spectra_la_corr_high_cut0.C', and 'spectra_la_corr_all_cut0.C' is for obtaining the pT spectra and yields, one should run them one after another.

For systematic errors, one should change the analysis cuts, and check the variations of pT spectra.
