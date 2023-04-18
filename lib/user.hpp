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