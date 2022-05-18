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
  std::vector<int> myvector(2);

  myvector.push_back(78);
  myvector.push_back(16);

  // now front equals 78, and back 16
  std::cout << myvector.front() << " and " << myvector.back() << std::endl;
  myvector.front() -= myvector.back();

  std::cout << "myvector.front() is now " << myvector.front() << '\n';

  return 0;
}