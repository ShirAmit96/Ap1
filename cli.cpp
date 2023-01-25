#include "cli.h"
/*The constructor of the cli.
 initializes a vector of all the commands */
Cli::Cli(SocketIO* dio, int socket) {
    this->dio=dio;
    this->sock=socket;
    commands.push_back(new UploadCSV(dio));
    commands.push_back(new Settings(dio));
    commands.push_back(new Classify(dio));
    commands.push_back(new DisplayResults(dio));
    commands.push_back(new Download(dio));
    commands.push_back(new Exit(dio));
}
/*This function runs the CLI component. it sends the menu, gets a command from the client and
 calls the relevant command to be executed*/
void Cli::start(){
    // create a shredData object that will hold a shared memory for the commands:
    SharedData sharedData;
    sharedData.socket=this->sock;
    while(true){
        bool flagBreak = false;
        // create the menu using the command's description:
        string menu="Welcome to the KNN classifier Server. Please choose an option:\n";
        for(int i=0;i<commands.size();i++){
            int num=i+1;
            if(i==5){
               flagBreak = true;
               num=8;
            }
           menu+=to_string(num) + ". "+commands[i]->description;
            if (flagBreak){
                break;
            }
        }
        // write the menu to the client using dio:
        cout << "I WANTED TO PRINT THE MENU IN CLI LINE 36"<< endl;
        dio->write(menu);
        //std::this_thread::sleep_for(std::chrono::milliseconds(120));
        cout << "MENU SENT FROM CLI" << endl;
        //cout<<menu<<endl;
        // read the inserted command from the client using dio:
        string input = dio->read();
        cout<<"input is:::"<<input<<endl;
        // choose the relevant command and execute it:
        if (input == "1"){
            cout<<"line 44"<<endl;
            commands[0]->execute(&sharedData);
            cout << "I FINISHED COMMAND 1 NOW IN CLI"<< endl;
        }
        else if (input == "2"){
            commands[1]->execute(&sharedData);
        }
        else if (input == "3"){
            commands[2]->execute(&sharedData);
        }
        else if (input == "4"){
            commands[3]->execute(&sharedData);
            cout << "I FINISHED COMMAND 4 AND IM IN CLI" << endl;
        }
        else if (input == "5"){
            commands[4]->execute(&sharedData);
        }
        else if (input == "8"){
            commands[5]->execute(&sharedData);
            break;
        }else{
            dio->write("invalid input.\n@@");
        }
       //std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}


Cli::~Cli() {
    for(size_t i=0;i<commands.size();i++){
        delete commands[i];
    }
}