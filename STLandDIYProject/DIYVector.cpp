//The implementation for the DIY Vector

#include "DIYVector.h"
#include <fstream>
#include <iostream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include <algorithm>
#include <Windows.h>
#include <Psapi.h>

cVector diyPeopleVec;
strVector diyMaleFirstNamesVec;
strVector diyFemaleFirstNamesVec;
strVector diyLastNamesVec;

void DIYVector::initPerfData()
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

void DIYVector::updatePerfData()
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

float diyVecCalculateDistance(sPoint location1, sPoint location2)
{
	float xS = std::pow((location2.x - location1.x), 2);
	float yS = std::pow((location2.y - location1.y), 2);
	float zS = std::pow((location2.z - location1.z), 2);
	float distance = std::sqrt(xS + yS + zS);

	return distance;
}


bool DIYVector::LoadDataFilesIntoContainer(std::string firstNameFemaleFileName,
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
		diyFemaleFirstNamesVec.InsertStringAtEnd(name);
		updatePerfData();
	}

	femaleFile.close();

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
		diyMaleFirstNamesVec.InsertStringAtEnd(name);
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
		diyLastNamesVec.InsertStringAtEnd(name);
		updatePerfData();
	}

	lastFile.close();

	updatePerfData();

	return true;

}

bool DIYVector::FindPeopleByName(std::vector<sPerson>& vecPeople, sPerson personToMatch, int maxNumberOfPeople)
{
	initPerfData();

	//clear vector in case it has diyPeopleVec in it already
	vecPeople.clear();

	//If no first or last name, add everybody to vector
	if (personToMatch.first == "" && personToMatch.last == "")
	{
		if (maxNumberOfPeople <= diyPeopleVec.GetSize())
		{
			for (int i = 0; i < maxNumberOfPeople; i++)
			{
				sPerson person;
				diyPeopleVec.GetPersonAtIndex(i, person);
				vecPeople.push_back(person);
				updatePerfData();
			}
		}
		else
		{
			for (int i = 0; i < diyPeopleVec.GetSize(); i++)
			{
				sPerson person;
				diyPeopleVec.GetPersonAtIndex(i, person);
				vecPeople.push_back(person);
				updatePerfData();
			}
		}
	}
	//If no last name, add anybody with matching first name to vector
	else if (personToMatch.first != "" && personToMatch.last == "")
	{
		for (int i = 0; i < diyPeopleVec.GetSize(); i++)
		{
			sPerson person;
			diyPeopleVec.GetPersonAtIndex(i, person);

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
		}
	}
	//If no first name, add anybody with last name to vector
	else if (personToMatch.first == "" && personToMatch.last != "")
	{
		for (int i = 0; i < diyPeopleVec.GetSize(); i++)
		{
			sPerson person;
			diyPeopleVec.GetPersonAtIndex(i, person);
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
		for (int i = 0; i < diyPeopleVec.GetSize(); i++)
		{
			sPerson person;
			diyPeopleVec.GetPersonAtIndex(i, person);
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

bool DIYVector::FindPeopleByName(std::vector<sPerson>& vecPeople, std::vector<sPerson>& vecPeopleToMatch, int maxNumberOfPeople)
{
	initPerfData();

	//clear vector in case it has diyPeopleVec in it already
	vecPeople.clear();

	for (int c = 0; c < vecPeopleToMatch.size(); c++)
	{
		sPerson personToMatch = vecPeopleToMatch[c];

		//If no first or last name, add everybody to vector
		if (personToMatch.first == "" && personToMatch.last == "")
		{
			if (maxNumberOfPeople <= diyPeopleVec.GetSize())
			{
				for (int i = 0; i < maxNumberOfPeople; i++)
				{
					sPerson person;
					diyPeopleVec.GetPersonAtIndex(i, person);
					vecPeople.push_back(person);
					updatePerfData();
				}
			}
			else
			{
				for (int i = 0; i < diyPeopleVec.GetSize(); i++)
				{
					sPerson person;
					diyPeopleVec.GetPersonAtIndex(i, person);
					vecPeople.push_back(person);
					updatePerfData();
				}
			}
		}
		//If no last name, add anybody with matching first name to vector
		else if (personToMatch.first != "" && personToMatch.last == "")
		{
			for (int i = 0; i < diyPeopleVec.GetSize(); i++)
			{
				sPerson person;
				diyPeopleVec.GetPersonAtIndex(i, person);
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
			}
		}
		//If no first name, add anybody with last name to vector
		else if (personToMatch.first == "" && personToMatch.last != "")
		{
			for (int i = 0; i < diyPeopleVec.GetSize(); i++)
			{
				sPerson person;
				diyPeopleVec.GetPersonAtIndex(i, person);
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
			for (int i = 0; i < diyPeopleVec.GetSize(); i++)
			{
				sPerson person;
				diyPeopleVec.GetPersonAtIndex(i, person);
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

bool DIYVector::FindPersonByID(sPerson & person, unsigned long long uniqueID)
{
	initPerfData();

	for (int i = 0; i < diyPeopleVec.GetSize(); i++)
	{
		sPerson personA;
		diyPeopleVec.GetPersonAtIndex(i, personA);
		if (personA.uniqueID == uniqueID)
		{
			person = personA;
			updatePerfData();
			return true;
		}
	}
	updatePerfData();
	return false;
}

bool DIYVector::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, int maxPeopleToReturn)
{
	initPerfData();

	//clear vector in case it has diyPeopleVec in it already
	vecPeople.clear();

	//Loop over all diyPeopleVec
	for (int i = 0; i < diyPeopleVec.GetSize(); i++)
	{
		sPerson person;
		diyPeopleVec.GetPersonAtIndex(i, person);
		if (i < maxPeopleToReturn)
		{
			//Add diyPeopleVec within distance range
			float dist = diyVecCalculateDistance(location, person.location);
			if (dist <= radius)
			{
				vecPeople.push_back(person);
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

bool DIYVector::FindPeople(std::vector<sPerson>& vecPeople, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	initPerfData();

	//clear vector in case it has diyPeopleVec in it already
	vecPeople.clear();

	//Loop over all diyPeopleVec
	for (int i = 0; i < diyPeopleVec.GetSize(); i++)
	{
		sPerson person;
		diyPeopleVec.GetPersonAtIndex(i, person);
		if (i < maxPeopleToReturn)
		{
			//Add diyPeopleVec with health within range
			if (person.health >= minHealth && person.health <= maxHealth)
			{
				vecPeople.push_back(person);
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

bool DIYVector::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	initPerfData();

	//clear vector in case it has diyPeopleVec in it already
	vecPeople.clear();

	//Loop over all diyPeopleVec
	for (int i = 0; i < diyPeopleVec.GetSize(); i++)
	{
		sPerson person;
		diyPeopleVec.GetPersonAtIndex(i, person);
		if (i < maxPeopleToReturn)
		{
			//Add diyPeopleVec with minimum distance
			float dist = diyVecCalculateDistance(location, person.location);
			updatePerfData();
			if (dist <= radius)
			{
				//Add diyPeopleVec within health range
				if (person.health >= minHealth && person.health <= maxHealth)
				{
					vecPeople.push_back(person);
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

eContainerType DIYVector::getContainerType(void)
{
	initPerfData();
	updatePerfData();
	//return eContainerType();
	return CUSTOM_DIY_VECTOR;
}

//Helper function for sorting by lowest health
void diyVecSortLowerHealth()
{
	for (int i = 0; i < diyPeopleVec.GetSize() - 1; i++)
	{
		for (int j = 0; j < diyPeopleVec.GetSize() - i - 1; j++)
		{
			sPerson personA;
			diyPeopleVec.GetPersonAtIndex(j, personA);
			sPerson personB;
			diyPeopleVec.GetPersonAtIndex(j+1, personB);
			if (personA.health > personB.health)
			{
				diyPeopleVec.SwapPeople(j, j + 1);
			}
		}
	}
}

//Helper function for sorting by higher health
void diyVecSortHigherHealth()
{
	for (int i = 0; i < diyPeopleVec.GetSize() - 1; i++)
	{
		for (int j = 0; j < diyPeopleVec.GetSize() - i - 1; j++)
		{
			sPerson personA;
			diyPeopleVec.GetPersonAtIndex(j, personA);
			sPerson personB;
			diyPeopleVec.GetPersonAtIndex(j + 1, personB);
			if (personA.health < personB.health)
			{
				diyPeopleVec.SwapPeople(j, j + 1);
			}
		}
	}
}

//Helper function for sorting by lower id
void diyVecSortLowerID()
{
	for (int i = 0; i < diyPeopleVec.GetSize() - 1; i++)
	{
		for (int j = 0; j < diyPeopleVec.GetSize() - i - 1; j++)
		{
			sPerson personA;
			diyPeopleVec.GetPersonAtIndex(j, personA);
			sPerson personB;
			diyPeopleVec.GetPersonAtIndex(j + 1, personB);
			if (personA.uniqueID > personB.uniqueID)
			{
				diyPeopleVec.SwapPeople(j, j+1);
			}
		}
	}
}

//Helper function for sorting by higher id
void diyVecSortHigherID()
{
	for (int i = 0; i < diyPeopleVec.GetSize() - 1; i++)
	{
		for (int j = 0; j < diyPeopleVec.GetSize() - i - 1; j++) 
		{
			sPerson personA;
			diyPeopleVec.GetPersonAtIndex(j, personA);
			sPerson personB;
			diyPeopleVec.GetPersonAtIndex(j + 1, personB);
			if (personA.uniqueID < personB.uniqueID)
			{
				diyPeopleVec.SwapPeople(j, j + 1);
			}
		}
	}
}

//Helper function for sorting by lower first name, then last name
void diyVecSortLowerFirstThenLast()
{
	for (int i = 0; i < diyPeopleVec.GetSize() - 1; i++)
	{
		for (int j = 0; j < diyPeopleVec.GetSize() - i - 1; j++)
		{
			sPerson personA;
			diyPeopleVec.GetPersonAtIndex(j, personA);
			sPerson personB;
			diyPeopleVec.GetPersonAtIndex(j + 1, personB);

			if (personA.first == personB.first)
			{
				if (personA.last > personB.last)
				{
					diyPeopleVec.SwapPeople(j, j+1);
				}
			}
			else
			{
				if (personA.first > personB.first)
				{
					diyPeopleVec.SwapPeople(j, j+1);
				}
			}
		}
	}
}

//Helper function for sorting by higher first name, then last name
void diyVecSortHigherFirstThenLast()
{
	for (int i = 0; i < diyPeopleVec.GetSize() - 1; i++)
	{
		for (int j = 0; j < diyPeopleVec.GetSize() - i - 1; j++)
		{
			sPerson personA;
			diyPeopleVec.GetPersonAtIndex(j, personA);
			sPerson personB;
			diyPeopleVec.GetPersonAtIndex(j + 1, personB);

			if (personA.first == personB.first)
			{
				if (personA.last < personB.last)
				{
					diyPeopleVec.SwapPeople(j, j+1);
				}
			}
			else
			{
				if (personA.first < personB.first)
				{
					diyPeopleVec.SwapPeople(j, j+1);
				}
			}
		}
	}
}

//Helper function for sorting by lower last name, then first name
void diyVecSortLowerLastThenFirst()
{
	for (int i = 0; i < diyPeopleVec.GetSize() - 1; i++)
	{
		for (int j = 0; j < diyPeopleVec.GetSize() - i - 1; j++)
		{
			sPerson personA;
			diyPeopleVec.GetPersonAtIndex(j, personA);
			sPerson personB;
			diyPeopleVec.GetPersonAtIndex(j + 1, personB);

			if (personA.last == personB.last)
			{
				if (personA.first > personB.first)
				{
					diyPeopleVec.SwapPeople(j, j+1);
				}
			}
			else
			{
				if (personA.last > personB.last)
				{
					diyPeopleVec.SwapPeople(j, j+1);
				}
			}
		}
	}
}

//Helper function for sorting by higher last name, then first name
void diyVecSortHigherLastThenFirst()
{
	for (int i = 0; i < diyPeopleVec.GetSize() - 1; i++)
	{
		for (int j = 0; j < diyPeopleVec.GetSize() - i - 1; j++)
		{
			sPerson personA;
			diyPeopleVec.GetPersonAtIndex(j, personA);
			sPerson personB;
			diyPeopleVec.GetPersonAtIndex(j + 1, personB);

			if (personA.last == personB.last)
			{
				if (personA.first < personB.first)
				{
					diyPeopleVec.SwapPeople(j, j+1);
				}
			}
			else
			{
				if (personA.last < personB.last)
				{
					diyPeopleVec.SwapPeople(j, j+1);
				}
			}
		}
	}
}


bool DIYVector::SortPeople(std::vector<sPerson> &vecPeople, eSortType sortType)
{
	initPerfData();

	switch (sortType)
	{
	case eSortType::ASC_BY_HEALTH:
		diyVecSortLowerHealth();
		updatePerfData();
		break;
	case eSortType::ASC_BY_ID:
		diyVecSortLowerID();
		updatePerfData();
		break;
	case eSortType::ASC_FIRST_THEN_LAST:
		diyVecSortLowerFirstThenLast();
		updatePerfData();
		break;
	case eSortType::ASC_LAST_THEN_FIRST:
		diyVecSortLowerLastThenFirst();
		updatePerfData();
		break;
	case eSortType::DESC_BY_HEALTH:
		diyVecSortHigherHealth();
		updatePerfData();
		break;
	case eSortType::DESC_BY_ID:
		diyVecSortHigherID();
		updatePerfData();
		break;
	case eSortType::DESC_FIRST_THEN_LAST:
		diyVecSortHigherFirstThenLast();
		updatePerfData();
		break;
	case eSortType::DESC_LAST_THEN_FIRST:
		diyVecSortLowerLastThenFirst();
		updatePerfData();
		break;
	default:
		updatePerfData();
		return false;
	}

	vecPeople.clear();
	for (int i = 0; i < diyPeopleVec.GetSize(); i++)
	{
		sPerson person;
		diyPeopleVec.GetPersonAtIndex(i, person);
		vecPeople.push_back(person);
	}

	//vecPeople = diyPeopleVec;
	updatePerfData();
	return true;
}

bool DIYVector::MakeRandomPeople(int numPeople)
{
	initPerfData();

	//first clear the vector in case there are diyPeopleVec in it already
	diyPeopleVec.Clear();

	srand(NULL);

	unsigned long long id = 0;

	//If we can't make a person, then return false
	if (diyMaleFirstNamesVec.GetSize() == 0 && diyFemaleFirstNamesVec.GetSize() == 0 && diyLastNamesVec.GetSize() == 0)
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
		int male = rand() % diyMaleFirstNamesVec.GetSize();
		int female = rand() % diyFemaleFirstNamesVec.GetSize();
		int last = rand() % diyLastNamesVec.GetSize();

		//Generate age
		int age = rand() % 100 + 1; //1 - 100

		//Generate health (assuming a rating of 0(dead) to 100%(perfectly healthy))
		float health = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); //generates a number from 0 to 1.0
		health *= 100.0f;

		//Generate location
		float xLoc = ((rand() % 201) - 100) * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)); //random number from -100 to 100
		float yLoc = ((rand() % 201) - 100) * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)); //random number from -100 to 100
		float zLoc = ((rand() % 201) - 100) * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)); //random number from -100 to 100

		//Assign first name
		if (mfCheck) //if male
		{
			if (diyMaleFirstNamesVec.GetSize() > 0)
			{
				diyMaleFirstNamesVec.GetStringAtIndex(male, person.first);
			}
			else if (diyFemaleFirstNamesVec.GetSize() > 0)
			{
				diyFemaleFirstNamesVec.GetStringAtIndex(female, person.first);
			}
			updatePerfData();
		}
		else //if female
		{
			if (diyFemaleFirstNamesVec.GetSize() > 0)
			{
				diyFemaleFirstNamesVec.GetStringAtIndex(female, person.first);
			}
			else if (diyMaleFirstNamesVec.GetSize() > 0)
			{
				diyMaleFirstNamesVec.GetStringAtIndex(male, person.first);
			}
			updatePerfData();
		}

		//Assign last name
		if (diyLastNamesVec.GetSize() > 0)
		{
			diyLastNamesVec.GetStringAtIndex(last, person.last);
		}
		updatePerfData();

		person.age = age;
		person.health = health;
		person.location.x = xLoc;
		person.location.y = yLoc;
		person.location.z = zLoc;
		person.uniqueID = id;

		id++;

		diyPeopleVec.InsertPersonAtEnd(person);
		updatePerfData();
	}

	updatePerfData();
	return true;
}

bool DIYVector::GetPerformanceFromLastCall(sPerfData & callStats)
{
	callStats = performanceData;
	//std::cout << "CallStats: " << callStats.elapsedCallTime_ms << ", " << callStats.memoryUsageBytes_avg << std::endl;
	return true;
}
