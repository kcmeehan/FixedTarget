#!/usr/local/bin/tcsh
setenv STAR_LEVEL SL10k_embed
if ( -e $GROUP_DIR/group_env.csh ) then
        source $GROUP_DIR/group_env.csh
endif

root4star -b -q reconstruct_v0.C\(\"$1\",$2,$3,\"$4\",\"$5\"\)
