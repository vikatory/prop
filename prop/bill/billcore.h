#pragma once

#include <string>
#include <vector>
#include "str.h"

class CItem;

class CBill
{
public:
	CBill();
	~CBill();
	bool load();
	void addItem(CItem* pItem);

private:
	std::vector<CItem*> m_Items;
};




class CCoin
{
public:
	CCoin();
	CCoin(std::string sCoin);
	~CCoin();

	friend std::ostream & operator<<(std::ostream & os, const CCoin & c);

private:
	int m_Jin = 0;
	int m_Yin = 0;
	int m_Tong = 0;
};


class CGoods
{
public:
	CGoods();
	CGoods(int nOrder, std::string sType, int nNum, CCoin oPrice, CCoin oTotalPrice, CCoin oCustodial);
	~CGoods();

private:
	int m_Order = -1;
	std::string m_Type = "";
	int m_Num = 0;
	CCoin m_Price;
	CCoin m_TotalPrice;
	CCoin m_Custodial;
	bool m_IsValid = false;
};

class CVolume
{
public:
	CVolume();
	CVolume(int nOrder, std::string sTime);
	~CVolume();
	void addGoods(CGoods * pGoods);

private:
	int m_Order = -1;
	std::string m_Time = "";
	std::vector<CGoods*> m_Goods;
	bool m_IsValid = false;
};

class CItem
{
public:
	CItem();
	CItem(int nOrder, std::string sName);
	~CItem();
	void addVolume(CVolume* pVolume);

private:
	int m_Order = -1;
	std::string m_Name = "";
	std::vector<CVolume*> m_Volumes;
};







