#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;
int main(){
   unordered_map<string,string>store;
   string command,key,value;
   while(true){
    cout<<">";
    cin>>command;
    if(command=="SET"){
        cin>>key>>value;
        store[key]=value;
        cout<<"OK\n";
    }else if(command=="GET"){
        cin>>key;
        if(store.count(key)) cout<<store[key]<<"\n";
        else cout<<"Not present\n";
    }else if(command=="EXIT"){
        break;
    }else if(command=="DEL"){
          cin>>key;
          if(store.count(key)){
             store.erase(key);
             cout<<"Deleted\n";
          }
          else{
            cout<<"Not Present\n";
          }
    }
    else{
        cout<<"Unknown Command"<<"\n";
    }
   }
}