#include "database.h"
#include <iostream>
#include <fstream>
using namespace std;

database::database(){
  cout<<"DATABASE_H WORKING"<<endl;
  ifstream read;
  read.open("./data/hash.txt");
  ofstream write;
  write.open("./data/hash_base.txt");
  string hash;
  int i = 0;
  while(read>>hash){
    write<<i<<" "<<hash<<endl;
    i++;
  }
}

void database::ShowData(){
}

