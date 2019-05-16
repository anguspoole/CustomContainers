#include "RBTree.h"
#include <algorithm>

//====================
// Person RB Tree
//====================

//Constructor
RBTree::RBTree()
{
	this->root = NULL;
}

//Deconstructor
RBTree::~RBTree()
{
}

//Function for rotating a node to the left
void RBTree::rotateLeft(sRBNode * nodeA, sRBNode * nodeB)
{
	sRBNode* right = nodeA->right;
	sRBNode* p = nodeA->parent;

	//Empty leaf nodes cannot become internal nodes
	if (nodeA->right == NULL)
	{
		return;
	}

	nodeA->right = right->left;
	right->left = nodeA;
	nodeA->parent = right;

	if (nodeA->right != NULL)
		nodeA->right->parent = nodeA;

	right->parent = nodeA->parent;

	if (p != NULL) // initially n could be the root
	{
		if (nodeA == p->left)
			p->left = right;
		else if (nodeA == p->right) // if (...) is excessive
			p->right = right;
	}

	right->parent = p;
}

//Function for rotating a node to the right
void RBTree::rotateRight(sRBNode * nodeA, sRBNode * nodeB)
{
	sRBNode* left = nodeA->left;
	sRBNode* p = nodeA->parent;

	//Empty leaf nodes cannot become internal nodes
	if (nodeA->left == NULL)
	{
		return;
	}

	nodeA->left = left->right;
	left->right = nodeA;
	nodeA->parent = left;

	if (nodeA->left != NULL)
		nodeA->left->parent = nodeA;

	left->parent = nodeA->parent;

	if (p != NULL) // initially n could be the root
	{
		if (nodeA == p->left)
			p->left = left;
		else if (nodeA == p->right) // if (...) is excessive
			p->right = left;
	}

	left->parent = p;
}

//Function for Re-balancing tree if there is an issue
void RBTree::balance(sRBNode * nodeA, sRBNode * nodeB)
{
	sRBNode *parent = NULL;
	sRBNode *grandParent = NULL;

	while ((nodeA != nodeB) && (nodeA->color != BLACK) &&
		(nodeA->parent->color == RED))
	{

		parent = nodeA->parent;
		grandParent = nodeA->parent->parent;

		// If nodeA's parent is left child of Grand-parent
		if (parent == grandParent->left)
		{
			//Right child of grandparent = right uncle of nodeA
			sRBNode *rightUncle = grandParent->right;

			//Recolour if the right child of grandparent is also red
			if (rightUncle != NULL && rightUncle->color == RED)
			{
				grandParent->color = RED;
				parent->color = BLACK;
				rightUncle->color = BLACK;
				nodeA = grandParent;
			}

			else
			{
				//Rotate left if nodeA is right child of parent
				if (nodeA == parent->right)
				{
					rotateLeft(parent, nodeB);
					nodeA = parent;
					parent = nodeA->parent;
				}
				if (nodeA == parent->left)
				{
					//Rotate right if nodeA is left child of parent 
					rotateRight(grandParent, nodeB);
					std::swap(parent->color, grandParent->color);
					nodeA = parent;
				}
			}
		}

		// If nodeA's parent is right child of Grand-parent
		else
		{
			//left child of grandparent = left uncle of nodeA
			sRBNode *leftUncle = grandParent->left;

			//Recolour if left child of grandparent is red
			if ((leftUncle != NULL) && (leftUncle->color == RED))
			{
				grandParent->color = RED;
				parent->color = BLACK;
				leftUncle->color = BLACK;
				nodeA = grandParent;
			}
			else
			{
				//Rotate right if nodeA is left child of parent
				if (nodeA == parent->left)
				{
					rotateRight(parent, nodeB);
					nodeA = parent;
					parent = nodeA->parent;
				}
				if (nodeA == parent->right)
				{
					//Rotate left if nodeA is right child of parent
					rotateLeft(grandParent, nodeB);
					std::swap(parent->color, grandParent->color);
					nodeA = parent;
				}
			}
		}
	}

	nodeB->color = BLACK;
}

