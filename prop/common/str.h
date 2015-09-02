#pragma once
#ifndef __STR_H__
#define __STR_H__

#include <string>

class str
{
public:
	str();
	str(std::string s);
	str(char *s);
	str(int n);
	~str();
	size_t len() const;
	str replace(std::string sOld, std::string sNew, size_t num = 1);  // num:替换的次数
	str strip();
	str lstrip();
	str rstrip();
	size_t count(std::string s) const;
	bool startswith(std::string s) const;
	bool endswith(std::string s) const;
	size_t find(std::string s, size_t pos=0) const;
	size_t rfind(std::string s) const;
	size_t rfind(std::string s, size_t pos) const;  // 匹配[:pos]区间的，但pos可以是s(模式)的起始位置 
	str lower();
	str upper();
	//void join(list l);
	//list split(std::string s);
	//list partition(std::string s);
	//list rpartition(std::string s);
	str regexsearch(std::string patt) const;
	bool regex_replace(std::string patt, std::string sNew, size_t num = 1);  // num:替换的次数
	static str repeat(std::string s, int num);
	friend std::ostream & operator<<(std::ostream & os, const str & s);
	str operator+(const str & s) const;
	str operator+(const std::string & s) const;
	friend str operator+(std::string s1, const str & s2);
	str operator*(int times) const;
	bool operator==(const std::string & s) const;
	bool operator==(const str & s) const;
	bool operator==(const char s[]) const;
	bool operator!=(const char s[]) const;
	friend bool operator==(std::string s1, const str & s2);
	bool operator!=(const std::string & s) const;
	bool operator!=(const str & s) const;
	friend bool operator!=(std::string s1, const str & s2);

	std::string operator[] (int index) const;  // 某个索引处的字符
	str operator[] (str sRange) const;  // 参考python切片，这里写成string
	str substr(size_t Off = 0, size_t Count = std::string::npos) const;
	//切片
	//* + [] for (:)
	operator std::string() const; //在函数名后面表示是常成员函数，该函数不能修改对象内的任何成员，只能发生读操作，不能发生写操作。
	std::string tostring() const;
	int toInt() const;
	float toFloat() const;
	double toDouble() const;
private:
	void ToUpperString(std::string &str);
	void ToLowerString(std::string &str);

private:
	std::string m_s = "";
};


#endif // __STR_H__
