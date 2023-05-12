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
#include <magic.h> // libmagic-dev
#include "inicpp.h" // https://github.com/Rookfighter/inifile-cpp
#include "json.hpp" // https://github.com/nlohmann/json
namespace fs = std::filesystem;
using namespace std;

// <--- Version Information Start --->
// <--- Don't modify the text here --->

const string ver = "0.3.3";
const string vertype = "beta";

// <--- Version Information End --->

// <-------- Main user.hpp starts here -------->

// A dynamic String for storing temporary data
string *tempstr = new string;

// A dynamic String which contains the current path location
string *current_path = new string(fs::current_path());

// A dynamic String for storing total arguments passed through this binary
string *args = new string;

// An integer for storing temporary long integers
unsigned long long int tempint;

// An integer variable which contains the program exit code
int errorcode = 0;

// Configuration file location
string *confL = new string("/etc/qsort/qsort.conf");

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

// Function to execute Commands into Host System
// And redirect output to a string or std::ostream
string execute_cmd(const string& cmd)
{
    string result;
    FILE* output = popen(cmd.c_str(), "r");
    if (!output)
        throw std::runtime_error("Error: Can't read qsort.conf, Syntax Error");
    
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), output) != nullptr)
        result += buffer;
    
    pclose(output);
    result.erase(result.find_last_not_of("\n") + 1);
    return result;
}