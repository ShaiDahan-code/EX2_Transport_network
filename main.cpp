#include <iostream>
#include "Execute.h"

#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    Execute execute;
    execute.execute(argc, argv);

//    EXAMPLE for Insiert
//
//    string from = "Zefat";
//    vector<vector<string> > s = {{""}};
//    cout << s.size() << endl;
//    for(int i=1;i<s.size();i++){
//        s[i].push_back("0");
//    }
//    s[0].push_back(from);
//    vector<string> temp;
//    temp.push_back(from);
//    for(int i=0;i<s.size();i++){
//        temp.push_back("0");
//    }
//    s.push_back(temp);
//    from = "Haifa";
//    for(int i=1;i<s.size();i++){
//        s[i].push_back("0");
//    }
//    s[0].push_back(from);
//    vector<string> temp2;
//    temp2.push_back(from);
//    for(int i=0;i<s.size();i++){
//        temp2.push_back("0");
//    }
//    s.push_back(temp2);
//
//
//    for(int i=0;i<s.size();i++){
//        for(int j=0;j<s.size();j++){
//            cout << s[i][j] << "\t";
//        }
//        cout << endl;
//    }

    return 0;
}
