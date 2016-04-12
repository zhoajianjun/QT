#include <iostream>
#include "cache.h"
#include "fiforeplacealgorithm.h"


using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    Cache cache(LRU);
    cache.Replace();
    return 0;
}