void RBTree::insertCase1(sRBNode* nodeA)
{
	if (nodeA->parent == NULL)
		nodeA->color = BLACK;
}

void RBTree::insertCase2(sRBNode* nodeA)
{
	return; //tree is still valid
}

void RBTree::insertCase3(sRBNode* nodeA)
{
	nodeA->parent->color = BLACK;

	if (nodeA->parent->parent->left == nodeA->parent)
	{
		nodeA->parent->parent->right->color = BLACK;
	}
	else if (nodeA->parent->parent->right == nodeA->parent)
	{
		nodeA->parent->parent->left->color = BLACK;
	}
	nodeA->parent->parent->color = RED;
	balanceInsert(nodeA->parent->parent);
}

void RBTree::insertCase4(sRBNode* nodeA)
{
	sRBNode* p = nodeA->parent;
	sRBNode* g = nodeA->parent->parent;

	if (nodeA == p->right && p == g->left) {
		rotateLeft(p, root);
		nodeA = nodeA->left;
	}
	else if (nodeA == p->left && p == g->right) {
		rotateRight(p, root);
		nodeA = nodeA->right;
	}

	insertCase4P2(nodeA);
}

void RBTree::insertCase4P2(sRBNode * nodeA)
{
	sRBNode* p = nodeA->parent;
	sRBNode* g = nodeA->parent->parent;

	if (nodeA == p->left)
		rotateRight(g, root);
	else
		rotateLeft(g, root);
	p->color = BLACK;
	g->color = RED;
}



void RBTree::balanceInsert(sRBNode * nodeA)
{
	if (nodeA->parent == NULL) {
		insertCase1(nodeA);
	}
	else if (nodeA->parent->color == BLACK) {
		insertCase2(nodeA);
	}
	else
	{
		if (nodeA->parent->parent->left == nodeA->parent)
		{
			if (nodeA->parent->parent->right != NULL && nodeA->parent->parent->right->color == RED) 
			{
				insertCase3(nodeA);
			}
		}
		else if (nodeA->parent->parent->right == nodeA->parent)
		{
			if (nodeA->parent->parent->left != NULL && nodeA->parent->parent->left->color == RED)
			{
				insertCase3(nodeA);
			}
		}
		else
		{
			insertCase4(nodeA);
		}
	}
}

//Function for inserting a new node into the tree
void RBTree::insert(int key, sPerson person)
{
	sRBNode* node = new sRBNode(key, person);

	if (nodeCount == 0)
	{
		root = node;
		node->color = BLACK;
		nodeCount++;
		return;
	}

	BSTInsert(node, root);
	balanceInsert(node);

	// find the new root
	sRBNode* rootNode = root;
	if (rootNode == NULL)
	{
		rootNode = node;
	}

	while (rootNode->parent != NULL)
		rootNode = rootNode->parent;
	this->root = rootNode;

	this->nodeCount++;
}

//Insert for binary search tree
void RBTree::BSTInsert(sRBNode* nodeA, sRBNode* nodeB)
{
	// recursively descend the tree until a leaf is found
	if (nodeB != NULL && nodeA->key < nodeB->key) 
	{
		if (nodeB->left != NULL) 
		{
			BSTInsert(nodeA, nodeB->left);
			//return;
		}
		else
			nodeB->left = nodeA;
	}
	else if (nodeB != NULL && nodeA->key > nodeB->key) 
	{
		if (nodeB->right != NULL) 
		{
			BSTInsert(nodeA, nodeB->right);
			//return;
		}
		else
			nodeB->right = nodeA;
	}

	// insert new node n
	nodeA->parent = nodeB;
	nodeA->left = NULL;
	nodeA->right = NULL;
	nodeA->color = RED;

	//balance(nodeA, nodeB);
}

