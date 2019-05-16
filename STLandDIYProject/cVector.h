#ifndef _DIYVector_HG_
#define _DIYVector_HG_

#include "cPerson.h"
#include "iPersonMotron.h"

class cVector
{
public:
	cVector();
	~cVector();

	void InsertPersonAtEnd(sPerson person);			// push_back()
	// Every single insert causes a "shift and copy" 
	// and also might cause a resize (and copy)
	void InsertPersonAtIndex(unsigned int index, sPerson person);
	bool GetPersonAtIndex(unsigned int index, sPerson &thePerson);		// operator[]

	void SwapPeople(unsigned int indexA, unsigned int indexB); //swap people at indices

	void SetCapacity(unsigned int newCapacity);		// vec.reserve();

	unsigned int GetSize(void);		// Number of things in array
	unsigned int GetCapacity(void);	// Actual size of internal array

	void Clear(); //For clearing vector of values

private:


	// Store data dynamically
	sPerson* m_pMyData;			// "array" of data


	// Vector can hold 3 things at the start
	static unsigned int INIT_CAPACITY;// = 3;
	unsigned int m_curCapacity;		// How big the array is
	unsigned int m_nextIndex;		// The "end" of the array
	unsigned int m_ElementSize; //How big each element of the array is
};

class strVector
{
public:
	strVector();
	~strVector();

	void InsertStringAtEnd(std::string person);			// push_back()
	// Every single insert causes a "shift and copy" 
	// and also might cause a resize (and copy)
	void InsertStringAtIndex(unsigned int index, std::string str);
	bool GetStringAtIndex(unsigned int index, std::string &str);		// operator[]

	void SetCapacity(unsigned int newCapacity);		// vec.reserve();

	unsigned int GetSize(void);		// Number of things in array
	unsigned int GetCapacity(void);	// Actual size of internal array

	void Clear(); //For clearing vector of values

private:


	// Store data dynamically
	std::string* m_pMyData;			// "array" of data


	// Vector can hold 3 things at the start
	static unsigned int INIT_CAPACITY;// = 3;
	unsigned int m_curCapacity;		// How big the array is
	unsigned int m_nextIndex;		// The "end" of the array
	unsigned int m_ElementSize; //How big each element of the array is
};

#endif

