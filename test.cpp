#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){


    ifstream inputFile("tasks.txt");

    if (!inputFile.is_open()){
        cerr << "Cannot find or open file" << endl;
        return 1;
    }

    std::string line;

    cout << "file content " << endl;
    while(getline(inputFile, line)){
        cout << line << endl;
    }

    // dont forget to clsoe the file
    inputFile.close();

    return 0;

}


