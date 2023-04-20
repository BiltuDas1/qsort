#include<stdio.h>
#include<iostream>
#include<filesystem>
#include<string>
#include<unistd.h>
#include<fstream>
#include"inicpp.h" // https://github.com/Rookfighter/inifile-cpp

namespace fs = std::filesystem;
using namespace std;

string *ver = new string("0.1");
string *vertype = new string("beta");
string *tempstr = new string;

int errorcode = 0;

// [exclude] in qsort.conf
namespace exclude
{
    string *extensions = new string;
    string *filenames = new string;
}

// [path] in qsort.conf
namespace path
{
    string *general = new string;
    string *documents = new string;
    string *pictures = new string;
    string *videos = new string;
    string *music = new string;
}

// extensions.json data
namespace json
{
    string *documents = new string;
    string *pictures = new string;
    string *musics = new string;
    string *videos = new string;
}