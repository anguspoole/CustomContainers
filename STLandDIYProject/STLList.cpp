//The implementation for the STL List

#include "STLList.h"
#include <fstream>
#include <iostream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include <algorithm>
#include <Windows.h>
#include <Psapi.h>

std::list<sPerson> people;
std::list<std::string> maleFirstNames;
std::list<std::string> femaleFirstNames;
std::list<std::string> lastNames;

void STLList::initPerfData()
{

	perfClock = clock();

	performanceData.elapsedCallTime_ms = 0.0f;
	performanceData.memoryUsageBytes_avg = 0.0f;
	performanceData.memoryUsageBytes_max = 0.0f;
	performanceData.memoryUsageBytes_min = 0.0f;

	PROCESS_MEMORY_COUNTERS pmc;
	bool gotInfo = GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	if (gotInfo)
	{
		//Set initial values to be the amount of memory allocated
		performanceData.memoryUsageBytes_avg = pmc.WorkingSetSize;
		performanceData.memoryUsageBytes_max = pmc.WorkingSetSize;
		performanceData.memoryUsageBytes_min = pmc.WorkingSetSize;

		//std::cout << performanceData.memoryUsageBytes_avg << std::endl;
	}
	else
	{
		std::cout << "Could not get process memory info" << std::endl;
	}
}

void STLList::updatePerfData()
{
	performanceData.elapsedCallTime_ms = (float)((clock() - perfClock)/CLOCKS_PER_SEC) * 1000.0f;
	//std::cout << "clock: " << performanceData.elapsedCallTime_ms << std::endl;

	PROCESS_MEMORY_COUNTERS pmc;
	bool gotInfo = GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	if (gotInfo)
	{
		//std::cout << "Got Info: " << pmc.WorkingSetSize << std::endl;

		if (performanceData.memoryUsageBytes_min > pmc.WorkingSetSize)
		{
			performanceData.memoryUsageBytes_min = pmc.WorkingSetSize;
		}
		if (performanceData.memoryUsageBytes_max < pmc.WorkingSetSize)
		{
			performanceData.memoryUsageBytes_max = pmc.WorkingSetSize;
		}

		//Calculate new average
		performanceData.memoryUsageBytes_avg = (performanceData.memoryUsageBytes_min + performanceData.memoryUsageBytes_max) / 2.0f;
	}
	else
	{
		std::cout << "Could not get process memory info" << std::endl;
	}
}

float stlListCalculateDistance(sPoint location1, sPoint location2)
{
	float xS = std::pow((location2.x - location1.x), 2);
	float yS = std::pow((location2.y - location1.y), 2);
	float zS = std::pow((location2.z - location1.z), 2);
	float distance = std::sqrt(xS + yS + zS);

	return distance;
}


bool STLList::LoadDataFilesIntoContainer(std::string firstNameFemaleFileName,
	std::string firstNameMaleFileName,
	std::string lastNameFileName)
{
	initPerfData();

	std::string name; //name of person
	float namePercent; 
	float totalPercent;
	unsigned long long id;

	//open up female firstname files
	std::ifstream femaleFile(firstNameFemaleFileName);
	if (!femaleFile)
	{
		std::cout << "Error loading female firstname file" << std::endl;
		updatePerfData();
		return false;
	}

	//read through file
	while (femaleFile >> name >> namePercent >> totalPercent >> id)
	{
		femaleFirstNames.push_back(name);

		//create a person
		//sPerson person;
		//person.first = name;
		//person.uniqueID = id;
		//people.push_back(person);
		updatePerfData();
	}

	femaleFile.close();

	//for (int c = 0; c < people.size(); c++)
	//{
	//	std::cout << "Name: " << people[c].first << std::endl;
	//}

	//open up male firstname files
	std::ifstream maleFile(firstNameMaleFileName);
	if (!maleFile)
	{
		std::cout << "Error loading male firstname file" << std::endl;
		updatePerfData();
		return false;
	}

	//read through file
	while (maleFile >> name >> namePercent >> totalPercent >> id)
	{
		maleFirstNames.push_back(name);

		//create a person
		//sPerson person;
		//person.first = name;
		//person.uniqueID = id;
		//people.push_back(person);
		updatePerfData();
	}

	maleFile.close();

	//open up male firstname files
	std::ifstream lastFile(lastNameFileName);
	if (!lastFile)
	{
		std::cout << "Error loading lastname file" << std::endl;
		updatePerfData();
		return false;
	}

	//read through file
	while (lastFile >> name >> namePercent >> totalPercent >> id)
	{
		lastNames.push_back(name);

		//create a person
		//sPerson person;
		//person.first = name;
		//person.uniqueID = id;
		//people.push_back(person);
		updatePerfData();
	}

	lastFile.close();

	updatePerfData();

	return true;

}

