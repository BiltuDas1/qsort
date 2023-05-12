#!/bin/bash

# ENVIRONMENT
VER=$1

# Updates the version into control
default=$(cat DEBIAN/control | grep "Version" | awk '{print $2}')
if [[ "$default" != "$VER" ]]; then
    sed -i 's/Version: '"$default"'/Version: '"$VER"'/' DEBIAN/control
fi

# Updates total installed size
default=$(cat DEBIAN/control | grep "Installed-Size" | awk '{print $2}')
compiled=$(ls -l build/qsort | awk '{print $5}')
compiled=$((compiled/1024))
if [[ "$compiled" -ne "$default" ]]; then
    sed -i 's/Installed-Size: '"$default"'/Installed-Size: '"$compiled"'/' DEBIAN/control
fi