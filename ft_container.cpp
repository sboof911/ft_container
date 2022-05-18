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
  vector<int> myvector;

  myvector.push_back(78);
  myvector.push_back(16);

  // now front equals 78, and back 16
  std::cout << myvector.front() << " and " << myvector.back() << std::endl;
  myvector.front() -= myvector.back();

  std::cout << "myvector.front() is now " << myvector.front() << '\n';

  return 0;
}