#include<iostream>
#include<string>
#include<sstream>
#include<unordered_map>
using namespace std;
int main(){
   unordered_map<string,string>store;
   string line;
   while(true){
    cout<<">";
    if(!getline(cin,line)) break;
    istringstream iss(line);
    string command;
    if(!(iss>>command)) continue;
    if(command=="SET"){
        string key,value;
        if(!(iss>>key)){
            cout<<"ERR wrong number of arguments\n";
            continue;
        } 
        getline(iss,value);
        if(value.empty()){
            cout<<"ERR wrong number of arguments\n";
            continue;
        }
        store[key]=value;
        cout<<"OK\n";
    }else if(command=="GET"){
        string key;
        if(!(iss>>key)){
            cout<<"ERR wrong number of arguments\n";
            continue;
        }
        if(store.count(key)) cout<<store[key]<<"\n";
        else cout<<"nil\n";
    }else if(command=="EXIT"){
        break;
    }else if(command=="DEL"){
          string key;
          if(!(iss>>key)){
            cout<<"ERR wrong number of arguments\n";
            continue;
          }
          if(store.count(key)){
             store.erase(key);
             cout<<"Deleted\n";
          }
          else{
            cout<<"nil\n";
          }
    }
    else{
        cout<<"Unknown Command"<<"\n";
    }
   }
}