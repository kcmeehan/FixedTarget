# Instructions for Running the FXT Femtoscopy Analysis

## Making Histograms
The steps in this section should be performed on RCF.
Download the code from the github repository.
(You may first need to start an ssh-agent and add a key to it.)

```shell
eval `ssh-agent`
ssh-add ~/.ssh/[github key file]
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