bool STLList::FindPeopleByName(std::vector<sPerson>& vecPeople, sPerson personToMatch, int maxNumberOfPeople)
{
	initPerfData();

	//clear vector in case it has people in it already
	vecPeople.clear();

	std::list<sPerson>::iterator it = people.begin();

	//If no first or last name, add everybody to vector
	if (personToMatch.first == "" && personToMatch.last == "")
	{
		if (maxNumberOfPeople <= people.size())
		{
			it = people.begin();
			for (int i = 0; i < maxNumberOfPeople; i++)
			{
				vecPeople.push_back(*it);
				it++;
				updatePerfData();
			}
		}
		else
		{
			for (it = people.begin(); it != people.end(); it++)
			{
				vecPeople.push_back(*it);
				updatePerfData();
			}
		}
	}
	//If no last name, add anybody with matching first name to vector
	else if (personToMatch.first != "" && personToMatch.last == "")
	{
		for (it = people.begin(); it != people.end(); it++)
		{
			if ((*it).first == personToMatch.first && vecPeople.size() < maxNumberOfPeople)
			{
				vecPeople.push_back(*it);
				updatePerfData();
			}
			if (vecPeople.size() >= maxNumberOfPeople)
			{
				updatePerfData();
				break;
			}
		}
	}
	//If no first name, add anybody with last name to vector
	else if (personToMatch.first == "" && personToMatch.last != "")
	{
		for (it = people.begin(); it != people.end(); it++)
		{
			if ((*it).last == personToMatch.last && vecPeople.size() < maxNumberOfPeople)
			{
				vecPeople.push_back(*it);
				updatePerfData();
			}
			if (vecPeople.size() >= maxNumberOfPeople)
			{
				updatePerfData();
				break;
			}
		}
	}
	//Add exact person to vector
	else
	{
		for (it = people.begin(); it != people.end(); it++)
		{
			if ((*it).first == personToMatch.first &&
				(*it).last == personToMatch.last &&
				vecPeople.size() < maxNumberOfPeople)
			{
				vecPeople.push_back(*it);
				updatePerfData();
			}
			if (vecPeople.size() >= maxNumberOfPeople)
			{
				updatePerfData();
				break;
			}
		}
	}

	if (vecPeople.size() > 0)
	{
		updatePerfData();
		return true;
	}
	else
	{
		updatePerfData();
		return false;
	}
}

bool STLList::FindPeopleByName(std::vector<sPerson>& vecPeople, std::vector<sPerson>& vecPeopleToMatch, int maxNumberOfPeople)
{
	initPerfData();

	//clear vector in case it has people in it already
	vecPeople.clear();

	std::list<sPerson>::iterator it = people.begin();

	int remainingMax = maxNumberOfPeople;

	for (int c = 0; c < vecPeopleToMatch.size(); c++)
	{
		if (remainingMax == 0)
		{
			break;
		}

		sPerson personToMatch = vecPeopleToMatch[c];

		//If no first or last name, add everybody to vector
		if (personToMatch.first == "" && personToMatch.last == "")
		{
			if (maxNumberOfPeople <= people.size())
			{
				it = people.begin();
				for (int i = 0; i < maxNumberOfPeople; i++)
				{
					vecPeople.push_back(*it);
					it++;
					updatePerfData();
				}
			}
			else
			{
				for (it = people.begin(); it != people.end(); it++)
				{
					vecPeople.push_back(*it);
					updatePerfData();
				}
			}
		}
		//If no last name, add anybody with matching first name to vector
		else if (personToMatch.first != "" && personToMatch.last == "")
		{
			for (it = people.begin(); it != people.end(); it++)
			{
				if ((*it).first == personToMatch.first && vecPeople.size() < maxNumberOfPeople)
				{
					vecPeople.push_back(*it);
					updatePerfData();
				}
				if (vecPeople.size() >= maxNumberOfPeople)
				{
					updatePerfData();
					break;
				}
			}
		}
		//If no first name, add anybody with last name to vector
		else if (personToMatch.first == "" && personToMatch.last != "")
		{
			for (it = people.begin(); it != people.end(); it++)
			{
				if ((*it).last == personToMatch.last && vecPeople.size() < maxNumberOfPeople)
				{
					vecPeople.push_back(*it);
					updatePerfData();
				}
				if (vecPeople.size() >= maxNumberOfPeople)
				{
					updatePerfData();
					break;
				}
			}
		}
		//Add exact person to vector
		else
		{
			for (it = people.begin(); it != people.end(); it++)
			{
				if ((*it).first == personToMatch.first &&
					(*it).last == personToMatch.last &&
					vecPeople.size() < maxNumberOfPeople)
				{
					vecPeople.push_back(*it);
					updatePerfData();
				}
				if (vecPeople.size() >= maxNumberOfPeople)
				{
					updatePerfData();
					break;
				}
			}
		}
	}

	if (vecPeople.size() > 0)
	{
		updatePerfData();
		return true;
	}
	else
	{
		updatePerfData();
		return false;
	}
}

