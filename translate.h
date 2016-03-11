
#ifndef _TRANSLATE
#define _TRANSLATE


#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <algorithm>

using namespace std;

vector<string> make3sections(vector<string> v);
vector<string> split(string str, char delimiter);
vector<string> toNasm(vector<string> input, string &section, vector<string> &vars);
vector<string> regList();
bool isInlist(string key, vector<string> list);
string checkData(string key, vector<string> s);
vector<string> conver2Param (vector<string> masmstr,  vector<string> vars);
string compressVec(vector<string>);
vector<string> convertVar (vector<string> masmstr, vector<string> &vars);
vector<string> conver2Param (vector<string> masmstr, vector<string> vars);


vector<string> make3sections(vector<string> v)
{
  //
  // Seperate a vector of strings based on the comma between operators.
  //
  
      int i = 0;
      string tmpstr = "";
      string otmp;
      vector<string> that;
      
      for(string str: v){
      

      if(i == 0) // command
      {
        that.push_back(str);
      }
      else if(str[str.size()-1] != ',') //value with no comma
      {
        if(tmpstr == "")
        {  
          tmpstr += str;
        }
        else{
          tmpstr = tmpstr + " " + str;
        }
        
      }
      else if(str[str.size()-1] == ',') // value with comma
      {
        otmp = str.substr(0, str.size()-1);
        if(tmpstr == ""){
          that.push_back(otmp); 
        }
        else{
          tmpstr = tmpstr + " " + otmp;
          that.push_back(tmpstr);
          tmpstr == "";
        }
      }
      
      i++;
    }
    that.push_back(tmpstr);
    
    return that;
}


vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  
  return internal;
}


//
//
//
// This is the main function. All conversions get called from inside here.
//
//


vector<string> toNasm(vector<string> input, string &section, vector<string> &vars)
{

  vector<string> nasm;
  
  if(input.front()=="mov")
  {
    nasm = conver2Param(input, vars); 
  }
  else if(input.front()=="add")
  {
    nasm = conver2Param(input, vars); 
  }
  else if(input.front()=="sub")
  {
    nasm = conver2Param(input, vars);
  }
    else if(input.front()=="inc")
  {
    nasm = input;
  } 
  else if(input.front()=="dec")
  {
    nasm = input;
  }
  
  else if(input.front()==".data")
  {
   nasm.push_back("SECTION .data"); // Direct translation to NASM
   section = ".data"; 
  }
  else if(input.front()==".code")
  {
    nasm.push_back("SECTION .text"); // Direct translation to NASM
    section = ".code"; 
  }
  else if(input.front() == "INVOKE")
  {
    if(input.at(1) == "ExitProcess,"){
      nasm.push_back("_exit:\nmov eax, 0\nmov ebx, 1\nint 80h");
    }
  }
  else if(input.front() == "main") // TODO: set up for more than just identify the main function
  {
    if(input.back() == "PROC")
      nasm.push_back("global _main\n_main:");
    else if (input.back() == "ENDP")
      nasm.push_back(""); //Do nothing
  }
  else if(input.front() == "END" || input.front() == ".386" || input.front() == ".MODEL" || 
  input.front() == ".STACK" || input.front() == "ExitProcess" || input.front() == "dwExitCode:DWORD")
  {
    nasm.push_back(""); //Do nothing
  }
  else if(section == ".data") // WE are currently in the data section looking at a varible and not the end of the .data section
  {
    nasm = convertVar(input, vars);
  }
  else
  {
    // some unknown line of asembly code
    nasm.push_back(" ; Could not convert --> { " + compressVec(input) + " } ");    
  }
  
  return nasm;
}




vector<string> instList(){
  
  std::vector<string> list;
  
  list.push_back("mov");
  list.push_back("MOV");
  list.push_back("add");
  list.push_back("ADD");
  
  return list;
}




vector<string> regList()
{
  
  vector<string> list;
  
  list.push_back("eax");
  list.push_back("ebx");
  list.push_back("ecx");
  list.push_back("edx");
  list.push_back("EAX");
  list.push_back("EBX");
  list.push_back("ECX");
  list.push_back("EDX");
  list.push_back("ax");
  list.push_back("bx");
  list.push_back("cx");
  list.push_back("dx");
  list.push_back("AX");
  list.push_back("BX");
  list.push_back("CX");
  list.push_back("DX");
  list.push_back("ah");
  list.push_back("bh");
  list.push_back("ch");
  list.push_back("dh");
  list.push_back("AH");
  list.push_back("BH");
  list.push_back("CH");
  list.push_back("DH");
  list.push_back("al");
  list.push_back("bl");
  list.push_back("cl");
  list.push_back("dl");
  list.push_back("AL");
  list.push_back("BL");
  list.push_back("CL");
  list.push_back("DL");
  
  list.push_back("ebi");
  list.push_back("edi");
  list.push_back("esp");
  list.push_back("epi");
  list.push_back("edi");
  list.push_back("EBI");
  list.push_back("EDI");
  list.push_back("ESP");
  list.push_back("EPI");
  list.push_back("EDI");
  
  return list;
}





