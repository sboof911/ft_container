#include "vector.hpp"


// int     main()
// {
//     vector<int>     help(5);

//     std::cout << help.size() << std::endl;
//     help.resize(10);
//     std::cout << help.size() << std::endl;
//     std::cout << help.capacity() << std::endl;
//     help.push_back(5);
//     std::cout << help.size() << std::endl;
//     std::cout << help.capacity() << std::endl;
// }

int main ()
{
  std::vector<int>::size_type sz;

  std::vector<int> foo;
  std::vector<int>::iterator it;
  
  foo.assign(7, 100);
  std::cout << foo.size() << " and " << foo.capacity() << std::endl;


  return 0;
}
