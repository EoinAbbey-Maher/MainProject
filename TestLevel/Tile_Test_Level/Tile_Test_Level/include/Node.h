#ifndef NODE_H
#define NODE_H

#include "Global.h"

enum class NodeType
{
	Player,
	NPC
};

class Node
{
public:
	Node();
	~Node();
private:

	sf::Vector2i indexPosition;
	sf::Vector2f m_position{ 0,0 };

	NodeType m_type;
};

#endif // !NODE

