#include "AVLTree.h"

sAVLPersonNode* makeNode(int key, sPerson person)
{
	sAVLPersonNode* node = new sAVLPersonNode();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->person = person;
	node->height = 1; // new node is initially 
					  // added at leaf  
	return(node);
}

sAVLStrNode* makeNode(int key, std::string name)
{
	sAVLStrNode* node = new sAVLStrNode();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->name = name;
	node->height = 1; // new node is initially 
					  // added at leaf  
	return(node);
}

sAVLStrPersonNode* makeNode(std::string key, sPerson person)
{
	sAVLStrPersonNode* node = new sAVLStrPersonNode();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->person = person;
	node->height = 1; // new node is initially 
					  // added at leaf  
	return(node);
}

//=================================
// AVLPersonTree
//=================================

AVLPersonTree::AVLPersonTree()
{
	this->root = NULL;
}

AVLPersonTree::~AVLPersonTree()
{
}

int AVLPersonTree::getMax(int a, int b)
{
	return (a > b) ? a : b;
}

int AVLPersonTree::getHeight(sAVLPersonNode * N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

sAVLPersonNode * AVLPersonTree::rightRotate(sAVLPersonNode * y)
{
	sAVLPersonNode *x = y->left;
	sAVLPersonNode *T2 = x->right;

	// Perform rotation  
	x->right = y;
	y->left = T2;

	// Update heights  
	y->height = getMax(getHeight(y->left),
		getHeight(y->right)) + 1;
	x->height = getMax(getHeight(x->left),
		getHeight(x->right)) + 1;

	// Return new root  
	return x;
}

sAVLPersonNode * AVLPersonTree::leftRotate(sAVLPersonNode * x)
{
	sAVLPersonNode *y = x->right;
	sAVLPersonNode *T2 = y->left;

	// Perform rotation  
	y->left = x;
	x->right = T2;

	// Update heights  
	x->height = getMax(getHeight(x->left),
		getHeight(x->right)) + 1;
	y->height = getMax(getHeight(y->left),
		getHeight(y->right)) + 1;

	// Return new root  
	return y;
}

int AVLPersonTree::getBalance(sAVLPersonNode * N)
{
	if (N == NULL)
		return 0;
	return getHeight(N->left) - getHeight(N->right);
}

sAVLPersonNode * AVLPersonTree::insertNode(sAVLPersonNode * node, int key, sPerson person)
{
	/* 1. Perform the normal BST insertion */
	if (node == NULL)
		return(makeNode(key, person));

	if (key < node->key)
		node->left = insertNode(node->left, key, person);
	else if (key > node->key)
		node->right = insertNode(node->right, key, person);
	else // Equal keys are not allowed in BST  
		return node;

	/* 2. Update height of this ancestor node */
	node->height = 1 + getMax(getHeight(node->left),
		getHeight(node->right));

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then  
	// there are 4 cases  

	// Left Left Case  
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case  
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case  
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case  
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}

void AVLPersonTree::insert(int key, sPerson person)
{
	if (getSize() == 0)
	{
		this->root = insertNode(NULL, key, person);
	}
	else
	{
		this->root = insertNode(this->root, key, person);
	}
	this->nodeCount++;
}

sAVLPersonNode * AVLPersonTree::find(int key, sAVLPersonNode * nodeA)
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
		if (key < nodeA->key)
		{
			//Look at left node
			if (nodeA->left != NULL)
			{
				nodeA = find(key, nodeA->left);
			}
			//If key is found, return node
			if (nodeA != NULL && nodeA->key == key)
			{
				return nodeA;
			}
		}
		else
		{
			//Look at right node
			if (nodeA->right != NULL)
			{
				nodeA = find(key, nodeA->right);
			}
			//If key is found, return node
			if (nodeA != NULL && nodeA->key == key)
			{
				return nodeA;
			}
		}
	}
	//Return null if key is not found
	return NULL;
}

sPerson * AVLPersonTree::findPerson(int key)
{
	sAVLPersonNode* node = find(key, getRoot());
	return &node->person;
}

int AVLPersonTree::getSize()
{
	return this->nodeCount;
}

void AVLPersonTree::clear(sAVLPersonNode * node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		this->nodeCount--;
		clear(node->left);
		clear(node->right);
		node->left = NULL;
		node->right = NULL;

		if (node == this->root)
		{
			root = NULL;
		}

		delete node;
	}
}

