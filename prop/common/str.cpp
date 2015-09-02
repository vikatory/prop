// -------------------------------------------------------------------------------
// @Author      : hejia
// @Created     : 2015-05-08 23:45
// @Desc        :
// -------------------------------------------------------------------------------

#pragma once
#include "str.h"
#include <cctype>
#include <sstream>
#include <regex>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;


str::str()
{
}

str::str(std::string s)
{
	m_s = s;
}

str::str(char *s)
{
	m_s = string(s);
}

str::str(int n)
{
	stringstream ss;
	m_s = "";
	ss << n;
	ss >> m_s;
}

str::~str()
{
}

size_t str::len() const
{
	return m_s.length();
}

str str::replace(string sOld, string sNew, size_t num)
{
	if (num < 1)
		return *this;

	size_t idx = 0;
	size_t start = 0;
	size_t nOldLen = sOld.length();
	size_t nNewLen = sNew.length();
	size_t cnt = 0;
	while(idx!=-1)
	{
		idx = m_s.find(sOld, start);
		if(idx!=-1)
			cnt++;
		else
			break;
		if(cnt>num)
			break;
		m_s.replace(idx, nOldLen, sNew);
		start = idx + nNewLen;
	}

	return *this;
}




str str::strip()
{
	lstrip();
	rstrip();
	return *this;
}


str str::lstrip()
{
	if (m_s.empty())
	{
		return *this;
	}
	m_s.erase(0,m_s.find_first_not_of(" "));
	m_s.erase(0, m_s.find_first_not_of("\n"));
	m_s.erase(0, m_s.find_first_not_of("\t"));
	return *this;
}

str str::rstrip()
{
	if (m_s.empty())
	{
		return *this;
	}
	m_s.erase(m_s.find_last_not_of(" ") + 1);
	m_s.erase(m_s.find_last_not_of("\n") + 1);
	m_s.erase(m_s.find_last_not_of("\t") + 1);
	return *this;
}

size_t str::count(std::string s) const
{
	size_t idx = 0;
	size_t start = 0;
	size_t ilen = s.length();
	size_t cnt = 0;
	while(idx!=-1)
	{
		idx = m_s.find(s, start);
		if(idx!=-1)
		{
			cnt++;
		}
		start = idx + ilen;
	}
	return cnt;
}

bool str::startswith(std::string s) const
{
	return m_s.find(s) != -1;
}

bool str::endswith(std::string s) const
{
	return m_s.rfind(s) != -1;
}

size_t str::find(string s, size_t pos) const
{
	return m_s.find(s, pos);
}

size_t str::rfind(string s) const
{
	return m_s.rfind(s);
}

size_t str::rfind(string s, size_t pos) const
{
	return m_s.rfind(s, pos);
}


str str::lower()
{
	ToLowerString(m_s);
	return *this;
}

str str::upper()
{
	ToUpperString(m_s);
	return *this;
}

str RegexSearch(std::string tar, std::string patt);

str str::regexsearch(std::string patt) const
{
	return RegexSearch(m_s, patt);
}

bool str::regex_replace(string patt, string sNew, size_t num)  // 待测试
{
	bool bSucc = false;
	if (num < 1)
		return bSucc;

	size_t idx = 0;
	size_t nOldLen = 0;
	size_t nNewLen = sNew.length();
	size_t cnt = 0;
	string tar = m_s;
	string match = "";
	string result = "";

	match = RegexSearch(tar, patt);
	while (match!="")
	{
		cnt++;
		if (cnt>num)
			break;
		bSucc = true;
		nOldLen = match.length();
		idx = tar.find(match, 0);  // 必然找到了
		tar.replace(idx, nOldLen, sNew);
		result += tar.substr(0, idx);
		tar = tar.substr(idx + nNewLen);
		match = RegexSearch(tar, patt);
	}
	result += tar;
	m_s = result;
	return bSucc;
}












std::ostream & operator<<(std::ostream & os, const str & s)
{
	os << s.m_s;
	return os;
}

str str::operator + (const str & s) const
{
	return str(m_s+s.tostring());
}

str str::operator + (const string & s) const
{
	return str(m_s+s);
}

str operator + (string s1, const str & s2)
{
	return str(s1 + s2.tostring());
}

str str::operator * (int times) const
{
	string result;
	result.reserve(times*m_s.length()); // 避免重复的重新分配
	for (int a = 0; a < times; a++)
		result += m_s;
	return str(result);
}


bool str::operator==(const std::string & s) const
{
	return m_s == s;
}

bool str::operator==(const str & s) const
{
	return m_s == s.tostring();
}

bool operator==(std::string s1, const str & s2)
{
	return s1 == s2.tostring();
}

bool str::operator==(const char s[]) const
{
	return m_s == s;
}

bool str::operator!=(const char s[]) const
{
	return m_s != s;
}

bool str::operator!=(const std::string & s) const
{
	return m_s != s;
}

bool str::operator!=(const str & s) const
{
	return m_s != s.tostring();
}

bool operator!=(std::string s1, const str & s2)
{
	return s1 != s2.tostring();
}

std::string str::operator[] (int index) const
{
	size_t idx = index;
	if (0 <= idx && idx < m_s.length())
	{
		return m_s.substr(idx, 1);
	}
	return "";
}

str str::operator[] (str sRange) const
{
	sRange.strip();
	string digit = "";
	int idx = 0;
	int beg = 0;
	int end = 0;
	vector<str> num;
	if (sRange.regexsearch("^[0-9]+$") != "")  // 单独一个狮子座
	{
		idx = sRange.toInt();
	}
	else if (sRange.regexsearch("^[0-9]*:[0-9]*$") != "")  // [:]
	{

	}
	else if (sRange.regexsearch("^[0-9]+:[0-9]+:[0-9]+$") != "")  // [::]
	{

	}
	return str();
}


str str::substr(size_t Off, size_t Count) const
{
	return m_s.substr(Off, Count);
}







str::operator std::string() const
{
	return m_s;
}

string str::tostring() const
{
	return m_s;
}

int str::toInt() const
{
	// 不严谨，其他进制的情况
	string digit = str(m_s).strip().regexsearch("^[0-9]+$");
	int n = 0;
	if (digit != "")
	{
		n = atoi(digit.c_str());
	}
	return n;
}








void str::ToUpperString(string &str)
{
	transform(str.begin(), str.end(), str.begin(), (int(*)(int))toupper);
}

void str::ToLowerString(string &str)
{
	transform(str.begin(), str.end(), str.begin(), (int(*)(int))tolower);
}

str RegexSearch(std::string tar, std::string patt)
{
	const regex pattern(patt);
	match_results<string::const_iterator> result;
	string match = "";
	bool valid = regex_search(tar, result, pattern);
	if (valid)
	{
		match = result[0];
	}
	return match;
}