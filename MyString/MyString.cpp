#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

#include "MyString.h"



CMyString::CMyString(){			//create empty string
	m_pstr = new char[MAXSIZE + 1];
	if (!m_pstr){
		cerr << "Allocation Error" << endl;
		return;
	}
	this->m_ncurlen = 0;
	m_pstr[0] = '\0';
}

CMyString::CMyString(const char *init){		//initialize the string with char*
	m_pstr = new char[MAXSIZE + 1];
	if (!m_pstr){
		cerr << "Allocation Error" << endl;
		return;
	}
	this->m_ncurlen = strlen(init);
	strcpy(m_pstr, init);
}

CMyString::CMyString(const CMyString &copy){	//initialize the string with string
	m_pstr = new char[MAXSIZE + 1];
	if (!m_pstr){
		cerr << "Allocation Error" << endl;
		return;
	}
	this->m_ncurlen = copy.m_ncurlen;
	strcpy(m_pstr, copy.m_pstr);
}

int CMyString::Find(CMyString part) const{		//string match :KMP
	int posP = 0, posT = 0;
	int lengthP = part.m_ncurlen, lengthT = this->m_ncurlen;

	part.Next();
	while (posP < lengthP&&posT < lengthT){
		if (part.m_pstr[posP] == this->m_pstr[posT]){
			posP++;
			posT++;
		}
		else{
			if (posP == 0){
				posT++;
			}
			else{
				posP = part.m_pnext[posP - 1];
			}
		}
	}
	delete[] part.m_pnext;
	if (posP < lengthP){
		return 0;
	}
	else{
		return 1;
	}
}

void CMyString::Next(){			//get the next char for matching : KMP
	int length = this->m_ncurlen;
	this->m_pnext = new int[length];
	this->m_pnext[0] = 0;
	for (int i = 1; i < length; i++){
		int j = this->m_pnext[i - 1];
		while (*(this->m_pstr + i) != *(this->m_pstr + j) && j > 0){
			j = this->m_pnext[j - 1];
		}
		if (*(this->m_pstr + i) == *(this->m_pstr + j)){
			this->m_pnext[i] = j + 1;
		}
		else{
			this->m_pnext[i] = 0;
		}
	}
	//	for(int i=0;i<length;i++)
	//		cout<<i<<":\t"<<m_pnext[i]<<endl;
}

char *CMyString::GetBuffer() const{		//get the char* from string
	return this->m_pstr;
}

CMyString& CMyString::operator()(int pos, int len){		//get len char with the begining of pos
	CMyString *temp = new CMyString;
	if (pos<0 || pos + len - 1>MAXSIZE || len < 0){
		temp->m_ncurlen = 0;
		temp->m_pstr[0] = '\0';
	}
	else{
		if (pos + len - 1 >= m_ncurlen){
			len = m_ncurlen - pos;
		}
		temp->m_ncurlen = len;
		for (int i = 0, j = pos; i < len; i++, j++){
			temp->m_pstr[i] = m_pstr[j];
		}
		temp->m_pstr[len] = '\0';
	}
	return *temp;
}

bool CMyString::operator==(const CMyString cmp_str) const{
	if (this->m_ncurlen != cmp_str.m_ncurlen){
		return 0;
	}
	for (int i = 0; i < this->m_ncurlen; i++){
		if (this->m_pstr[i] != cmp_str.m_pstr[i])
			return 0;
	}
	return 1;
}
bool CMyString::operator!=(const CMyString cmp_str) const{
	if (*this == cmp_str)
		return 0;
	return 1;
}
bool CMyString::operator<(const CMyString cmp_str) const{
	if (this->m_ncurlen != cmp_str.m_ncurlen){
		return this->m_ncurlen < cmp_str.m_ncurlen;
	}
	for (int i = 0; i < this->m_ncurlen; i++){
		if (this->m_pstr[i] != cmp_str.m_pstr[i]){
			return this->m_pnext[i]<cmp_str.m_pnext[i];
		}
	}
	return 0;
}
bool CMyString::operator>(const CMyString cmp_str) const{
	if (*this < cmp_str || *this == cmp_str){
		return 0;
	}
	return 1;
}
CMyString& CMyString::operator=(const CMyString &copy){		//赋值操作
	delete[] this->m_pstr;
	this->m_pstr = new char[copy.m_ncurlen + 1];
	strcpy
		(this->m_pstr, copy.m_pstr);
	return *this;
}
CMyString& CMyString::operator+=(const CMyString &add){		//字符串追加
	int length = this->m_ncurlen + add.m_ncurlen;
	int n = this->m_ncurlen;
	CMyString temp(*this);
	delete[] this->m_pstr;
	this->m_pstr = new char[length + 1];
	for (int i = 0; i < n; i++){
		this->m_pstr[i] = temp[i];
	}
	for (int i = n; i < length; i++){
		this->m_pstr[i] = add.m_pstr[i - n];
	}
	this->m_pstr[length] = '\0';
	return *this;
}
char& CMyString::operator[](int i){		//取元素
	if (i < 0 || i >= this->m_ncurlen){
		cout << "out of boundary!" << endl;
	}
	return this->m_pstr[i];
}

ostream& operator<<(ostream& os, CMyString& str){
	os << str.m_pstr;
	return os;
}

istream& operator>>(istream& is, CMyString& str){
	is >> str.m_pstr;
	return is;
}
