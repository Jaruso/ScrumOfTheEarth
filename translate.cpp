// #include "translate.h"

// vector<string> make3sections(vector<string> v)
// {
//   //
//   // Seperate a vector of strings based on the comma between operators.
//   //
  

//       int i = 0;
//       string tmpstr = "";
//       string otmp;
//       vector<string> that;
      
//       for(string str: v){
      

//       if(i == 0) // command
//       {
//         that.push_back(str);
//       }
//       else if(str[str.size()-1] != ',') //value with no comma
//       {
//         if(tmpstr == "")
//         {  
//           tmpstr += str;
//         }
//         else{
//           tmpstr = tmpstr + " " + str;
//         }
        
//       }
//       else if(str[str.size()-1] == ',') // value with comma
//       {
//         otmp = str.substr(0, str.size()-1);
//         if(tmpstr == ""){
//           that.push_back(otmp); 
//         }
//         else{
//           tmpstr = tmpstr + " " + otmp;
//           that.push_back(tmpstr);
//           tmpstr == "";
//         }
//       }
      
      
//       i++;
//     }
//     that.push_back(tmpstr);
    
//     return that;
// }




// vector<string> split(string str, char delimiter) {
//   vector<string> internal;
//   stringstream ss(str); // Turn the string into a stream.
//   string tok;
  
//   while(getline(ss, tok, delimiter)) {
//     internal.push_back(tok);
//   }
  
//   return internal;
// }


// vector<string> toNasm(vector<string> input)
// {
  
//   vector<string> nasm = convertMov(input, tempVars());  

//   return nasm;
// }

// vector<string> tempVars(){
  
//   vector<string> list;
  
//   list.push_back("temp DWORD");
//   list.push_back("otemp BYTE");

//   return list;
  
  
// }


// vector<string> regList()
// {
  
//   vector<string> list;
  
  
//   list.push_back("eax");
//   list.push_back("ebx");
//   list.push_back("ecx");
//   list.push_back("edx");
//   list.push_back("EAX");
//   list.push_back("EBX");
//   list.push_back("ECX");
//   list.push_back("EDX");
//   list.push_back("ax");
//   list.push_back("bx");
//   list.push_back("cx");
//   list.push_back("dx");
//   list.push_back("AX");
//   list.push_back("BX");
//   list.push_back("CX");
//   list.push_back("DX");
//   list.push_back("ah");
//   list.push_back("bh");
//   list.push_back("ch");
//   list.push_back("dh");
//   list.push_back("AH");
//   list.push_back("BH");
//   list.push_back("CH");
//   list.push_back("DH");
//   list.push_back("al");
//   list.push_back("bl");
//   list.push_back("cl");
//   list.push_back("dl");
//   list.push_back("AL");
//   list.push_back("BL");
//   list.push_back("CL");
//   list.push_back("DL");
  
//   list.push_back("ebi");
//   list.push_back("edi");
//   list.push_back("esp");
//   list.push_back("epi");
//   list.push_back("edi");
//   list.push_back("EBI");
//   list.push_back("EDI");
//   list.push_back("ESP");
//   list.push_back("EPI");
//   list.push_back("EDI");
  
//   return list;
// }


// bool isInlist(string key, vector<string> list){
  
  
//   if(key[key.size()-1] == ','){
//     key = key.substr(0, key.size()-1);
    
//     if (std::find(list.begin(), list.end(), key ) != list.end()) {
      
//       return true;
//     }
//     else
//       return false;
//   }
//   else{
//         if (std::find(list.begin(), list.end(), key ) != list.end()) {
      
//       return true;
//     }
//     else
//       return false;
//   }
  
// }



// bool checkData(string key, vector<string> list){

// // checks if the key is in the list. This list contians varibles,
// // with each string being the name, and size of tghe variable respectivlly.
// // ie. "temp DWORD"
// string tok;

// for(std::vector<string>::iterator it = list.begin(); it != list.end(); ++it) {
//     stringstream ss(*it);
//     getline(ss, tok, ' ');
//     if(tok == key)
//     {
//       return true;
//     }
//   }
//   return false;
// }



// vector<string> convertMov (vector<string> masmstr, vector<string> vars){
    
    
//     vector<string> nasm;
//     int i = 0;
//     bool size;
//     vector<string> tmpline;
//     masmstr = make3sections(masmstr);
//     std::vector<string> varnames;
    
//     for(std::vector<string>::iterator it = vars.begin(); it != vars.end(); ++it) {
//       //cout << *it;
//     }
//       //
//     cout << " convert \n";
//     for(string str: masmstr){
//       if(i == 0) // command
//       {
//         nasm.push_back("mov"); // will have to chnage to acomadtae for movl and such
//       }
//       else if(i == 1) //first operator
//       {
//         bool sp = false;
//         for(char c: str){
//           if(c==' ')
//             sp=true;
//         }
//         if(sp){ // str has space in it
           
//         }
//         else{ // no space in the string
//           if(isInlist(str, regList())){ //str is a register
//             nasm.push_back(str);
//           }
//           else{ // str is NOT a register
//             if(isInlist(str, varnames)){
              
//             }
          
            
//           }
//         }
        
//       }
//       else if(i == 2) //second operator
//       {
//         bool sp = false;
//         for(char c: str){
//           if(c==' ')
//             sp=true;
//         }
//         if(sp){ // str has space in it
           
//         }
//         else{ // no space in the string
//           if(isInlist(str, regList())){ //str is a register
//             nasm.push_back(str);
//           }
//           else{ // str is NOT a register
            
//           }
//         }
//       }
      
//       i++;
//     }
//     cout << "\n";
    
//     return nasm;
    


// }

