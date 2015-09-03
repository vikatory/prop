#include "billcore.h"
#include "sys.h"
#include "QFile.h"
#include <windows.h>
#include "CommonFuncs.h"
//#include <atlstr.h>  //CString
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;



string UTF8ToGBK(const string& strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	unsigned short * wszGBK = new unsigned short[len + 1];
	memset((LPWSTR)wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, (LPWSTR)wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL); //strUTF8 = szGBK; 
	std::string strTemp(szGBK);
	delete[]szGBK;
	delete[]wszGBK;
	return strTemp;
}

string GBKToUTF8(const string& strGBK)
{
	string strOutUTF8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUTF8;
}



CBill::CBill()
{
	load();
}

CBill::~CBill()
{
	for_each(m_Items.begin(), m_Items.end(), [](CItem * pItem) {delete pItem; });
}

void CBill::addItem(CItem* pItem)
{
	m_Items.push_back(pItem);
}

void CBill::addItem(int nItemOrder, std::string sItemName)
{
	CItem* pItem = new CItem(nItemOrder, sItemName);
	addItem(pItem);
	cout << "添加物品: " << nItemOrder << " " << sItemName << endl;
}

TiXmlElement* CBill::tiXmlElement()
{
	TiXmlElement *pRoot = new TiXmlElement("bill");
	for_each(m_Items.begin(), m_Items.end(), [&pRoot](CItem * pItem) {pRoot->LinkEndChild(pItem->tiXmlElement()); });
	return pRoot;
}

void CBill::correctOrder()
{
	int nNum = 1;
	for_each(m_Items.begin(), m_Items.end(), [&nNum](CItem * pItem) {pItem->setOrder(nNum++); pItem->correctOrder(); });
}

void CBill::showItems()
{

}

CItem*  CBill::item(int nItemOrder)
{
	int cnt = m_Items.size();
	if (nItemOrder <= cnt)
	{
		return m_Items[nItemOrder - 1];
	}
	return nullptr;
}

void CBill::save()
{
	correctOrder();
	string appPath = getAppPath();
	string sFileNmae = appPath + "tdbilldata.xml";
	try
	{
		TiXmlDocument *pDocument = new TiXmlDocument();
		TiXmlDeclaration * pDecl = new TiXmlDeclaration("1.0", "UTF-8", "");
		TiXmlElement *pRoot = tiXmlElement();
		pDocument->LinkEndChild(pDecl);
		pDocument->LinkEndChild(pRoot);
		pDocument->SaveFile(sFileNmae.c_str());
		delete pDocument;  // 子节点的delete在析构里
	}
	catch (exception& e)
	{
		cout << "Standard exception: " << e.what() << endl;
	}
}

void CBill::reload()
{
	for_each(m_Items.begin(), m_Items.end(), [](CItem * pItem) {delete pItem; });
	m_Items.clear();
	load();
}

