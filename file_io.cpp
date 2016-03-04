#include <iostream>
#include <fstream>
#include <sstream> 
#include  <stdlib.h>

using namespace std;

////////Function Prototypes/////////
void readFile();
void writeFile();
int menu();
int functionManager(int menuChoice);

////////Global Variables/////////
string CURRENT_INPUT_FILENAME;
string CURRENT_OUTPUT_FILENAME;
string CURRENT_FILE_TEXT;
ifstream INPUT_FILE_STREAM;
ofstream OUTPUT_FILE_STREAM;

////////calls menu function and initializes global variables/////////
int main()
{
    int menuChoice = 0;
    CURRENT_INPUT_FILENAME = "No Active File";
    CURRENT_OUTPUT_FILENAME = "No Active File";
    CURRENT_FILE_TEXT = "";
    
    while(menuChoice != 2)
    {
        menuChoice = menu();
        if(menuChoice != 2)
            functionManager(menuChoice);
    }
    
    return 0;
}

////////menu for all file io tasks/////////
int menu()
{
    int choice;
    
    system("clear");
    
    cout << "Active Input File: " << CURRENT_INPUT_FILENAME << endl;
    cout << "Active Output File: " << CURRENT_OUTPUT_FILENAME << "\n"<< endl;
    
    cout << "Please Make Selection:" << endl;  
    cout << "Read in File - 0" << endl;
    cout << "Save file - 1" << endl;
    cout << "exit - 2" << endl;
    
    cin >> choice;
    
    return choice;
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
void readFile()
{
    string line = "";
    string fileName;
    
    cout << "Please Enter Input File Path: " << endl;  
    cin >> fileName;
    
    CURRENT_INPUT_FILENAME = fileName;
    
    INPUT_FILE_STREAM.open(CURRENT_INPUT_FILENAME);
    
    if (INPUT_FILE_STREAM.is_open())
    {
        while ( getline (INPUT_FILE_STREAM,line) )
        {
          CURRENT_FILE_TEXT += line + "\n";
        }
        INPUT_FILE_STREAM.close();
    }
    else 
    {
        cout << "Unable to open file"; 
    }
    
    return;
}

////////prompts user  for output file path, writes global CURRENT_FILE_TEXT into file/////////
void writeFile()
{
    string line = "";
    string contents = "";
    string fileName;
    
    cout << "Please Enter Output File Path: " << endl;  
    cin >> fileName;
    CURRENT_OUTPUT_FILENAME = fileName;
    
    OUTPUT_FILE_STREAM.open(CURRENT_OUTPUT_FILENAME);
    OUTPUT_FILE_STREAM << CURRENT_FILE_TEXT;
    OUTPUT_FILE_STREAM.close();
    
    return;
}