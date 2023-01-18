//
// Created by 97252 on 11/01/2023.
//

#include "standardIO.h"

string StandardIO::read(){
    string input;
    getline(cin, input);
    return input;
}
void StandardIO::write(string text){
    cout<<text;

}