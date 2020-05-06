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
  ifstream read_price;
  read_price.open("./data/data.txt");
  int junk;
  read_price>>junk>>price>>med_price>>volume;
  read_price.close();
}

void market::StartMarket(int id_temp){
  ifstream read;
  read.open("./data/hash_base.txt");
  string hash_t;int id_t;
  id = id_temp;
  while(read>>id_t>>hash_t)
    if(id_t == id_temp)
      hash = hash_t;
  read.close();
}

void market::GetData(){
  ofstream write;
  write.open("./data/data.txt");
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

  string price_t =  obj["lowest_price"].asString();
  price_t = price_t.erase(0, 1);
  string median_price_t = obj["median_price"].asString();
  median_price_t = median_price_t.erase(0, 1);
  string volume_t = obj["volume"].asString();
  write<<id<<" "<<price_t<<" "<<median_price_t<<" "<<volume_t<<endl;
  write<<endl;
  write.close();
}

void market::GetName(){
  string url = hash;//We copy the hash into a new stringc

  string currency_t = "currency=";//9
  string mhn_t = "market_hash_name=";//15
  string statrack_t = "StatTrak";//8

  bool GetCurrency = false;
  bool market_hash_t = false;
  bool GetStatrack = false;
  bool GetName = false;
  bool GetQuality = false;
  int is_statrak = 0;

  string word_temp;
  for(int i = 0;i<url.size();i++){

      if(GetCurrency==false&&url[i]=='c'&&url[i+1]=='u'){
        for(int j = i;j<i+currency_t.size();j++)
          word_temp.push_back(url[j]);
        if(word_temp == currency_t){
          i+=currency_t.size();
          currency = url[i+currency_t.size()]-'0';
          GetCurrency = true;
        }
      }



      else if(market_hash_t == false){
        for(int j = i;j<i+mhn_t.size();j++)
          word_temp.push_back(url[j]);
        if(word_temp == mhn_t){
          i+=16;
          market_hash_t = true;
        }
      }

      else if(GetName == false && GetCurrency==true&& market_hash_t == true){
        if(GetStatrack==false&&url[i]=='S'){
          GetStatrack = true;
          for(int j = i;j<i+8;j++)
            word_temp.push_back(url[j]);
          if(word_temp==statrack_t){
            statrack = true;
            is_statrak = 1;
            word_temp.erase();
          }
        }
        
        int l;

        if(is_statrak == 1){
          statrack_word = "True";
          l = i+8;}

        else if(is_statrak != 1){
          statrack_word = "False";
          l = i;}

        while(url[l]!='>'){
          word_temp.push_back(url[l]);
          l++;
        }

        while(word_temp[0]==' ')
          word_temp.erase(0,1);
        name = word_temp;
        GetName = true;
      }


      else if(GetQuality == false){
        if(url[i]=='>'){
          for(int j = i+1;j<url.size();j++){
            word_temp.push_back(url[j]);}
          quality = word_temp;
          GetQuality = true;
        }
      }

      word_temp.clear();
    }
}

void market::UrlDecrypter(){
  string url = hash;//We copy the hash into a new workable string

  string url20 = "%20";//' '
  string url28 = "%28";//'('
  string url29 = "%29";//')'
  string url7C = "%7C";//'|'
  string urlE284 = "%E2";//'™'

  string word_temp;
  for(int i = 0;i<url.size();i++){

    if(url[i]=='%'){
      for(int j = i;j<i+3;j++)
        word_temp.push_back(url[j]);

      if(word_temp==url20 || word_temp==url29){
        for(int j = i;j<=i+2;j++){
          if(j!=i+2)
            url[j]='\0';
          else
            url[j]=' ';
        }i+=2;
      }

      else if(word_temp==url28){
        for(int j = i;j<=i+2;j++){
          if(j!=i+2)
            url[j]='\0';
          else
            url[j]='>';
        }i+=2;
      }

      else if(word_temp==url7C){
        for(int j = i;j<=i+2;j++){
          if(j!=i+2)
            url[j]='\0';
          else
            url[j]='|';
        }i+=2;
      }

      else if(word_temp==urlE284){
        for(int j = i;j<=i+8;j++){
          if(j!=i+8)
            url[j]='\0';
          else
            url[j]=' ';
        }i+=8;
      }

      word_temp.clear();
    }
  }

  string url_t;
  for(int i = 0;i<url.size();i++){
    if(url[i]!='\0'){
      url_t.push_back(url[i]);
    }
  }
  hash = url_t;
}
