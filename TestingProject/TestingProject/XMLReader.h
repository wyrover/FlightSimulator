#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "DocumentObjectModel.h"

class XMLReader
{
private:
	DocumentObjectModel		m_documentObjectModel;

	void					FindAndStoreTags(std::string &line);
	int						FindStartTag(std::string &line);
	int						FindEndTag(std::string &line, int start = 0);

	int						FindNextCharacter(const std::string &line) const;

	bool					IsStartTag(const std::string &tag);

	std::string				GetTagName(std::string &line, unsigned start, unsigned length) const;

public:
	XMLReader();
	~XMLReader();

	void					ReadFile(const char* file);
};

