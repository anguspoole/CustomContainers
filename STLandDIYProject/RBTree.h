#ifndef _RB_TREE_HG_
#define _RB_TREE_HG_

#include <string>
#include "cPerson.h"

// RBTree class is used for storing information for the DIYMap
// Based on the code found here: https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
// And on the code found here: https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
class RBTree
{
public:

	RBTree();
	~RBTree();

	//Red or Black color for nodes
	enum eRBColor
	{
		RED,
		BLACK
	};

	//The structure for each node in the tree
	struct sRBNode
	{
		int key; //the key for the mapping
		sPerson person; //the person associated with the key
		eRBColor color; //the color of the node

		sRBNode* left, *right, *parent; //pointers to associated nodes

		sRBNode(int key, sPerson person)
		{
			this->key = key;
			this->person = person;
			this->left = NULL;
			this->right = NULL;
			this->parent = NULL;
		}
	};

	void rotateLeft(sRBNode* nodeA, sRBNode* nodeB);
	void rotateRight(sRBNode* nodeA, sRBNode* nodeB);
	void balanceInsert(sRBNode * nodeA);
	void balance(sRBNode* nodeA, sRBNode* nodeB);
	void insertCase1(sRBNode * nodeA);
	void insertCase2(sRBNode * nodeA);
	void insertCase3(sRBNode * nodeA);
	void insertCase4(sRBNode * nodeA);
	void insertCase4P2(sRBNode * nodeA);
	void insert(int key, sPerson person);
	sRBNode* traverseInOrder(sRBNode* nodeA);
	sRBNode* find(int key, sRBNode* nodeA);
	sPerson* findPerson(int key);
	void traverseLevelOrder();
	int getSize();
	void clear(sRBNode* node);
	sRBNode* getRoot();

private:
	sRBNode* root;
	void BSTInsert(sRBNode* nodeA, sRBNode* nodeB);

	int nodeCount;
};

class strRBTree
{
public:

	strRBTree();
	~strRBTree();

	//Red or Black color for nodes
	enum eStrRBColor
	{
		RED,
		BLACK
	};

	//The structure for each node in the tree
	struct sStrRBNode
	{
		int key; //the key for the mapping
		std::string name; //the name associated with the key
		eStrRBColor color; //the color of the node

		sStrRBNode* left, *right, *parent; //pointers to associated nodes

		sStrRBNode(int key, std::string name)
		{
			this->key = key;
			this->name = name;
			this->left = NULL;
			this->right = NULL;
			this->parent = NULL;
		}
	};

	void rotateLeft(sStrRBNode& nodeA, sStrRBNode& nodeB);
	void rotateRight(sStrRBNode& nodeA, sStrRBNode& nodeB);
	void balanceInsert(sStrRBNode& nodeA);
	void balance(sStrRBNode& nodeA, sStrRBNode& nodeB);
	void insertCase1(sStrRBNode& nodeA);
	void insertCase2(sStrRBNode& nodeA);
	void insertCase3(sStrRBNode& nodeA);
	void insertCase4(sStrRBNode& nodeA);
	void insertCase4P2(sStrRBNode& nodeA);
	void insert(int key, std::string name);
	sStrRBNode* traverseInOrder(sStrRBNode& nodeA);
	sStrRBNode* find(int key, sStrRBNode& nodeA);
	std::string findName(int key);
	void traverseLevelOrder();
	int getSize();
	void clear(sStrRBNode* node);
	sStrRBNode* getRoot();

private:
	sStrRBNode* root;
	void BSTInsert(sStrRBNode& nodeA, sStrRBNode& nodeB);

	int nodeCount;
};

#endif // !_RB_TREE_HG_