bool isInlist(string key, vector<string> list){
  
  
  if(key[key.size()-1] == ','){
    key = key.substr(0, key.size()-1);
    
    if (std::find(list.begin(), list.end(), key ) != list.end()) {
      
      return true;
    }
    else
      return false;
  }
  else{
        if (std::find(list.begin(), list.end(), key ) != list.end()) {
      
      return true;
    }
    else
      return false;
  }
  
}



// --------------
// Checks if the key is in the list. This list contians varible info seperated by a space.
// This being the name, and size of the variable respectivlly.
// ie. "temp DWORD"
// --------------

string checkData(string key, vector<string> list){

string tok;
for(std::vector<string>::iterator it = list.begin(); it != list.end(); ++it) {
    stringstream ss(*it);
    getline(ss, tok, ' ');
    
    if(tok == key)
    {
      getline(ss, tok, ' ');
      return tok;
    }
  }
  return "";
}




string compressVec(vector<string> vec){
  
  string total = "";
  int i = 0;
  for(string str: vec){
    total += str;
    if(i < str.size())
    {
      total += " ";
    }
    i++;
  } 
  //TODO: cut off the extra " " at the end of total
  
  return total;
  
}






vector<string> convertVar (vector<string> masmstr, vector<string> &vars){
  
  
  vector<string> nasmstr;
  
  string varnamesize = "";
  
  int i =0;
  
  if(masmstr[2] =="?"){ //uninitialised var
   for(string str: masmstr){
     if(i==0){
      varnamesize += str;
      nasmstr.push_back(str + ":");
     }
     else if(i==1){
      varnamesize += " ";
      if(masmstr[1] == "DWORD"){
        nasmstr.push_back("resd");
        varnamesize += "DWORD";
      }
      else if(masmstr[1] == "BYTE"){
        nasmstr.push_back("resb");
        varnamesize += "BYTE";
      }
      else if(masmstr[1] == "WORD"){
        nasmstr.push_back("resw");
        varnamesize += "WORD";
      }
      else if(masmstr[1] == "QWORD"){
        nasmstr.push_back("resq");
        varnamesize += "QWORD";
      }
     }
     else if(i==2){
      nasmstr.push_back("1"); // single uninitilised varible (etc. 1 DWORD)
     }
     i++;
    }
  }
  else if (masmstr.size() >= 4){ // an array
    for(string str: masmstr){
     if(i==0){
      varnamesize += str;
      nasmstr.push_back(str + ":");
     }
     else if(i==1){
      varnamesize += " ";
      varnamesize += str;
      if(str == "DWORD")
        nasmstr.push_back("DD,");
      else if(str == "BYTE,")
        nasmstr.push_back("DB,");
      else if(str == "WORD,")
        nasmstr.push_back("DW,");
      else if(str == "QWORD")
        nasmstr.push_back("DQ,");
     }
     else if (i == masmstr.size()){
       nasmstr.push_back(str);
     }
    else {
       nasmstr.push_back( str);
     }
    i++;
    }
  }
  else{   //initialused var
    for(string str: masmstr){
    
     if(str==""){
      nasmstr.push_back("");
     }
     else if(i==0){
      varnamesize += str;
      nasmstr.push_back(str + ":");
     }
     else if(i==1){
      varnamesize += " ";
      varnamesize += str;
      if(str == "DWORD")
        nasmstr.push_back("DD");
      else if(str == "BYTE")
        nasmstr.push_back("DB");
      else if(str == "WORD")
        nasmstr.push_back("DW");
      else if(str == "QWORD")
        nasmstr.push_back("DQ");
     }
     else if(i==2){
      nasmstr.push_back(str);
     }
     i++;
    }
  }
  vars.push_back(varnamesize);
  
  return nasmstr;
}




vector<string> conver2Param (vector<string> masmstr, vector<string> vars){
    
    
    vector<string> nasm;
    int i = 0;
    vector<string> tmpline;
    masmstr = make3sections(masmstr);
    string size;
    
    for(string str: masmstr){
      if(i == 0) // command
      {
        //nasm.push_back("mov"); // will have to chnage to acomadtae for movl and such
      
        nasm.push_back(str);
        
      }
      else if(i == 1) //first operator
      {
        bool sp = false;
        for(char c: str){
          if(c==' ')
            sp=true;
        }
        if(sp){ // str has space in it
           tmpline = split(str, ' ');
           if(tmpline.front() == "OFFSET") // operator is an offset
            nasm.push_back(tmpline.back());
          else
            {  } //Not sure what else
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
            else
            {
              nasm.push_back(str + ","); // integer
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
           tmpline = split(str, ' ');
           if(tmpline.front() == "OFFSET") // operator is an offset
            nasm.push_back(tmpline.back());
          else
            {  }//Not sure what else
        }
        else{ // no space in the string
          if(isInlist(str, regList())){ //str is a register
             nasm.push_back(str);
          }
          else{ // str is NOT a register
            size = checkData(str, vars);
            if(size != ""){
              nasm.push_back(size + " [" + str +"]"); // TODO make sure this is correct syntaxt for nasm
            }
            else
            {
              nasm.push_back(str); //integer
            }
          }
        }
      }
      
      i++;
    }
    cout << "\n";
    
    return nasm;
    
}



#endif
