#include "Canvas.h"

void Canvas::init(RenderWindow* wnd)
{
	m_Window = wnd;
	m_Legend.create("C = Create Node\nS = Start Path\nE = End Path\nQ = Clear Node Connections\nT = Clear Nodes\nEsc = Clear Node Selection");
	m_Legend.setPosition(Vec2(150, 50));

	m_SelectedID.create("");
	m_SelectedID.setPosition(Vec2(30, 150));
	m_SelectedID.setColor(Color::Red);
	m_SelectedGValue.create("");
	m_SelectedGValue.setPosition(Vec2(30, 180));
	m_SelectedGValue.setColor(Color::Red);
	m_SelectedHValue.create("");
	m_SelectedHValue.setPosition(Vec2(30, 210));
	m_SelectedHValue.setColor(Color::Red);
	m_SelectedFValue.create("");
	m_SelectedFValue.setPosition(Vec2(30, 240));
	m_SelectedFValue.setColor(Color::Red);
	m_SelectedParentID.create("");
	m_SelectedParentID.setPosition(Vec2(30, 270));
	m_SelectedParentID.setColor(Color::Red);

	m_Done = false;
	m_Timer.restart();

}

void Canvas::handleKbdEvent(Keyboard::Key k, bool pressed)
{
	if (pressed)
	{
		switch (k)
		{
		case Keyboard::C:
			m_Nodes.push_back(new Node((Vec2)Mouse::getPosition(*m_Window)));
			break;
		case Keyboard::S:
			if (m_SelectedNode)
			{
				m_BeginNode = m_SelectedNode;
				m_SelectedNode->setNodeType(START);
			}
			break;
		case Keyboard::E:
			if (m_SelectedNode)
			{
				m_EndNode = m_SelectedNode;
				m_SelectedNode->setNodeType(END);
				setDestinationNode(m_SelectedNode);
				if (m_BeginNode)
				{
					findPath();
				}
			}
			break;
		case Keyboard::Q:
			m_NodeConnections.clear();
			break;
		case Keyboard::T:
			m_NodeConnections.clear();
			m_Nodes.clear();
			break;
		case Keyboard::Escape:
			if (m_SelectedNode)
			{
				m_SelectedNode->setSelected(false);
				m_SelectedNode = nullptr;
			}
			break;
		}
	}
}

void Canvas::handleMouseEvent(Mouse::Button b, bool pressed)
{
	if (pressed)
	{

		//find nearest node to mouse pos
		Node* closest = nullptr;
		float shortestDistance = 1000;

		for (size_t i = 0; i < m_Nodes.size(); i++)
		{
			float distance = getDistance((Vec2)Mouse::getPosition(*m_Window), m_Nodes[i]->getPosition());
			if (distance < shortestDistance)
			{
				shortestDistance = distance;
				closest = m_Nodes[i];
			}
		}
		

		if (b == Mouse::Left)
		{
			for (size_t i = 0; i < m_Nodes.size(); i++)
			{
				m_Nodes[i]->setSelected(false);
			}
			if (closest)
			{
				m_SelectedNode = closest;
				m_SelectedNode->setSelected(true);


			}

		}
		else if (b == Mouse::Right && m_SelectedNode != nullptr)
		{
			if (m_Nodes.size() > 1)
			{
				if (validateNodeConnection(m_Nodes[queryNodeForIndex(m_SelectedNode)], closest))
				{
					m_NodeConnections.push_back(new NodeConnection(m_Nodes[queryNodeForIndex(m_SelectedNode)], closest));
					m_SelectedNode->addNeighbor(closest);
					closest->addNeighbor(m_SelectedNode);
				}
			}
		}
	}
}

void Canvas::update(Time delta)
{
	if (m_SelectedNode && m_Done)
	{
		m_SelectedID.setString("Node ID: " + std::to_string(m_SelectedNode->getID()));
		m_SelectedGValue.setString("Node G Value: " + std::to_string(m_SelectedNode->getGValue()));
		m_SelectedHValue.setString("Node Heuristic: " + std::to_string(m_SelectedNode->getHeuristic()));
		m_SelectedFValue.setString("Node F Value: " + std::to_string(m_SelectedNode->getFValue()));
		m_SelectedParentID.setString("Node Parent:" + std::to_string(m_SelectedNode->getParent()->getID()));
	}
	else
	{
		m_SelectedID.setString("Node ID: ");
		m_SelectedGValue;
		m_SelectedHValue.setString("Node Heuristic: ");
		m_SelectedFValue;
		m_SelectedParentID;
	}
}

void Canvas::setFocus(bool focus)
{
	m_Focus = focus;
}

void Canvas::draw(RenderTarget& target, RenderStates states) const
{
	if (!m_NodeConnections.empty())
	{
		for (size_t i = 0; i < m_NodeConnections.size(); i++)
		{
			target.draw(*m_NodeConnections[i]);
		}
	}


	if (!m_Nodes.empty())
	{
		for (size_t i = 0; i < m_Nodes.size(); i++)
		{
			target.draw(*m_Nodes[i]);
		}
	}



	target.draw(m_Legend);
	target.draw(m_SelectedID);
	target.draw(m_SelectedGValue);
	target.draw(m_SelectedHValue);
	target.draw(m_SelectedFValue);
	target.draw(m_SelectedParentID);
}

