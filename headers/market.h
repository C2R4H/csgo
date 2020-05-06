#ifndef market_h
#define market_h
#include <string>
using namespace std;
class market{
  private:
    string name;
    string quality;
    string hash;
    string statrack_word;
    bool statrack;
    int id;
    double price;
    double med_price;
    double volume;
    double currency;
  public:
    market();

    void StartMarket(int id);
    int ShowId(){return id;}

    void ChangeHash(string hash){this->hash = hash;}
    string ShowHash(){return hash;}

    void ChangeName(string name){this->name = name;}
    string ShowName(){return name;}

    void ChangeQuality(string quality){this->quality = quality;}
    string ShowQuality(){return quality;}

    void ChangeStatrack(bool statrack){this->statrack = statrack;}
    bool ShowStatrack(){return statrack;}

    string ShowStatrackW(){return statrack_word;}
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
    void UrlDecrypter();//We decrypt the URL (%28->'(')
};

#endif
