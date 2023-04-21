#include "lib/user.hpp"

// Initialization
class init
{
    inline string read_path_variable()
    {
        return getenv("PATH");
    }

    inline string home_path()
    {
        return getenv("HOME");
    }
    public:
    void init_required(){
          getjson();
        getconfig();

    }
    void getconfig()
    {
        /// Code

        // configaration file name

        ifstream config_file(home_path() + "/.qsort/config.conf");
        string section_name;
        string line;
        // while (getline(config_file, line))
        // {
        //     // Line processing code
        // }

        // string line;
        while (getline(config_file, line))
        {
            // Removing white spaces from line
            line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

            // Skip empty and comment lines
            if (line.empty() || line[0] == '#')
                continue;

            // Get section name
            if (line[0] == '[' && line[line.size() - 1] == ']')
            {
                section_name = line.substr(1, line.size() - 2);
            }
            else
            {
                // Parse the line into key and value
                auto delimiter_pos = line.find('=');
                auto key = line.substr(0, delimiter_pos);
                auto value = line.substr(delimiter_pos + 1);

                // Store the value into the appropriate variable based on section and key name
                if (section_name == "Path")
                {
                    if (key == "General")
                        *path::general = value;
                    else if (key == "Videos")
                        *path::videos = value;
                    else if (key == "Pictures")
                        *path::pictures = value;
                    else if (key == "Documents")
                        *path::documents = value;
                    else if (key == "Music")
                        *path::music = value;
                }
                else if (section_name == "Exclude")
                {
                    if (key == "Extensions")
                        *exclude::extensions = value;
                    else if (key == "Filenames")
                        *exclude::filenames = value;
                }
            }
        }

        // string g = "/home/biltudas1"; // Function or Variable
        // *path::general = g;
    }

    void getjson()
    {
        using json = nlohmann::json;

        ifstream json_file(home_path() + "/.qsort/extensions.json");
        json jsondata = json::parse(json_file);

    // Access the values in the JSON file
    auto documents = jsondata["Documents"];
    for (auto& document : documents) {
        std::cout << document << std::endl;
    }

    auto pictures = jsondata["Pictures"];
    for (auto& picture : pictures) {
        std::cout << picture << std::endl;
    }

    auto musics = jsondata["Musics"];
    for (auto& music : musics) {
        std::cout << music << std::endl;
    }

    auto videos = jsondata["Videos"];
    for (auto& video : videos) {
        std::cout << video << std::endl;
    }
}



    };


    // Dependencies



// Main Program
class base : protected init
{
    void version()
    {
        cout << "version " << *ver << " " << *vertype << endl;
    }
    void help(string exec)
    {
        cout << "Parameters of qsort are:\n\n";
        cout << "--version       Prints the version information\n";
        cout << "--help          Shows this window" << endl;
    }
    void error(string err)
    {
        cout << "Error: Unrecognized parameter " << err << endl;
        errorcode = 1;
    }

public:
    base(int arg, char **argv)
    {
        // If arguments passed into the executable
        if (arg > 1)
        {
            // Version Information
            *tempstr = argv[1];
            if (!tempstr->compare("--version"))
            {
                if (arg == 2)
                {
                    version();
                }
                else
                {
                    error(argv[2]);
                }
            }
            // Help
            if (!tempstr->compare("--help"))
            {
                if (arg == 2)
                {
                    help(argv[0]);
                }
                else
                {
                    error(argv[2]);
                }
            }
            // If no arguments passed then do main operation
        }
        else
        {
            // Initializing Variables/Settings
            init::init_required();

            // Listing all folder/files
            for (auto const &files : fs::directory_iterator{fs::current_path()})
            {
                if (fs::is_regular_file(files))
                {
                    fs::path pathfile{files};
                    *tempstr = pathfile.u8string();
                    string *extension = new string;

                    // Storing File Names into tempstr
                    tempstr->erase(0, tempstr->find_last_of("/") + 1);
                    if (tempstr->find_last_of(".") != string::npos)
                    {
                        *extension = tempstr->substr(tempstr->find_last_of(".") + 1);

                        // Check If extension exist into configuration
                        if (exclude::extensions->find(*extension) != string::npos)
                            continue;

                        // Check if extension exist into Catagories
                        string *mvpath = new string;
                        if (json::documents->find(*extension) != string::npos)
                            *mvpath = *path::documents;

                        else if (json::pictures->find(*extension) != string::npos)
                            *mvpath = *path::pictures;

                        else if (json::musics->find(*extension) != string::npos)
                            *mvpath = *path::music;

                        else if (json::videos->find(*extension) != string::npos)
                            *mvpath = *path::videos;
                        else
                            *mvpath = *path::general;

                        fs::rename(pathfile, *mvpath + "/" + *tempstr);

                        delete extension, mvpath;
                    }
                    else
                    {
                        // If no extension and file not found into Exclude list then move to General
                        if (exclude::filenames->find(*tempstr) == string::npos)
                        {
                            fs::path temp_path = *path::general + "/" + *tempstr;
                            fs::rename(pathfile, temp_path);
                        }
                    }
                }
            }
        }
    }

    ~base()
    {
        delete ver, vertype, tempstr;
        delete exclude::extensions, exclude::filenames;
        delete path::documents, path::general, path::music, path::pictures, path::videos;
        delete json::documents, json::musics, json::pictures, json::videos;
    }
};

int main(int arg, char **argv)
{
    // Passing parameters to the base class
    base *b = new base(arg, argv);
    delete b;
    // init abc;
    // abc.init_required();
    return errorcode;
}
