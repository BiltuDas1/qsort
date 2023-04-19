#include"lib/user.hpp"

// Initialization
class init
{
    inline string read_path_variable() {
        return getenv("PATH");
    }

    protected:
        // Dependencies
        void init_required(){

        }
};

// Main Program
class base : protected init
{
    void version(){
        cout << "version " << *ver << " " << *vertype << endl;
    }
    void help(string exec){
        cout << "Parameters of qsort are:\n\n";
        cout << "--version       Prints the version information\n";
        cout << "--help          Shows this window" << endl;
    }
    void error(string err){
        cout << "Error: Unrecognized parameter " << err << endl;
        errorcode = 1;
    }
    public:
        base(int arg, char **argv){
            // If arguments passed into the executable
            if (arg > 1){
                // Version Information
                *tempstr = argv[1];
                if (!tempstr->compare("--version")){
                    if(arg == 2){
                        version();
                    } else {
                        error(argv[2]);
                    }
                }
                // Help
                if (!tempstr->compare("--help")){
                    if(arg == 2){
                        help(argv[0]);
                    } else {
                        error(argv[2]);
                    }
                }
            // If no arguments passed then do main operation
            } else {
                // Initializing Variables/Settings
                init::init_required();

                // Listing all folder/files
                for(auto const& files : fs::directory_iterator{fs::current_path()}) 
                {
                    if(fs::is_regular_file(files)){
                        fs::path pathfile{files};
                        *tempstr = pathfile.u8string();
                        string *extension = new string;

                        // Storing File Names into tempstr
                        tempstr->erase(0, tempstr->find_last_of("/") + 1);
                        if(tempstr->find_last_of(".") != string::npos){
                            *extension = tempstr->substr(tempstr->find_last_of(".") + 1);

                            // Check If extension exist into configuration
                            if(exclude::extensions->find(*extension) != string::npos)
                                continue;

                            // Check if extension exist into Catagories
                            string *mvpath = new string;
                            if(json::documents->find(*extension) != string::npos)
                                *mvpath = *path::documents;

                            else if(json::pictures->find(*extension) != string::npos)
                                *mvpath = *path::pictures;

                            else if(json::musics->find(*extension) != string::npos)
                                *mvpath = *path::music;

                            else if(json::videos->find(*extension) != string::npos)
                                *mvpath = *path::videos;
                            else
                                *mvpath = *path::general;
                            
                            fs::rename(pathfile, *mvpath + "/" + *tempstr);

                            delete extension, mvpath;
                        } else {
                            // If no extension and file not found into Exclude list then move to General
                            if(exclude::filenames->find(*tempstr) == string::npos){
                                fs::path temp_path = *path::general + "/" + *tempstr;
                                fs::rename(pathfile, temp_path);
                            }
                        }
                    }
                }
            }
        }
        
        ~base(){
            delete ver, vertype, tempstr;
            delete exclude::extensions, exclude::filenames;
            delete path::documents, path::general, path::music, path::pictures, path::videos;
            delete json::documents, json::musics, json::pictures, json::videos;
        }
};

int main(int arg, char **argv){
    // Passing parameters to the base class
    base *b = new base(arg, argv);
    delete b;
    return errorcode;
}