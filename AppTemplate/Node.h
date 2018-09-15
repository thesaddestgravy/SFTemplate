#pragma once

#include "Backend.h"
#include "UIString.h"
#include "MathUtil.h"
#include "UIString.h"

enum NodeType { NONE, START, END };

class Node : public Drawable
{
public:
	Node(Vec2 position);
	void addNeighbor(Node* n);
	std::vector<Node*> getNeighbors();

	void setSelected(bool selected);
	bool contains(Vec2 point);
	Vec2 getPosition();
	void setNodeType(NodeType nt);
	NodeType getNodeType();
	unsigned int getID();
	Node* getParent();
	void setParent(Node* n);

	void setHeuristic(int h);
	int getHeuristic();

	void setGValue(int g);
	int getGValue();

	void setFValue(int f);
	int getFValue();
private:
	void draw(RenderTarget& target, RenderStates states) const;
	Vec2 m_Position;
	std::vector<Node*> m_Neighbors;



	RectangleShape m_Point;
	NodeType m_NodeType;
	static unsigned int m_ID;
	unsigned int m_UniqueID;
	UIString m_IDString;

	Node* m_Parent;
	int m_GValue;
	int m_HValue;
	int m_FValue;
};

class NodeConnection : public Drawable
{
public:
	NodeConnection(Node* one, Node* two);
	std::pair<Node*, Node*> getConnection();

	void setColor(Color c);
private:
	void draw(RenderTarget& target, RenderStates states) const;

	Vertex m_Line[2];
	int m_Distance;
	UIString m_DistanceText;

	std::pair<Node*, Node*> m_Connection;
};
