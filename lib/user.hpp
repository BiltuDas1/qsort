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

int errorcode = 0;

string *tempstr = new string;
// int *tempint = new int;
// double *tempdouble = new double;
// char *tempchar = new char;

namespace exclude
{
    string *extensions = new string;
    string *filenames = new string;
}

namespace path
{
    string *general = new string;
    string *documents = new string;
    string *pictures = new string;
    string *videos = new string;
    string *music = new string;
}