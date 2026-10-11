#include<iostream>
#include<cctype>
#include<string>
#include<sstream>
#include<unordered_map>
using namespace std;
string execute(string line,unordered_map<string,string>&store){
   istringstream iss(line);
   string command;
   if(!(iss>>command)) return "";
   for(char &c:command)
      c=toupper((unsigned char)c);
   if(command=="SET"){
     string key,value;
     if(!(iss>>key)){
       return "ERR wrong number of arguments";
     }
     getline(iss>>ws,value);
     if(value.empty()){
        return "ERR wrong number of arguments";
     }
     store[key]=value;
     return "ok";
   }
   else if(command=="GET"){
      string key,extra;
      if(!(iss>>key))
        return "ERR wrong number of arguments";
      if(iss>>extra)
        return "ERR wrong number of arguments";
      auto it = store.find(key);
      if(it!=store.end())
         return it->second;
      else
        return "nil";
   }else if(command=="DEL"){
     string key,extra;
     if(!(iss>>key))
       return "ERR wrong number of arguments";
     if(iss>>extra)
       return "ERR wrong number of arguments";
    if(store.erase(key))
      return "Deleted";
    else
      return "nil";
   } else if(command=="EXIT"){
    string extra;
    if(iss>>extra)
      return "ERR wrong number of arguments";
    return "EXIT";
   } else{
     return "Unknown command";
   }
}
int main(){
   unordered_map<string,string>store;
   string line;
   while(true){
    cout<<">";
    if(!getline(cin,line)) break;
    string reply=execute(line,store);
    if(reply=="EXIT")
        break;
    cout<<reply<<"\n";
   }
}