#!/bin/bash

# ENVIRONMENT
VER=$1
OLD_VER=$(cat Version)

# Updates the CHANGELOG.md
if ! grep -c "\[$VER\]" CHANGELOG.md >/dev/null; then
    sed -i 's/\[unreleased\]: https:\/\/github.com\/BiltuDas1\/qsort\/compare\/0.3.2-beta...pre\/beta/\['$VER'\]: https:\/\/github.com\/BiltuDas1\/qsort\/compare\/'$OLD_VER'...'$VER'/' CHANGELOG.md
    sed -i 's/\[unreleased\]/\['$VER'\] - '$(date +%F)'/' CHANGELOG.md
    sed -i 's/'$OLD_VER'/'$VER'/' Version

    fp=$(grep -n "##" CHANGELOG.md | head -1 | cut -f1 -d:)
    cat CHANGELOG.md | head -$((fp-1)) > CHANGELOG.md.swap
    echo \#\# \[unreleased\] >> CHANGELOG.md.swap
    echo - There\'s Nothing but Crickets ¯\\\\_\(ツ\)_/¯ >> CHANGELOG.md.swap
    echo >> CHANGELOG.md.swap

    sp=$(grep -n "\-\-\-" CHANGELOG.md | cut -f1 -d:)
    cat CHANGELOG.md | head -$sp | tail +$fp >> CHANGELOG.md.swap
    echo >> CHANGELOG.md.swap
    echo \[unreleased\]: https://github.com/BiltuDas1/qsort/compare/$VER...pre/beta >> CHANGELOG.md.swap
    cat CHANGELOG.md | tail +$((sp+2)) >> CHANGELOG.md.swap
    
    rm CHANGELOG.md
    mv CHANGELOG.md.swap CHANGELOG.md
fi

echo qsort_v"$VER"_1_amd64.deb >.gitignore
echo build >.gitignore
echo .gitignore >>.gitignore

cmake -B build .
cd build/
make deb
cd ..
mv "qsort-debian.deb" "qsort_v"$VER"_1_amd64.deb"