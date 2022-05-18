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
  vector<int> myvector (10);   // 10 zero-initialized ints

  // assign some values:
  for (unsigned i=0; i<myvector.size(); i++)
    myvector.at(i)=i;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector.at(i);
  std::cout << '\n';

  return 0;
}