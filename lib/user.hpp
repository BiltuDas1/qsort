// <----- Header files ----->
#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <unistd.h>
#include <thread>
#include <ranges>
#include <span>
#include <fstream>
#include "inicpp.h" // https://github.com/Rookfighter/inifile-cpp
#include "json.hpp" // https://github.com/nlohmann/json
namespace fs = std::filesystem;
using namespace std;

// <--- Version Information Start --->
// <--- Don't modify the text here --->
const string ver = "0.3";
const string vertype = "beta";
// <--- Version Information End --->

// <-------- Main user.hpp starts here -------->
string *tempstr = new string;
string *current_path = new string(fs::current_path());
unsigned long long int tempint;

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