bool CBill::load()
{
	string appPath = getAppPath();
	string sFileNmae = appPath + "tdbilldata.xml";
	// 有时间编译boost
	//if (QFileInfo(sFileNmae).exists())
	//{
	//	cout << sFileNmae << endl;
	//}
	//else
	//{
	//	cout << "未发现数据文件" << endl;
	//}
	cout << sFileNmae << endl;

	//读取xml文件，并遍历
	try
	{
		//创建一个xml的文档对象。
		TiXmlDocument *oDocument = new TiXmlDocument(sFileNmae.c_str());
		oDocument->LoadFile();
		TiXmlElement* root = oDocument->RootElement();

		for (TiXmlNode*  item = root->FirstChild("item"); item;	item = item->NextSibling("item"))
		{
			TiXmlAttribute *oItemAttr = item->ToElement()->FirstAttribute();
			int nItemOrder = boost::lexical_cast<int>(oItemAttr->Value());
			oItemAttr = oItemAttr->Next();
			string sItemName = UTF8ToGBK(string(oItemAttr->Value()));  // 能自动判断编码就好
			CItem* pItem = new CItem(nItemOrder, sItemName);

			for (TiXmlNode* volume = item->FirstChild("volume"); volume; volume = volume->NextSibling("volume"))
			{
				TiXmlAttribute *oVolumeAttr = volume->ToElement()->FirstAttribute();
				int nVolumeOrder = boost::lexical_cast<int>(oVolumeAttr->Value());
				oVolumeAttr = oVolumeAttr->Next();
				string sVolumeTime = UTF8ToGBK(string(oVolumeAttr->Value()));
				CVolume* pVolume = new CVolume(nVolumeOrder, sVolumeTime);

				for (TiXmlNode* goods = volume->FirstChild("goods"); goods; goods = goods->NextSibling("goods"))
				{
					TiXmlAttribute *oGoodsAttr = goods->ToElement()->FirstAttribute();
					int nGoodsOrder = boost::lexical_cast<int>(oGoodsAttr->Value());
					oGoodsAttr = oGoodsAttr->Next();
					string sGoodsType = UTF8ToGBK(string(oGoodsAttr->Value()));
					oGoodsAttr = oGoodsAttr->Next();
					int nGoodsNum = boost::lexical_cast<int>(oGoodsAttr->Value());
					oGoodsAttr = oGoodsAttr->Next();
					string sGoodsPrice = string(oGoodsAttr->Value());
					oGoodsAttr = oGoodsAttr->Next();
					string sGoodsTotalPrice = string(oGoodsAttr->Value());
					oGoodsAttr = oGoodsAttr->Next();
					string sGoodsCustodial = oGoodsAttr->Value();
					oGoodsAttr = oGoodsAttr->Next();
					int nSucc = boost::lexical_cast<int>(oGoodsAttr->Value());

					CCoin oGoodsPrice = CCoin(sGoodsPrice);
					CCoin oGoodsTotalPrice = CCoin(sGoodsTotalPrice);
					CCoin oGoodsCustodial = CCoin(sGoodsCustodial);

					CGoods * pGoods = new CGoods(nGoodsOrder, sGoodsType, nGoodsNum, sGoodsPrice, sGoodsTotalPrice, sGoodsCustodial, TOBOOL(nSucc));
					pVolume->addGoods(pGoods);
				}
				pItem->addVolume(pVolume);
			}
			addItem(pItem);
		}
	}
	catch (string& e)
	{
		cout << "读取数据失败: " << e << endl;
		return false;
	}
	return true;
}

void data_extract()
{

}


CCoin::CCoin()
{
}

CCoin::CCoin(string sCoin)
{
	boost::trim(sCoin);
	sCoin = sCoin.substr(1, sCoin.length() - 2);
	vector<string> tokens;
	boost::split(tokens, sCoin, boost::is_any_of(","));
	if (tokens.size() == 3)
	{
		try
		{
			m_Jin = boost::lexical_cast<int>(tokens[0]);
			m_Yin = boost::lexical_cast<int>(tokens[1]);
			m_Tong = boost::lexical_cast<int>(tokens[2]);
		}
		catch (boost::bad_lexical_cast& exobj)
		{
			cout << "Convert err:" << endl;
			cout << exobj.what() << endl;
		}
	}
	else
	{
		cout << "金币格式错误" << endl;
	}
}

CCoin::~CCoin()
{
}

std::ostream & operator<<(std::ostream & os, const CCoin & c)
{
	os << c.serial();
	return os;
}

string CCoin::serial() const
{
	return "(" + boost::lexical_cast<string>(m_Jin) + "," + boost::lexical_cast<string>(m_Yin) + "," + boost::lexical_cast<string>(m_Tong) + ")";
}


CGoods::CGoods()
{
}


CGoods::CGoods(int nOrder, string sType, int nNum, CCoin oPrice, CCoin oTotalPrice, CCoin oCustodial, bool bSucc)
{
	m_Order = nOrder;
	m_Type = sType;
	m_Num = nNum;
	m_Price = oPrice;
	m_TotalPrice = oTotalPrice;
	m_Custodial = oCustodial;
	m_Succ = bSucc;
	m_IsValid = true;
	cout <<"货物构造: "<< m_Order << " " << m_Type << " " << m_Num << " " << m_Price << " " << m_TotalPrice << " " << m_Custodial << " " << m_Succ << endl;
}

CGoods::~CGoods()
{
	cout << "货物析构: " << m_Order << " " << m_Type << " " << m_Num << " " << m_Price << " " << m_TotalPrice << " " << m_Custodial << endl;
}

