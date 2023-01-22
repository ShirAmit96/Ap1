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
        string menu="Welcome to the KNN classifier Server. Please choose an option:\n";
        for(int i=0;i<commands.size();i++){
            int num=i+1;
            if(i==5){
               flagBreak = true;
               num=8;
            }
           menu+=to_string(num) + "."+commands[i]->description;
            if (flagBreak){
                break;
            }
        }
        dio->write(menu);
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