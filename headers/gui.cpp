#include "gui.h"
#include <iostream>
using namespace std;

void gui::ShowMenu(){
  cout<<"1-->Add a gun"<<endl;
}

int gui::GetChoice(){
  int choice;
  cout<<"Insert chosen number : ";cin>>choice;
  return choice;
}
