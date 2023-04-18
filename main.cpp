#include"lib/user.hpp"

// Initialization
class init
{
    protected:
        
};

// Main Program
class base : protected init
{
    public:
        base(int arg, char **argv){
            
        }
        
};

int main(int arg, char **argv){
    // Passing parameters to the base class
    base *b = new base(arg, argv);
    return 0;
}