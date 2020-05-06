#ifndef weapon_h
#define weapon_h
#include <string>
using namespace std;
class weapon{
  private:
    string name;//Name of the weapon
    string hash;//Web hash to get all the numbers
    double price;//Price on the market 
    double old_price;//Price that you buyed the item for
    double volume;//How many items are on the market
  public:
    weapon();

    string ShowName(){return name;}
    void ChangeName(string name){this->name = name;}

    string ShowHash(){return hash;}
    void ChangeHash(string hash){this->hash = hash;}

    double ShowOldPrice(){return old_price;}
    void ChangeOldPrice(double old_price){this->old_price = old_price;}

    double ShowVolume(){return volume;}
    void RefreshVolume(double volume){this->volume = volume;}

    double ShowPrice(){return price;}
    void RefreshPrice(double price){this->price = price;}
};

#endif
