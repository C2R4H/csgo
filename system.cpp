#include <iostream>
#include <string>
//Header files
#include "headers/weapon.h"
#include "headers/weapon.cpp"
#include "headers/gui.h"
#include "headers/gui.cpp"
#include "headers/market.h"
#include "headers/market.cpp"
#include "headers/database.h"
#include "headers/database.cpp"

using namespace std;

int main(){
  database database;
  market market;
  market.StartMarket(0);
  market.GetData();
  market.UrlDecrypter();
  market.GetName();

  cout<<market.ShowPrice()<<endl;
  cout<<market.ShowName()<<endl;
  cout<<market.ShowStatrackW()<<endl;
  cout<<market.ShowVolume()<<endl;
  cout<<market.ShowMedPrice()<<endl;
  cout<<market.ShowQuality()<<endl;
  cout<<market.ShowId()<<endl;
}
