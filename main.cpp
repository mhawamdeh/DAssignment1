#include <iostream>
#include <fstream>
#include "hash256.h"
using namespace std;

int main() {
    ifstream originalFile;
    ofstream resultFile;
    originalFile.open("/etc/passwd", ios::in);
    resultFile.open("results.txt", ios::trunc);//to delete the content of the file when opening it and start with an empty file
    string passwords;
    string hashedPassword;
    if (originalFile.is_open()){
        while (getline(originalFile, passwords)){
            if(passwords[0]=='#'){
                continue;
            }
            else{
                if (passwords[0]=='_'){
                    passwords = passwords[1, passwords.length()-1];
                    hashedPassword = picosha2::hash256_hex_string(passwords);
                    resultFile<<hashedPassword<<endl;
                }
            }
        }
    }
    originalFile.close();
    resultFile.close();
}