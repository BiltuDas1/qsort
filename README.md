# Quick File Sorter
A quicker way to sort files using one command

## How it works
It reads all extensions data from extensions.json and then load into different groups(C++ Strings) and read the qsort.conf file and move files to specific path according to the matched extensions using the C++ std::filesystem::rename.

### Building & Installing

```
git clone https://github.com/BiltuDas1/qsort.git
cd qsort/
make
sudo make install
```

### Source Code Building
|Task Name|`main`|`pre/beta`|
|---------|------|----------|
|AutoCheck|![AutoCheck](https://github.com/BiltuDas1/qsort/actions/workflows/autoscript.yml/badge.svg?branch=main)|![AutoCheck](https://github.com/BiltuDas1/qsort/actions/workflows/autoscript.yml/badge.svg?branch=pre/beta)|
|Release|![Release](https://github.com/BiltuDas1/qsort/actions/workflows/release.yml/badge.svg?branch=main)| Not Applicable :x: |

### Parameters
Use `qsort --help` to see what parameters it supports.

### Speed
I can't gurentee that the speed will be same into your own Condition, but here is the speed for my personal laptop

![Sorting Speed](.github/Speed.png)

It took about 7 second to sort 100k + 2 files

Processor: Intel Core i5 M460 @ 2.53GHz  
RAM: 6GiB  
Hard Disk: HS-SSD-E100 256G