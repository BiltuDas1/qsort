#include "lib/user.hpp"

#define home_path getenv("HOME")

// Initialization
class init
{
    public:
    static void getconfig()
    {
        ini::IniFile conf;
        conf.load("/etc/qsort/qsort.conf");

        *path::general = conf["Path"]["General"].as<string>();
        *path::documents = conf["Path"]["Documents"].as<string>();
        *path::pictures = conf["Path"]["Pictures"].as<string>();
        *path::videos = conf["Path"]["Videos"].as<string>();
        *path::music = conf["Path"]["Music"].as<string>();
        
        if(path::general->find("$HOME") != string::npos){
            path::general->replace(path::general->find("$HOME"), 5, home_path);
        }

        if(path::documents->find("$HOME") != string::npos){
            path::documents->replace(path::documents->find("$HOME"), 5, home_path);
        }

        if(path::pictures->find("$HOME") != string::npos){
            path::pictures->replace(path::pictures->find("$HOME"), 5, home_path);
        }

        if(path::videos->find("$HOME") != string::npos){
            path::videos->replace(path::videos->find("$HOME"), 5, home_path);
        }

        if(path::music->find("$HOME") != string::npos){
            path::music->replace(path::music->find("$HOME"), 5, home_path);
        }

        *exclude::extensions = conf["Exclude"]["Extensions"].as<string>();
        *exclude::filenames = conf["Exclude"]["Filenames"].as<string>();
    }

    static void getjson()
    {
        using nljson = nlohmann::json;

        ifstream json_file("/etc/qsort/extensions.json");
        nljson jsondata = nljson::parse(json_file);

        // Access the values in the JSON file
        auto documents = jsondata["Documents"];
        for (auto& document : documents) {
            json::documents->append(" ");
            json::documents->append(document);
        }

        auto pictures = jsondata["Pictures"];
        for (auto& picture : pictures) {
            json::pictures->append(" ");
            json::pictures->append(picture);
        }

        auto musics = jsondata["Musics"];
        for (auto& music : musics) {
            json::musics->append(" ");
            json::musics->append(music);
        }

        auto videos = jsondata["Videos"];
        for (auto& video : videos) {
            json::videos->append(" ");
            json::videos->append(video);
        }
    }

};


// Main Program
class base : protected init
{
    unsigned short thread_count = std::thread::hardware_concurrency();

    void version()
    {
        cout << "version " << ver << " " << vertype << endl;
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

    static void operations(const long long int count, const long long int start_point){
            // Listing all folder/files
            auto iter = fs::directory_iterator{*current_path};
            auto subrange = iter | ranges::views::drop(start_point);

            for (auto const &files : subrange | ranges::views::take(count))
            {
                if (fs::is_regular_file(files.path()))
                {
                    fs::path pathfile{files.path()};
                    string filename = files.path().filename().string();
                    string extension;

                    // Storing File Names into filename
                    filename.erase(0, filename.find_last_of("/") + 1);
                    if (filename.find_last_of(".") != string::npos)
                    {
                        extension = filename.substr(filename.find_last_of(".") + 1);

                        // Check If extension exist into configuration
                        if (exclude::extensions->find(extension) != string::npos)
                            continue;
                            
                        // If filename exist into configuration
                        if (exclude::filenames->find(filename) != string::npos)
                            continue;

                        // Check if extension exist into Catagories
                        string mvpath;
                        if (json::documents->find(extension) != string::npos)
                            mvpath = *path::documents;

                        else if (json::pictures->find(extension) != string::npos)
                            mvpath = *path::pictures;

                        else if (json::musics->find(extension) != string::npos)
                            mvpath = *path::music;

                        else if (json::videos->find(extension) != string::npos)
                            mvpath = *path::videos;
                        else
                            mvpath = *path::general;

                        try {
                            fs::rename(pathfile, mvpath + "/" + filename);
                        }
                        catch(...){
                            cout << "Unable to rename: " << pathfile << endl;
                        }

                    }
                    else
                    {
                        // If no extension and file not found into Exclude list then move to General
                        if (exclude::filenames->find(filename) == string::npos)
                        {
                            fs::path temp_path = *path::general + "/" + filename;
                            fs::rename(pathfile, temp_path);
                        }
                    }
                }
            }
    }


public:
    base(const int arg, const char **argv)
    {
        // If arguments passed into the executable
        if (arg > 1)
        {
            // Version Information
            *tempstr = argv[1];
            if (!tempstr->compare("--version"))
            {
                if (arg == 2)
                    version();
                else
                    error(argv[2]);
            }
            // Help
            if (!tempstr->compare("--help"))
            {
                if (arg == 2)
                    help(argv[0]);
                else
                    error(argv[2]);
            }
            // If no arguments passed then do main operation
        }
        else
        {
            // Initializing Variables/Settings
            thread g_config(init::getconfig);
            thread g_json(init::getjson);
            g_config.join();
            g_json.join();

            const long long unsigned int file_count = distance(fs::directory_iterator(*current_path), fs::directory_iterator{});

            thread threads[thread_count];
            const long long int thread_process = file_count/thread_count;

            if (thread_process > thread_count){
                tempint = 0;

                // Creating threads
                for(unsigned short i = 0; i < thread_count; ++i){
                    threads[i] = thread(&base::operations, thread_process, tempint);
                    cout << "Thread " << i + 1 << " [Range: " << tempint << "-" << tempint + thread_process << "]" << endl;
                    tempint = tempint + thread_process + 1;
                    if(tempint > file_count){
                        tempint = file_count;
                    }
                }

                // Waiting for thread to complete
                for(auto &thread : threads){
                    thread.join();
                }
            }

            // Checks if any remaining files
            tempint = 0;
            const unsigned int remaining_count = distance(fs::directory_iterator(*current_path), fs::directory_iterator{});
            if (remaining_count){
                operations(remaining_count, tempint);
            }
        }
    }

    ~base()
    {
        delete tempstr, current_path;
        delete exclude::extensions, exclude::filenames;
        delete path::documents, path::general, path::music, path::pictures, path::videos;
        delete json::documents, json::musics, json::pictures, json::videos;
    }
};

int main(const int arg, const char **argv)
{
    // Passing parameters to the base class
    base *b = new base(arg, argv);
    delete b;
    return errorcode;
}
