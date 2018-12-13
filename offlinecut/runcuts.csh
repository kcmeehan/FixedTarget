#!/bin/tcsh
setenv STAR_LEVEL SL16a_embed
if ( -e $GROUP_DIR/group_env.csh ) then
        source $GROUP_DIR/group_env.csh
endif

root4star -b -q cuts_$1_cut0.C\(0,10000\) 