bool Canvas::validateNodeConnection(Node* one, Node* two)
{
	if (getDistance(one->getPosition(), two->getPosition()) < 1)
	{
		return false;
	}
	for (size_t i = 0; i < m_NodeConnections.size(); i++)
	{
		std::pair<Node*, Node*> check = m_NodeConnections[i]->getConnection();
		if (check.first == one && check.second == two ||
			check.second == one && check.first == two)
		{
			return false;
		}
	}
	return true;
}

size_t Canvas::queryNodeForIndex(Node* n)
{
	for (size_t i = 0; i < m_Nodes.size(); i++)
	{
		if (m_Nodes[i] == n)
		{
			return i;
		}
	}

	return NODE_NOT_FOUND;
}

size_t Canvas::queryOpenListForIndex(Node * n)
{
	for (size_t i = 0; i < m_OpenNodes.size(); i++)
	{
		if (m_OpenNodes[i] == n)
		{
			return i;
		}
	}

	return NODE_NOT_FOUND;
}

bool Canvas::searchClosedListForNode(Node* n)
{
	for (size_t i = 0; i < m_ClosedNodes.size(); i++)
	{
		if (m_ClosedNodes[i] == n)
		{
			return true;
		}
	}

	return false;
}

bool Canvas::searchOpenListForNode(Node * n)
{
	for (size_t i = 0; i < m_OpenNodes.size(); i++)
	{
		if (m_OpenNodes[i] == n)
		{
			return true;
		}
	}

	return false;
}

Node* Canvas::findOpenListLowestFValue()
{
	if (!m_OpenNodes.empty())
	{
		int lowestF = 10000;
		Node* lowest = nullptr;
		for (size_t i = 0; i < m_OpenNodes.size(); i++)
		{
			if (m_OpenNodes[i]->getFValue() < lowestF)
			{
				lowestF = m_OpenNodes[i]->getFValue();
				lowest = m_OpenNodes[i];
			}
		}
		return lowest;
	}

	return nullptr;
}

void Canvas::setDestinationNode(Node* n)
{
	for (size_t i = 0; i < m_Nodes.size(); i++)
	{
		m_Nodes[i]->setHeuristic(getDistance(m_Nodes[i]->getPosition(), n->getPosition()));
	}
}

void Canvas::findPath()
{
	Node* current = m_BeginNode;
	current->setParent(current);
	current->setGValue(0);
	current->setHeuristic(getDistance(current->getPosition(), m_EndNode->getPosition()));
	current->setFValue(current->getGValue() + current->getHeuristic());
	float totalDistance;

	m_OpenNodes.push_back(m_BeginNode);

	while (current != m_EndNode)
	{
		current = findOpenListLowestFValue();

		if (current == m_EndNode)
		{
			std::cout << "found shortest path!\n";
			Node* sentinel = m_EndNode;
			while (sentinel != m_BeginNode)
			{
				m_NodeConnections.push_back(new NodeConnection(sentinel, sentinel->getParent()));
				m_NodeConnections[m_NodeConnections.size() - 1]->setColor(Color::Red);
				std::cout << "Node " << sentinel->getID() << " has parent " << sentinel->getParent()->getID() << std::endl;
				sentinel = sentinel->getParent();
				m_Done = true; 
			}
			return;
		}

		size_t index = queryOpenListForIndex(current);
		m_OpenNodes.erase(m_OpenNodes.begin() + index);
		m_ClosedNodes.push_back(current);

		if (current != m_BeginNode)
		{
			//std::cout << "current ID = " << current->getID() << " has parent ID " << current->getParent()->getID() << std::endl;
		}

		for (size_t i = 0; i < current->getNeighbors().size(); i++)
		{
			if (current->getNeighbors()[i]->getParent() == nullptr)
			{
				current->getNeighbors()[i]->setParent(current);
			}

			if (!searchClosedListForNode(current->getNeighbors()[i]))
			{
				//in this context current node = current neighbor of current
				//calculate g value of current node
				int gval = 0;
				Node* sentinel = current->getNeighbors()[i];

				while (sentinel != m_BeginNode)
				{
					gval += getDistance(sentinel->getPosition(), sentinel->getParent()->getPosition());
					sentinel = sentinel->getParent();
				}

				std::cout << "G value for node " << current->getNeighbors()[i]->getID() << " is " << gval << std::endl;
				current->getNeighbors()[i]->setGValue(gval);

				if (!searchOpenListForNode(current->getNeighbors()[i])) //discovered new node
				{
					m_OpenNodes.push_back(current->getNeighbors()[i]);
				}
				else if (gval > current->getNeighbors()[i]->getGValue())
				{
					//this is not a better path
				}
				else //node is already in open list and this is a new better path
				{
					//calculate h value of current node
					int hval = getDistance(m_EndNode->getPosition(), current->getNeighbors()[i]->getPosition());
					current->getNeighbors()[i]->setHeuristic(hval);

					//calculate f value of current node
					int fval = gval + hval;
					if (current->getNeighbors()[i]->getFValue() < fval || current->getNeighbors()[i]->getFValue() == FVAL_NOT_SET)
					{
						current->getNeighbors()[i]->setFValue(fval);
					}
				}



			}
		}
	}
}
