#pragma once
#ifndef __QFILE_H__
#define __QFILE_H__
#include <string>

class QFileInfo
{
public:
	QFileInfo(std::string filename);  //¾ø¶ÔÂ·¾¶
	std::string basename();
	std::string absoluteFilePath();
	std::string absolutePath() const;
	bool exists();
private:
	std::string m_FilePath = "";
};

#endif // __QFILE_H__

