#ifndef market_h
#define market_h
#include <string>
#include <fstream>
using namespace std;
class market{
  private:
    string name;
    string quality;
    string hash;
    bool statrack;
    double price;
    double med_price;
    double volume;
    double currency;
  public:
    market();

    string ShowQuality(){return quality;}
    string ShowName(){return name;}
    void ChangeName(string name){this->name = name;}
    void ChangeQuality(string quality){this->quality = quality;}
    bool ShowStatrack(){return statrack;}
    void ChangeStatrack(bool statrack){this->statrack = statrack;}
    double ShowPrice(){return price;}
    void RefreshPrice(double price){this->price = price;}
    double ShowMedPrice(){return med_price;}
    void RefreshMedPrice(double med_price){this->med_price = med_price;}
    double ShowVolume(){return volume;}
    void RefreshVolume(double volume){this->volume = volume;}
    double ShowCurrency(){return currency;}
    void RefreshCurrency(double currency){this->currency = currency;}

    string GetHash(){return hash;}
    void GetData();//Lowest Price \ Median Price \Volume(Quantity)
    void GetName();//Name of the weapon \ Quality \ is Statrack?
};

#endif
