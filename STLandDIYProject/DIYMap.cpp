//The implementation for the DIY Map

#include "DIYMap.h"
#include <fstream>
#include <iostream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include <algorithm>
#include <Windows.h>
#include <Psapi.h>

//sPerfData performanceData;

DIYMap::DIYMap()
{
	diyPeopleMap = new cMap();
	diyMaleFirstNamesMap = new strMap();
	diyFemaleFirstNamesMap = new strMap();
	diyLastNamesMap = new strMap();
}

DIYMap::~DIYMap()
{
}

void DIYMap::initPerfData()
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

void DIYMap::updatePerfData()
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

float DIYMapCalculateDistance(sPoint location1, sPoint location2)
{
	float xS = std::pow((location2.x - location1.x), 2);
	float yS = std::pow((location2.y - location1.y), 2);
	float zS = std::pow((location2.z - location1.z), 2);
	float distance = std::sqrt(xS + yS + zS);

	return distance;
}


bool DIYMap::LoadDataFilesIntoContainer(std::string firstNameFemaleFileName,
	std::string firstNameMaleFileName,
	std::string lastNameFileName)
{
	initPerfData();

	std::string name; //name of person
	float namePercent; 
	float totalPercent;
	unsigned long long id;
	int counter = 0;

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
		diyFemaleFirstNamesMap->InsertStringAtIndex(counter, name);
		updatePerfData();
		counter++;
	}

	femaleFile.close();

	//Reset the counter
	counter = 0;

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
		diyMaleFirstNamesMap->InsertStringAtIndex(counter, name);
		updatePerfData();
		counter++;
	}

	maleFile.close();

	//Reset counter
	counter = 0;

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
		diyLastNamesMap->InsertStringAtIndex(counter, name);
		updatePerfData();
		counter++;
	}

	lastFile.close();

	updatePerfData();

	return true;

}

