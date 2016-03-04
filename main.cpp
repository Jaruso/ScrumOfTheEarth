#include "translate.h"



vector<string> convertMov (vector<string> masmstr, vector<string> vars){
    
    
    vector<string> nasm;
    int i = 0;
    bool size;
    vector<string> tmpline;
    masmstr = make3sections(masmstr);
    std::vector<string> varnames;
    
    for(std::vector<string>::iterator it = vars.begin(); it != vars.end(); ++it) {
      //cout << *it;
    }
      //
    cout << " convert \n";
    for(string str: masmstr){
      //cout << str << " ";
      if(i == 0) // command
      {
        nasm.push_back("mov"); // will have to chnage to acomadtae for movl and such
      }
      else if(i == 1) //first operator
      {
        bool sp = false;
        for(char c: str){
          if(c==' ')
            sp=true;
        }
        if(sp){ // str has space in it
           
        }
        else{ // no space in the string
          if(isInlist(str, regList())){ //str is a register
            cout << "in else and if";
             nasm.push_back(str);
          }
          else{ // str is NOT a register
            cout << "in else and else\n";
            if(!checkData(str, varnames)){
              stringstream ss(str);
              string name, size;
              ss >> size;
              getline(ss, name, ' ');
              ss << size;
              cout << "  --  " << name << " " << size << "  --\n";
            }
          
            
          }
        }
        
      }
      else if(i == 2) //second operator
      {
        bool sp = false;
        for(char c: str){
          if(c==' ')
            sp=true;
        }
        if(sp){ // str has space in it
           
        }
        else{ // no space in the string
          if(isInlist(str, regList())){ //str is a register
             nasm.push_back(str);
          }
          else{ // str is NOT a register
            
          }
        }
      }
      
      i++;
    }
    cout << "\n";
    
    return nasm;
    


}





int main()
{

    ofstream myfile;
    myfile.open ("testMASMtext.txt");

    string test = "mov temp, eax";

  
    if(checkData("temp",tempVars()))
      cout << "its here\n";
    else
      cout << "not here\n";
    vector<string> newString = toNasm(split(test, ' '));


    cout << test + "\n";
   
    for(string str: newString){
      cout << str + " ";
    }
    
    return 0;

}




