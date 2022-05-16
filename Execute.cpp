//
// Created by shai0 on 5/16/2022.
//

#include <iterator>
#include "Execute.h"


using namespace std;

//Get unlimited number of arguments from the user
void Execute::getFromFile_i(const string tail) {
    if(tail == "-c" || tail == "-o"){
        cout << tail << endl;
        return;
    }
    //Get the file name
    string fileName = tail;


    //Open the file
    ifstream file(fileName);

    //Check if the file is open
    if (!file.is_open()) {
        cout << "File is not open" << endl;
        return;
    }

    //Get the arguments from the file
    string line;
    while (getline(file, line)) {
        cout << line << endl;

    }

    //Close the file
    file.close();

}

void Execute::execute(int argc, char* argv[]){
    int index = 1;

    if(argc==1){
        cout<<"No arguments"<<endl;
        return;
    }
    while(index<argc){
        if(string(argv[index]) == "-i"){
            index++;
            while(index<argc && string(argv[index]) != "[-o]" && string(argv[index]) != "[-c]"){ // get only the input from -i flag.
                //TODO: check what kind of input is it{rail,sprinter,tram,bus }
                getFromFile_i(string(argv[index]));
                index++;
            }
        }

        else if(string(argv[index]) == "[-c]"){
            index++;
            while(index<argc && string(argv[index]) != "-i" && string(argv[index]) != "[-o]"){ // get only the input from -c flag.
                //TODO: check what kind of input is it{rail,sprinter,tram,bus }
                index++;
            }
        }

        else if(string(argv[index]) == "[-o]"){
            index++;
            while(index<argc && string(argv[index]) != "-i" && string(argv[index]) != "[-c]"){ // get only the input from -o flag.
                //TODO: check what kind of input is it{rail,sprinter,tram,bus }
                index++;
            }
        }

    }




}

void Execute::getFromFile_c(string fname) {

}

void Execute::getFromFile_o(string fname) {

}
