#!/bin/bash

# ENVIRONMENT
OLD_VER=$(cat Version)
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

# Updates the CHANGELOG.md
if ! grep -c "\[$VER\]" CHANGELOG.md >/dev/null; then
    sed -i 's/\[unreleased\]: https:\/\/github.com\/BiltuDas1\/qsort\/compare\/0.3.2-beta...pre\/beta/\['$VER'\]: https:\/\/github.com\/BiltuDas1\/qsort\/compare\/'$OLD_VER'...'$VER'/' CHANGELOG.md
    sed -i 's/\[unreleased\]/\['$VER'\] - '$(date +%F)'/' CHANGELOG.md
    sed -i 's/'$OLD_VER'/'$VER'/' Version

    fp=$(grep -n "##" CHANGELOG.md | head -1 | cut -f1 -d:)
    cat CHANGELOG.md | head -$((fp-1)) > CHANGELOG.md.swap
    echo \#\# \[unreleased\] >> CHANGELOG.md.swap
    echo - There\'s Nothing but Crickets ¯\\\_\(ツ\)_/¯ >> CHANGELOG.md.swap
    echo >> CHANGELOG.md.swap

    sp=$(grep -n "\-\-\-" CHANGELOG.md | cut -f1 -d:)
    cat CHANGELOG.md | head -$sp | tail +$fp >> CHANGELOG.md.swap
    echo >> CHANGELOG.md.swap
    echo \[unreleased\]: https://github.com/BiltuDas1/qsort/compare/$VER...pre/beta >> CHANGELOG.md.swap
    cat CHANGELOG.md | tail +$((sp+2)) >> CHANGELOG.md.swap
    
    rm CHANGELOG.md
    mv CHANGELOG.md.swap CHANGELOG.md
fi