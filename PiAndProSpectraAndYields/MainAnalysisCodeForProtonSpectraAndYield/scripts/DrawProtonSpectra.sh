#!/bin/sh

#root -q -l -b ../macros/DrawProtonSpectra.C\(\"../rootfiles/proton_AlAu_THERMAL.root\",\"FixedTarget2015\",\"Al+Au\",4.9,0\)
#root -q -l -b ../macros/DrawProtonSpectra.C\(\"../rootfiles/proton_AlAu_THERMAL.root\",\"FixedTarget2015\",\"Al+Au\",4.9,1\)
#root -q -l -b ../macros/DrawProtonSpectra.C\(\"../rootfiles/proton_AlAu_THERMAL.root\",\"FixedTarget2015\",\"Al+Au\",4.9,2\)
#root -q -l -b ../macros/DrawProtonSpectra.C\(\"../rootfiles/proton_AlAu_THERMAL.root\",\"FixedTarget2015\",\"Al+Au\",4.9,3\)
#root -l ../macros/DrawProtonSpectra.C\(\"../rootfiles/proton_AlAu_THERMAL.root\",\"FixedTarget2015\",\"Al+Au\",4.9,4\)
#root -q -l -b ../macros/DrawProtonSpectra.C\(\"../rootfiles/proton_AlAu_THERMAL.root\",\"FixedTarget2015\",\"Al+Au\",4.9,5\)
root -l -q -b ../drawingmacros/DrawProtonSpectra.C\(\"../userfiles/AuAu_4_5GeV_2015/analysis/protondNdyFit.root\",\"FixedTarget2015\",\"Au+Au\",4.5\)
