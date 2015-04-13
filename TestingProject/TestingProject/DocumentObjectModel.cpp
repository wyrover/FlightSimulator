#include "DocumentObjectModel.h"
#include <iostream>

DocumentObjectModel::DocumentObjectModel()
{
}

DocumentObjectModel::~DocumentObjectModel()
{
}

void DocumentObjectModel::StartTag(const std::string &tag)
{
	if (m_pRoot)
	{
		AddNewTag(tag);
	}
	else
	{
		SetRootNode(tag);
	}
}

void DocumentObjectModel::EndTag()
{
	if (m_pNodeIndex != m_pRoot)
	{
		m_pNodeIndex = m_pNodeIndex->pParent;
	}
}

void DocumentObjectModel::AddNewTag(const std::string &tag)
{
	TagNodePtr newNode = CreateNewNode();
	
	newNode->name = tag;
	newNode->pParent = m_pNodeIndex;

	m_pNodeIndex->children.push_back(newNode);

	m_pNodeIndex = newNode;
}

void DocumentObjectModel::SetRootNode(const std::string &tag)
{
	m_pRoot = CreateNewNode();
	m_pRoot->name = tag;

	m_pNodeIndex = m_pRoot;
}

TagNodePtr DocumentObjectModel::CreateNewNode() const
{
	return std::make_shared<TagNode>();
}

void DocumentObjectModel::AddDataToCurrentTag(const std::string &type, const std::string &value)
{
	m_pNodeIndex->data[type] = value;
}

void DocumentObjectModel::PrintTags() const
{
	PrintTags(m_pRoot);
}

void DocumentObjectModel::PrintTags(TagNodePtr tag) const
{
	std::cout << tag->name;

	std::cout << " : ";

	for (const auto type : tag->data)
	{
		std::cout << type.first << "; " << type.second << " ";
	}

	std::cout << std::endl;

	for (TagNodePtr node : tag->children)
	{
		PrintTags(node);
	}
}