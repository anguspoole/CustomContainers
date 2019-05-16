#ifndef _AVL_TREE_HG_
#define _AVL_TREE_HG_

#include <string>
#include "cPerson.h"

// An AVL tree node  
struct sAVLPersonNode
{
public:
	int key;
	sPerson person;
	sAVLPersonNode *left = NULL;
	sAVLPersonNode *right = NULL;
	int height;
};

// An AVL tree node  
struct sAVLStrNode
{
public:
	int key;
	std::string name;
	sAVLStrNode *left = NULL;
	sAVLStrNode *right = NULL;
	int height;
};

// An AVL tree node  
struct sAVLStrPersonNode
{
public:
	std::string key;
	sPerson person;
	sAVLStrPersonNode *left = NULL;
	sAVLStrPersonNode *right = NULL;
	int height;
};

class AVLPersonTree
{
public:
	AVLPersonTree();
	~AVLPersonTree();

	// Function to determine largest of two ints 
	int getMax(int a, int b);

	// Function to get the height of tree 
	int getHeight(sAVLPersonNode* N);

	// Function to right rotate subtree based on root y  
	sAVLPersonNode* rightRotate(sAVLPersonNode* y);

	// Function to left rotate subtree based on root x
	sAVLPersonNode* leftRotate(sAVLPersonNode* x);

	// Function to determine how balanced the tree is (left vs right)
	int getBalance(sAVLPersonNode* N);

	// Function being called by other classes to add a node
	void insert(int key, sPerson person);

	// Function being called by other classes to find person with specific key
	sPerson* findPerson(int key);

	// Function to get the size of the tree
	int getSize();

	// Function to clear the entire tree
	void clear(sAVLPersonNode* node);

	// Function to get the root of the tree
	sAVLPersonNode* getRoot();

private:
	sAVLPersonNode* root;
	int nodeCount = 0;

	// Function to add a node to the tree (internal)
	sAVLPersonNode* insertNode(sAVLPersonNode* node, int key, sPerson person);
	// Function to find a node with specific key (internal)
	sAVLPersonNode* find(int key, sAVLPersonNode* nodeA);
};

class AVLStrTree
{
public:
	AVLStrTree();
	~AVLStrTree();

	// A utility function to get maximum of two integers  
	int getMax(int a, int b);

	// A utility function to get the height of the tree  
	int getHeight(sAVLStrNode* N);

	// A utility function to right rotate subtree rooted with y  
	sAVLStrNode* rightRotate(sAVLStrNode* y);

	// A utility function to left rotate subtree rooted with x
	sAVLStrNode* leftRotate(sAVLStrNode* x);

	int getBalance(sAVLStrNode* N);

	sAVLStrNode* insertNode(sAVLStrNode* node, int key, std::string name);
	void insert(int key, std::string name);

	sAVLStrNode* find(int key, sAVLStrNode* nodeA);
	std::string findName(int key);
	int getSize();
	void clear(sAVLStrNode* node);
	sAVLStrNode* getRoot();

private:
	sAVLStrNode* root;
	int nodeCount = 0;
};

class AVLStrPersonTree
{
public:
	AVLStrPersonTree();
	~AVLStrPersonTree();

	// Function to determine largest of two strings 
	int getMax(int a, int b);

	// Function to get the height of tree 
	int getHeight(sAVLStrPersonNode* N);

	// Function to right rotate subtree based on root y  
	sAVLStrPersonNode* rightRotate(sAVLStrPersonNode* y);

	// Function to left rotate subtree based on root x
	sAVLStrPersonNode* leftRotate(sAVLStrPersonNode* x);

	// Function to determine how balanced the tree is (left vs right)
	int getBalance(sAVLStrPersonNode* N);

	// Function being called by other classes to add a node
	void insert(std::string key, sPerson person);

	// Function being called by other classes to find person with specific key
	sPerson* findPerson(std::string key);

	// Function to get the size of the tree
	int getSize();

	// Function to clear the entire tree
	void clear(sAVLStrPersonNode* node);

	void resetCurrent();
	sPerson startIntLoop(sAVLStrPersonNode * root, int targetNumber);
	sAVLStrPersonNode* preOrder(sAVLStrPersonNode *root, int targetNumber);

	// Function to get the root of the tree
	sAVLStrPersonNode* getRoot();

private:
	sAVLStrPersonNode* root;
	sAVLStrPersonNode* currentNode;
	int travelCounter = 0;
	int nodeCount = 0;

	// Function to add a node to the tree (internal)
	sAVLStrPersonNode* insertNode(sAVLStrPersonNode* node, std::string key, sPerson person);
	// Function to find a node with specific key (internal)
	sAVLStrPersonNode* find(std::string key, sAVLStrPersonNode* nodeA);
};

#endif // !_AVL_TREE_HG_

