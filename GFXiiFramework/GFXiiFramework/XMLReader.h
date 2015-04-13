#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "DocumentObjectModel.h"

class XMLReader
{
private:

	enum TagType { Start, End, SelfClosing };

	DocumentObjectModelPtr			m_documentObjectModel;

	void							FindAndStoreTags(std::string &line);
	int								FindStartTag(const std::string &line) const;
	int								FindEndTag(const std::string &line, const int start = 0) const;

	int								FindNextCharacter(const std::string &line) const;

	bool							IsStartTag(const std::string &tag) const;
	unsigned						AttributeCount(const std::string &tag) const;

	TagType							GetTagType(const std::string &tag) const;

	std::string						GetTagName(const std::string &line) const;

	bool							FindNextAttribute(std::string &line, std::string &outName, std::string &outValue) const;

public:
	XMLReader();
	~XMLReader();

	void					ReadFile(const char* file);

	inline const DocumentObjectModelPtr		GetDOM() const
	{
		return m_documentObjectModel;
	}
};
