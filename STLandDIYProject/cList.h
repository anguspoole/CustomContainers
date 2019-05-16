#ifndef _CLIST_HG_
#define _CLIST_HG_

#include "cPerson.h"

struct sPersonListNode
{
	sPerson person;
	sPersonListNode* prevNode = NULL;
	sPersonListNode* nextNode = NULL;
};

struct sStringListNode
{
	std::string name;
	sStringListNode* prevNode = NULL;
	sStringListNode* nextNode = NULL;
};

class cPersonList
{
public:
	cPersonList();
	~cPersonList();

	void InsertPerson(sPerson person);
	void Begin();
	void End();
	void TraverseList(int amount);
	void TraverseListBack(int amount);
	//void InsertPersonAtIndex(unsigned int index, sPerson person);
	//bool GetPersonAtIndex(unsigned int index, sPerson &thePerson);		// operator[]
	void GetPersonAtCurrentIndex(sPerson &thePerson);
	unsigned int GetSize(void);		// Number of things in array
	void Clear(); //For clearing vector of values

private:
	sPersonListNode* beginNode = NULL;
	sPersonListNode* endNode = NULL;
	sPersonListNode* currentNode = NULL;
	int currentIndex = -1;
	int nodeCount = 0;
};

class cStringList
{
public:
	cStringList();
	~cStringList();

	void InsertName(std::string name);
	void Begin();
	void End();
	void TraverseList(int amount);
	void TraverseListBack(int amount);
	//void InsertNameAtIndex(unsigned int index, std::string name);
	//bool GetNameAtIndex(unsigned int index, std::string &name);		// operator[]
	void GetNameAtCurrentIndex(std::string &theName);
	unsigned int GetSize(void);		// Number of things in array
	void Clear(); //For clearing vector of values

private:
	sStringListNode* beginNode = NULL;
	sStringListNode* endNode = NULL;
	sStringListNode* currentNode = NULL;
	int currentIndex = -1;
	int nodeCount = 0;
};

#endif // !_CLIST_HG_
