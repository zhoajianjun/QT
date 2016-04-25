#include <iostream>
#include <boost/foreach.hpp>
#include <boost/assign.hpp>
#include <vector>
#include <map>
#include <boost/algorithm/minmax_element.hpp>
#include <boost/algorithm/clamp.hpp>
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
using namespace std;
#define foreachs BOOST_FOREACH
#define reverseforeach BOOST_REVERSE_FOREACH

int main1()
{
    using namespace boost::assign;
    vector<int > v=(list_of(1),2,3,4,5,6);

    BOOST_FOREACH(auto c,v)
    {
        cout<<c<<",";
    }
    string str("boost foreach");
    BOOST_FOREACH(auto& d,str)
    {
        cout<<d<<",";
    }

    cout << "Hello World!" << endl;
    return 0;
}
int main2()
{
    int arr[]={1,2,3,4,5};
    foreachs(auto& x,arr)
    {
        cout<<x<<endl;
    }
    map<int,string> m={{1,"AA"},{2,"BB"}};
    foreachs(auto& c,m)
    {
        cout<<c.first<<c.second<<endl;
    }



    return 0;
}
int main3()
{
    string str1("100");
    string str2("200");
    //auto y=minmax(str1,str2);
    auto y=minmax({1,2,3,4,8});
    cout<<get<0>(y)<<get<1>(y)<<endl;


    return 0;
}
int main4()
{
    vector<int> v={1,23,4,5,7,30};

    auto x=minmax_element(v.begin(),v.end());
    cout<<*x.first<<"   "<<*x.second<<endl;

    return 0;
}
int main5()
{
    using namespace boost::algorithm;
    cout<<clamp(5,1,10)<<endl;
    cout<<clamp(5,5,10)<<endl;
    cout<<clamp(5,1,5)<<endl;
    cout<<clamp(5,1,4)<<endl;
    cout<<clamp(5,6,10)<<endl;

    return 0;
}
int main6()
{
    using namespace boost;
    unordered_set<int> s={1,2,3,4,5,6};
    for(auto& c:s)
    {
        cout<<c<<endl;
    }
    cout<<s.size()<<endl;
    s.clear();
    s.insert(5);
    s.insert(6);
    cout<<s.size()<<endl;
    cout<<*s.find(6)<<endl;
    return 0;
}
int main()
{
    using namespace boost::assign;
    using namespace boost;
    unordered_map<int ,string> mp=map_list_of(1,"aa")(2,"bb")(3,"cc");
    mp.insert(make_pair(10,"dd"));
    mp[11]="ee";
    mp[12]="ff";
    auto x =mp.begin();
    for(;x!=mp.end();++x)
    {
        cout<<x->first<<x->second<<endl;
    }
    mp.erase(11);
    cout<<mp.size()<<endl;

    return 0;
}