bool STLList::FindPersonByID(sPerson & person, unsigned long long uniqueID)
{
	initPerfData();

	for(std::list<sPerson>::iterator it = people.begin(); it != people.end(); it++)
	{
		if ((*it).uniqueID == uniqueID)
		{
			person = (*it);
			updatePerfData();
			return true;
		}
	}
	updatePerfData();
	return false;
}

bool STLList::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, int maxPeopleToReturn)
{
	initPerfData();

	//clear vector in case it has people in it already
	vecPeople.clear();

	int count = 0;

	//Loop over all people
	for (std::list<sPerson>::iterator it = people.begin(); it != people.end(); it++)
	{
		if (count < maxPeopleToReturn)
		{
			//Add people within distance range
			float dist = stlListCalculateDistance(location, (*it).location);
			if (dist <= radius)
			{
				vecPeople.push_back(*it);
				updatePerfData();
			}
		}
		else
		{
			updatePerfData();
			break;
		}
		count++;
	}

	if (vecPeople.size() > 0)
	{
		updatePerfData();
		return true;
	}
	else
	{
		updatePerfData();
		return false;
	}
}

bool STLList::FindPeople(std::vector<sPerson>& vecPeople, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	initPerfData();

	//clear vector in case it has people in it already
	vecPeople.clear();

	int count = 0;

	//Loop over all people
	for (std::list<sPerson>::iterator it = people.begin(); it != people.end(); it++)
	{
		if (count < maxPeopleToReturn)
		{
			//Add people with health within range
			if ((*it).health >= minHealth && (*it).health <= maxHealth)
			{
				vecPeople.push_back(*it);
				updatePerfData();
			}
		}
		else
		{
			updatePerfData();
			break;
		}
		count++;
	}

	if (vecPeople.size() > 0)
	{
		updatePerfData();
		return true;
	}
	else
	{
		updatePerfData();
		return false;
	}
}

bool STLList::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	initPerfData();

	//clear vector in case it has people in it already
	vecPeople.clear();

	int count = 0;

	//Loop over all people
	for (std::list<sPerson>::iterator it = people.begin(); it != people.end(); it++)
	{
		if (count < maxPeopleToReturn)
		{
			//Add people with minimum distance
			float dist = stlListCalculateDistance(location, (*it).location);
			updatePerfData();
			if (dist <= radius)
			{
				//Add people within health range
				if ((*it).health >= minHealth && (*it).health <= maxHealth)
				{
					vecPeople.push_back(*it);
					updatePerfData();
				}
			}
		}
		else
		{
			updatePerfData();
			break;
		}
		count++;
	}

	if (vecPeople.size() > 0)
	{
		updatePerfData();
		return true;
	}
	else
	{
		updatePerfData();
		return false;
	}
}

eContainerType STLList::getContainerType(void)
{
	initPerfData();
	updatePerfData();
	//return eContainerType();
	return STD_LIST;
}

//Helper function for checking for lower health
bool stlListCheckLowerHealth (sPerson a, sPerson b)
{
	return a.health < b.health;
}

//Helper function for checking for higher health
bool stlListCheckHigherHealth(sPerson a, sPerson b)
{
	return a.health > b.health;
}

//Helper function for checking for lower id
bool stlListCheckLowerID(sPerson a, sPerson b)
{
	return a.uniqueID < b.uniqueID;
}

//Helper function for checking for higher id
bool stlListCheckHigherID(sPerson a, sPerson b)
{
	return a.uniqueID > b.uniqueID;
}

//Helper function for checking for lower first name, then last name
bool stlListCheckLowerFirstThenLast(sPerson a, sPerson b)
{
	if (a.first == b.first)
	{
		return a.last < b.last;
	}
	else
	{
		return a.first < b.first;
	}
}

//Helper function for checking for higher first name, then last name
bool stlListCheckHigherFirstThenLast(sPerson a, sPerson b)
{
	if (a.first == b.first)
	{
		return a.last > b.last;
	}
	else
	{
		return a.first > b.first;
	}
}

//Helper function for checking for lower last name, then first name
bool stlListCheckLowerLastThenFirst(sPerson a, sPerson b)
{
	if (a.last == b.last)
	{
		return a.first < b.first;
	}
	else
	{
		return a.last < b.last;
	}
}

