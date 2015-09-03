#include "bill.h"
#include <boost/algorithm/string.hpp>
#include <exception>
#include <boost/lexical_cast.hpp>
#include <iostream>

using namespace std;


CBillApp::CBillApp()
{
}

CBillApp::~CBillApp()
{
	if (m_Bill != nullptr)
	{
		delete m_Bill;
	}
}

void CBillApp::run()
{
	m_Bill = new CBill();
	loop();
}

void CBillApp::loop()
{
	while (!isExit)
	{
		str cmd = input();
		processCmd(cmd);
	}
}

string CBillApp::input()
{
	cout << str("=") * 80 << endl;
	cout << "����ָ��:";
	char cmd[256];
	cin.getline(cmd, 256);
	return string(cmd);
}

//   ָ����    ָ����          ָ��        ����                       
//  +---------+---------------+-----------+---------------------------------------------+
//  �����Ʒ   addItem         ai          ��� ��Ʒ��
//  +---------+---------------+-----------+---------------------------------------------+
//  �������   addVoume        av          ��Ʒ�� ��� ʱ��=0(��ǰʱ��)
//  +---------+---------------+-----------+---------------------------------------------+
//  ��ӻ���   addGoods        ag          ��Ʒ�� ���κ� ���� ���� ���� ���� �ܼ� ���ܷ�
//  +---------+---------------+-----------+---------------------------------------------+
//  ɾ������   delGoods        dg          ��Ʒ�� ���κ� ����
//  +---------+---------------+-----------+---------------------------------------------+
//  У���۸�   correctionPrice cp          ��Ʒ�� ���κ� ���� [1У������2У���ܼ�]
//  +---------+---------------+-----------+---------------------------------------------+
//  �鿴����   showEarnings    se          ��Ʒ�� ���κ�=0(ȫ������)
//  +---------+---------------+-----------+---------------------------------------------+
//  �����ļ�   save            save         
//  +---------+---------------+-----------+---------------------------------------------+


#define RETURN_IF(condition) if(condition) return;

void CBillApp::processCmd(string cmd)
{
	vector<string> tokens;
	boost::split(tokens, cmd, boost::is_any_of(" "));
	for_each(tokens.begin(), tokens.end(), [](string &s) {boost::trim(s); });
	tokens.erase(remove_if(tokens.begin(), tokens.end(), [](string s) {return s == ""; }), tokens.end());
	if (tokens.size() < 1) return;
	string sCmdName = tokens[0];

	try
	{
		tokens.erase(tokens.begin());

		if (sCmdName == "ai")
		{
			int nItemOrdr = boost::lexical_cast<int>(tokens[0]);
			string sItemName = tokens[1];
			m_Bill->addItem(nItemOrdr, sItemName);
		}
		else if (sCmdName == "av")
		{

		}
		else if (sCmdName == "ag")
		{


		}
		else if (sCmdName == "dg")
		{

		}
		else if (sCmdName == "cp")
		{

		}
		else if (sCmdName == "se")
		{

		}
		else if (sCmdName == "save")
		{
			m_Bill->save();
		}
	}
	catch (exception& e)
	{
		cout << "Standard exception: " << e.what() << endl;
		cout << "ָ���������" << endl;
	}
}


void CBillApp::exit()
{
	isExit = true;
}