RBTree::sRBNode* RBTree::traverseInOrder(RBTree::sRBNode* nodeA)
{
	if (nodeA->left == NULL)
		return nodeA;
	//Traverse through left node
	traverseInOrder(nodeA->left);
	//Traverse through right node
	traverseInOrder(nodeA->right);

}

RBTree::sRBNode * RBTree::find(int key, sRBNode * nodeA)
{
	if (nodeA == NULL)
	{
		return NULL;
	}
	//If key is found, return node
	if (nodeA->key == key)
	{
		return nodeA;
	}
	else
	{
		//Look at left node
		if (nodeA->left != NULL)
		{
			nodeA = find(key, nodeA->left);
		}
		//If key is found, return node
		if (nodeA->key == key)
		{
			return nodeA;
		}
		else
		{
			//Look at right node
			if (nodeA->right != NULL)
			{
				nodeA = find(key, nodeA->right);
			}
			//If key is found, return node
			if (nodeA->key == key)
			{
				return nodeA;
			}
		}
	}
	//Return null if key is not found
	return NULL;
}

sPerson* RBTree::findPerson(int key)
{
	sRBNode* node = find(key, getRoot());
	return &node->person;
}

void RBTree::traverseLevelOrder()
{
}

int RBTree::getSize()
{
	return this->nodeCount;
}

//Function for clearing tree of all nodes
void RBTree::clear(sRBNode* node)
{
	if (node == NULL)
	{
		return;
	}
	
	if (node->left != NULL)
	{
		clear(node->left);
	}
	if (node->right != NULL)
	{
		clear(node->right);
	}

	//just in case, set pointers to null
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;

	if (node != root)
	{
		delete node;
		this->nodeCount--;
	}
	else
	{
		delete node;
		sRBNode * newRoot = NULL;
		this->root = newRoot;
		this->nodeCount = 0;
	}
}

RBTree::sRBNode * RBTree::getRoot()
{
	return this->root;
}

//====================
// String RB Tree
//====================

strRBTree::strRBTree()
{
	this->root = NULL;
}

strRBTree::~strRBTree()
{
}

//Function for rotating a node to the left
void strRBTree::rotateLeft(sStrRBNode &nodeA, sStrRBNode &nodeB)
{
	sStrRBNode* right = nodeA.right;
	sStrRBNode* p = nodeA.parent;

	//Empty leaf nodes cannot become internal nodes
	if (nodeA.right == NULL)
	{
		return;
	}

	nodeA.right = right->left;
	right->left = (&nodeA);
	nodeA.parent = right;

	if (nodeA.right != NULL)
		nodeA.right->parent = &nodeA;

	right->parent = nodeA.parent;

	if (p != NULL) // initially n could be the root
	{
		if (&nodeA == p->left)
			p->left = right;
		else if (&nodeA == p->right) // if (...) is excessive
			p->right = right;
	}

	right->parent = p;
}

//Function for rotating a node to the right
void strRBTree::rotateRight(sStrRBNode& nodeA, sStrRBNode& nodeB)
{
	sStrRBNode* left = nodeA.left;
	sStrRBNode* p = nodeA.parent;

	//Empty leaf nodes cannot become internal nodes
	if (nodeA.left == NULL)
	{
		return;
	}

	nodeA.left = left->right;
	left->right = &nodeA;
	nodeA.parent = left;

	if (nodeA.left != NULL)
		nodeA.left->parent = &nodeA;

	left->parent = nodeA.parent;

	if (p != NULL) // initially n could be the root
	{
		if (&nodeA == p->left)
			p->left = left;
		else if (&nodeA == p->right) // if (...) is excessive
			p->right = left;
	}

	left->parent = p;
}

