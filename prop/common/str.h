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
	str replace(std::string sOld, std::string sNew, size_t num = 1);  // num:�滻�Ĵ���
	str strip();
	str lstrip();
	str rstrip();
	size_t count(std::string s) const;
	bool startswith(std::string s) const;
	bool endswith(std::string s) const;
	size_t find(std::string s, size_t pos=0) const;
	size_t rfind(std::string s) const;
	size_t rfind(std::string s, size_t pos) const;  // ƥ��[:pos]����ģ���pos������s(ģʽ)����ʼλ�� 
	str lower();
	str upper();
	//void join(list l);
	//list split(std::string s);
	//list partition(std::string s);
	//list rpartition(std::string s);
	str regexsearch(std::string patt) const;
	bool regex_replace(std::string patt, std::string sNew, size_t num = 1);  // num:�滻�Ĵ���
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

	std::string operator[] (int index) const;  // ĳ�����������ַ�
	str operator[] (str sRange) const;  // �ο�python��Ƭ������д��string
	str substr(size_t Off = 0, size_t Count = std::string::npos) const;
	//��Ƭ
	//* + [] for (:)
	operator std::string() const; //�ں����������ʾ�ǳ���Ա�������ú��������޸Ķ����ڵ��κγ�Ա��ֻ�ܷ��������������ܷ���д������
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
