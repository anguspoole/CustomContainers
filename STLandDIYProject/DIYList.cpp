//The implementation for the DIY List

#include "DIYList.h"
#include "cList.h"
#include <fstream>
#include <iostream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include <algorithm>
#include <Windows.h>
#include <Psapi.h>
#include "MergeSort.h"

cPersonList diyPeopleList;
cStringList diyMaleFirstNamesList;
cStringList diyFemaleFirstNamesList;
cStringList diyLastNamesList;

void DIYList::initPerfData()
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

void DIYList::updatePerfData()
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

float DIYListCalculateDistance(sPoint location1, sPoint location2)
{
	float xS = std::pow((location2.x - location1.x), 2);
	float yS = std::pow((location2.y - location1.y), 2);
	float zS = std::pow((location2.z - location1.z), 2);
	float distance = std::sqrt(xS + yS + zS);

	return distance;
}


bool DIYList::LoadDataFilesIntoContainer(std::string firstNameFemaleFileName,
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
		diyFemaleFirstNamesList.InsertName(name);
		//diyFemaleFirstNamesList.push_back(name);

		//create a person
		//sPerson person;
		//person.first = name;
		//person.uniqueID = id;
		//diyPeopleList.push_back(person);
		updatePerfData();
	}

	femaleFile.close();

	//for (int c = 0; c < diyPeopleList.size(); c++)
	//{
	//	std::cout << "Name: " << diyPeopleList[c].first << std::endl;
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
		diyMaleFirstNamesList.InsertName(name);
		//diyMaleFirstNamesList.push_back(name);

		//create a person
		//sPerson person;
		//person.first = name;
		//person.uniqueID = id;
		//diyPeopleList.push_back(person);
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
		diyLastNamesList.InsertName(name);
		//diyLastNamesList.push_back(name);

		//create a person
		//sPerson person;
		//person.first = name;
		//person.uniqueID = id;
		//diyPeopleList.push_back(person);
		updatePerfData();
	}

	lastFile.close();

	updatePerfData();

	return true;

}

