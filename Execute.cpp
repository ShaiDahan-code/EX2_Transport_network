//
// Created by shai0 on 5/16/2022.
//

#include <iterator>
#include "Execute.h"


using namespace std;

//Get unlimited number of arguments from the user
void Execute::getFromFile_i(const string& tail) {

    //Get the file name
    const string& fileName = tail;

    //Open the file
    ifstream file(fileName);

    //check with kind of name is the file {bus,tram,sprinter,rail}
    if (fileName.find("bus") != string::npos) {
        cout << "check" << endl;
        //Get the data from the file
        readFile(tail, "bus");
    } else if (fileName.find("tram") != string::npos) {
        //Get the data from the file
        readFile(tail, "tram");
    } else if (fileName.find("sprinter") != string::npos) {
        //Get the data from the file
        readFile(tail, "sprinter");
    } else if (fileName.find("rail") != string::npos) {
        //Get the data from the file
        readFile(tail, "rail");
    } else {
        //If the file name is not valid
        cout << "The file name is not valid" << endl;
    }

    //Check if the file is open
    if (!file.is_open()) {
        cout << "File is not open" << endl;
        return;
    }



    //Close the file
    file.close();

}

void Execute::execute(int argc, char* argv[]){
    int index = 1;
    string command ,load_file ,city_name;


    if(argc==1){
        cout<<"No arguments"<<endl;
        return;
    }

    while(index<argc){
        if(string(argv[index]) == "-i"){
            index++;
            while(index<argc && string(argv[index]) != "-o" && string(argv[index]) != "-c"){ // get only the input from -i flag.
                getFromFile_i(string(argv[index]));
                index++;
            }
        }

        else if(string(argv[index]) == "-c"){
            index++;
            while(index<argc && string(argv[index]) != "-i" && string(argv[index]) != "-o"){ // get only the input from -c flag.
                //TODO: check what kind of input is it{rail,sprinter,tram,bus }
                getConfigFromFile(string(argv[index]));
                index++;
            }
        }

        else if(string(argv[index]) == "-o"){
            index++;
            while(index<argc && string(argv[index]) != "-i" && string(argv[index]) != "[-c]"){ // get only the input from -o flag.
                writeToFile(string(argv[index]));
                _output_file = argv[index];
                index++;
            }
        }

    }
    while(command != "EXIT"){
        cout << "[input]\t";
        cin >> command;
        if (command == "load") {
            cin>>load_file;
            getFromFile_i(load_file);
            cout << "Update was successful." << endl;
        }
        else if (command == "outbound") {
            cin>>city_name;
            mg.call_BFS_By_Type(city_name);
            //outbound(city_name);
        }
        else if (command == "inbound") {
            cin>>city_name;
            //inbound(city_name);
        }
        else if (command == "uniExpress") {

        }
        else if (command == "multiExpress") {

        }
        else if (command == "print") {
            writeToFile(_output_file);
        }
        else if (command == "EXIT") {
            break;
        }
    }
}



void Execute::readFile(const string& fname, const string& type) {
    ifstream file(fname);
    cout << "file name is " << fname << endl;
    if (!file.is_open()) {
        cerr << "[output]\tERROR opening the specified file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        // if any error cause because the input is not valid.
        string origin, destination;
        int time;
        try {
            //split the line to vector by "\t"
            stringstream ss(line);
            ss >> origin >> destination >> time;
        } catch (exception &e) {
            cerr << "Error: " << e.what() << endl;
        }

        //check if origin and destination already exist in the all_stop_stations
        mg.addNewEdgeByType(origin, destination, time, type);
    }

}

void Execute::getConfigFromFile(const string& fname) {
    ifstream file(fname);
    cout << "file name is " << fname << endl;
    if (!file.is_open()) {
        cerr << "File is not open" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        string type ;
        int time;
        try {
            //split the line to vector by "\t"
            stringstream ss(line);
            ss >> type >> time;
        } catch (exception &e) {
            cerr << "Error: " << e.what() << endl;
        }
        if(mg.getStopCarTimeMap().count(type)){
            mg.getStopCarTimeMap()[type] = time;
        }
        if(mg.getStopCityTimeMap().count(type)){
            mg.getStopCityTimeMap()[type] = time;
        }
    }
}

void Execute::writeToFile(string fname) {
    string s = "";
    s += mg.all_object_to_string(mg.getBusMatrix());
    s += mg.all_object_to_string(mg.getTramMatrix());
    s += mg.all_object_to_string(mg.getRailMatrix());
    s += mg.all_object_to_string(mg.getSprinterMatrix());

    ofstream file(fname);
    cout << "file name is " << fname << endl;
    if (!file.is_open()) {
        cerr << "File is not open" << endl;
        return;
    }
    file << s;

}


