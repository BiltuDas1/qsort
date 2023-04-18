#include"lib/user.hpp"

// Initialization
class init{
    public:
        init(int arg, char** argv){
            printf("%s\n", argv[0]);
        }
};

// Main Program
class base{
    
};

int main(int arg, char **argv){
    // Passing parameters to the program
    init *ini = new init(arg, argv);
    return 0;
}