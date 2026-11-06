#include<iostream>
#include<cctype>
#include<string>
#include<sstream>
#include<unordered_map>
#include<vector>
using namespace std;
string err="ERR wrong number of arguments";
string execute(const vector<string> &v,unordered_map<string,string>&store){
  string command=v[0];
   if(command=="SET"){
     string key=v[1],value="";
     for(size_t i=2;i<v.size();i++){
      if(i!=v.size()-1)
       value+=(v[i]+" ");
      else
       value+=v[i];
     }
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
   return "";
}
vector<string>tokenize(const string& line){
  vector<string>v;
  string x;
  istringstream iss(line);
  while(iss>>x)
    v.push_back(x);
  if(!v.empty()){
   for(char &c:v[0])
     c=toupper(static_cast<unsigned char>(c));}
  return v;
}
struct ValidationResult{
  bool ok=true;
  string msg="";
};
ValidationResult validate(const vector<string>&v){
   ValidationResult res;
   if(v[0]=="SET" && v.size()<3){
       res.ok=false;
       res.msg=err;
   }
   else if((v[0]=="GET"||v[0]=="DEL")&& v.size()!=2){
       res.ok=false;
       res.msg=err;
   }
   else if(v[0]=="EXIT" && v.size()>1){
    res.ok=false;
    res.msg=err;
   }else if(v[0]!="SET"&& v[0]!="GET" && v[0]!="DEL" && v[0]!="EXIT"){
    res.ok=false;
    res.msg="ERR unknown command";
   }
   return res;
}
int main(){
   unordered_map<string,string>store;
   string line;
   while(true){
    cout<<">";
    if(!getline(cin,line)) break;
    vector<string>tokens=tokenize(line);
    if(tokens.empty())
      continue;
    ValidationResult res=validate(tokens);
    if(!res.ok){
      cout<<res.msg<<"\n";
      continue;
    }
    if(tokens[0]=="EXIT")
      break;
    cout<<execute(tokens,store)<<"\n";
   }
}