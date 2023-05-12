#!/bin/bash

# ENVIRONMENT
VER=$1

ver=$(echo $VER | cut -f1 -d-)
vertype=$(echo $VER | cut -f2 -d-)
userver=$(grep -n "const string ver = \"" lib/user.hpp | head -1 | awk '{print $5}' | cut -f2 -d\")
uservertype=$(grep -n "const string vertype = \"" lib/user.hpp | head -1 | awk '{print $5}' | cut -f2 -d\")

# Updates the version information into user.hpp
if [[ "$ver" != "$userver" ]]; then
    sed -i 's/const string ver = "'"$userver"'";/const string ver = "'"$ver"'";/' lib/user.hpp
fi

# Updates the version type into user.hpp
if [[ "$vertype" != "$uservertype" ]]; then
    sed -i 's/const string vertype = "'"$uservertype"'";/const string vertype = "'"$vertype"'";/' lib/user.hpp
fi