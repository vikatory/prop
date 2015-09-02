#include "bill.h"
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
		//cin<<
	}
}

str CBillApp::input()
{
	cout << str("=") * 80 << endl;
	cout << str("=") * 80 << endl;
	cout << "输入指令:";
	char cmd[256];
	cin.getline(cmd, 256);
	return str(cmd);
}

//   指令名    指令名          指令        参数                       
//  +---------+---------------+-----------+---------------------------------------------+
//  添加物品   addItem         ai          序号 物品名
//  +---------+---------------+-----------+---------------------------------------------+
//  添加批次   addVoume        av          物品名 序号 时间=0(当前时间)
//  +---------+---------------+-----------+---------------------------------------------+
//  添加货单   addGoods        ag          物品名 批次号 单号 类型 数量 单价 总价 保管费
//  +---------+---------------+-----------+---------------------------------------------+
//  删除货单   delGoods        dg          物品名 批次号 单号
//  +---------+---------------+-----------+---------------------------------------------+
//  校正价格   correctionPrice cp          物品名 批次号 单号 [1校正单价2校正总价]
//  +---------+---------------+-----------+---------------------------------------------+
//  查看收益   showEarnings    se          物品名 批次号=0(全部批次)
//  +---------+---------------+-----------+---------------------------------------------+

void CBillApp::processCmd(str cmd)
{
	cout << cmd << endl;

}


void CBillApp::exit()
{
	isExit = true;
}