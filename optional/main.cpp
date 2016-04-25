#include <iostream>
#include <boost/optional.hpp>

using namespace std;
using namespace boost;

int main()
{
    cout << "Hello World!" << endl;
optional<int> n(10);
cout<<*n<<endl;
optional<string> str("sstring");
cout<<*str<<endl;
//str.emplace("monado",3);
cout<<*str<<endl;
    return 0;
}

