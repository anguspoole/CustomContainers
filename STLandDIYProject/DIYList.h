#ifndef _DIY_LIST_HG_
#define _DIY_LIST_HG_

#include "iPersonMotron.h"
#include <list>
#include <time.h>
//#include "cPerson.h"

	// *************************************************************
//	   _          __              _   _             _ 
//	  /_\   ___  / _|_  _ _ _  __| |_(_)___ _ _  __(_)
//	 / _ \ (_-< |  _| || | ' \/ _|  _| / _ \ ' \(_-<_ 
//	/_/ \_\/__/ |_|  \_,_|_||_\__|\__|_\___/_||_/__(_)
//	                                                  
// *************************************************************

class DIYList : public iPersonMotron
{
public:
	void initPerfData();
	void updatePerfData();

// Loads data into the "main" container.
// Whenever this is called, any "old" data is destroyed.
	bool LoadDataFilesIntoContainer(std::string firstNameFemaleFileName,
		std::string firstNameMaleFileName,
		std::string lastNameFileName);

	// Returns only people with this name 
	// If the name (first or last) is blank (""), then ignore this parameter.
	// For example: 
	// - if last name is "", search only by first name
	// - if first name is "", search only by last name
	// - if both names are blank, return everyone
	bool FindPeopleByName(std::vector<sPerson> &vecPeople, sPerson personToMatch, int maxNumberOfPeople = INT_MAX);
	bool FindPeopleByName(std::vector<sPerson> &vecPeople, std::vector<sPerson> &vecPeopleToMatch, int maxNumberOfPeople = INT_MAX);

	// Returns false if not found.
	bool FindPersonByID(sPerson &person, unsigned long long uniqueID);

	// Finds the closest people (could be zero), from a point and radius. 
	// Assume that location is "less than or equal" to radius
	bool FindPeople(std::vector<sPerson> &vecPeople, sPoint location, float radius,
		int maxPeopleToReturn = INT_MAX);
	// Finds people with a cetain health range (inclusive of the min and max values)
	bool FindPeople(std::vector<sPerson> &vecPeople, float minHealth, float maxHealth,
		int maxPeopleToReturn = INT_MAX);
	// Combination of the two functions above
	bool FindPeople(std::vector<sPerson> &vecPeople,
		sPoint location, float radius, float minHealth, float maxHealth,
		int maxPeopleToReturn = INT_MAX);

	// Returns the enum from the cPerson.h file
	eContainerType getContainerType(void);

	//enum eSortType
	//{
	//	ASC_FIRST_THEN_LAST,
	//	DESC_FIRST_THEN_LAST,
	//	ASC_LAST_THEN_FIRST,
	//	DESC_LAST_THEN_FIRST,
	//	ASC_BY_ID,
	//	DESC_BY_ID,
	//	ASC_BY_HEALTH,
	//	DESC_BY_HEALTH
	//};

	// Sorts the people, then returns the container of sorted people
	// - this is from the data loaded by LoadDataFilesIntoContainer()
	bool SortPeople(std::vector<sPerson> &vecPeople, eSortType sortType);

	bool MakeRandomPeople(int numPeople);

	// Can be called after every function. 
	// Calls from any of the above functions overwrites this data. 
	// Measuring starts from when call is made to just before it returns.
	bool GetPerformanceFromLastCall(sPerfData &callStats);

	clock_t perfClock;
	sPerfData performanceData;
};
#endif