bool DIYList::FindPeopleByName(std::vector<sPerson>& vecPeople, sPerson personToMatch, int maxNumberOfPeople)
{
	initPerfData();

	//clear vector in case it has diyPeopleList in it already
	vecPeople.clear();

	diyPeopleList.Begin();

	//If no first or last name, add everybody to vector
	if (personToMatch.first == "" && personToMatch.last == "")
	{
		if (maxNumberOfPeople <= diyPeopleList.GetSize())
		{
			for (int i = 0; i < maxNumberOfPeople; i++)
			{
				diyPeopleList.Begin();
				diyPeopleList.TraverseList(i);
				sPerson person;
				diyPeopleList.GetPersonAtCurrentIndex(person);
				vecPeople.push_back(person);
				updatePerfData();
			}
		}
		else
		{
			for (int i = 0; i < diyPeopleList.GetSize(); i++)
			{
				diyPeopleList.Begin();
				diyPeopleList.TraverseList(i);
				sPerson person;
				diyPeopleList.GetPersonAtCurrentIndex(person);
				vecPeople.push_back(person);
				//diyPeopleList.TraverseList(1);
				updatePerfData();
			}
		}
	}
	//If no last name, add anybody with matching first name to vector
	else if (personToMatch.first != "" && personToMatch.last == "")
	{
		for (int i = 0; i < diyPeopleList.GetSize(); i++)
		{
			diyPeopleList.Begin();
			diyPeopleList.TraverseList(i);
			sPerson person;
			diyPeopleList.GetPersonAtCurrentIndex(person);
			if (person.first == personToMatch.first && vecPeople.size() < maxNumberOfPeople)
			{
				vecPeople.push_back(person);
				updatePerfData();
			}
			if (vecPeople.size() >= maxNumberOfPeople)
			{
				updatePerfData();
				break;
			}
			//diyPeopleList.TraverseList(1);
		}
	}
	//If no first name, add anybody with last name to vector
	else if (personToMatch.first == "" && personToMatch.last != "")
	{
		for (int i = 0; i < diyPeopleList.GetSize(); i++)
		{
			diyPeopleList.Begin();
			diyPeopleList.TraverseList(i);
			sPerson person;
			diyPeopleList.GetPersonAtCurrentIndex(person);
			if (person.last == personToMatch.last && vecPeople.size() < maxNumberOfPeople)
			{
				vecPeople.push_back(person);
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
		for (int i = 0; i < diyPeopleList.GetSize(); i++)
		{
			diyPeopleList.Begin();
			diyPeopleList.TraverseList(i);
			sPerson person;
			diyPeopleList.GetPersonAtCurrentIndex(person);
			if (person.first == personToMatch.first &&
				person.last == personToMatch.last &&
				vecPeople.size() < maxNumberOfPeople)
			{
				vecPeople.push_back(person);
				updatePerfData();
			}
			if (vecPeople.size() >= maxNumberOfPeople)
			{
				updatePerfData();
				break;
			}
			//diyPeopleList.TraverseList(1);
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

bool DIYList::FindPeopleByName(std::vector<sPerson>& vecPeople, std::vector<sPerson>& vecPeopleToMatch, int maxNumberOfPeople)
{
	initPerfData();

	//clear vector in case it has diyPeopleList in it already
	vecPeople.clear();

	int remainingMax = maxNumberOfPeople;

	for (int c = 0; c < vecPeopleToMatch.size(); c++)
	{
		if (remainingMax == 0)
		{
			break;
		}

		sPerson personToMatch = vecPeopleToMatch[c];

		//****************************************

		diyPeopleList.Begin();

		//If no first or last name, add everybody to vector
		if (personToMatch.first == "" && personToMatch.last == "")
		{
			if (maxNumberOfPeople <= diyPeopleList.GetSize())
			{
				for (int i = 0; i < maxNumberOfPeople; i++)
				{
					diyPeopleList.Begin();
					diyPeopleList.TraverseList(i);
					sPerson person;
					diyPeopleList.GetPersonAtCurrentIndex(person);
					vecPeople.push_back(person);
					updatePerfData();
				}
			}
			else
			{
				for (int i = 0; i < diyPeopleList.GetSize(); i++)
				{
					diyPeopleList.Begin();
					diyPeopleList.TraverseList(i);
					sPerson person;
					diyPeopleList.GetPersonAtCurrentIndex(person);
					vecPeople.push_back(person);
					//diyPeopleList.TraverseList(1);
					updatePerfData();
				}
			}
		}
		//If no last name, add anybody with matching first name to vector
		else if (personToMatch.first != "" && personToMatch.last == "")
		{
			for (int i = 0; i < diyPeopleList.GetSize(); i++)
			{
				diyPeopleList.Begin();
				diyPeopleList.TraverseList(i);
				sPerson person;
				diyPeopleList.GetPersonAtCurrentIndex(person);
				if (person.first == personToMatch.first && vecPeople.size() < maxNumberOfPeople)
				{
					vecPeople.push_back(person);
					updatePerfData();
				}
				if (vecPeople.size() >= maxNumberOfPeople)
				{
					updatePerfData();
					break;
				}
				//diyPeopleList.TraverseList(1);
			}
		}
		//If no first name, add anybody with last name to vector
		else if (personToMatch.first == "" && personToMatch.last != "")
		{
			for (int i = 0; i < diyPeopleList.GetSize(); i++)
			{
				diyPeopleList.Begin();
				diyPeopleList.TraverseList(i);
				sPerson person;
				diyPeopleList.GetPersonAtCurrentIndex(person);
				if (person.last == personToMatch.last && vecPeople.size() < maxNumberOfPeople)
				{
					vecPeople.push_back(person);
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
			for (int i = 0; i < diyPeopleList.GetSize(); i++)
			{
				diyPeopleList.Begin();
				diyPeopleList.TraverseList(i);
				sPerson person;
				diyPeopleList.GetPersonAtCurrentIndex(person);
				if (person.first == personToMatch.first &&
					person.last == personToMatch.last &&
					vecPeople.size() < maxNumberOfPeople)
				{
					vecPeople.push_back(person);
					updatePerfData();
				}
				if (vecPeople.size() >= maxNumberOfPeople)
				{
					updatePerfData();
					break;
				}
				//diyPeopleList.TraverseList(1);
			}
		}
		//****************************************
		updatePerfData();
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

bool DIYList::FindPersonByID(sPerson & person, unsigned long long uniqueID)
{
	initPerfData();

	//diyPeopleList.Begin();
	for (int i = 0; i < diyPeopleList.GetSize(); i++)
	{
		diyPeopleList.Begin();
		diyPeopleList.TraverseList(i);
		sPerson foundPerson;
		diyPeopleList.GetPersonAtCurrentIndex(foundPerson);

		if (foundPerson.uniqueID == uniqueID)
		{
			person = foundPerson;
			updatePerfData();
			return true;
		}
		//diyPeopleList.TraverseList(1);
	}
	updatePerfData();
	return false;
}

bool DIYList::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, int maxPeopleToReturn)
{
	initPerfData();

	//clear vector in case it has diyPeopleList in it already
	vecPeople.clear();

	int count = 0;

	//Loop over all diyPeopleList
	//diyPeopleList.Begin();
	for (int i = 0; i < diyPeopleList.GetSize(); i++)
	{
		diyPeopleList.Begin();
		diyPeopleList.TraverseList(i);
		sPerson foundPerson;
		diyPeopleList.GetPersonAtCurrentIndex(foundPerson);
		if (count < maxPeopleToReturn)
		{
			//Add diyPeopleList within distance range
			float dist = DIYListCalculateDistance(location, foundPerson.location);
			if (dist <= radius)
			{
				vecPeople.push_back(foundPerson);
				updatePerfData();
			}
		}
		else
		{
			updatePerfData();
			break;
		}
		count++;
		//diyPeopleList.TraverseList(1);
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

bool DIYList::FindPeople(std::vector<sPerson>& vecPeople, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	initPerfData();

	//clear vector in case it has diyPeopleList in it already
	vecPeople.clear();

	int count = 0;

	//Loop over all diyPeopleList
	//diyPeopleList.Begin();
	for (int i = 0; i < diyPeopleList.GetSize(); i++)
	{
		diyPeopleList.Begin();
		diyPeopleList.TraverseList(i);
		sPerson foundPerson;
		diyPeopleList.GetPersonAtCurrentIndex(foundPerson);

		if (count < maxPeopleToReturn)
		{
			//Add diyPeopleList with health within range
			if (foundPerson.health >= minHealth && foundPerson.health <= maxHealth)
			{
				vecPeople.push_back(foundPerson);
				updatePerfData();
			}
		}
		else
		{
			updatePerfData();
			break;
		}
		count++;
		//diyPeopleList.TraverseList(1);
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

bool DIYList::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	initPerfData();

	//clear vector in case it has diyPeopleList in it already
	vecPeople.clear();

	int count = 0;

	//Loop over all diyPeopleList
	//diyPeopleList.Begin();
	for (int i = 0; i < diyPeopleList.GetSize(); i++)
	{
		diyPeopleList.Begin();
		diyPeopleList.TraverseList(i);
		sPerson foundPerson;
		diyPeopleList.GetPersonAtCurrentIndex(foundPerson);

		if (count < maxPeopleToReturn)
		{
			//Add diyPeopleList with minimum distance
			float dist = DIYListCalculateDistance(location, (foundPerson).location);
			updatePerfData();
			if (dist <= radius)
			{
				//Add diyPeopleList within health range
				if ((foundPerson).health >= minHealth && (foundPerson).health <= maxHealth)
				{
					vecPeople.push_back(foundPerson);
					updatePerfData();
				}
			}
		}
		else
		{
			updatePerfData();
			break;
		}
		//diyPeopleList.TraverseList(1);
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

eContainerType DIYList::getContainerType(void)
{
	initPerfData();
	updatePerfData();
	//return eContainerType();
	return CUSTOM_DIY_LIST;
}

//Helper function for checking for lower health
bool DIYListCheckLowerHealth (sPerson a, sPerson b)
{
	return a.health < b.health;
}

//Helper function for checking for higher health
bool DIYListCheckHigherHealth(sPerson a, sPerson b)
{
	return a.health > b.health;
}

//Helper function for checking for lower id
bool DIYListCheckLowerID(sPerson a, sPerson b)
{
	return a.uniqueID < b.uniqueID;
}

//Helper function for checking for higher id
bool DIYListCheckHigherID(sPerson a, sPerson b)
{
	return a.uniqueID > b.uniqueID;
}

//Helper function for checking for lower first name, then last name
bool DIYListCheckLowerFirstThenLast(sPerson a, sPerson b)
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
bool DIYListCheckHigherFirstThenLast(sPerson a, sPerson b)
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
bool DIYListCheckLowerLastThenFirst(sPerson a, sPerson b)
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
bool DIYListCheckHigherLastThenFirst(sPerson a, sPerson b)
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


bool DIYList::SortPeople(std::vector<sPerson> &vecPeople, eSortType sortType)
{
	initPerfData();

	cPersonList emptyList;

	TopDownMergeSort(diyPeopleList, emptyList, diyPeopleList.GetSize(), sortType);

	//switch (sortType)
	//{
	//case eSortType::ASC_BY_HEALTH:
	//	diyPeopleList.sort(DIYListCheckLowerHealth);
	//	updatePerfData();
	//	break;
	//case eSortType::ASC_BY_ID:
	//	diyPeopleList.sort(DIYListCheckLowerID);
	//	updatePerfData();
	//	break;
	//case eSortType::ASC_FIRST_THEN_LAST:
	//	diyPeopleList.sort(DIYListCheckLowerFirstThenLast);
	//	updatePerfData();
	//	break;
	//case eSortType::ASC_LAST_THEN_FIRST:
	//	diyPeopleList.sort(DIYListCheckLowerLastThenFirst);
	//	updatePerfData();
	//	break;
	//case eSortType::DESC_BY_HEALTH:
	//	diyPeopleList.sort(DIYListCheckHigherHealth);
	//	updatePerfData();
	//	break;
	//case eSortType::DESC_BY_ID:
	//	diyPeopleList.sort(DIYListCheckHigherID);
	//	updatePerfData();
	//	break;
	//case eSortType::DESC_FIRST_THEN_LAST:
	//	diyPeopleList.sort(DIYListCheckHigherFirstThenLast);
	//	updatePerfData();
	//	break;
	//case eSortType::DESC_LAST_THEN_FIRST:
	//	diyPeopleList.sort(DIYListCheckHigherLastThenFirst);
	//	updatePerfData();
	//	break;
	//default:
	//	updatePerfData();
	//	return false;
	//}

	vecPeople.clear();

	for (int i = 0; i < diyPeopleList.GetSize(); i++)
	{
		diyPeopleList.Begin();
		diyPeopleList.TraverseList(i);
		sPerson foundPerson;
		diyPeopleList.GetPersonAtCurrentIndex(foundPerson);
		vecPeople.push_back(foundPerson);
	}

	emptyList.Clear();

	updatePerfData();
	return true;
}

bool DIYList::MakeRandomPeople(int numPeople)
{
	initPerfData();

	//first clear the vector in case there are diyPeopleList in it already
	diyPeopleList.Clear();

	srand(NULL);

	unsigned long long id = 0;

	//If we can't make a person, then return false
	if (diyMaleFirstNamesList.GetSize() == 0 && diyFemaleFirstNamesList.GetSize() == 0 && diyLastNamesList.GetSize() == 0)
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
		int male = rand() % diyMaleFirstNamesList.GetSize();
		int female = rand() % diyFemaleFirstNamesList.GetSize();
		int last = rand() % diyLastNamesList.GetSize();

		//Generate age
		int age = rand() % 100 + 1; //1 - 100

		//Generate health (assuming a rating of 0(dead) to 100%(perfectly healthy))
		float health = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); //generates a number from 0 to 1.0
		health *= 100.0f;

		//Generate location
		float xLoc = ((rand() % 201) - 100) * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)); //random number from -100 to 100
		float yLoc = ((rand() % 201) - 100) * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)); //random number from -100 to 100
		float zLoc = ((rand() % 201) - 100) * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)); //random number from -100 to 100

		std::string name;

		//Assign first name
		if (mfCheck) //if male
		{
			if (diyMaleFirstNamesList.GetSize() > 0)
			{
				diyMaleFirstNamesList.Begin();
				diyMaleFirstNamesList.TraverseList(male);
				diyMaleFirstNamesList.GetNameAtCurrentIndex(name);
				person.first = name;
			}
			else if (diyFemaleFirstNamesList.GetSize() > 0)
			{
				diyFemaleFirstNamesList.Begin();
				diyFemaleFirstNamesList.TraverseList(female);
				diyFemaleFirstNamesList.GetNameAtCurrentIndex(name);
				person.first = name;
			}
			updatePerfData();
		}
		else //if female
		{
			if (diyFemaleFirstNamesList.GetSize() > 0)
			{
				diyFemaleFirstNamesList.Begin();
				diyFemaleFirstNamesList.TraverseList(female);
				diyFemaleFirstNamesList.GetNameAtCurrentIndex(name);
				person.first = name;
			}
			else if (diyMaleFirstNamesList.GetSize() > 0)
			{
				diyMaleFirstNamesList.Begin();
				diyMaleFirstNamesList.TraverseList(male);
				diyMaleFirstNamesList.GetNameAtCurrentIndex(name);
				person.first = name;
			}
			updatePerfData();
		}

		//Assign last name
		if (diyLastNamesList.GetSize() > 0)
		{
			diyLastNamesList.Begin();
			diyLastNamesList.TraverseList(last);
			diyLastNamesList.GetNameAtCurrentIndex(name);
			person.last = name;
		}
		updatePerfData();

		person.age = age;
		person.health = health;
		person.location.x = xLoc;
		person.location.y = yLoc;
		person.location.z = zLoc;
		person.uniqueID = id;

		id++;

		diyPeopleList.InsertPerson(person);
		updatePerfData();
	}

	updatePerfData();
	return true;
}

bool DIYList::GetPerformanceFromLastCall(sPerfData & callStats)
{
	callStats = performanceData;
	//std::cout << "CallStats: " << callStats.elapsedCallTime_ms << ", " << callStats.memoryUsageBytes_avg << std::endl;
	return true;
}
