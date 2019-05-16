#include "cVector.h"

//================================================
//	Person Vector
//================================================

cVector::cVector()
{
	// Set up init data
		
	//static const unsigned int INIT_CAPACITY = 3;

	this->m_curCapacity = cVector::INIT_CAPACITY;

	this->m_ElementSize = sizeof(sPerson);
	
	// Allocate the array
	this->m_pMyData = new sPerson[this->m_curCapacity];

	this->m_nextIndex = 0;		// Initial insert index location

	return;
}

//static
unsigned int cVector::INIT_CAPACITY = 3;

cVector::~cVector()
{
	delete [] this->m_pMyData;

	return;
}

//Get the size of the array
unsigned int cVector::GetSize(void)
{
	return this->m_nextIndex;
}

unsigned int cVector::GetCapacity(void)
{
	return this->m_curCapacity;
}

void cVector::Clear()
{
	delete[] this->m_pMyData;
	// Allocate the array
	this->m_pMyData = new sPerson[this->m_curCapacity];

	this->m_nextIndex = 0;		// Initial insert index location
}





void cVector::InsertPersonAtEnd(sPerson person)
{
	this->m_pMyData[this->m_nextIndex] = person;

	// Move to the "next" location
	this->m_nextIndex++;			// 3

	// Check to see if I've exceeded the capacity of the array
	if ( this->m_nextIndex >= this->m_curCapacity )
	{
		// Calculate new size
		this->m_curCapacity *= 2;		// 6  3

		// Make a new array 
		sPerson* pNewArray = new sPerson[this->m_curCapacity];		// 6 in size

		// Copy the old data into the new one
		for ( unsigned int index = 0; index < this->m_nextIndex; index++ )
		{
			pNewArray[index] = this->m_pMyData[index];
		}

		// Delete the old one
		delete [] this->m_pMyData;			// Bye, bye

		// Point the array to the new location
		this->m_pMyData = pNewArray;
	}

	return;
}

void cVector::InsertPersonAtIndex(unsigned int index, sPerson person)
{
	// TODO:
	return;
}


bool cVector::GetPersonAtIndex(unsigned int index, sPerson &thePerson)
{
	thePerson = this->m_pMyData[index];
	return true;
}

void cVector::SwapPeople(unsigned int indexA, unsigned int indexB)
{

	sPerson personA = this->m_pMyData[indexA];
	sPerson personB = this->m_pMyData[indexB];
	sPerson* personC = new sPerson(personA);

	this->m_pMyData[indexA] = personB;
	this->m_pMyData[indexB] = (*personC);
	delete personC; //delete the allocated memory
}

//================================================
//	String Vector
//================================================

//static
unsigned int strVector::INIT_CAPACITY = 3;

strVector::strVector()
{
	// Set up init data

	this->m_curCapacity = strVector::INIT_CAPACITY;

	this->m_ElementSize = sizeof(std::string);

	// Allocate the array
	this->m_pMyData = new std::string[this->m_curCapacity];

	this->m_nextIndex = 0;		// Initial insert index location

	return;
}

strVector::~strVector()
{
	delete[] this->m_pMyData;
}

//Get the size of the array
unsigned int strVector::GetSize(void)
{
	return this->m_nextIndex;
}

unsigned int strVector::GetCapacity(void)
{
	return this->m_curCapacity;
}

void strVector::Clear()
{
	delete[] this->m_pMyData;
	// Allocate the array
	this->m_pMyData = new std::string[this->m_curCapacity];

	this->m_nextIndex = 0;		// Initial insert index location
}





void strVector::InsertStringAtEnd(std::string str)
{
	this->m_pMyData[this->m_nextIndex] = str;

	// Move to the "next" location
	this->m_nextIndex++;			// 3

	// Check to see if I've exceeded the capacity of the array
	if (this->m_nextIndex >= this->m_curCapacity)
	{
		// Calculate new size
		this->m_curCapacity *= 2;		// 6  3

		// Make a new array 
		std::string* pNewArray = new std::string[this->m_curCapacity];		// 6 in size

		// Copy the old data into the new one
		for (unsigned int index = 0; index < this->m_nextIndex; index++)
		{
			pNewArray[index] = this->m_pMyData[index];
		}

		// Delete the old one
		delete[] this->m_pMyData;			// Bye, bye

		// Point the array to the new location
		this->m_pMyData = pNewArray;
	}

	return;
}

void strVector::InsertStringAtIndex(unsigned int index, std::string str)
{
	// TODO:
	return;
}


bool strVector::GetStringAtIndex(unsigned int index, std::string &str)
{
	str = this->m_pMyData[index];
	return true;
}
