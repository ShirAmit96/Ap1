#include "cli.h"
#include "standardIO.h"
int main(){

    DefaultIO* sio  = new StandardIO;
    Cli cli (sio);
    cli.start();
    return 0;
}