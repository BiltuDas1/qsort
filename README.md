# Quick File Sorter
Quick File Sorter is a command-line tool for automatically sorting files based on their file extension. It can sort various types of files, such as documents, images, music, and videos, into their respective folders. This tool can save you a lot of time and effort in manually sorting your files.

## Features
* Automatically sorts files based on their file extensions
* Supports various types of files, such as documents, images, music, and videos
* Easy to configure using qsort.conf file
* Available as a command-line tool
Supports for Linux

## How it works
Quick File Sorter reads all extension data from extensions.json and loads them into different groups using C++ strings. It then reads the qsort.conf file and moves files to a specific path based on the matched extensions using the C++ std::filesystem::rename function.

## Building & Installing
You can build the source code yourself by cloning the repository and running the following commands:

```
git clone https://github.com/BiltuDas1/qsort.git
cd qsort/
cmake -B build .
cd build/
sudo make install
```
Note: It requires CMake 3.22 or higher  
Alternatively, you can download pre-built binaries from the releases page.

### Source Code Building
|Task Name|`main`|`pre/beta`|
|---------|------|----------|
|AutoCheck|![AutoCheck](https://github.com/BiltuDas1/qsort/actions/workflows/autoscript.yml/badge.svg?branch=main)|![AutoCheck](https://github.com/BiltuDas1/qsort/actions/workflows/autoscript.yml/badge.svg?branch=pre/beta)|
|Release|![Release](https://github.com/BiltuDas1/qsort/actions/workflows/release.yml/badge.svg?branch=main)| Not Applicable :x: |

## Usage
Once installed, simply navigate to the directory containing the files you want to sort and enter the `qsort` command. Quick File Sorter will automatically sort files to their respective type of documents (i.e doc, ppt, pdf all those file will be moved into Document Folder).


### Parameters
Use `qsort --help` to see what parameters it supports.

### Speed
I can't gurentee that the speed will be same into your own Condition, but here is the speed for my personal laptop

![Sorting Speed](.github/Speed.png)

It took about 7 second to sort 100k + 2 files

Processor: Intel Core i5 M460 @ 2.53GHz  
RAM: 6GiB  
Hard Disk: HS-SSD-E100 256G

## License
This project is licensed under [MIT License](/LICENSE)

## Contributing
Contributions to Quick File Sorter are welcome and encouraged! To contribute, please create a pull request with your proposed changes.