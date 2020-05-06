#ifndef database_h
#define database_h
#include <string>
using namespace std;
class database{
  private:
    string hash;
    int id;
  public:
    database();
    void ShowData(int input);
};
#endif
