#include <iostream>
#include <fstream>
#include <sstream> 
#include  <stdlib.h>
//#include "translate.h"
using namespace std;

////////Function Prototypes/////////
bool readFile();
bool writeFile();
int Mainmenu();
int functionManager(int menuChoice);
void NewTranslation();
void ParseAndDistribute();

////////Global Variables/////////
string CURRENT_INPUT_FILENAME;
string CURRENT_OUTPUT_FILENAME;
string CURRENT_FILE_TEXT;
ifstream INPUT_FILE_STREAM;
ofstream OUTPUT_FILE_STREAM;
stringstream MASM_STREAM;


//////////Command Vectors///////////



////////calls menu function and initializes global variables/////////
int main()
{
    int menuChoice = 0;
    CURRENT_INPUT_FILENAME = "No Active File";
    CURRENT_OUTPUT_FILENAME = "No Active File";
    CURRENT_FILE_TEXT = "";
    
    while(menuChoice != 1)
    {
        menuChoice = Mainmenu();
        if(menuChoice != 1)
            NewTranslation();
    }
    
    return 0;
}

////////menu for all file io tasks/////////
int Mainmenu()
{
    int choice;
    
    system("clear");
    cout << "...Welcome To The..." << endl;
    cout << "Masm To Nasm Translator\n" << endl;
    
    cout << "Active Input File: " << CURRENT_INPUT_FILENAME << endl;
    cout << "Active Output File: " << CURRENT_OUTPUT_FILENAME << "\n"<< endl;
    
    cout << "Please Make Selection:" << endl;  
    cout << "Start New Translation - 0" << endl;
    cout << "exit - 1" << endl;
    
    cin >> choice;
    
    return choice;
}

void ParseAndDistribute()
{
    string line;
    string newLine = " ";
    
    if(CURRENT_FILE_TEXT != "")
    {
        MASM_STREAM << CURRENT_FILE_TEXT;
        cout << "Stream Worked" << endl;
    }
    else
    {
        cout << "No Input" << endl;
        return;
    }
    
    
    while ( getline (MASM_STREAM,line) )
    {
      newLine += line + "\n";
      //cout << newLine;
    }
    
    
    return;
}

void NewTranslation()
{
    int choice;
    bool sucessfulRead = false;
    system("clear");
    cout << "...Make New Translation..." << endl;
    
    sucessfulRead = readFile();
    
    if(sucessfulRead)
    {
        ParseAndDistribute();
        writeFile();
    }
    
    
    
    return;
}

////////takes in the menu choice and calls the corresponding utility function/////////
int functionManager(int choice)
{
    string fileContents;
    switch (choice)
    {
        case 0:
            readFile();
            break;
        case 1:
            cout << "save file" << endl;
            writeFile();
            break;
        case 2:
            cout << "Thanks for playing" << endl;
            break;
        default:
            cout << "Invalid Choice" << endl;
    }
        
    return 0;
}



////////prompts user  for input file path, reads file contents into global CURRENT_FILE_TEXT/////////
bool readFile()
{
    string line = "";
    string fileName;
    bool readFlag = false;
    cout << "Please Enter Input File Path: " << endl;  
    cin >> fileName;
    
    CURRENT_INPUT_FILENAME = fileName;
    
    INPUT_FILE_STREAM.open(CURRENT_INPUT_FILENAME);
    
    if (INPUT_FILE_STREAM.is_open())
    {
        while (getline (INPUT_FILE_STREAM,line) )
        {
            
           // if (line == "")
          //          continue;
            
            CURRENT_FILE_TEXT += line + "\n";
            
            
            
            
        }
        INPUT_FILE_STREAM.close();
        readFlag = true;
    }
    else 
    {
        cout << "Unable to open Input file"; 
    }
    
    return readFlag;
}

////////prompts user  for output file path, writes global CURRENT_FILE_TEXT into file/////////
bool writeFile()
{
    string line = "";
    string contents = "";
    string fileName;
    bool writeFlag = false;
    
    
    cout << "Please Enter Output File Path: " << endl;  
    cin >> fileName;
    
    CURRENT_OUTPUT_FILENAME = fileName;
    OUTPUT_FILE_STREAM.open(CURRENT_OUTPUT_FILENAME);
    
    if (OUTPUT_FILE_STREAM.is_open())
    {
        OUTPUT_FILE_STREAM << CURRENT_FILE_TEXT;
        OUTPUT_FILE_STREAM.close();
        writeFlag = true;
    }
    else
    {
        cout << "Unable to open output file";
    }
    
    return writeFlag;
}