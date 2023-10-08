#include "engine_interface.hpp"

int main( int argc, char** argv, char** env )
{
    if( EngineInterface::StartEngine(argc,argv,env) )
        return 0; // in case that everything handled fine.

    return -1; // in case that something went wrong.
}
