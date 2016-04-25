#include <iostream>
#include <boost/version.hpp>
#include <boost/smart_ptr.hpp>

using namespace std;
using namespace boost;

int main1()
{
    cout << "Hello World!" << endl;
    cout<<BOOST_VERSION<<endl;
    scoped_ptr<string> sp(new string("test"));
    assert(sp);
    cout<<*sp<<endl;
    //scoped_ptr<string> sp1=sp;
    return 0;
}

// Copyright (c) 2015
// Author: Chrono Law

void case1()
{
    scoped_ptr<string> sp(new string("text"));

    assert(sp);
    assert(sp != nullptr);

    cout << *sp << endl;
    cout <<  sp->size() << endl;
}

//////////////////////////////////////////

struct posix_file
{
    posix_file(const char * file_name)
    {   cout << "open file:" << file_name << endl; }
    ~posix_file()
    {   cout << "close file" << endl;   }
};

void case2()
{
    scoped_ptr<posix_file> fp(new posix_file("/tmp/a.txt"));

    scoped_ptr<int> p(new int);

    if (p)
    {
        *p = 100;
        cout << *p << endl;
    }

    p.reset();

    assert(p == 0);
    if (!p)
    {   cout << "scoped_ptr == nullptr" << endl;   }

}

//////////////////////////////////////////

class ptr_owned final
{
    scoped_ptr<int> m_ptr;
};

void bad_case()
{
    scoped_ptr<string> sp(new string("text"));

    //sp++;
    //scoped_ptr<string> sp2 = sp;
    //std::prev(sp);
    //ptr_owned p;
    //ptr_owned p2(p);
}

//////////////////////////////////////////

//void case_unique()
//{
//    auto p = boost::make_unique<int>(10);

//    assert(p && *p == 10);

//    p.release();
//    assert(!p);

//    auto a = boost::make_unique<int[]>(5);
//    a[0] = 100;
//    a[4] = 500;
//    //a[5] = 1000;
//}

//////////////////////////////////////////
/// \brief main
/// \return
///
void case3()
{

    int *arr=new int[10];
    scoped_array<int> sa(arr);
    fill_n(&sa[0],10,5);
    cout<<sa[0]<<sa[1]<<sa[2]<<endl;
}
void case4()
{
    unique_ptr<int[]> up(new int[10]);
    assert(up);
    up[0]=10;
    cout<<up[0]<<endl;
}
void case5()
{
    std::shared_ptr<int> ptr(new int(10));
    cout<<*ptr<<endl;
    std::shared_ptr<string> pts(new string("smart"));
    cout<<*pts<<endl;
}

int main()
{
    case1();
    case2();
    case3();
    case4();
    case5();
    //case_unique();
}
