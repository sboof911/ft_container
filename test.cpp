#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// int main()
// {
//     allocator<int> tmp;
//     int *i = tmp.allocate(2);
//     tmp.construct(i, 5);
//     cout << *i <<endl;

//     vector<int> help;
// }

int main ()
{
std::vector<int>::size_type sz;

  std::vector<int> foo;
  std::vector<int>::iterator it;
  
  foo.assign(7, 100);
  std::cout << foo.size() << " and " << foo.capacity() << std::endl;
  std::cout << foo[5] << std::endl;
  foo.assign(10, 22);
  std::cout << foo.size() << " and " << foo.capacity() << std::endl;
  std::cout << foo[5] << std::endl;
}