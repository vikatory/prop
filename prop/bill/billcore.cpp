#include "billcore.h"
#include "sys.h"
#include "QFile.h"
#include "tinyxml.h"
#include "tinystr.h"
#include <windows.h>
//#include <atlstr.h>  //CString
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

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


string UTF8ToGBK(const std::string& strUTF8)
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

string GBKToUTF8(const std::string& strGBK)
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
			string sItemName = UTF8ToGBK(string(oItemAttr->Value()));
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

					CCoin oGoodsPrice = CCoin(sGoodsPrice);
					CCoin oGoodsTotalPrice = CCoin(sGoodsTotalPrice);
					CCoin oGoodsCustodial = CCoin(sGoodsCustodial);

					CGoods * pGoods = new CGoods(nGoodsOrder, sGoodsType, nGoodsNum, sGoodsPrice, sGoodsTotalPrice, sGoodsCustodial);
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
	//用assign
	string serial = "(" + boost::lexical_cast<string>(c.m_Jin) + "," + boost::lexical_cast<string>(c.m_Yin) + "," + boost::lexical_cast<string>(c.m_Tong) + ")";
	os << serial;
	return os;
}


CGoods::CGoods()
{
}


CGoods::CGoods(int nOrder, string sType, int nNum, CCoin oPrice, CCoin oTotalPrice, CCoin oCustodial)
{
	m_Order = nOrder;
	m_Type = sType;
	m_Num = nNum;
	m_Price = oPrice;
	m_TotalPrice = oTotalPrice;
	m_Custodial = oCustodial;
	m_IsValid = true;
	cout <<"货物构造: "<< m_Order << " " << m_Type << " " << m_Num << " " << m_Price << " " << m_TotalPrice << " " << m_Custodial << endl;
}

CGoods::~CGoods()
{
	cout << "货物析构: " << m_Order << " " << m_Type << " " << m_Num << " " << m_Price << " " << m_TotalPrice << " " << m_Custodial << endl;
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





