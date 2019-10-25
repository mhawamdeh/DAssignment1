#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "hash256.h"


using namespace std;

struct line{
    string userName;
    string password;
    string UID;
    string GID;
    string UIDINFO;
    string homeDirectory;
    string Shell;
};
class RedingFilesLineByLine {
public:
    vector<string> splitLine(string eachLine, char delimenter) {
        stringstream lineStream(eachLine);
        string tempField;
        vector<string> resultOFLine;
        while (getline(lineStream, tempField, delimenter)) {
            resultOFLine.push_back(tempField);
        }

        return resultOFLine;
    }
};

int main() {
    ifstream originalFile;
    originalFile.open("/etc/passwd", ios::in);
    string passwords;

    if (originalFile.is_open()) {
        line outInfo;
        string inputUser;
        cout << "please enter a user: ";
        cin >> inputUser;
        while (getline(originalFile, passwords)) {
            if (passwords[0] == '#') {
                continue;
            } else {

                RedingFilesLineByLine myFile;
                vector<string> v = myFile.splitLine(passwords, ':');
                outInfo.userName = v[0];
                outInfo.password = v[1];
                outInfo.UID = v[2];
                outInfo.GID = v[3];
                outInfo.UIDINFO = v[4];
                outInfo.homeDirectory = v[5];
                outInfo.Shell = v[6];
            }

            if (outInfo.userName == inputUser) {
                cout << "$user:" << outInfo.userName <<endl<< "$groupid:" << outInfo.GID <<endl << "$path:"
                     << outInfo.homeDirectory <<endl << "hash: "<<picosha2::hash256_hex_string(passwords) << endl;
            }
        }
        originalFile.close();
        return 0;

    }
}