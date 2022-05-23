#include <iostream>
#include <memory>
#include <vector>
#include <iterator>
using namespace std;

// int main()
// {
//     allocator<int> tmp;
//     int *i = tmp.allocate(2);
//     tmp.construct(i, 5);
//     cout << *i <<endl;

//     vector<int> help;
// }


class InternationalStudent
{
  private :
      string  _Nation;
  
  public :
      InternationalStudent() : _Nation(NULL){};
      InternationalStudent(string nation) : _Nation(nation){};
      bool  isFounded(){return (!_Nation.empty());};
    
};

int   main()
{
  int   n[10];
}