bool DIYMap::FindPeopleByName(std::vector<sPerson>& vecPeople, sPerson personToMatch, int maxNumberOfPeople)
{
	initPerfData();

	//clear vector in case it has diypeople in it already
	vecPeople.clear();

	//If no first or last name, add everybody to vector
	if (personToMatch.first == "" && personToMatch.last == "")
	{
		if (maxNumberOfPeople <= diyPeopleMap->GetSize())
		{
			for (int i = 0; i < maxNumberOfPeople; i++)
			{
				sPerson foundPerson;
				diyPeopleMap->GetPersonAtIndex(i, foundPerson);
				vecPeople.push_back(foundPerson);
				updatePerfData();
			}
		}
		else
		{
			for (int i = 0; i < diyPeopleMap->GetSize(); i++)
			{
				sPerson foundPerson;
				diyPeopleMap->GetPersonAtIndex(i, foundPerson);
				vecPeople.push_back(foundPerson);
				updatePerfData();
			}
		}
	}
	//If no last name, add anybody with matching first name to vector
	else if (personToMatch.first != "" && personToMatch.last == "")
	{
		for (int i = 0; i < diyPeopleMap->GetSize(); i++)
		{
			sPerson foundPerson;
			diyPeopleMap->GetPersonAtIndex(i, foundPerson);
			if (foundPerson.first == personToMatch.first && vecPeople.size() < maxNumberOfPeople)
			{
				vecPeople.push_back(foundPerson);
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
		for (int i = 0; i < diyPeopleMap->GetSize(); i++)
		{
			sPerson foundPerson;
			diyPeopleMap->GetPersonAtIndex(i, foundPerson);
			if (foundPerson.last == personToMatch.last && vecPeople.size() < maxNumberOfPeople)
			{
				vecPeople.push_back(foundPerson);
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
		for (int i = 0; i < diyPeopleMap->GetSize(); i++)
		{
			sPerson foundPerson;
			diyPeopleMap->GetPersonAtIndex(i, foundPerson);
			if (foundPerson.first == personToMatch.first &&
				foundPerson.last == personToMatch.last &&
				vecPeople.size() < maxNumberOfPeople)
			{
				vecPeople.push_back(foundPerson);
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

bool DIYMap::FindPeopleByName(std::vector<sPerson>& vecPeople, std::vector<sPerson>& vecPeopleToMatch, int maxNumberOfPeople)
{
	initPerfData();

	//clear vector in case it has diypeople in it already
	vecPeople.clear();

	for (int c = 0; c < vecPeopleToMatch.size(); c++)
	{
		if (vecPeople.size() < maxNumberOfPeople)
		{
			sPerson personToMatch = vecPeopleToMatch[c];

			//If no first or last name, add everybody to vector
			if (personToMatch.first == "" && personToMatch.last == "")
			{
				if (maxNumberOfPeople <= diyPeopleMap->GetSize())
				{
					for (int i = 0; i < maxNumberOfPeople; i++)
					{
						sPerson foundPerson;
						diyPeopleMap->GetPersonAtIndex(i, foundPerson);
						vecPeople.push_back(foundPerson);
						updatePerfData();
					}
				}
				else
				{
					for (int i = 0; i < diyPeopleMap->GetSize(); i++)
					{
						sPerson foundPerson;
						diyPeopleMap->GetPersonAtIndex(i, foundPerson);
						vecPeople.push_back(foundPerson);
						updatePerfData();
					}
				}
			}
			//If no last name, add anybody with matching first name to vector
			else if (personToMatch.first != "" && personToMatch.last == "")
			{
				for (int i = 0; i < diyPeopleMap->GetSize(); i++)
				{
					sPerson foundPerson;
					diyPeopleMap->GetPersonAtIndex(i, foundPerson);
					if (foundPerson.first == personToMatch.first && vecPeople.size() < maxNumberOfPeople)
					{
						vecPeople.push_back(foundPerson);
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
				for (int i = 0; i < diyPeopleMap->GetSize(); i++)
				{
					sPerson foundPerson;
					diyPeopleMap->GetPersonAtIndex(i, foundPerson);
					if (foundPerson.last == personToMatch.last && vecPeople.size() < maxNumberOfPeople)
					{
						vecPeople.push_back(foundPerson);
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
				for (int i = 0; i < diyPeopleMap->GetSize(); i++)
				{
					sPerson foundPerson;
					diyPeopleMap->GetPersonAtIndex(i, foundPerson);
					if (foundPerson.first == personToMatch.first &&
						foundPerson.last == personToMatch.last &&
						vecPeople.size() < maxNumberOfPeople)
					{
						vecPeople.push_back(foundPerson);
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

bool DIYMap::FindPersonByID(sPerson & person, unsigned long long uniqueID)
{
	initPerfData();

	for (int i = 0; i < diyPeopleMap->GetSize(); i++)
	{
		sPerson foundPerson;
		diyPeopleMap->GetPersonAtIndex(i, foundPerson);
		if (foundPerson.uniqueID == uniqueID)
		{
			person = foundPerson;
			updatePerfData();
			return true;
		}
	}
	updatePerfData();
	return false;
}

bool DIYMap::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, int maxPeopleToReturn)
{
	initPerfData();

	//clear vector in case it has diypeople in it already
	vecPeople.clear();

	//Loop over all diypeople
	for (int i = 0; i < diyPeopleMap->GetSize(); i++)
	{
		if (i < maxPeopleToReturn)
		{
			sPerson foundPerson;
			diyPeopleMap->GetPersonAtIndex(i, foundPerson);

			//Add diypeople within distance range
			float dist = DIYMapCalculateDistance(location, foundPerson.location);
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

bool DIYMap::FindPeople(std::vector<sPerson>& vecPeople, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	initPerfData();

	//clear vector in case it has diypeople in it already
	vecPeople.clear();

	//Loop over all diypeople
	for (int i = 0; i < diyPeopleMap->GetSize(); i++)
	{
		if (i < maxPeopleToReturn)
		{
			sPerson foundPerson;
			diyPeopleMap->GetPersonAtIndex(i, foundPerson);
			//Add diypeople with health within range
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

bool DIYMap::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	initPerfData();

	//clear vector in case it has diypeople in it already
	vecPeople.clear();

	//Loop over all diypeople
	for (int i = 0; i < diyPeopleMap->GetSize(); i++)
	{
		if (i < maxPeopleToReturn)
		{
			sPerson foundPerson;
			diyPeopleMap->GetPersonAtIndex(i, foundPerson);

			//Add diypeople with minimum distance
			float dist = DIYMapCalculateDistance(location, foundPerson.location);
			updatePerfData();
			if (dist <= radius)
			{
				//Add diypeople within health range
				if (foundPerson.health >= minHealth && foundPerson.health <= maxHealth)
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

eContainerType DIYMap::getContainerType(void)
{
	initPerfData();
	updatePerfData();
	//return eContainerType();
	return CUSTOM_DIY_MAP;
}

//Sort the map in ascending health order
void DIYMap::DIYMapSortAscHealth()
{
	//Create a second map, ordered by name and id
	strPersonMap tempMap;

	//Populate map in correct order (health, and if tied, ID)
	for (int i = 0; i < diyPeopleMap->GetSize(); i++)
	{
		sPerson foundPerson;
		diyPeopleMap->GetPersonAtIndex(i, foundPerson);
		std::string tempID = std::to_string(foundPerson.health) + std::to_string(foundPerson.uniqueID);
		tempMap.InsertPersonAtIndex(tempID, foundPerson);
		//tempMap[tempID] = foundPerson;
	}

	//Empity existing map
	diyPeopleMap->Clear();

	int count = 0;

	//Re-populate existing map
	
	for (int i = 0; i < tempMap.GetSize(); i++)
	{
		sPerson foundPerson;
		tempMap.GetPersonAtIntIndex(i, foundPerson);
		diyPeopleMap->InsertPersonAtIndex(count, foundPerson);
		count++;
	}
}

//Sort the map in descending health order
void DIYMap::DIYMapSortDescHealth()
{
	//Create a second map, ordered by name and id
	strPersonMap tempMap;

	//Populate map in correct order (health, and if tied, ID)
	for (int i = 0; i < diyPeopleMap->GetSize(); i++)
	{
		sPerson foundPerson;
		diyPeopleMap->GetPersonAtIndex(i, foundPerson);
		std::string tempID = std::to_string(foundPerson.health) + std::to_string(foundPerson.uniqueID);
		tempMap.InsertPersonAtIndex(tempID, foundPerson);
		//tempMap[tempID] = foundPerson;
	}

	//Empity existing map
	diyPeopleMap->Clear();

	int count = 0;

	//Re-populate existing map
	for (int i = tempMap.GetSize() - 1; i >= 0; i--)
	{
		sPerson foundPerson;
		tempMap.GetPersonAtIntIndex(i, foundPerson);
		diyPeopleMap->InsertPersonAtIndex(count, foundPerson);
		count++;
	}
}

//Helper function for checking for lower id
void DIYMap::DIYMapSortAscID()
{
	//Create a second map, ordered by name and id
	strPersonMap tempMap;

	//Populate map in correct order (health, and if tied, ID)
	for (int i = 0; i < diyPeopleMap->GetSize(); i++)
	{
		sPerson foundPerson;
		diyPeopleMap->GetPersonAtIndex(i, foundPerson);
		tempMap.InsertPersonAtIndex(std::to_string(foundPerson.uniqueID), foundPerson);
	}

	//Empity existing map
	diyPeopleMap->Clear();

	int count = 0;

	//Re-populate existing map
	for (int i = 0; i < tempMap.GetSize(); i++)
	{
		sPerson foundPerson;
		tempMap.GetPersonAtIntIndex(i, foundPerson);
		diyPeopleMap->InsertPersonAtIndex(count, foundPerson);
		count++;
	}
}

//Helper function for checking for higher id
void DIYMap::DIYMapSortDescID()
{
	//Create a second map, ordered by name and id
	strPersonMap tempMap;

	//Populate map in correct order (health, and if tied, ID)
	for (int i = 0; i < diyPeopleMap->GetSize(); i++)
	{
		sPerson foundPerson;
		diyPeopleMap->GetPersonAtIndex(i, foundPerson);
		tempMap.InsertPersonAtIndex(std::to_string(foundPerson.uniqueID), foundPerson);
	}

	//Empity existing map
	diyPeopleMap->Clear();

	int count = 0;

	//Re-populate existing map
	for (int i = tempMap.GetSize() - 1; i >= 0; i--)
	{
		sPerson foundPerson;
		tempMap.GetPersonAtIntIndex(i, foundPerson);
		diyPeopleMap->InsertPersonAtIndex(count, foundPerson);
		count++;
	}
}

//Helper function for checking for lower first name, then last name
void DIYMap::DIYMapSortAscFirstThenLast()
{
	//Create a second map, ordered by name and id
	strPersonMap tempMap;

	//Populate map in correct order
	for (int i = 0; i < diyPeopleMap->GetSize(); i++)
	{
		sPerson foundPerson;
		diyPeopleMap->GetPersonAtIndex(i, foundPerson);
		std::string tempID = foundPerson.first + foundPerson.last + std::to_string(foundPerson.uniqueID);
		tempMap.InsertPersonAtIndex(tempID, foundPerson);
	}

	//Empity existing map
	diyPeopleMap->Clear();

	int count = 0;

	//Re-populate existing map
	for (int i = 0; i < tempMap.GetSize(); i++)
	{
		sPerson foundPerson;
		tempMap.GetPersonAtIntIndex(i, foundPerson);
		diyPeopleMap->InsertPersonAtIndex(count, foundPerson);
		count++;
	}
}

//Helper function for checking for higher first name, then last name
void DIYMap::DIYMapSortDescFirstThenLast()
{
	//Create a second map, ordered by name and id
	strPersonMap tempMap;

	//Populate map in correct order
	for (int i = 0; i < diyPeopleMap->GetSize(); i++)
	{
		sPerson foundPerson;
		diyPeopleMap->GetPersonAtIndex(i, foundPerson);
		std::string tempID = foundPerson.first + foundPerson.last + std::to_string(foundPerson.uniqueID);
		tempMap.InsertPersonAtIndex(tempID, foundPerson);
	}

	//Empity existing map
	diyPeopleMap->Clear();

	int count = 0;

	//Re-populate existing map
	for (int i = tempMap.GetSize() - 1; i >= 0; i--)
	{
		sPerson foundPerson;
		tempMap.GetPersonAtIntIndex(i, foundPerson);
		diyPeopleMap->InsertPersonAtIndex(count, foundPerson);
		count++;
	}
}

//Helper function for checking for lower last name, then first name
void DIYMap::DIYMapSortAscLastThenFirst()
{
	//Create a second map, ordered by name and id
	strPersonMap tempMap;

	//Populate map in correct order
	for (int i = 0; i < diyPeopleMap->GetSize(); i++)
	{
		sPerson foundPerson;
		diyPeopleMap->GetPersonAtIndex(i, foundPerson);
		std::string tempID = foundPerson.last + foundPerson.first + std::to_string(foundPerson.uniqueID);
		tempMap.InsertPersonAtIndex(tempID, foundPerson);
	}

	//Empity existing map
	diyPeopleMap->Clear();

	int count = 0;

	//Re-populate existing map
	for (int i = 0; i < tempMap.GetSize(); i++)
	{
		sPerson foundPerson;
		tempMap.GetPersonAtIntIndex(i, foundPerson);
		diyPeopleMap->InsertPersonAtIndex(count, foundPerson);
		count++;
	}
}

//Helper function for checking for higher last name, then first name
void DIYMap::DIYMapSortDescLastThenFirst()
{
	//Create a second map, ordered by name and id
	strPersonMap tempMap;

	//Populate map in correct order
	for (int i = 0; i < diyPeopleMap->GetSize(); i++)
	{
		sPerson foundPerson;
		diyPeopleMap->GetPersonAtIndex(i, foundPerson);
		std::string tempID = foundPerson.last + foundPerson.first + std::to_string(foundPerson.uniqueID);
		tempMap.InsertPersonAtIndex(tempID, foundPerson);
	}

	//Empity existing map
	diyPeopleMap->Clear();

	int count = 0;

	//Re-populate existing map
	for (int i = tempMap.GetSize() - 1; i >= 0; i--)
	{
		sPerson foundPerson;
		tempMap.GetPersonAtIntIndex(i, foundPerson);
		diyPeopleMap->InsertPersonAtIndex(count, foundPerson);
		count++;
	}
}


bool DIYMap::SortPeople(std::vector<sPerson> &vecPeople, eSortType sortType)
{
	initPerfData();

	switch (sortType)
	{
	case eSortType::ASC_BY_HEALTH:
		DIYMapSortAscHealth();
		updatePerfData();
		break;
	case eSortType::ASC_BY_ID:
		DIYMapSortAscID();
		updatePerfData();
		break;
	case eSortType::ASC_FIRST_THEN_LAST:
		DIYMapSortAscFirstThenLast();
		updatePerfData();
		break;
	case eSortType::ASC_LAST_THEN_FIRST:
		DIYMapSortAscLastThenFirst();
		updatePerfData();
		break;
	case eSortType::DESC_BY_HEALTH:
		DIYMapSortDescHealth();
		updatePerfData();
		break;
	case eSortType::DESC_BY_ID:
		DIYMapSortDescID();
		updatePerfData();
		break;
	case eSortType::DESC_FIRST_THEN_LAST:
		DIYMapSortDescFirstThenLast();
		updatePerfData();
		break;
	case eSortType::DESC_LAST_THEN_FIRST:
		DIYMapSortDescLastThenFirst();
		updatePerfData();
		break;
	default:
		updatePerfData();
		return false;
	}

	//reset vector
	vecPeople.clear();

	for (int i = 0; i < diyPeopleMap->GetSize(); i++)
	{
		sPerson foundPerson;
		diyPeopleMap->GetPersonAtIndex(i, foundPerson);
		vecPeople.push_back(foundPerson);
	}

	updatePerfData();
	return true;
}

bool DIYMap::MakeRandomPeople(int numPeople)
{
	initPerfData();

	//first clear the vector in case there are diypeople in it already
	diyPeopleMap->Clear();

	srand(NULL);

	unsigned long long id = 0;

	//If we can't make a person, then return false
	if (diyMaleFirstNamesMap->GetSize() == 0 && diyFemaleFirstNamesMap->GetSize() == 0 && diyLastNamesMap->GetSize() == 0)
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
		int male = rand() % diyMaleFirstNamesMap->GetSize();
		int female = rand() % diyFemaleFirstNamesMap->GetSize();
		int last = rand() % diyLastNamesMap->GetSize();

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
			if (diyMaleFirstNamesMap->GetSize() > 0)
			{
				diyMaleFirstNamesMap->GetStringAtIndex(male, name);
				person.first = name;
			}
			else if (diyFemaleFirstNamesMap->GetSize() > 0)
			{
				diyFemaleFirstNamesMap->GetStringAtIndex(female, name);
				person.first = name;
			}
			updatePerfData();
		}
		else //if female
		{
			if (diyFemaleFirstNamesMap->GetSize() > 0)
			{
				diyFemaleFirstNamesMap->GetStringAtIndex(female, name);
				person.first = name;
			}
			else if (diyMaleFirstNamesMap->GetSize() > 0)
			{
				diyMaleFirstNamesMap->GetStringAtIndex(male, name);
				person.first = name;
			}
			updatePerfData();
		}

		//Assign last name
		if (diyLastNamesMap->GetSize() > 0)
		{
			diyLastNamesMap->GetStringAtIndex(last, name);
			person.last = name;
		}
		updatePerfData();

		person.age = age;
		person.health = health;
		person.location.x = xLoc;
		person.location.y = yLoc;
		person.location.z = zLoc;
		person.uniqueID = id;

		diyPeopleMap->InsertPersonAtIndex(id, person);

		id++;

		updatePerfData();
	}

	updatePerfData();
	return true;
}

bool DIYMap::GetPerformanceFromLastCall(sPerfData & callStats)
{
	callStats = performanceData;
	//std::cout << "CallStats: " << callStats.elapsedCallTime_ms << ", " << callStats.memoryUsageBytes_avg << std::endl;
	return true;
}
