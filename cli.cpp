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
    while(true){
        cout << "line 15" << endl;
        bool flagBreak = false;
        dio->write("Welcome to the Anomaly Detection Server.\n");
        dio->write("Please choose an option:\n");
        for(int i=0;i<commands.size();i++){
            string s("1.");
            s[0]=((char)(i+1+'0'));
            if(i==5){
                s[0]=((char)(8+'0'));
                flagBreak = true;
            }
            dio->write(s);
            //s="";
            dio->write(commands[i]->description);
            if (flagBreak){
                break;
            }
        }
        cout << "line 27" << endl;
        string input = dio->read();
        if (input == "1"){
            commands[0]->execute(&sharedData);
        }
        if (input == "2"){
            commands[1]->execute(&sharedData);
        }
        if (input == "3"){
            commands[2]->execute(&sharedData);
        }
        if (input == "4"){
            commands[3]->execute(&sharedData);
        }
        if (input == "5"){
            commands[4]->execute(&sharedData);
        }
        if (input == "8"){
            commands[5]->execute(&sharedData);
            break;
        }
        else{
            cout << "%&%&%&%&%&%&%"<<input << endl;
            input ="";
            continue;
        }
    }
}


Cli::~Cli() {
    for(size_t i=0;i<commands.size();i++){
        delete commands[i];
    }
}