#include "STLVector.h"
#include "STLMap.h"
#include "STLList.h"
#include "DIYVector.h"
#include "DIYMap.h"
#include "DIYList.h"
#include <iostream>

void TestMain()
{

	sPerfData perfData;
	
	STLVector* test = new STLVector();
	//STLMap* test = new STLMap();
	//STLList* test = new STLList();
	//DIYVector* test = new DIYVector();
	//DIYMap* test = new DIYMap();
	//DIYList* test = new DIYList();
	

	test->LoadDataFilesIntoContainer("dist.female.first.txt", "dist.male.first.txt", "US_LastNames.txt");

	test->GetPerformanceFromLastCall(perfData);

	std::cout << "Elapsed: " << perfData.elapsedCallTime_ms << " \nAverage: " << perfData.memoryUsageBytes_avg 
		<< " \nMin: " << perfData.memoryUsageBytes_min << " \nMax: " << perfData.memoryUsageBytes_max << std::endl;

	test->MakeRandomPeople(10);

	std::vector<sPerson> matchingPeople;
	sPerson person;
	person.first = "";
	person.last = "";

	std::cout << "people made" << std::endl;

	test->FindPeopleByName(matchingPeople, person, 10);

	for (int i = 0; i < matchingPeople.size(); i++)
	{
		std::cout << "Found: " << matchingPeople[i].first << " " << matchingPeople[i].last
			<< std::endl;
	}

	test->GetPerformanceFromLastCall(perfData);

	std::cout << "Elapsed: " << perfData.elapsedCallTime_ms << " \nAverage: " << perfData.memoryUsageBytes_avg
		<< " \nMin: " << perfData.memoryUsageBytes_min << " \nMax: " << perfData.memoryUsageBytes_max << std::endl;

	std::cout << "---\n---" << std::endl;

	test->FindPeople(matchingPeople, 30.0f, 60.0f, 10);
	for (int i = 0; i < matchingPeople.size(); i++)
	{
		std::cout << "Found: " << matchingPeople[i].first << " " << matchingPeople[i].health
			<< std::endl;
	}

	test->GetPerformanceFromLastCall(perfData);

	std::cout << "Elapsed: " << perfData.elapsedCallTime_ms << " \nAverage: " << perfData.memoryUsageBytes_avg
		<< " \nMin: " << perfData.memoryUsageBytes_min << " \nMax: " << perfData.memoryUsageBytes_max << std::endl;

	std::cout << "---\n---" << std::endl;

	sPoint pointA;
	pointA.x = 0.0f;
	pointA.y = 0.0f;
	pointA.z = 0.0f;

	test->FindPeople(matchingPeople, pointA, 30.0f, 10);
	for (int i = 0; i < matchingPeople.size(); i++)
	{
		std::cout << "Found: " << matchingPeople[i].first << " " << matchingPeople[i].location.x
			<< " " << matchingPeople[i].location.y << " " << matchingPeople[i].location.z
			<< std::endl;
	}

	test->GetPerformanceFromLastCall(perfData);

	std::cout << "Elapsed: " << perfData.elapsedCallTime_ms << " \nAverage: " << perfData.memoryUsageBytes_avg
		<< " \nMin: " << perfData.memoryUsageBytes_min << " \nMax: " << perfData.memoryUsageBytes_max << std::endl;

	std::cout << "---\n---" << std::endl;

	//test->FindPeopleByName(matchingPeople, person, 50);
	person.first = "";
	person.last = "";
	test->FindPeopleByName(matchingPeople, person, 10);
	//for (int i = 0; i < matchingPeople.size(); i++)
	//{
	//	std::cout << "Found Person1: " << matchingPeople[i].first << " " << matchingPeople[i].last
	//		<< std::endl;
	//}
	std::vector<sPerson> peopleToFind = matchingPeople;
	test->FindPeopleByName(matchingPeople, peopleToFind, 5);

	for (int i = 0; i < matchingPeople.size(); i++)
	{
		std::cout << "Found Person2: " << matchingPeople[i].first << " " << matchingPeople[i].last
			<< std::endl;
	}

	test->GetPerformanceFromLastCall(perfData);

	std::cout << "Elapsed: " << perfData.elapsedCallTime_ms << " \nAverage: " << perfData.memoryUsageBytes_avg
		<< " \nMin: " << perfData.memoryUsageBytes_min << " \nMax: " << perfData.memoryUsageBytes_max << std::endl;

	std::cout << "---\n---" << std::endl;

	test->FindPersonByID(person, 4);
	std::cout << "Found: " << person.first << " " << person.uniqueID
		<< std::endl;

	test->GetPerformanceFromLastCall(perfData);

	std::cout << "Elapsed: " << perfData.elapsedCallTime_ms << " \nAverage: " << perfData.memoryUsageBytes_avg
		<< " \nMin: " << perfData.memoryUsageBytes_min << " \nMax: " << perfData.memoryUsageBytes_max << std::endl;

	std::cout << "---\n---" << std::endl;

	std::cout << "container type: " << test->getContainerType() << std::endl;

	test->GetPerformanceFromLastCall(perfData);

	std::cout << "Elapsed: " << perfData.elapsedCallTime_ms << " \nAverage: " << perfData.memoryUsageBytes_avg
		<< " \nMin: " << perfData.memoryUsageBytes_min << " \nMax: " << perfData.memoryUsageBytes_max << std::endl;

	std::cout << "---\n---" << std::endl;

	test->SortPeople(matchingPeople, test->ASC_FIRST_THEN_LAST);

	for (int i = 0; i < matchingPeople.size(); i++)
	{
		std::cout << "Sorted: " << matchingPeople[i].first << " " << matchingPeople[i].last 
			<< std::endl;
	}

	test->GetPerformanceFromLastCall(perfData);

	std::cout << "Elapsed: " << perfData.elapsedCallTime_ms << " \nAverage: " << perfData.memoryUsageBytes_avg
			<< " \nMin: " << perfData.memoryUsageBytes_min << " \nMax: " << perfData.memoryUsageBytes_max << std::endl;

	//matchingPeople[0].last = "";
	std::cout << "---\n---" << std::endl;

	test->SortPeople(matchingPeople, test->DESC_LAST_THEN_FIRST);

	for (int i = 0; i < matchingPeople.size(); i++)
	{
		std::cout << "Sorted: " << matchingPeople[i].first << " " << matchingPeople[i].last
			<< std::endl;
	}

	test->GetPerformanceFromLastCall(perfData);

	std::cout << "Elapsed: " << perfData.elapsedCallTime_ms << " \nAverage: " << perfData.memoryUsageBytes_avg
		<< " \nMin: " << perfData.memoryUsageBytes_min << " \nMax: " << perfData.memoryUsageBytes_max << std::endl;

	std::cout << "---\n---" << std::endl;

	test->SortPeople(matchingPeople, test->DESC_BY_HEALTH);

	for (int i = 0; i < matchingPeople.size(); i++)
	{
		std::cout << "Sorted: " << matchingPeople[i].first << " " << matchingPeople[i].health
			<< std::endl;
	}

	test->GetPerformanceFromLastCall(perfData);

	std::cout << "Elapsed: " << perfData.elapsedCallTime_ms << " \nAverage: " << perfData.memoryUsageBytes_avg
		<< " \nMin: " << perfData.memoryUsageBytes_min << " \nMax: " << perfData.memoryUsageBytes_max << std::endl;

	std::cout << "---\n---" << std::endl;

	test->SortPeople(matchingPeople, test->ASC_BY_ID);

	for (int i = 0; i < matchingPeople.size(); i++)
	{
		std::cout << "Sorted: " << matchingPeople[i].first << " " << matchingPeople[i].uniqueID
			<< std::endl;
	}

	test->GetPerformanceFromLastCall(perfData);

	std::cout << "Elapsed: " << perfData.elapsedCallTime_ms << " \nAverage: " << perfData.memoryUsageBytes_avg
		<< " \nMin: " << perfData.memoryUsageBytes_min << " \nMax: " << perfData.memoryUsageBytes_max << std::endl;

	std::cout << "---\n---" << std::endl;

	return;
}

int main()
{
	TestMain();
}