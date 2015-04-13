#pragma once
#include <memory>
#include <list>
#include <string>

class DocumentObjectModel;

typedef struct Node
{
	std::list<std::shared_ptr<Node>> children;
	std::shared_ptr<Node> pParent;

	std::string name, data;
} TagNode;

typedef std::shared_ptr<TagNode> TagNodePtr;
typedef std::shared_ptr<DocumentObjectModel> DocumentObjectModelPtr;

class DocumentObjectModel
{
private:
	TagNodePtr					m_pRoot;
	TagNodePtr					m_pNodeIndex;

	void						AddNewTag(const std::string &tag);
	void						SetRootNode(const std::string &tag);

	TagNodePtr					CreateNewNode() const;

	void						PrintTags(TagNodePtr tag) const;

public:
	DocumentObjectModel();
	~DocumentObjectModel();

	inline const TagNodePtr		GetRoot() const
	{
		return m_pRoot;
	}

	void						StartTag(const std::string &tag);
	void						EndTag();

	void						AddTextToCurrentNode(const std::string &text);
	void						PrintTags() const;
};