//Helper function for checking for higher last name, then first name
bool stlListCheckHigherLastThenFirst(sPerson a, sPerson b)
{
	if (a.last == b.last)
	{
		return a.first > b.first;
	}
	else
	{
		return a.last > b.last;
	}
}


bool STLList::SortPeople(std::vector<sPerson> &vecPeople, eSortType sortType)
{
	initPerfData();

	switch (sortType)
	{
	case eSortType::ASC_BY_HEALTH:
		people.sort(stlListCheckLowerHealth);
		updatePerfData();
		break;
	case eSortType::ASC_BY_ID:
		people.sort(stlListCheckLowerID);
		updatePerfData();
		break;
	case eSortType::ASC_FIRST_THEN_LAST:
		people.sort(stlListCheckLowerFirstThenLast);
		updatePerfData();
		break;
	case eSortType::ASC_LAST_THEN_FIRST:
		people.sort(stlListCheckLowerLastThenFirst);
		updatePerfData();
		break;
	case eSortType::DESC_BY_HEALTH:
		people.sort(stlListCheckHigherHealth);
		updatePerfData();
		break;
	case eSortType::DESC_BY_ID:
		people.sort(stlListCheckHigherID);
		updatePerfData();
		break;
	case eSortType::DESC_FIRST_THEN_LAST:
		people.sort(stlListCheckHigherFirstThenLast);
		updatePerfData();
		break;
	case eSortType::DESC_LAST_THEN_FIRST:
		people.sort(stlListCheckHigherLastThenFirst);
		updatePerfData();
		break;
	default:
		updatePerfData();
		return false;
	}

	vecPeople.clear();
	for (std::list<sPerson>::iterator it = people.begin(); it != people.end(); it++)
	{
		vecPeople.push_back(*it);
	}

	updatePerfData();
	return true;
}

bool STLList::MakeRandomPeople(int numPeople)
{
	initPerfData();

	//first clear the vector in case there are people in it already
	people.clear();

	srand(NULL);

	unsigned long long id = 0;

	//If we can't make a person, then return false
	if (maleFirstNames.size() == 0 && femaleFirstNames.size() == 0 && lastNames.size() == 0)
	{
		updatePerfData();
		return false;
	}

	for (int c = 0; c < numPeople; c++)
	{
		//The person
		sPerson person;

		//Decide if male or female
		int mfCheck = rand() % 2; //random number 0 or 1

		//Generate name
		int male = rand() % maleFirstNames.size();
		int female = rand() % femaleFirstNames.size();
		int last = rand() % lastNames.size();

		//Generate age
		int age = rand() % 100 + 1; //1 - 100

		//Generate health (assuming a rating of 0(dead) to 100%(perfectly healthy))
		float health = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); //generates a number from 0 to 1.0
		health *= 100.0f;

		//Generate location
		float xLoc = ((rand() % 201) - 100) * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)); //random number from -100 to 100
		float yLoc = ((rand() % 201) - 100) * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)); //random number from -100 to 100
		float zLoc = ((rand() % 201) - 100) * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)); //random number from -100 to 100

		std::list<std::string>::iterator it;

		//Assign first name
		if (mfCheck) //if male
		{
			if (maleFirstNames.size() > 0)
			{
				it = maleFirstNames.begin();
				std::advance(it, male);
				person.first = (*it);
			}
			else if (femaleFirstNames.size() > 0)
			{
				it = femaleFirstNames.begin();
				std::advance(it, female);
				person.first = (*it);
			}
			updatePerfData();
		}
		else //if female
		{
			if (femaleFirstNames.size() > 0)
			{
				it = femaleFirstNames.begin();
				std::advance(it, female);
				person.first = (*it);
			}
			else if (maleFirstNames.size() > 0)
			{
				it = maleFirstNames.begin();
				std::advance(it, male);
				person.first = (*it);
			}
			updatePerfData();
		}

		//Assign last name
		if (lastNames.size() > 0)
		{
			it = lastNames.begin();
			std::advance(it, last);
			person.last = (*it);
		}
		updatePerfData();

		person.age = age;
		person.health = health;
		person.location.x = xLoc;
		person.location.y = yLoc;
		person.location.z = zLoc;
		person.uniqueID = id;

		id++;

		people.push_back(person);
		updatePerfData();
	}

	updatePerfData();
	return true;
}

bool STLList::GetPerformanceFromLastCall(sPerfData & callStats)
{
	callStats = performanceData;
	//std::cout << "CallStats: " << callStats.elapsedCallTime_ms << ", " << callStats.memoryUsageBytes_avg << std::endl;
	return true;
}
