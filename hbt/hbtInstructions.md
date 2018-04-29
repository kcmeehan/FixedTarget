# Instructions for Running the FXT Femtoscopy Analysis

## Overview
There are four separate sets of analysis cut used to make the various figures for the HBT section.

### Narrow pt, integrated kt, pi-pi- pairs
In order to match with the E895 data, the following cuts are used for the correlation function figure and the excitation function figure:

 * Pion p_T: 0.1 GeV - 0.3 GeV
 * Only pi-pi- pairs
 * Pair k_T: 0.15 GeV to 0.6 GeV
 * Centrality: 0-10%

### Wide pt, integrated kt, pi-pi- pairs
In order to match with the E866 data, the following cuts are used for the m_T dependence figure:

 * Pion p_T: 0.1 GeV - 0.8 GeV (E866 had an upper cut of p < 1.85 GeV, but pion spectrum is negligable after 0.8 GeV)
 * Only pi-pi- pairs
 * Pair k_T: 0.15 GeV to 0.6 GeV in 4 bins
 * Centrality: 0-15%

### Wide pt, integrated kt, pi-pi- and pi+pi+ pairs
The figure that shows the centrality dependence of the radii doesn't compare with other experiments, so we use standard STAR HBT cuts:

 * Pion p_T: 0.1 GeV - 0.8 GeV
 * pi-pi- and pi+pi+ pairs
 * Pair k_T: 0.15 GeV to 0.6 GeV
 * Centrality: 0-30% in 5% bins

### Wide pt, low kt, pi-pi- and pi+pi+ pairs
In order to match the STAR BES and ALICE data, the following cuts are used for the R_side vs. R_long figure:

 * Pion p_T: 0.1 GeV - 0.8 GeV
 * pi-pi- and pi+pi+ pairs
 * Pair k_T: 0.15 GeV to 0.25 GeV
 * Centrality: 0-5%

 The analysis is done in two main steps.
 First you must run over the data on RCF to create the HBT histogram files.
 Second you must fit the histograms to extract the HBT radii.
 This second step should be done on your local laptop or workstation.


## Making Histograms
The steps in this section should be performed on RCF.
Download the code from the github repository.
Move to the directory where the hbt code is stored and run the `setup.sh` script.
This will create some directories in your scratch space and compile the code.
The code should take several minutes to compile.

```shell
git clone https://github.com/DavidTlusty/FixedTarget 
cd FixedTarget/hbt
./setup.sh
```

Once the code has compiled, you can submit the femtoscopy jobs with the `submitFxtFemtoscopy.bash` submission script.

```shell
./submitFxtFemtoAnalysis.bash
```

This script starts 8 batches of jobs on RCF: one batch for each of six centrality bins for the wide pT analysis, and one batch for the two most central bins for the narrow pT analysis.
The job submission should take 5-10 minutes, and the jobs will take several hours to complete.
Once the jobs have completed, the output and logs will be stored in the scratch directories created by the `setup.sh` script.

You can `hadd` the files together with the `submitHadd.bash` script, which will combine the two centrality bins for the narrow pT analysis, and give six seperate output files for the wide pT analysis.

```shell
./submitHadd.bash
```

In the next section you'll copy the files to your local machine to fit the histograms.
Once the `hadd` jobs have finished, move the output files to a temporary location in your home directory for easy `scp`'ing.
Finally, there's one manual `hadd` to do to get a combined 0-15% centrality file for the widePt analysis.

```shell
mkdir ~/tempHbtOutput
cp /gpfs/mnt/gpfs01/star/scratch/$USER/fxtHbt/*root ~/tempHbtOutput
cd ~/tempHbtOutput
hadd 4x5GeVFemto_widePt_multBins_3to5.root 4x5GeVFemto_widePt_multBin_{3..5}.root
```

## Fitting the histograms
The steps in this section should be performed locally.
Fitting the histograms to get the HBT radii is not very computationally intensive, and is easiest to do on your local laptop or workstation.
Clone the github repository to a local directory, and copy the HBT histogram files from RCF.

```shell
git clone https://github.com/DavidTlusty/FixedTarget 
cd FixedTarget/hbt/fitting
./copyScript.bash [RCF username] tempHbtOutput
```

The script `copyScript.bash` takes two arguments: the first is your RCF username and the second is the name of the temporary directory where you placed the HBT histogram files.
It will copy the files to the `output_histograms` directory.
You may then fit the histograms using the `runFits.bash` script.

```shell
./runFits.bash
```

After you've run the fits, you can make the HBT plots with the `drawAllFigures.C` script.

```shell
root drawAllFigures.C
```
