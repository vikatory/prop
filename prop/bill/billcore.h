#pragma once

#include <string>
#include <vector>
#include "str.h"
#include "tinyxml.h"
#include "tinystr.h"

class CItem;

class CBill
{
public:
	CBill();
	~CBill();
	bool load();
	void reload();
	void addItem(CItem* pItem);
	void addItem(int nItemOrder, std::string sItemName);
	void save();
	TiXmlElement* tiXmlElement();
	void correctOrder();
	void showItems();
	CItem* item(int nItemOrder);
private:
	std::vector<CItem*> m_Items;
};




class CCoin
{
public:
	CCoin();
	CCoin(std::string sCoin);
	~CCoin();
	std::string serial() const;

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
	CGoods(int nOrder, std::string sType, int nNum, CCoin oPrice, CCoin oTotalPrice, CCoin oCustodial, bool bSucc);
	~CGoods();
	TiXmlElement* tiXmlElement();
	void setOrder(int nOrder);
private:
	int m_Order = -1;
	std::string m_Type = "";
	int m_Num = 0;
	CCoin m_Price;
	CCoin m_TotalPrice;
	CCoin m_Custodial;
	bool m_Succ;
	bool m_IsValid = false;
};

class CVolume
{
public:
	CVolume();
	CVolume(int nOrder, std::string sTime);
	~CVolume();
	void addGoods(CGoods * pGoods);
	void addGoods(int nOrder, std::string sType, int nNum, std::string sPrice, std::string sTotalPrice, std::string sCustodial, bool bSucc);
	TiXmlElement* tiXmlElement();
	void setOrder(int nOrder);
	void correctOrder();
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
	void addVolume(int nOrder);
	CVolume* volume(int nVolumeOrder);
	TiXmlElement* tiXmlElement();
	void setOrder(int nOrder);
	void correctOrder();
private:
	int m_Order = -1;
	std::string m_Name = "";
	std::vector<CVolume*> m_Volumes;
};







