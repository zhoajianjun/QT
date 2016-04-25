#include <iostream>
#include <array>

int main ()
{
      std::array<int,5> myarray = { 2, 16, 77, 34, 50 };

        std::cout << "myarray contains:";
          for ( auto it = myarray.begin(); it != myarray.end(); ++it )
                  std::cout << ' ' << *it;
            std::cout << '\n';

              return 0;
}
