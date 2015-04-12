#pragma once
#include <memory>
#include <list>
#include <string>

typedef struct Node
{
	std::list<std::shared_ptr<Node>> children;
	std::shared_ptr<Node> pParent;

	std::string name, data;
} TagNode;

typedef std::shared_ptr<TagNode> TagNodePtr;

class DocumentObjectModel
{
private:
	TagNodePtr					m_pRoot;
	TagNodePtr					m_pNodeIndex;

	void						AddNewTag(std::string &tag);
	void						SetRootNode(std::string &tag);

	TagNodePtr					CreateNewNode() const;

	void						PrintTags(TagNodePtr tag) const;

public:
	DocumentObjectModel();
	~DocumentObjectModel();

	void						StartTag(std::string &tag);
	void						EndTag();

	void						AddTextToCurrentNode(const std::string &text);
	void						PrintTags() const;
};