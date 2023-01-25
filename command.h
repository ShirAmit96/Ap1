
#ifndef AP1_COMMAND_H
#define AP1_COMMAND_H
#include "defaultIO.h"
#include "socketIO.h"
#include "database.h"
#include "knn.h"
#include "reader_class.h"
#include "command.h"
#include <string>

struct SharedData{
    int socket;
    DataBase db_classified;
    DataBase db_unclassified;
    Knn k_model;
    int k = 5;
    string distanceMetric = "AUC";
    bool dataUploaded=false;
    bool dataClassified=false;
    bool k_initialized=false;
};

class Command{
protected:
    SocketIO* dio;
public:
    const string description;
    Command(SocketIO* dio,const string description):dio(dio),description(description){}
    virtual void execute(SharedData* sharedData)=0;
    virtual ~Command(){}
};
class UploadCSV:public Command {
public:
    UploadCSV(SocketIO* dio):Command(dio,"upload an unclassified csv data file\n"){}
    virtual void execute(SharedData* sharedData);
    string writeCSV(SharedData* sharedData, string fileContent, bool classified);
};
class Settings:public Command{
public:
    Settings(SocketIO* dio):Command(dio,"algorithm settings\n"){}
    virtual void execute(SharedData* sharedData);
    virtual ~Settings(){}
};
class Classify:public Command{
public:
    Classify(SocketIO* dio):Command(dio,"classify data\n"){}
    virtual void execute(SharedData* sharedData);
    virtual ~Classify(){}
};
class DisplayResults:public Command{
public:
    DisplayResults(SocketIO* dio):Command(dio,"display results\n"){}
    virtual void execute(SharedData* sharedData);
};
class Download:public Command{
public:
    Download(SocketIO* dio):Command(dio,"download results\n"){}
    virtual void execute(SharedData* sharedData);
    void sendFile(SharedData* sharedData);

};
class Exit:public Command {
public:
    Exit(SocketIO* dio):Command(dio,"exit\n@@"){};
    virtual void execute(SharedData* sharedData);
};


#endif //AP1_COMMAND_H
