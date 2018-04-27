# Instructions for Running the FXT Femtoscopy Analysis

## Making Histograms
The steps in this section should be performed on RCF.
Download the code from the github repository.
(You may first need to start an ssh-agent and add a key to it.)

```shell
eval `ssh-agent`                    # May not be necessary, depending
ssh-add ~/.ssh/[github key file]    # on how your ssh agent is setup.
git clone https://github.com/DavidTlusty/FixedTarget 
```

Move to the directory where the hbt code is stored and run the `setup.sh` script.
This will create some directories in your scratch space and compile the code.
The code should take several minutes to compile.

```shell
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

You can `hadd` the files together with the `submitHadd.bash` script, which will combine the two centrality bins for the low pT analysis, and give six seperate output files for the high pT analysis.

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
hadd 4x5GeVFemto_highPt_multBins_3to5.root 4x5GeVFemto_highPt_multBin_{3..5}.root
```

## Fitting the histograms
The steps in this section should be performed locally.
Fitting the histograms to get the HBT radii is not very computationally intensive, and is easiest to do on your local laptop or workstation.
Clone the github repository to a local directory, and copy the HBT histogram files from RCF.

```shell
eval `ssh-agent`                    # May not be necessary, depending
ssh-add ~/.ssh/[github key file]    # on how your ssh agent is setup.
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
