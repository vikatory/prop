// -------------------------------------------------------------------------------
// @Author      : hejia
// @Created     : 2015/5/4
// @Desc        :
// -------------------------------------------------------------------------------

#include "QFile.h"
#include "custom.h"
#include <string>
#include <iostream>
#include <regex>
//#include "SimpleSymbolEngine.h"

//#include <boost/filesystem/operations.hpp>
//#include <boost/filesystem/path.hpp>
//#include <boost/filesystem/convenience.hpp>

using namespace std;

QFileInfo::QFileInfo(string filename)
{
	str sFileName = filename;
	while (sFileName.regex_replace("/[^/]+/\\.\\.", ""))
	{
	}
	m_FilePath = sFileName;
}

string QFileInfo::basename()
{
	return "";
}
string QFileInfo::absoluteFilePath()
{
	return "";
}
string QFileInfo::absolutePath() const
{
	return str(m_FilePath).endswith("/") ? m_FilePath : m_FilePath+"/";
}

//bool QFileInfo::exists()
//{
//	namespace fs = boost::filesystem;
//	return fs::exists(m_FilePath);
//}



