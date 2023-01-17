#include "cli.h"
#include "cli.cpp"
#include "standardIO.h"
int main(){

    StandardIO* standardIo;
    Cli cli (standardIo);
    cli.start();
    return 0;
}