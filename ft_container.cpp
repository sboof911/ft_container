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
// int main ()
// {
//   ft::vector<int>   myvector (10);   // 10 zero-initialized ints
//   ft::iterator<int>  it;
//   // assign some values:
//   for (unsigned i=0; i<myvector.size(); i++)
//     myvector.at(i)=i;

//   std::cout << "myvector contains:";
//   for (it=0; it<myvector.size(); it++)
//     std::cout << ' ' << myvector[it];
//   std::cout << '\n';

//   return 0;
// }

// int main () {
//   // ft::vector<int> myvector;
//   // for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

//   // typedef ft::vector<int>::iterator iter_type;

//   // ft::iterator<iter_type> rev_it;

//   // rev_it = myvector.begin() + 3;

//   // std::cout << "The fourth element from the end is: " << *rev_it << '\n';

//   // return 0;
// }

int main ()
{
  ft::vector<int> myvector;
  for (int i=1; i<=5; i++) myvector.push_back(i);

  std::cout << "myvector contains:";
  std::cout << "begin = " << *myvector.begin() << " and end = " << *myvector.end() << std::endl;
  for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}