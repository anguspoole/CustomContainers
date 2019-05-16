#include "cMap.h"

//===============================
//	Int-Person Map
//===============================

cMap::cMap()
{
	// Set up init data

	//this->tree = new RBTree();
	this->tree = new AVLPersonTree();

	return;
}

cMap::~cMap()
{
	return;
}

//Get the size of the map
unsigned int cMap::GetSize(void)
{
	return tree->getSize();
}

void cMap::Clear()
{
	tree->clear(tree->getRoot());
}

void cMap::InsertPersonAtIndex(unsigned int index, sPerson person)
{
	tree->insert(index, person);
	return;
}

bool cMap::GetPersonAtIndex(unsigned int index, sPerson &thePerson)
{
	thePerson = *(tree->findPerson(index));
	return true;
}

//================================================
//	Int-String Map
//================================================

strMap::strMap()
{
	// Set up init data

	//this->tree = new strRBTree();
	this->tree = new AVLStrTree();

	return;
}

strMap::~strMap()
{
	return;
}

//Get the size of the map
unsigned int strMap::GetSize(void)
{
	return tree->getSize();
}

void strMap::Clear()
{
	tree->clear(tree->getRoot());
}

void strMap::InsertStringAtIndex(unsigned int index, std::string str)
{
	tree->insert(index, str);
	return;
}

bool strMap::GetStringAtIndex(unsigned int index, std::string &theString)
{
	theString = tree->findName(index);
	return true;
}

//===============================
//	String-Person Map
//===============================

strPersonMap::strPersonMap()
{
	// Set up init data
	this->tree = new AVLStrPersonTree();

	return;
}

strPersonMap::~strPersonMap()
{
	return;
}

//Get the size of the map
unsigned int strPersonMap::GetSize(void)
{
	return tree->getSize();
}

void strPersonMap::Clear()
{
	tree->clear(tree->getRoot());
}

void strPersonMap::InsertPersonAtIndex(std::string index, sPerson person)
{
	tree->insert(index, person);
	return;
}

bool strPersonMap::GetPersonAtIndex(std::string index, sPerson &thePerson)
{
	thePerson = *(tree->findPerson(index));
	return true;
}

bool strPersonMap::GetPersonAtIntIndex(int index, sPerson & thePerson)
{
	thePerson = this->tree->startIntLoop(this->tree->getRoot(), index);
	return false;
}
