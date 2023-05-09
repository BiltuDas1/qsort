#include "lib/user.hpp"

#define yes true
#define no false

// Initialization
class init
{
    static void xdg_user_dir(string& value, const string optional){
        value = execute_cmd("xdg-user-dir " + optional);
    }
    static void xdg_user_dir(string& value){
        int firstpath, secondpath;
        string str;
        while(value.find("$") != string::npos){
            firstpath = value.find_first_of("$");
            str = value.substr(firstpath + 1);
            // If the val doesn't contains any slash
            if(str.find_first_of("/") != string::npos){
                secondpath = str.find_first_of("/") + 1;
            } else {
                secondpath = str.length() + 1;
            }
            str.erase(secondpath - 1);
            str = execute_cmd("xdg-user-dir " + str);
            if(!value.find_first_of("/")){
                if(str.substr(0, 1) == "/" && value.substr(firstpath - 1, 1) == "/"){
                    value.replace(firstpath - 1, secondpath + 1, str);
                    return;
                }
            }
            value.replace(firstpath, secondpath, str);
        }
    }

    public:
    static void getconfig()
    {
        ini::IniFile conf;
        conf.load(*confL);

        *path::general = conf["Path"]["General"].as<string>();
        *path::documents = conf["Path"]["Documents"].as<string>();
        *path::pictures = conf["Path"]["Pictures"].as<string>();
        *path::videos = conf["Path"]["Videos"].as<string>();
        *path::music = conf["Path"]["Music"].as<string>();
        
        // If no value is set then
        if(path::general->empty())
            xdg_user_dir(*path::general, "HOME");
        else
            xdg_user_dir(*path::general);
        if(path::documents->empty())
            xdg_user_dir(*path::documents, "DOCUMENTS");
        else
            xdg_user_dir(*path::documents);
        if(path::pictures->empty())
            xdg_user_dir(*path::pictures, "PICTURES");
        else
            xdg_user_dir(*path::pictures);
        if(path::videos->empty())
            xdg_user_dir(*path::videos, "VIDEOS");
        else
            xdg_user_dir(*path::videos);
        if(path::music->empty())
            xdg_user_dir(*path::music, "MUSIC");
        else
            xdg_user_dir(*path::music);

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
        cout << "qsort v" << ver << "-" << vertype << endl;
    }

    void help(string exec)
    {
        cout << exec << " [--thread] [count]\n\n";
        cout << "Parameters of qsort are:\n";
        cout << "--version                  Prints the version information\n";
        cout << "--help                     Shows this window\n";
        cout << "--edit-conf [cli]          Opens qsort configuration file(requires sudo)\n";
        cout << "   cli                     Force to cli mode\n";
        cout << "--thread [count]           Threads count which will be used\n";
        cout << "                           The count range only can between [1-" << thread_count << "]\n";
        cout << "--custom-conf [filename]   Choose a Custom qsort.conf file\n";
        cout << "   -cc                     Same as --custom-conf";
        cout << endl;
    }

    void error(string err)
    {
        cerr << "Error: Unrecognized parameter " << err << endl;
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

    void work_thread(){
            // If no arguments passed then do main operation
            // Initializing Variables/Settings
            thread g_config(init::getconfig);
            thread g_json(init::getjson);
            g_config.join();
            g_json.join();

            const long long unsigned int file_count = distance(fs::directory_iterator(*current_path), fs::directory_iterator{});

            thread threads[thread_count];
            const long long int thread_process = file_count/thread_count;

            bool taskDone = no;

            if (thread_process > thread_count){
                tempint = 0;

                cout << "Using " << thread_count << " Threads\n";
                // Creating threads
                for(unsigned short i = 0; i < thread_count; ++i){
                    threads[i] = thread(&base::operations, thread_process, tempint);
                    tempint = tempint + thread_process;
                    if(tempint > file_count){
                        tempint = file_count;
                    }
                }

                // Waiting for thread to complete
                for(auto &thread : threads){
                    thread.join();
                }

                taskDone = yes;
            }

            // Checks if any remaining files
            tempint = 0;
            const unsigned int remaining_count = distance(fs::directory_iterator(*current_path), fs::directory_iterator{});
            if (remaining_count){
                operations(remaining_count, tempint);
            }

            // If operation completed
            if(taskDone){
                cout << "Operation Completed" << endl;
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
            else if (!tempstr->compare("--help"))
            {
                if (arg == 2)
                    help(argv[0]);
                else
                    error(argv[2]);
            }
            // Edit Configuration
            else if (!tempstr->compare("--edit-conf"))
            {
                const char *editor;
                if (arg == 2){
                    if(access("/usr/bin/xdg-open", X_OK)){
                        editor = "editor";
                    } else {
                        editor = "xdg-open";
                    }
                } else {
                    *tempstr = argv[2];
                    if (!tempstr->compare("cli")){
                        editor = "editor";
                    }
                }
                
                char* const args[] = {const_cast<char*>(editor), const_cast<char*>("/etc/qsort/qsort.conf"), nullptr};

                if (geteuid() != 0){
                    cerr << "Error: Sudo permission required\n";
                } else {
                    execvp(editor, args); // Open default text editor
                    cerr << "Error: Could not open text editor\n";
                }
                errorcode  = 1;
            }
            // Thread parameter
            else if (!tempstr->compare("--thread"))
            {
                if (arg == 2)
                {
                    work_thread();
                } else {
                    *tempstr = argv[2];
                    if (stoi(*tempstr) <= thread_count && stoi(*tempstr) >= 1){
                        this->thread_count = stoi(*tempstr);
                        work_thread();
                    } else {
                        cout << "Error: Out of range. You can only use any thread between [1-" << thread_count << "]." << "\n";
                    }
                }
            }
            // Custom qsort.conf
            else if (!tempstr->compare("--custom-conf") || !tempstr->compare("-cc"))
            {
                if (arg == 2){
                    error("No configuration file name specified");
                } else {
                    *tempstr = argv[2];
                    if(fs::exists(*tempstr)){
                        if(fs::is_regular_file(*tempstr) && !fs::is_empty(*tempstr)){
                            *confL = *tempstr;
                            work_thread();
                        } else {
                            error("Error: " + *tempstr + " is not a valid configuration file");
                        }
                    } else {
                        error("Error: Configuration file not found");
                    }
                }
            }
        }
        else
            work_thread();
    }

    ~base()
    {
        delete tempstr, current_path, confL;
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
