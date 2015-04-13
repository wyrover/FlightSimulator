#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "DocumentObjectModel.h"

class XMLReader
{
private:
	DocumentObjectModelPtr					m_pDocumentObjectModel;

	void									FindAndStoreTags(std::string &line);
	int										FindStartTag(const std::string &line) const;
	int										FindEndTag(const std::string &line, const int start = 0) const;

	int										FindNextCharacter(const std::string &line) const;

	bool									IsStartTag(const std::string &tag) const;

	std::string								GetTagName(const std::string &line, const unsigned start, const unsigned length) const;

public:
	XMLReader();
	~XMLReader();

	void									ReadFile(const char* file);

	inline const DocumentObjectModelPtr		GetDOM() const
	{
		return m_pDocumentObjectModel;
	}
};