sAVLPersonNode * AVLPersonTree::getRoot()
{
	return this->root;
}


//=================================
// AVL String Tree
//=================================

AVLStrTree::AVLStrTree()
{
	this->root = NULL;
}

AVLStrTree::~AVLStrTree()
{
}

int AVLStrTree::getMax(int a, int b)
{
	return (a > b) ? a : b;
}

int AVLStrTree::getHeight(sAVLStrNode * N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

sAVLStrNode * AVLStrTree::rightRotate(sAVLStrNode * y)
{
	sAVLStrNode *x = y->left;
	sAVLStrNode *T2 = x->right;

	// Perform rotation  
	x->right = y;
	y->left = T2;

	// Update heights  
	y->height = getMax(getHeight(y->left),
		getHeight(y->right)) + 1;
	x->height = getMax(getHeight(x->left),
		getHeight(x->right)) + 1;

	// Return new root  
	return x;
}

sAVLStrNode * AVLStrTree::leftRotate(sAVLStrNode * x)
{
	sAVLStrNode *y = x->right;
	sAVLStrNode *T2 = y->left;

	// Perform rotation  
	y->left = x;
	x->right = T2;

	// Update heights  
	x->height = getMax(getHeight(x->left),
		getHeight(x->right)) + 1;
	y->height = getMax(getHeight(y->left),
		getHeight(y->right)) + 1;

	// Return new root  
	return y;
}

int AVLStrTree::getBalance(sAVLStrNode * N)
{
	if (N == NULL)
		return 0;
	return getHeight(N->left) - getHeight(N->right);
}

sAVLStrNode * AVLStrTree::insertNode(sAVLStrNode * node, int key, std::string name)
{
	/* 1. Perform the normal BST insertion */
	if (node == NULL)
		return(makeNode(key, name));

	if (key < node->key)
		node->left = insertNode(node->left, key, name);
	else if (key > node->key)
		node->right = insertNode(node->right, key, name);
	else // Equal keys are not allowed in BST  
		return node;

	/* 2. Update height of this ancestor node */
	node->height = 1 + getMax(getHeight(node->left),
		getHeight(node->right));

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then  
	// there are 4 cases  

	// Left Left Case  
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case  
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case  
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case  
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}

void AVLStrTree::insert(int key, std::string name)
{
	if (getSize() == 0)
	{
		this->root = insertNode(NULL, key, name);
	}
	else
	{
		//sAVLStrNode* node = newNode(key, name);
		//sAVLStrNode* node = new sAVLStrNode();

		this->root = insertNode(this->root, key, name);
	}
	this->nodeCount++;
}

sAVLStrNode * AVLStrTree::find(int key, sAVLStrNode * nodeA)
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
		if (key < nodeA->key)
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

std::string AVLStrTree::findName(int key)
{
	sAVLStrNode* node = find(key, getRoot());
	return node->name;
}

int AVLStrTree::getSize()
{
	return this->nodeCount;
}

void AVLStrTree::clear(sAVLStrNode * node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		this->nodeCount--;
		clear(node->left);
		clear(node->right);
		node->left = NULL;
		node->right = NULL;

		if (node == this->root)
		{
			root = NULL;
		}
		delete node;
	}
}

sAVLStrNode * AVLStrTree::getRoot()
{
	return this->root;
}

//=================================
// AVL String Person Tree
//=================================

AVLStrPersonTree::AVLStrPersonTree()
{
	this->root = NULL;
}

AVLStrPersonTree::~AVLStrPersonTree()
{
}

int AVLStrPersonTree::getMax(int a, int b)
{
	return (a > b) ? a : b;
}