TiXmlElement* CGoods::tiXmlElement()
{
	TiXmlElement *pRoot = new TiXmlElement("goods");
	pRoot->SetAttribute("order", m_Order);
	pRoot->SetAttribute("type", GBKToUTF8(m_Type).c_str());
	pRoot->SetAttribute("num", m_Num);
	pRoot->SetAttribute("price", m_Price.serial().c_str());
	pRoot->SetAttribute("totalprice", m_TotalPrice.serial().c_str());
	pRoot->SetAttribute("custodial", m_Custodial.serial().c_str());
	pRoot->SetAttribute("succ", (int)m_Succ);
	return pRoot;
}

void CGoods::setOrder(int nOrder)
{
	m_Order = nOrder;
}



CVolume::CVolume()
{
}

CVolume::CVolume(int nOrder, string sTime)
{
	m_Order = nOrder;
	m_Time = sTime;
	m_IsValid = true;
	cout << "批次构造: " << m_Order << " " << m_Time << endl;
}

CVolume::~CVolume()
{
	for_each(m_Goods.begin(), m_Goods.end(), [](CGoods * pGoods) {delete pGoods; });
}

void CVolume::addGoods(CGoods * pGoods)
{
	m_Goods.push_back(pGoods);
}

void CVolume::addGoods(int nOrder, string sType, int nNum, string sPrice, string sTotalPrice, string sCustodial, bool bSucc)
{
	CGoods* pGoods = new CGoods(nOrder, sType, nNum, CCoin(sPrice), CCoin(sTotalPrice), CCoin(sCustodial), bSucc);
	nOrder = max(0, --nOrder);
	nOrder = min((int)m_Goods.size(), nOrder);
	m_Goods.insert(m_Goods.begin() + nOrder, pGoods);
}

TiXmlElement* CVolume::tiXmlElement()
{
	TiXmlElement *pRoot = new TiXmlElement("volume");
	pRoot->SetAttribute("order", m_Order);
	pRoot->SetAttribute("time", m_Time.c_str());
	for_each(m_Goods.begin(), m_Goods.end(), [&pRoot](CGoods * pGoods) {pRoot->LinkEndChild(pGoods->tiXmlElement()); });
	return pRoot;
}

void CVolume::setOrder(int nOrder)
{
	m_Order = nOrder;
}

void CVolume::correctOrder()
{
	int nNum = 1;
	for_each(m_Goods.begin(), m_Goods.end(), [&nNum](CGoods * pGoods) {pGoods->setOrder(nNum++); });
}





CItem::CItem()
{
}

CItem::CItem(int nOrder, std::string sName)
{
	m_Order = nOrder;
	m_Name = sName;
	cout << "物品构造: " << m_Order << " " << m_Name << endl;
}

CItem::~CItem()
{
	for_each(m_Volumes.begin(), m_Volumes.end(), [](CVolume * pVolume) {delete pVolume; });
}

void CItem::addVolume(CVolume* pVolume)
{
	m_Volumes.push_back(pVolume);
}

void CItem::addVolume(int nOrder)
{
	CVolume* pVolume = new CVolume(nOrder, "");
	nOrder = max(1, nOrder) - 1;
	m_Volumes.insert(m_Volumes.begin()+ nOrder, pVolume);
}

CVolume* CItem::volume(int nVolumeOrder)
{
	int cnt = m_Volumes.size();
	if (nVolumeOrder <= cnt)
	{
		return m_Volumes[nVolumeOrder - 1];
	}
	return nullptr;
}


TiXmlElement* CItem::tiXmlElement()
{
	TiXmlElement *pRoot = new TiXmlElement("item");
	pRoot->SetAttribute("order", m_Order);
	pRoot->SetAttribute("name", GBKToUTF8(m_Name).c_str());
	for_each(m_Volumes.begin(), m_Volumes.end(), [&pRoot](CVolume * pVolume) {pRoot->LinkEndChild(pVolume->tiXmlElement()); });
	return pRoot;
}

void CItem::setOrder(int nOrder)
{
	m_Order = nOrder;
}

void CItem::correctOrder()
{
	int nNum = 1;
	for_each(m_Volumes.begin(), m_Volumes.end(), [&nNum](CVolume * pVolume) {pVolume->setOrder(nNum++); pVolume->correctOrder(); });
}

