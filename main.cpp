#include<iostream>
#include<cctype>
#include<string>
#include<sstream>
#include<unordered_map>
#include<vector>
#include<algorithm>
using namespace std;
string err="ERR wrong number of arguments";
string execute(vector<string> v,unordered_map<string,string>&store){
  string command=v[0];
   if(command=="SET"){
     string key=v[1],value=v[2];
     store[key]=value;
     return "ok";
   }
   else if(command=="GET"){
      string key=v[1];
      auto it = store.find(key);
      if(it!=store.end())
         return it->second;
      else
        return "nil";
   }else if(command=="DEL"){
    string key=v[1];
    if(store.erase(key))
      return "Deleted";
    else
      return "nil";
   }
   return "ERR unknown command";
}
vector<string>tokenize(string line){
  vector<string>v(4);
  istringstream iss(line);
  if(!(iss>>v[0])){
      v[0]=err;
      return v;
  }
    for(char &c:v[0])
        c=toupper(c);
 if(v[0]=="EXIT"){
   if(iss>>v[1]){
      v[0]=err;
      v.erase(v.begin()+1,v.end());
      return v;
   } 
 } else if(v[0]=="GET"||v[0]=="DEL"){
  if(!(iss>>v[1])){
    v[0]=err;
    v.erase(v.begin()+1,v.end());
    return v;
  }
  if(iss>>v[2]){
    v[0]=err;
    v.erase(v.begin()+1,v.end());
    return v;
  } 
 }
 else if(v[0]=="SET"){
   if(!(iss>>v[1])){
    v[0]=err;
    v.erase(v.begin()+1,v.end());
    return v;
   } 
  getline(iss>>ws,v[2]);
  if(v[2].empty()){
    v[0]=err;
    v.erase(v.begin()+1,v.end());
    return v;
  }
 } else{
  v[0]="Unknown Command";
  v.erase(v.begin()+1,v.end());
  return v;
 }
  return v;
}
int main(){
   unordered_map<string,string>store;
   string line;
   while(true){
    cout<<">";
    if(!getline(cin,line)) break;
    vector<string>reply=tokenize(line);
    if(reply[0]==err)
       cout<<err<<"\n";
    else if(reply[0]=="EXIT")
        break;
    else if(reply[0]=="Unknown Command"){
      cout<<reply[0]<<"\n";
    }
    else{
      string ans=execute(reply,store);
      cout<<ans<<"\n";
    }
   }
}