//Function for Re-balancing tree if there is an issue
void strRBTree::balance(sStrRBNode& nodeA, sStrRBNode& nodeB)
{
	sStrRBNode *parent = NULL;
	sStrRBNode *grandParent = NULL;

	while ((&nodeA != &nodeB) && (nodeA.color != BLACK) &&
		(nodeA.parent->color == RED))
	{

		parent = nodeA.parent;
		grandParent = nodeA.parent->parent;

		// If nodeA's parent is left child of Grand-parent
		if (parent == grandParent->left)
		{
			//Right child of grandparent = right uncle of nodeA
			sStrRBNode *rightUncle = grandParent->right;

			//Recolour if the right child of grandparent is also red
			if (rightUncle != NULL && rightUncle->color == RED)
			{
				grandParent->color = RED;
				parent->color = BLACK;
				rightUncle->color = BLACK;
				nodeA = *grandParent;
			}

			else
			{
				//Rotate left if nodeA is right child of parent
				if (&nodeA == parent->right)
				{
					rotateLeft(*parent, nodeB);
					nodeA = *parent;
					parent = nodeA.parent;
				}
				if (&nodeA == parent->left)
				{
					//Rotate right if nodeA is left child of parent 
					rotateRight(*grandParent, nodeB);
					std::swap(parent->color, grandParent->color);
					nodeA = *parent;
				}
			}
		}

		// If nodeA's parent is right child of Grand-parent
		else
		{
			//left child of grandparent = left uncle of nodeA
			sStrRBNode *leftUncle = grandParent->left;

			//Recolour if left child of grandparent is red
			if ((leftUncle != NULL) && (leftUncle->color == RED))
			{
				grandParent->color = RED;
				parent->color = BLACK;
				leftUncle->color = BLACK;
				nodeA = *grandParent;
			}
			else
			{
				//Rotate right if nodeA is left child of parent
				if (&nodeA == parent->left)
				{
					rotateRight(*parent, nodeB);
					nodeA = *parent;
					parent = nodeA.parent;
				}
				if (&nodeA == parent->right)
				{
					//Rotate left if nodeA is right child of parent
					rotateLeft(*grandParent, nodeB);
					std::swap(parent->color, grandParent->color);
					nodeA = *parent;
				}
			}
		}
	}

	nodeB.color = BLACK;
}

void strRBTree::insertCase1(sStrRBNode& nodeA)
{
	if (nodeA.parent == NULL)
		nodeA.color = BLACK;
}

void strRBTree::insertCase2(sStrRBNode& nodeA)
{
	return; //tree is still valid
}

void strRBTree::insertCase3(sStrRBNode& nodeA)
{
	nodeA.parent->color = BLACK;

	if (nodeA.parent->parent->left == nodeA.parent)
	{
		nodeA.parent->parent->right->color = BLACK;
	}
	else if (nodeA.parent->parent->right == nodeA.parent)
	{
		nodeA.parent->parent->left->color = BLACK;
	}
	nodeA.parent->parent->color = RED;
	balanceInsert(*nodeA.parent->parent);
}

void strRBTree::insertCase4(sStrRBNode& nodeA)
{
	sStrRBNode* p = nodeA.parent;
	sStrRBNode* g = nodeA.parent->parent;

	if (&nodeA == p->right && p == g->left) {
		rotateLeft(*p, *root);
		nodeA = *nodeA.left;
	}
	else if (&nodeA == p->left && p == g->right) {
		rotateRight(*p, *root);
		nodeA = *nodeA.right;
	}

	insertCase4P2(nodeA);
}

void strRBTree::insertCase4P2(sStrRBNode& nodeA)
{
	sStrRBNode* p = nodeA.parent;
	sStrRBNode* g = nodeA.parent->parent;

	if (&nodeA == p->left)
		rotateRight(*g, *root);
	else
		rotateLeft(*g, *root);
	p->color = BLACK;
	g->color = RED;
}



void strRBTree::balanceInsert(sStrRBNode& nodeA)
{
	if (nodeA.parent == NULL) {
		insertCase1(nodeA);
	}
	else if (nodeA.parent->color == BLACK) {
		insertCase2(nodeA);
	}
	else
	{
		if (nodeA.parent->parent == NULL)
		{
			return;
		}
		if (nodeA.parent->parent->left == nodeA.parent)
		{
			if (nodeA.parent->parent->right != NULL && nodeA.parent->parent->right->color == RED)
			{
				insertCase3(nodeA);
			}
		}
		else if (nodeA.parent->parent->right == nodeA.parent)
		{
			if (nodeA.parent->parent->left != NULL && nodeA.parent->parent->left->color == RED)
			{
				insertCase3(nodeA);
			}
		}
		else
		{
			insertCase4(nodeA);
		}
	}
}

