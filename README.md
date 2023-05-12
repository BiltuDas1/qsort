![Downloads](https://img.shields.io/github/downloads/BIltuDas1/qsort/total?style=social)
# Quick File Sorter
Quick File Sorter is a command-line tool for automatically sorting files based on their file extension. It can sort various types of files, such as documents, images, music, and videos, into their respective folders. This tool can save you a lot of time and effort in manually sorting your files.

## Features
* This tool automatically sorts files based on their file extensions and mime types, although it currently does not support document type files.
* It supports various types of files including images, music, and videos, as well as documents.
* Configuration is easy through the use of the qsort.conf file.
* This tool is available as a command-line tool.

## How it works
Quick File Sorter reads all extension data from extensions.json and loads them into different groups using C++ strings. It then reads the qsort.conf file and moves files to a specific path based on the matched extensions using the C++ std::filesystem::rename function.

## Requirements

* CMake 3.22 or higher
* libmagic-dev

## Building & Installing
You can build the source code yourself by cloning the repository and running the following commands:

```
git clone https://github.com/BiltuDas1/qsort.git
cd qsort/
cmake -B build .
cd build/
sudo make install
```
Alternatively, you can download pre-built binaries from the releases page.

### Source Code Building
|Task Name|`main`|`pre/beta`|
|---------|------|----------|
|AutoCheck|![AutoCheck](https://github.com/BiltuDas1/qsort/actions/workflows/autoscript.yml/badge.svg?branch=main)|![AutoCheck](https://github.com/BiltuDas1/qsort/actions/workflows/autoscript.yml/badge.svg?branch=pre/beta)|
|Release|![Release](https://github.com/BiltuDas1/qsort/actions/workflows/release.yml/badge.svg?branch=main)| Not Applicable :x: |

## Usage
Once installed, simply navigate to the directory containing the files you want to sort and enter the `qsort` command. Quick File Sorter will automatically sort files to their respective type of documents (i.e doc, ppt, pdf all those file will be moved into Document Folder).


### Parameters
|Parameter|Description|  
|---------|-----------|
|--version|Prints the version information of the qsort program.|
|--help|Shows the help window, which lists all the available parameters and their descriptions.|
|--edit-conf [cli]|Opens the qsort configuration file. If the optional cli parameter is specified, then it will force the program to open the configuration file in command-line interface mode. This parameter requires sudo privileges.|
|--thread [count]|Specifies the number of threads that the qsort program will use for sorting. The value of count can be any positive integer between 1 and the max core your pc have. If this parameter is not specified, then the program will use a single thread for sorting.|
|--custom-conf [filename] or -cc|Allows the user to choose a custom configuration file for the qsort program. The filename parameter specifies the name of the custom configuration file that the user wants to use. The -cc option is a shorthand for this parameter.|
|--mime|(Beta) This parameter forces the qsort program to sort files according to their MIME type. By default, the program sorts files based on their file extensions. This parameter is still in beta, and its functionality may be limited or unstable.|

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