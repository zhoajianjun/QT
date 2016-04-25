#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

const int MAXSIZE = 100;

class CMyString
{
public:
	CMyString(const CMyString& copy);
	CMyString(const char *init);
	CMyString();
	~CMyString(){
		delete[] m_pstr;
	}
	int Length() const{
		return m_ncurlen;
	}
	int Find(CMyString part) const;
	char* GetBuffer() const;

public:
	CMyString& operator()(int pos, int len);
	bool operator==(const CMyString cmp_str) const;
	bool operator!=(const CMyString cmp_str) const;
	bool operator<(const CMyString cmp_str) const;
	bool operator>(const CMyString cmp_str) const;
	bool operator!() const{
		return m_ncurlen == 0;
	}
	CMyString& operator=(const CMyString &copy);
	CMyString& operator+=(const CMyString &add);
	char& operator[](int i);
	friend ostream& operator<<(ostream&, CMyString&);
	friend istream& operator>>(istream&, CMyString&);
private:
	void Next();

private:
	int m_ncurlen;
	char *m_pstr;
	int *m_pnext;
};
