#include "XMLReader.h"


XMLReader::XMLReader()
{
}


XMLReader::~XMLReader()
{
}

void XMLReader::FindAndStoreTags(std::string &line)
{
	int end, next;

	while (true)
	{
		// Check if there is another character
		if ((next = FindNextCharacter(line)) != -1)
		{
			// Start of a new tag
			if (line[next] == '<')
			{
				if ((end = FindEndTag(line, next)) != -1)
				{
					std::string tag = line.substr(next, end - next + 1);

					TagType type = GetTagType(tag);
					switch (type)
					{
					case TagType::Start:
					case TagType::SelfClosing:
						if (AttributeCount(tag) > 0)
						{
							m_documentObjectModel.StartTag(GetTagName(tag));

							std::string value, name;
							while (FindNextAttribute(tag, name, value))
							{
								m_documentObjectModel.AddDataToCurrentTag(name, value);
							}
						}
						else if (type == TagType::Start)
						{
							m_documentObjectModel.StartTag(GetTagName(tag));
						}
						else
						{
							m_documentObjectModel.StartTag(GetTagName(tag));
							m_documentObjectModel.EndTag();
						}
						break;
					case TagType::End:
						m_documentObjectModel.EndTag();
						break;
					}

					line = line.substr(end + 1);
				}
				else
				{
					// Something isn't formatted right
					return;
				}
			}
			else
			{
				// This should never happen for this parser
				_ASSERT(false);
			}
		}
		else
		{
			// Nonsense data, ignore
			return;
		}
	}
}

/*
	This function is coded awfully, but it does the job of finding xml attributes.
	
*/
bool XMLReader::FindNextAttribute(std::string &line, std::string &outName, std::string &outValue) const
{	
	for (unsigned index = 0; index < line.length(); index++)
	{
		// Find the space after a tag name or attribute value - NOTE: assumes the is one space before/after attributes
		if (line[index] == ' ')
		{
			std::string name = "";

			for (index++; index < line.length(); index++)
			{
				// Find the attribute name
				if (line[index] != '=')
				{
					name += line[index];
				}
				else
				{
					// Found data type
					outName = name;

					// Find data value
					index++;
					if (line[index] == '"')
					{
						index++;
						unsigned start = index;
						for (unsigned i = 0; index < line.length(); index++, i++)
						{
							if (line[index] == '"')
							{
								std::string value = line.substr(start, i);

								outValue = value;
								line = line.substr(index + 1);

								return true;
							}
						}
						return false;
					}
					return false;
				}
			}
			return false;
		}
	}
	return false;
}

XMLReader::TagType XMLReader::GetTagType(const std::string &tag) const
{
	if (tag[1] == '/')
	{
		return TagType::End;
	}
	else if (tag[tag.length() - 2] == '/')
	{
		return TagType::SelfClosing;
	}
	else
	{
		return TagType::Start;
	}
}

unsigned XMLReader::AttributeCount(const std::string &tag) const
{
	unsigned count = 0;

	for (unsigned index = 0; index < tag.length(); index++)
	{
		if (tag[index] == '"')
		{
			count++;
		}
	}

	if (count % 2 == 0)
	{
		return count / 2;
	}
	else if (count > 0)
	{
		_ASSERT(false);
	}
	return 0;
}

int XMLReader::FindStartTag(const std::string &line) const
{
	for (unsigned index = 0; index < line.length(); index++)
	{
		if (line[index] == '<')
		{
			return index;
		}
	}
	return -1;
}

int XMLReader::FindEndTag(const std::string &line, int start) const
{
	for (unsigned index = start; index < line.length(); index++)
	{
		if (line[index] == '>')
		{
			return index;
		}
	}
	return -1;
}

int XMLReader::FindNextCharacter(const std::string &line) const
{
	for (unsigned index = 0; index < line.length(); index++)
	{
		char c = line[index];

		if (c != ' ' && c != '\t')
		{
			return index;
		}
	}
	return -1;
}

bool XMLReader::IsStartTag(const std::string &tag) const
{
	if (tag[1] == '/')
	{
		return false;
	}
	else
	{
		return true;
	}
}

std::string XMLReader::GetTagName(const std::string &line) const
{
	std::string tag = "";

	if (line[0] == '<')
	{
		for (unsigned index = 1; index < line.length(); index++)
		{
			if (line[index] != ' ' && line[index] != '>' && line[index] != '/')
			{
				tag += line[index];
			}
			else
			{
				break;
			}
		}
	}
	return tag;
}

void XMLReader::ReadFile(const char* file)
{
	std::ifstream filestream;
	std::string line;

	filestream.open(file);

	if (filestream)
	{
		while (std::getline(filestream, line))
		{
			FindAndStoreTags(line);
		}
	}

	filestream.close();

	m_documentObjectModel.PrintTags();
}