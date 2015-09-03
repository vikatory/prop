#include "bill.h"
#include <boost/algorithm/string.hpp>
#include <exception>
#include <boost/lexical_cast.hpp>
#include "CommonFuncs.h"
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
	cout << "输入指令:";
	char cmd[256];
	cin.getline(cmd, 256);
	return string(cmd);
}

//   指令名    指令名          指令        参数                       
//  +---------+---------------+-----------+---------------------------------------------+
//  添加物品   addItem         ai          序号 物品名
//  +---------+---------------+-----------+---------------------------------------------+
//  添加批次   addVoume        av          物品序号 序号 时间=0(当前时间)
//  +---------+---------------+-----------+---------------------------------------------+
//  添加货单   addGoods        ag          物品序号 批次号 单号 类型 数量 单价 总价 保管费
//  +---------+---------------+-----------+---------------------------------------------+
//  删除货单   delGoods        dg          物品名 批次号 单号
//  +---------+---------------+-----------+---------------------------------------------+
//  校正价格   correctionPrice cp          物品名 批次号 单号 [1校正单价2校正总价]
//  +---------+---------------+-----------+---------------------------------------------+
//  查看收益   showEarnings    se          物品名 批次号=0(全部批次)
//  +---------+---------------+-----------+---------------------------------------------+
//  保存文件   save            save         
//  +---------+---------------+-----------+---------------------------------------------+


#define RETURN_IF(condition) if(condition) return;

void CBillApp::processCmd(string cmd)
{
	m_Bill->correctOrder();
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
			int nItemOrdr = boost::lexical_cast<int>(tokens[0]);
			int nVolumeOrdr = boost::lexical_cast<int>(tokens[1]);
			CItem *pItem = m_Bill->item(nItemOrdr);
			if (pItem != nullptr)
			{
				pItem->addVolume(nVolumeOrdr);
			}
		}
		else if (sCmdName == "ag")
		{
			int nItemOrdr = boost::lexical_cast<int>(tokens[0]);
			int nVolumeOrdr = boost::lexical_cast<int>(tokens[1]);
			int nGoodsOrder = boost::lexical_cast<int>(tokens[2]);
			string sGoodsType = tokens[3];
			int nGoodsNum = boost::lexical_cast<int>(tokens[4]);
			int nSucc = boost::lexical_cast<int>(tokens[4]);
			string sGoodsPrice = tokens[5];
			string sGoodsTotalPrice = tokens[6];
			string sGoodsCustodial = tokens[7];
			CItem *pItem = m_Bill->item(nItemOrdr);
			if (pItem != nullptr)
			{
				CVolume *pVolume = pItem->volume(nVolumeOrdr);
				if (pVolume != nullptr)
				{
					pVolume->addGoods(nGoodsOrder, sGoodsType, nGoodsNum, sGoodsPrice, sGoodsTotalPrice, sGoodsCustodial, TOBOOL(nSucc));
				}
			}
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
		else if (sCmdName == "reload")
		{
			m_Bill->reload();
		}
	}
	catch (exception& e)
	{
		cout << "Standard exception: " << e.what() << endl;
		cout << "指令解析错误" << endl;
	}
	m_Bill->correctOrder();
}


void CBillApp::exit()
{
	isExit = true;
}