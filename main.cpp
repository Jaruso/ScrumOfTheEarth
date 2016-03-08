#include "translate.h"



vector<string> convertMov (vector<string> masmstr, vector<string> vars){
    
    
    vector<string> nasm;
    int i = 0;
    vector<string> tmpline;
    masmstr = make3sections(masmstr);
    string size;
    
   // for(std::vector<string>::iterator it = vars.begin(); it != vars.end(); ++it) {
      //cout << *it;
   // }
      //
   // cout << " convert \n";
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
            //cout << "in else and if";
             nasm.push_back(str+ ",");
          }
          else{ // str is NOT a register
            //cout << "in else and else\n";
            size = checkData(str, vars);
            if(size != ""){
              nasm.push_back(size + " [" + str +"],");
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
    string test = "";

    cout << " \t Current variables for testing are (temp DWORD) and (otemp BYTE)\n";
    cout << "Input a line of Masm for translating. \n";
    getline(cin, test);
 //   test = "mov eax, ebx";

  
    vector<string> newString = toNasm(split(test, ' '));

    cout << "Input: " << endl;
    cout << test + "\n";
   
    cout << "Output: " << endl;
    for(string str: newString){
      cout << str + " ";
    }
    
    return 0;

}




