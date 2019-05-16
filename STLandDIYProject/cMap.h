#ifndef _CMap_HG_
#define _CMap_HG_

#include "cPerson.h"
#include "iPersonMotron.h"
//#include "RBTree.h"
#include "AVLTree.h"

class cMap
{
public:
	cMap();
	~cMap();

	void InsertPersonAtIndex(unsigned int index, sPerson person);
	bool GetPersonAtIndex(unsigned int index, sPerson &thePerson);		// operator[]
	unsigned int GetSize(void);		// Number of things in array
	void Clear(); //For clearing vector of values

private:

	AVLPersonTree* tree; //red black tree for storing data
};

class strMap
{
public:
	strMap();
	~strMap();

	void InsertStringAtIndex(unsigned int index, std::string str);
	bool GetStringAtIndex(unsigned int index, std::string &str);		// operator[]
	unsigned int GetSize(void);		// Number of things in array
	void Clear(); //For clearing vector of values

private:

	AVLStrTree* tree; //red black tree for storing data
};

class strPersonMap
{
public:
	strPersonMap();
	~strPersonMap();

	void InsertPersonAtIndex(std::string index, sPerson person);
	bool GetPersonAtIndex(std::string index, sPerson &thePerson);		// operator[]
	bool GetPersonAtIntIndex(int index, sPerson &thePerson);		// operator[]
	unsigned int GetSize(void);		// Number of things in array
	void Clear(); //For clearing vector of values

private:

	AVLStrPersonTree* tree; //red black tree for storing data
};

#endif

