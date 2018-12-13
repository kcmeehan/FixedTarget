#!/bin/tcsh
setenv STAR_LEVEL SL16a
if ( -e $GROUP_DIR/group_env.csh ) then
        source $GROUP_DIR/group_env.csh
endif

root4star -b -q cuts_ks_$1.C+\(0,50000,0,1\) 
root4star -b -q cuts_ks_$1.C+\(0,50000,1,1\) 
root4star -b -q cuts_ks_$1.C+\(0,50000,0,0\) 
root4star -b -q cuts_ks_$1.C+\(0,50000,1,0\) 
