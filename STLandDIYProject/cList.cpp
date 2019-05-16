#include "cList.h"

cPersonList::cPersonList()
{
}

cPersonList::~cPersonList()
{
}

// Function for inserting a new person into the list
void cPersonList::InsertPerson(sPerson person)
{
	sPersonListNode* node = new sPersonListNode();
	node->person = person;

	//if no nodes in the list
	if (this->nodeCount == 0)
	{
		node->prevNode = NULL;
		node->nextNode = NULL;
		beginNode = node;
		endNode = node;
		currentNode = node;
		currentIndex = 0;
	}
	else //if there are already nodes in the list
	{
		endNode->nextNode = node; //link this node to previous node
		node->prevNode = endNode; //link previous node to this node
		node->nextNode = NULL; //this node has no node after it
		endNode = node; //this node is now the last node in the list
	}

	nodeCount++;
}

void cPersonList::Begin()
{
	if (this->nodeCount > 0)
	{
		this->currentIndex = 0;
		this->currentNode = this->beginNode;
	}
	else
	{
		this->currentNode = NULL;
		this->currentIndex = -1;
	}
}

void cPersonList::End()
{
	if (this->nodeCount > 0)
	{
		this->currentIndex = this->nodeCount - 1;
		this->currentNode = this->endNode;
	}
	else
	{
		this->currentIndex = -1;
		this->currentNode = NULL;
	}
}

// Function for traversing forwards through the list
void cPersonList::TraverseList(int amount)
{
	int i = currentIndex; //starting point
	int max = currentIndex + amount; //ending point

	while (i < max)
	{
		if (i > this->nodeCount - 1)
		{
			return;
		}

		//Move current node to next node
		currentNode = currentNode->nextNode;
		//Increase current index
		currentIndex++;
		//Increment counter
		i++;
	}
}

// Function for traversing forwards through the list
void cPersonList::TraverseListBack(int amount)
{
	int i = currentIndex; //starting point
	int min = currentIndex - amount; //ending point

	while (i > min)
	{
		if (i < 0)
		{
			return;
		}

		//Move current node to previous node
		currentNode = currentNode->prevNode;
		//Decrease current index
		currentIndex--;
		//Decrement counter
		i--;
	}
}

//Get the person at the current index position
void cPersonList::GetPersonAtCurrentIndex(sPerson & thePerson)
{
	thePerson = currentNode->person;
}

unsigned int cPersonList::GetSize(void)
{
	return this->nodeCount;
}

void cPersonList::Clear()
{
	//Loop backwards over list, deleting as we go
	while (nodeCount > 1)
	{
		this->End();
		this->currentNode = this->currentNode->prevNode;
		currentIndex--;
		this->endNode = this->currentNode;
		delete this->currentNode->nextNode;
		this->currentNode->nextNode = NULL;
		nodeCount--;
	}

	if (nodeCount == 1)
	{
		this->endNode = NULL;
		this->beginNode = NULL;
		delete this->currentNode;
		this->currentNode = NULL;
		currentIndex--;
		nodeCount--;
	}
}

cStringList::cStringList()
{
}

cStringList::~cStringList()
{
}

void cStringList::InsertName(std::string name)
{
	sStringListNode* node = new sStringListNode();
	node->name = name;

	//if no nodes in the list
	if (this->nodeCount == 0)
	{
		node->prevNode = NULL;
		node->nextNode = NULL;
		beginNode = node;
		endNode = node;
		currentNode = node;
		currentIndex = 0;
	}
	else //if there are already nodes in the list
	{
		endNode->nextNode = node; //link this node to previous node
		node->prevNode = endNode; //link previous node to this node
		node->nextNode = NULL; //this node has no node after it
		endNode = node; //this node is now the last node in the list
	}

	nodeCount++;
}

void cStringList::Begin()
{
	if (this->nodeCount > 0)
	{
		this->currentIndex = 0;
		this->currentNode = this->beginNode;
	}
	else
	{
		this->currentNode = NULL;
		this->currentIndex = -1;
	}
}

void cStringList::End()
{
	if (this->nodeCount > 0)
	{
		this->currentIndex = this->nodeCount - 1;
		this->currentNode = this->endNode;
	}
	else
	{
		this->currentIndex = -1;
		this->currentNode = NULL;
	}
}

void cStringList::TraverseList(int amount)
{
	int i = currentIndex; //starting point
	int max = currentIndex + amount; //ending point

	while (i < max)
	{
		if (i > this->nodeCount - 1)
		{
			return;
		}

		//Move current node to next node
		currentNode = currentNode->nextNode;
		//Increase current index
		currentIndex++;
		//Increment counter
		i++;
	}
}

void cStringList::TraverseListBack(int amount)
{
	int i = currentIndex; //starting point
	int min = currentIndex - amount; //ending point

	while (i > min)
	{
		if (i < 0)
		{
			return;
		}

		//Move current node to previous node
		currentNode = currentNode->prevNode;
		//Decrease current index
		currentIndex--;
		//Decrement counter
		i--;
	}
}

void cStringList::GetNameAtCurrentIndex(std::string & theName)
{
	theName = this->currentNode->name;
}

unsigned int cStringList::GetSize(void)
{
	return this->nodeCount;
}

void cStringList::Clear()
{
	//Loop backwards over list, deleting as we go
	while (nodeCount > 1)
	{
		this->End();
		this->currentNode = this->currentNode->prevNode;
		currentIndex--;
		this->endNode = this->currentNode;
		delete this->currentNode->nextNode;
		this->currentNode->nextNode = NULL;
		nodeCount--;
	}

	if (nodeCount == 1)
	{
		this->endNode = NULL;
		this->beginNode = NULL;
		delete this->currentNode;
		this->currentNode = NULL;
		currentIndex--;
		nodeCount--;
	}
}
