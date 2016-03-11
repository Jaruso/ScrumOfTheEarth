#include "translate.h"

//global
int Mainmenu();
void NewTranslation();
void SetFileNames();
void ParseAndDistribute();
void ViewFile(bool viewInput);


////////Global Variables/////////
string CURRENT_INPUT_FILENAME;
string CURRENT_OUTPUT_FILENAME;
string CURRENT_FILE_TEXT;
ifstream INPUT_FILE_STREAM;
ofstream OUTPUT_FILE_STREAM;
stringstream MASM_STREAM;

int main()
{
    int menuChoice = 0;
    CURRENT_INPUT_FILENAME = "No Active File";
    CURRENT_OUTPUT_FILENAME = "No Active File";
    CURRENT_FILE_TEXT = "";
    
    while(menuChoice != 3)
    {
        menuChoice = Mainmenu();
        if(menuChoice == 0)
            NewTranslation();
        else if(menuChoice == 1)
            ViewFile(true);
        else if(menuChoice == 2)
            ViewFile(false);
        else
          cout << "GOODBYE" << endl;
    }
 
    return 0;
}

void ViewFile(bool isInput)
{
  system("clear");
  string tempName = "";
  
  if (isInput && (CURRENT_INPUT_FILENAME != "No Active File"))
  {
    tempName  = CURRENT_INPUT_FILENAME;
    cout << "...Viewing Input File... \n" << endl;
    cout << "File Name: " << tempName + "\n" << endl;
  }
  else if(!isInput && (CURRENT_OUTPUT_FILENAME != "No Active File"))
  {
    tempName  = CURRENT_OUTPUT_FILENAME;
    cout << "...Viewing Output File... \n" << endl;
    cout << "File Name: " << tempName + "\n" << endl;
  }
  else
  {
    cout << "No Active File Selected. Cannot View File." << endl;
    cout << "\n\n\n\n Enter Any Character To Return To Menu" << endl;
    string next;
  
    cin >> next; 
    
    return;
  }
    
  ifstream tempInStream;
  string line;

  tempInStream.open(tempName);
  
  if (tempInStream.is_open())
  {
    while (getline(tempInStream, line))
    {
     cout << line << endl;
    }
    
    tempInStream.close();
  }
  else 
  {
      cout << "Unable to open file"; 
  }
  
  cout << "\n\n\n\n Enter Any Character To Return To Menu" << endl;
  string next;
  
  cin >> next;
  return;
}


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
    cout << "View Input File - 1" << endl;
    cout << "View Output File - 2" << endl;
    cout << "exit - 3" << endl;
    
    cin >> choice;
    
    return choice;
}

void SetFileNames()
{
    //int choice;
    //bool sucessfulRead = false;
    string fileName = " ";
    
    system("clear");
    cout << "...Make New Translation..." << endl;
    
    cout << "Please Enter Input File Path: " << endl;  
    cin >> fileName;
    CURRENT_INPUT_FILENAME = fileName;
    
    cout << "Please Enter Output File Path: " << endl;  
    cin >> fileName;
    CURRENT_OUTPUT_FILENAME = fileName;
    
    return;
}

void NewTranslation()
{
    SetFileNames();
    ParseAndDistribute();
    
    return;
}

void ParseAndDistribute()
{
    
    string section = "";
    vector<string> vars;
    CURRENT_FILE_TEXT = " ";
    string mline = "";
    string nline = "";
    
    INPUT_FILE_STREAM.open(CURRENT_INPUT_FILENAME);
    OUTPUT_FILE_STREAM.open(CURRENT_OUTPUT_FILENAME);
    
    
    if (INPUT_FILE_STREAM.is_open())
    {
      while (getline(INPUT_FILE_STREAM, mline))
      {
                    // toNasm returns a vector of strings. this vector consits of the operation, and its operators or other things
                    //    depending on what kind of line it is. section tells the converter where in the file they are, which is 
                    //    needed for some conversions. vars is vector contianing meta-data about varibles, which is need to properly convert
                    //    operations that contain varibles.
                  
                    // compressVec squishes the vector into a string delimeted by ' ' characters
                    // split seperates the string by the delimiter provided
          if(mline != "")
            nline = compressVec(toNasm(split(mline, ' '), section, vars));
          else
            nline = "";
          OUTPUT_FILE_STREAM << nline << "\n";
          CURRENT_FILE_TEXT += mline;
      }
      INPUT_FILE_STREAM.close();
    }
    else 
    {
        cout << "Unable to open input file"; 
    }
  
    OUTPUT_FILE_STREAM.close();
  
    return;
}





