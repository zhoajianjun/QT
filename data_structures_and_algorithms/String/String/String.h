/*******************************************************************************
*
* FileName : String.h
* Comment  : ��string�ַ����࣬�ṩֵ���塢�ַ���д����I/O�����ַ�����������Ϊ
*			 ����������Ⱥ�ƴ����������������ü������ٸ��ƣ������þ�̬������
*			 ��������c����ַ�����
* Version  : 1.0
* Author   : haibindev.cnblogs.com
* Date     : 2007-5-31 3:33
*
*******************************************************************************/

#ifndef _F_STRING_H_INCLUDED
#define _F_STRING_H_INCLUDED

#include <iostream>

using std::ostream;
using std::istream;

//�����ܴ���50������Ϊ100���ַ���
const int N_INPUT=100;
const int N_BUF=50;

class String {
private:
	//ʹһ��ʵ�ʱ�ʾ�ܱ���������ͬ��ֵ��String����
	struct Srep {
		char *s;	//��Ԫ�ص�ֵ��
		int sz;		//�ַ�����
		int n;		//���ü���
		Srep(int nsz, const char* p)
		{
			n=1;
			sz=nsz;
			s=new char[sz+1];
			strcpy(s,p);
		}
		~Srep() { delete[] s; }
		Srep* get_own_copy()    //��Ҫʱ��¡(�����ĸ���)
		{
			if (n==1) return this;
			n--;
			return new Srep(sz,s);
		}
		//���������ϵĸ�ֵ
		void assign(int nsz, const char* p)
		{
			if (sz!=nsz) {
				delete[] s;
				sz=nsz;
				s=new char[sz+1];
			}
			strcpy(s,p);
		}
	private:				//��ֹ����
		Srep(const Srep&);
		Srep& operator=(const Srep&);
	};
	Srep* rep;

	char* get_temp_string();	  //���ؾ�̬������

public:
	class Cref{	// ����char
		friend class String;
	private:
		String& s;
		int i;
		Cref(String& ss, int ii) : s(ss), i(ii) {}
	public:
		operator char() const { return s.read(i); }
		void operator=(char c) { s.write(i,c); }
	};

	class Range {};	  //�����쳣

	//���졢��������ֵ����
	String();
	String(const char*);
	String(const String&);
	String& operator=(const char*);
	String& operator=(const String&);
	~String();

	//����±�Խ��
	void check(int i) const { if (i<0 || rep->sz<=i) throw Range(); }

	char read(int i) const { return rep->s[i]; }
	void write(int i, char c) { rep=rep->get_own_copy(); rep->s[i]=c; }

	Cref operator[](int i) { check(i); return Cref(*this,i); }
	char operator[](int i) const { check(i); return rep->s[i]; }

	int size() const { return rep->sz; }
	//����c����ַ���
	char* c_star() { char* s=get_temp_string(); strcpy(s,rep->s); return s; }

	String& operator+=(const String&);
	String& operator+=(const char*);

	friend ostream& operator<<(ostream&, const String&);
	friend istream& operator>>(istream&, String&);

	friend bool operator==(const String& x, const char* s)
	{ return strcmp(x.rep->s, s) == 0; }

	friend bool operator==(const String& x, const String& y)
	{ return strcmp(x.rep->s, y.rep->s) == 0; }

	friend bool operator!=(const String& x, const char* s)
	{ return strcmp(x.rep->s,s) != 0; }

	friend bool operator!=(const String& x, const String& y)
	{ return strcmp(x.rep->s, y.rep->s) != 0; }
};

//���ò����ؾ�̬������
char* String::get_temp_string()
{
	static int nbuf=0;
	static char buf[N_BUF][N_INPUT+1];
	for (int i=0; i<N_BUF; ++i)
		for (int j=0; j<N_INPUT; ++j)
			buf[i][j]='\0';
	if (nbuf == N_BUF) nbuf=0;
	return buf[nbuf++];
}

String::String()
{
	rep=new Srep(0,"");
}

String::String(const String& x)
{
	x.rep->n++;
	rep=x.rep;	  //ͨ��������ʵ�ָ���
}

String::~String()
{
	if (--rep->n == 0) delete rep;
}

String& String::operator=(const String& x)
{
	x.rep->n++;
	if (--rep->n == 0) delete rep;
	rep=x.rep;		//ͨ��������ʵ�ָ�ֵ
	return *this;
}

String::String(const char* s)
{
	rep=new Srep(strlen(s),s);
}

String& String::operator=(const char* s)
{
	if (rep->n == 1)
		rep->assign(strlen(s),s);
	else {
		rep->n--;
		rep=new Srep(strlen(s),s);
	}
	return *this;
}

String& String::operator+=(const String& y)
{
	int nn=rep->sz+y.rep->sz;
	char* p=new char[nn+1];
	int k1=0;
	for (; k1<rep->sz; ++k1)
		p[k1]=rep->s[k1];
	for (int k2=0; k2<y.rep->sz; ++k2, ++k1)
		p[k1]=y.rep->s[k2];
	p[k1]='\0';
	rep=rep->get_own_copy();
	rep->assign(nn,p);
	return *this;
}

String& String::operator+=(const char* s)
{
	int nn=rep->sz+strlen(s);
	char* p=new char[nn+1];
	int k1=0;
	for (; k1<rep->sz; ++k1)
		p[k1]=rep->s[k1];
	for (int k2=0; k2<strlen(s); ++k2, ++k1)
		p[k1]=s[k2];
	p[k1]='\0';
	rep=rep->get_own_copy();
	rep->assign(nn,p);
	return *this;
}

ostream& operator<<(ostream& output, const String& y)
{
	output<<y.rep->s;
	return output;
}

istream& operator>>(istream& input, String& y)
{
	char* s_temp=new char[N_INPUT+1];
	input>>s_temp;
	y.rep=y.rep->get_own_copy();
	y.rep->assign(strlen(s_temp),s_temp);
	return input;
}

#endif