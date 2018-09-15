#include "Node.h"

unsigned int Node::m_ID = 0;

Node::Node(Vec2 position)
{
	m_Position = position;
	m_Point.setSize(Vec2(16, 16));
	m_Point.setPosition(Vec2(m_Position.x - m_Point.getSize().x / 2, m_Position.y - m_Point.getSize().y / 2));
	m_Point.setFillColor(Color::White);
	m_ID++;
	m_UniqueID = m_ID;
	m_IDString.create(std::to_string(m_UniqueID));
	m_IDString.setPosition(m_Point.getPosition());

	m_Parent = nullptr;

	m_FValue = FVAL_NOT_SET;
}

void Node::addNeighbor(Node* n)
{
	m_Neighbors.push_back(n);
}

std::vector<Node*> Node::getNeighbors()
{
	return m_Neighbors;
}

void Node::setSelected(bool selected)
{
	if (selected)
	{
		m_Point.setFillColor(Color::Red);
	}
	else
	{
		if (m_NodeType == START)
		{
			m_Point.setFillColor(Color::Yellow);
		}
		else if (m_NodeType == END)
		{
			m_Point.setFillColor(Color::Cyan);
		}
		else
		{
			m_Point.setFillColor(Color::White);
		}
	}


}

bool Node::contains(Vec2 point)
{
	return m_Point.getGlobalBounds().contains(point);
}

Vec2 Node::getPosition()
{
	return Vec2(m_Point.getPosition().x + m_Point.getSize().x / 2, m_Point.getPosition().y + m_Point.getSize().y / 2);
}

void Node::setNodeType(NodeType nt)
{
	m_NodeType = nt;

	if (m_NodeType == START)
	{
		m_Point.setFillColor(Color::Yellow);
	}
	else if (m_NodeType == END)
	{
		m_Point.setFillColor(Color::Cyan);
	}
}

NodeType Node::getNodeType()
{
	return m_NodeType;
}

unsigned int Node::getID()
{
	return m_UniqueID;
}

Node* Node::getParent()
{
	return m_Parent;
}

void Node::setParent(Node* n)
{
	m_Parent = n;
}

void Node::setHeuristic(int h)
{
	m_HValue = h;
}

int Node::getHeuristic()
{
	return m_HValue;
}

void Node::setGValue(int g)
{
	m_GValue = g;
}

int Node::getGValue()
{
	return m_GValue;
}

void Node::setFValue(int f)
{
	m_FValue = f;
}

int Node::getFValue()
{
	return m_FValue;
}

void Node::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_Point);
	target.draw(m_IDString);
}




NodeConnection::NodeConnection(Node* one, Node* two)
{
	m_Line[0].position = one->getPosition();
	m_Line[1].position = two->getPosition();
	m_Line[0].color = Color(215, 195, 100);
	m_Line[1].color = Color(215, 195, 100);

	m_Distance = getDistance(two->getPosition(), one->getPosition());

	m_Connection.first = one;
	m_Connection.second = two;

	Vec2 midpoint;
	midpoint.x = (one->getPosition().x + two->getPosition().x) / 2;
	midpoint.y = (one->getPosition().y + two->getPosition().y) / 2;


	m_DistanceText.create(std::to_string(m_Distance));
	m_DistanceText.setPosition(midpoint);
	m_DistanceText.setColor(Color(215, 195, 100));
}

std::pair<Node*, Node*> NodeConnection::getConnection()
{
	return m_Connection;
}

void NodeConnection::setColor(Color c)
{
	m_Line[0].color = c;
	m_Line[1].color = c;
}

void NodeConnection::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_Line, 2, Lines);
	target.draw(m_DistanceText);
}
