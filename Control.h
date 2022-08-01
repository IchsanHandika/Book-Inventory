#ifndef _CONTROL_H
#define _CONTROL_H
#include <string>

using namespace std;

class Control {
public: 
    string username;
    string password;
    
void MakeFileBook();
    
void ChooseFileBook();
    
void DeleteFileBook();
    
void CommandLoop();
    
void FileBookLoop(string fileName);
};

#endif //_CONTROL_H