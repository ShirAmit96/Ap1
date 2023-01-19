#include "cli.h"
Cli::Cli(DefaultIO* dio) {
    this->dio=dio;
    commands.push_back(new UploadCSV(dio));
    commands.push_back(new Settings(dio));
    commands.push_back(new Classify(dio));
    commands.push_back(new DisplayResults(dio));
    commands.push_back(new Download(dio));
    commands.push_back(new Exit(dio));
}

void Cli::start(){
    SharedData sharedData;
    int index=-1;
    while(index!=7){
        dio->write("Welcome to the Anomaly Detection Server.\n");
        dio->write("Please choose an option:\n");
        for(size_t i=0;i<commands.size();i++){
            string s("1.");
            s[0]=((char)(i+1+'0'));
            if(i==5){
                s[0]=((char)(8+'0'));
            }
            dio->write(s);
            dio->write(commands[i]->description);
        }
        string input = dio->read();
        index=input[0]-'0'-1;
        if(index>=0 && index<=4||index==7) {
            commands[index]->execute(&sharedData);
        }
    }
}


Cli::~Cli() {
    for(size_t i=0;i<commands.size();i++){
        delete commands[i];
    }
}