int AVLStrPersonTree::getHeight(sAVLStrPersonNode * N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

sAVLStrPersonNode * AVLStrPersonTree::rightRotate(sAVLStrPersonNode * y)
{
	sAVLStrPersonNode *x = y->left;
	sAVLStrPersonNode *T2 = x->right;

	// Perform rotation  
	x->right = y;
	y->left = T2;

	// Update heights  
	y->height = getMax(getHeight(y->left),
		getHeight(y->right)) + 1;
	x->height = getMax(getHeight(x->left),
		getHeight(x->right)) + 1;

	// Return new root  
	return x;
}

sAVLStrPersonNode * AVLStrPersonTree::leftRotate(sAVLStrPersonNode * x)
{
	sAVLStrPersonNode *y = x->right;
	sAVLStrPersonNode *T2 = y->left;

	// Perform rotation  
	y->left = x;
	x->right = T2;

	// Update heights  
	x->height = getMax(getHeight(x->left),
		getHeight(x->right)) + 1;
	y->height = getMax(getHeight(y->left),
		getHeight(y->right)) + 1;

	// Return new root  
	return y;
}

int AVLStrPersonTree::getBalance(sAVLStrPersonNode * N)
{
	if (N == NULL)
		return 0;
	return getHeight(N->left) - getHeight(N->right);
}

sAVLStrPersonNode * AVLStrPersonTree::insertNode(sAVLStrPersonNode * node, std::string key, sPerson person)
{
	/* 1. Perform the normal BST insertion */
	if (node == NULL)
		return(makeNode(key, person));

	if (key < node->key)
		node->left = insertNode(node->left, key, person);
	else if (key > node->key)
		node->right = insertNode(node->right, key, person);
	else // Equal keys are not allowed in BST  
		return node;

	/* 2. Update height of this ancestor node */
	node->height = 1 + getMax(getHeight(node->left),
		getHeight(node->right));

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then  
	// there are 4 cases  

	// Left Left Case  
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case  
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case  
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case  
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}

void AVLStrPersonTree::insert(std::string key, sPerson person)
{
	if (getSize() == 0)
	{
		this->root = insertNode(NULL, key, person);
	}
	else
	{
		this->root = insertNode(this->root, key, person);
	}
	this->nodeCount++;
}

void AVLStrPersonTree::resetCurrent()
{
	this->currentNode = this->root;
}

sPerson AVLStrPersonTree::startIntLoop(sAVLStrPersonNode *root, int targetNumber)
{
	this->travelCounter = 0;
	this->currentNode = this->root;
	preOrder(this->root, targetNumber+1);
	return this->currentNode->person;
}

sAVLStrPersonNode* AVLStrPersonTree::preOrder(sAVLStrPersonNode *root, int targetNumber)
{
	if (root != NULL)
	{
		if (root->left != NULL)
		{
			if (this->travelCounter < targetNumber)
			{
				preOrder(root->left, targetNumber); //go to the left-most node
			}
		}

		//increment counter AFTER travelling through all LEFT children
		//effectively, only increment after we have properly settled on this node in the recursion
		this->travelCounter++;
		if (this->travelCounter == targetNumber)
		{
			this->currentNode = root; //set the current node to be the node used in the loop
			this->travelCounter++;
		}

		//only travel through right nodes AFTER we have dealt with this node
		//thus, we travel through tree left->parent->right, giving us the order from lowest to highest key
		if (root->right != NULL)
		{
			if (this->travelCounter < targetNumber)
			{
				preOrder(root->right, targetNumber);
			}
		}

		return root;
	}
	return NULL;
}

sAVLStrPersonNode * AVLStrPersonTree::find(std::string key, sAVLStrPersonNode * nodeA)
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
		if (key < nodeA->key)
		{
			//Look at left node
			if (nodeA->left != NULL)
			{
				nodeA = find(key, nodeA->left);
			}
			//If key is found, return node
			if (nodeA != NULL && nodeA->key == key)
			{
				return nodeA;
			}
		}
		else
		{
			//Look at right node
			if (nodeA->right != NULL)
			{
				nodeA = find(key, nodeA->right);
			}
			//If key is found, return node
			if (nodeA != NULL && nodeA->key == key)
			{
				return nodeA;
			}
		}
	}
	//Return null if key is not found
	return NULL;
}

sPerson * AVLStrPersonTree::findPerson(std::string key)
{
	sAVLStrPersonNode* node = find(key, getRoot());
	return &node->person;
}

int AVLStrPersonTree::getSize()
{
	return this->nodeCount;
}

void AVLStrPersonTree::clear(sAVLStrPersonNode * node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		this->nodeCount--;
		clear(node->left);
		clear(node->right);
		node->left = NULL;
		node->right = NULL;

		if (node == this->root)
		{
			root = NULL;
		}

		delete node;
	}
}

sAVLStrPersonNode * AVLStrPersonTree::getRoot()
{
	return this->root;
}
