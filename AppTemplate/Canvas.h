#pragma once

#include "Backend.h"

#include "Node.h"

class Canvas : public Drawable
{
public:
	void init(RenderWindow* wnd);

	void handleKbdEvent(Keyboard::Key k, bool pressed);
	void handleMouseEvent(Mouse::Button b, bool pressed);
	void update(Time delta);
	void setFocus(bool focus);
private:
	void draw(RenderTarget& target, RenderStates states) const;
	bool validateNodeConnection(Node* one, Node* two);
	size_t queryNodeForIndex(Node* n);
	size_t queryOpenListForIndex(Node* n);

	//pathfinding functions
	void setDestinationNode(Node* n);
	void findPath();
	bool searchClosedListForNode(Node* n);
	bool searchOpenListForNode(Node* n);
	Node* findOpenListLowestFValue();

	bool m_Focus;
	bool m_Done;

	Clock m_Timer;

	RenderWindow* m_Window;

	std::vector<Node*> m_Nodes;
	std::vector<Node*> m_ClosedNodes;
	std::vector<Node*> m_OpenNodes;
	std::vector <NodeConnection*> m_NodeConnections;

	Node* m_SelectedNode;

	Node* m_EndNode;
	Node* m_BeginNode;

	UIString m_Legend;

	UIString m_SelectedID;
	UIString m_SelectedGValue;
	UIString m_SelectedHValue;
	UIString m_SelectedFValue;
	UIString m_SelectedParentID;


	//pathfinding algorithm related data


};