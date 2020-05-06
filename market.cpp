#include "market.h"
#include <cctype>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
  ((string*)userp)->append((char*)contents, size * nmemb);
  return size* nmemb;
}
market::market(){
  cout<<"MARKET_H WORKING"<<endl;
  ifstream read;
  read.open("hash.txt");
  read>>hash;
  read.close();
}
void market::GetData(){
  ofstream write;
  write.open("data.txt",ios_base::app);
  CURL *curl;
  CURLcode res;
  string readBuffer;
  curl = curl_easy_init();
  const char* c = hash.c_str();
  if(curl){
    curl_easy_setopt(curl,CURLOPT_URL,c);
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }
  Json::Reader reader;
  Json::Value obj;
  reader.parse(readBuffer,obj);

  write<<obj["lowest_price"].asString()<<" ";
  write<<obj["median_price"].asString()<<" ";
  write<<obj["volume"].asString()<<" ";
  write<<endl;
  write.close();
}

void market::GetName(){
  string url = hash;
  char char_hash[hash.size() + 1];
  strcpy(char_hash,hash.c_str());
  string currency_t = "currency=";
  string market_hash_name_t = "market_hash_name=";
  string temp;
  for(int i = 0;i<hash.size();i++){//We get the currency and name from url
    if(isalpha(char_hash[i]) || char_hash[i] == '_' || char_hash[i] == '='){
      temp.push_back(char_hash[i]);
      if(temp==currency_t){
        currency = char_hash[i+=1]-'0';
      }else if(temp==market_hash_name_t){
        string space;
        bool stop_t = false;
        bool stop_s = false;
        for(int j = i+1;j<hash.size();j++){
          if(char_hash[j]=='%'&& stop_t == false){
            string space_t;
            for(int l = j;l<j+9;l++){
              space_t.push_back(char_hash[l]);
            }if(space_t=="%E2%84%A2"){
              for(int l = j;l<j+7;l++){
                char_hash[l] = '\0';
              }
              j+=8;stop_t = true;
            }space_t.clear();
          }
          else if(char_hash[j]=='S' && stop_s == false){
            for(int k = j;k<j+9;k++){
              char_hash[j] = ' ';
            }statrack = true;
            stop_s = true;
            j+=7;
          }
          else if(char_hash[j]=='%'){
            space.push_back(char_hash[j]);
            space.push_back(char_hash[j+1]);
            space.push_back(char_hash[j+2]);
            if(space=="%20"){
              char_hash[j] = ' ';
              char_hash[j+1] = ' ';
              char_hash[j+2] = ' ';
              j+=1;
            }
          }else{
            space.clear();
            name.push_back(char_hash[j]);
          }
        }break;
      }
    }else{
    temp.clear();
    }
  }
  for(int i = 0;i<name.size();i++){
    if(name[i]=='('){
      name[i]='\0';
      for(int j = i;j<name.size();j++){
        if(name[j]!=')'){
          quality.push_back(name[j]);
          name[j]='\0';
        }else{
          name[j]='\0';
          break;
        }
      }
    }
  }
}