//Function for inserting a new node into the tree
void strRBTree::insert(int key, std::string name)
{
	sStrRBNode* node = new sStrRBNode(key, name);

	if (nodeCount == 0)
	{
		root = node;
		node->color = BLACK;
		nodeCount++;
		return;
	}

	BSTInsert(*node, *root);
	balanceInsert(*node);

	// find the new root
	sStrRBNode* rootNode = root;
	if (rootNode == NULL)
	{
		rootNode = node;
	}

	while (rootNode->parent != NULL)
		rootNode = rootNode->parent;
	this->root = rootNode;

	this->nodeCount++;
}

//Insert for binary search tree
void strRBTree::BSTInsert(sStrRBNode& nodeA, sStrRBNode& nodeB)
{
	// recursively descend the tree until a leaf is found
	if (&nodeB != NULL && nodeA.key < nodeB.key)
	{
		if (nodeB.left != NULL)
		{
			BSTInsert(nodeA, *nodeB.left);
			//return;
		}
		else
			nodeB.left = &nodeA;
	}
	else if (&nodeB != NULL)
	{
		if (nodeB.right != NULL)
		{
			BSTInsert(nodeA, *nodeB.right);
			//return;
		}
		else
			nodeB.right = &nodeA;
	}

	// insert new node n
	nodeA.parent = &nodeB;
	nodeA.left = NULL;
	nodeA.right = NULL;
	nodeA.color = RED;

	balanceInsert(nodeA);
	//balance(nodeA, nodeB);
}

strRBTree::sStrRBNode* strRBTree::traverseInOrder(strRBTree::sStrRBNode& nodeA)
{
	if (nodeA.left == NULL)
		return &nodeA;
	//Traverse through left node
	traverseInOrder(*nodeA.left);
	//Traverse through right node
	traverseInOrder(*nodeA.right);

}

strRBTree::sStrRBNode * strRBTree::find(int key, sStrRBNode& nodeA)
{
	if (&nodeA == NULL)
	{
		return NULL;
	}
	//If key is found, return node
	if (nodeA.key == key)
	{
		return &nodeA;
	}
	else
	{
		//Look at left node
		if (nodeA.left != NULL)
		{
			nodeA = *(find(key, *nodeA.left));
		}
		//If key is found, return node
		if (nodeA.key == key)
		{
			return &nodeA;
		}
		else
		{
			//Look at right node
			if (nodeA.right != NULL)
			{
				nodeA = *(find(key, *nodeA.right));
			}
			//If key is found, return node
			if (nodeA.key == key)
			{
				return &nodeA;
			}
		}
	}
	//Return null if key is not found
	return NULL;
}

std::string strRBTree::findName(int key)
{
	sStrRBNode* node = find(key, *(getRoot()));
	return node->name;
}

void strRBTree::traverseLevelOrder()
{
}

int strRBTree::getSize()
{
	return this->nodeCount;
}

//Function for clearing tree of all nodes
void strRBTree::clear(sStrRBNode* node)
{
	if (node == NULL)
	{
		return;
	}

	if (node->left != NULL)
	{
		clear(node->left);
	}
	if (node->right != NULL)
	{
		clear(node->right);
	}

	//just in case, set pointers to null
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;

	if (node != root)
	{
		delete node;
		this->nodeCount--;
	}
	else
	{
		delete node;
		sStrRBNode * newRoot = NULL;
		this->root = newRoot;
		this->nodeCount = 0;
	}
}

strRBTree::sStrRBNode * strRBTree::getRoot()
{
	return this->root;
}
