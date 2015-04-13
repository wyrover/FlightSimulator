#include "XMLReader.h"


XMLReader::XMLReader()
{
	m_pDocumentObjectModel = std::make_shared<DocumentObjectModel>();
}


XMLReader::~XMLReader()
{
}

void XMLReader::FindAndStoreTags(std::string &line)
{
	int start, end, next;

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
					if (IsStartTag(line.substr(next, end - next)))
					{
						m_pDocumentObjectModel->StartTag(GetTagName(line, next, end - next));
					}
					else
					{
						m_pDocumentObjectModel->EndTag();
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
				// Some data
				start = FindStartTag(line);
				end = FindEndTag(line, start);

				if (start != -1 && end != -1)
				{
					m_pDocumentObjectModel->AddTextToCurrentNode(line.substr(next, start - next));

					line = line.substr(start);
				}
				else
				{
					// Nonsense data, ignore
					return;
				}
			}
		}
		else
		{
			// Nonsense data, ignore
			return;
		}
	}
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

std::string XMLReader::GetTagName(const std::string &line, const unsigned start, const unsigned length) const
{
	return line.substr(start + 1, length - 1);
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

	//m_pDocumentObjectModel->PrintTags();
}