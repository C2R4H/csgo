#include <iostream>
#include <string>
//Header files
#include "weapon.h"
#include "weapon.cpp"
#include "gui.h"
#include "gui.cpp"
#include "market.h"
#include "market.cpp"

using namespace std;

int main(){
  market market;
  market.GetData();
  market.GetName();
  cout<<market.ShowName()<<endl;
  cout<<market.ShowCurrency()<<endl;
  cout<<market.ShowStatrack()<<endl;
  cout<<market.ShowQuality()<<endl;
}
