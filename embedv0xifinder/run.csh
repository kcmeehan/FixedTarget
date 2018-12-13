#!/bin/tcsh
setenv STAR_LEVEL SL16a_embed
if ( -e $GROUP_DIR/group_env.csh ) then
        source $GROUP_DIR/group_env.csh
endif

root4star -b -q reconstruct_mcv0_$3.C\(\"$1\",$2,1,0,\"$4/\"\) 
