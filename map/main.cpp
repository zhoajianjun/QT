#include <iostream>
#include <map>
#include <string>

using namespace std;


int main ()
{
    std::map<char,int> mymap;

    // first insert function version (single parameter):
    mymap.insert ( pair<char,int>('a',100) );
    mymap.insert ( pair<char,int>('z',200) );
    mymap.insert ( pair<char,int>('c',300));

    pair<map<char,int>::iterator,bool> ret;
    ret = mymap.insert ( pair<char,int>('z',500) );
    if (ret.second==false) {
        cout << "element 'z' already existed";
        cout << " with a value of " << ret.first->second << '\n';
    }

    // second insert function version (with hint position):
    map<char,int>::iterator it = mymap.begin();
    mymap.insert (it, pair<char,int>('b',300));  // max efficiency inserting
    mymap.insert (it, pair<char,int>('c',400));  // no max efficiency inserting

    // third insert function version (range insertion):
    map<char,int> anothermap;
    anothermap.insert(mymap.begin(),mymap.find('c'));

    // showing contents:
    cout << "mymap contains:\n";
    for (it=mymap.begin(); it!=mymap.end(); ++it)
        cout << it->first << " => " << it->second << '\n';

    cout << "anothermap contains:\n";
    for (it=anothermap.begin(); it!=anothermap.end(); ++it)
        cout << it->first << " => " << it->second << '\n';

    cout<<mymap.size()<<endl;

    return 0;
}
int main7()
{
    map<char,int> mymap;
    mymap['a']=10;
    mymap['b']=20;
    mymap['c']=30;
    mymap['d']=40;
    auto it=mymap.find('a');
    if(it!=mymap.end())
        mymap.erase(it);
    cout<<"b=>"<<mymap.find('b')->second<<'\n';
    cout<<"c=>"<<mymap.find('c')->second<<'\n';
    cout<<"d=>"<<mymap.find('d')->second<<'\n';

    return 0;
}


int main6 ()
{
    std::map<char,int> mymap;
    //std::map<char,int>::iterator it;


    // insert some values:
    mymap['a']=10;
    mymap['b']=20;
    mymap['c']=30;
    mymap['d']=40;
    mymap['e']=50;
    mymap['f']=60;
    mymap['h']=70;

    auto it=mymap.find('b');
    mymap.erase (it);                   // erasing by iterator

    mymap.erase ('c');                  // erasing by key
    mymap.erase ('h');

    it=mymap.find ('e');
    mymap.erase ( it, mymap.end() );    // erasing by range

    // show content:
    for (it=mymap.begin(); it!=mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    return 0;
}
int main4 ()
{
    std::map<char,int> mymap;
    auto it = mymap.end();

    it = mymap.emplace_hint(it,'b',10);
    mymap.emplace_hint(it,'a',12);
    mymap.emplace_hint(mymap.end(),'c',14);

    std::cout << "mymap contains:";
    for (auto& x: mymap)
        std::cout << " [" << x.first << ':' << x.second << ']';
    std::cout << '\n';

    return 0;
}

int main3 ()
{
    std::map<char,int> mymap;
    char c;

    mymap ['a']=101;
    mymap ['c']=202;
    mymap ['f']=303;

    for (c='a'; c<'h'; c++)
    {
        std::cout << c;
        if (mymap.count(c)>0)
            std::cout << " is an element of mymap.\n";
        else
            std::cout << " is not an element of mymap.\n";
    }

    return 0;
}
/****clear****/
int main2()
{
    std::map<char,int> mymap;

    mymap['x']=100;
    mymap['y']=200;
    mymap['z']=300;

    std::cout << "mymap contains:\n";
    for (auto it=mymap.begin(); it!=mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    mymap.clear();//清除所有元素
    mymap['a']=1101;
    mymap['b']=2202;

    std::cout << "mymap contains:\n";
    for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    return 0;
}



/****cbegin()****/
int main1()
{
    map<char,int>mymap;
    mymap['a']=200;
    mymap['b']=300;
    mymap['c']=400;

//    for(auto it=mymap.begin();it!=mymap.end();++it)
//        cout<<(*it).first<<(*it).second;
    for(auto it=mymap.cbegin();it!=mymap.cend();++it)
        cout<<(*it).first<<(*it).second;
}
/****at****/
#if 0
int main()
{
    map<string,int> mymap={
        {"aaa",0},
        {"bbb",0},
        {"ccc",0}
    };
    mymap.at("aaa")=10;
    mymap.at("bbb")=20;
    mymap.at("ccc")=30;
    for(auto& x:mymap)
        cout<<x.first<<x.second<<endl;
    cout << "Hello World!" << endl;
    return 0;
}
#endif



