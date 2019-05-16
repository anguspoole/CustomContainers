#include "MergeSort.h"

// Array A[] has the items to sort; array B[] is a work array.
void TopDownMergeSort(cPersonList &listA, cPersonList &listB, int n, iPersonMotron::eSortType sortType)
{
	listA = MergeSort(listA, sortType);
}

//Sort using MergeSort
cPersonList MergeSort(cPersonList &listA, iPersonMotron::eSortType sortType)
{
	int size = listA.GetSize();

	//Return single-sized or 0-sized lists as they are
	if (size < 2)
		return listA;

	//halfway point
	int midPoint = (size) / 2;

	//Divide list into two halves
	cPersonList left;
	cPersonList right;
	for (int i = 0; i < size; i++)
	{
		sPerson person;
		listA.Begin();
		listA.TraverseList(i);
		listA.GetPersonAtCurrentIndex(person);
		if (i < midPoint)
		{
			left.InsertPerson(person);
		}
		else
		{
			right.InsertPerson(person);
		}
	}

	// recursively split and sort into two lists
	left = MergeSort(left, sortType);  // sort the left half
	right = MergeSort(right, sortType);  // sort the right half

	//merge the resulting lists
	return Merge(left, right, sortType);
}

// Function for merging two lists based on sortType
cPersonList Merge(cPersonList &listA, cPersonList &listB, iPersonMotron::eSortType sortType)
{

	cPersonList finalList;

	int i = 0;
	int j = 0;

	while (i < listA.GetSize() && j < listB.GetSize())
	{
		sPerson personA1;
		listA.Begin();
		listA.TraverseList(i);
		listA.GetPersonAtCurrentIndex(personA1);
		sPerson personA2;
		listB.Begin();
		listB.TraverseList(j);
		listB.GetPersonAtCurrentIndex(personA2);

		switch (sortType)
		{
		case iPersonMotron::eSortType::ASC_BY_HEALTH:
			if (personA1.health <= personA2.health) {
				finalList.InsertPerson(personA1);
				i = i + 1;
			}
			else {
				finalList.InsertPerson(personA2);
				j = j + 1;
			}
			break;
		case iPersonMotron::eSortType::ASC_BY_ID:
			if (personA1.uniqueID <= personA2.uniqueID) {
				finalList.InsertPerson(personA1);
				i = i + 1;
			}
			else {
				finalList.InsertPerson(personA2);
				j = j + 1;
			}
			break;
		case iPersonMotron::eSortType::ASC_FIRST_THEN_LAST:
			if (personA1.first <= personA2.first)
			{
				if (personA1.first == personA2.first)
				{
					//If a tie for first names, compare last names
					if (personA1.last <= personA2.last)
					{
						finalList.InsertPerson(personA1);
						i = i + 1;
					}
					else
					{
						finalList.InsertPerson(personA2);
						j = j + 1;
					}
				}
				else
				{
					finalList.InsertPerson(personA1);
					i = i + 1;
				}
			}
			else {
				finalList.InsertPerson(personA2);
				j = j + 1;
			}
			break;
		case iPersonMotron::eSortType::ASC_LAST_THEN_FIRST:
			if (personA1.last <= personA2.last)
			{
				if (personA1.last == personA2.last)
				{
					//If a tie for first names, compare last names
					if (personA1.first <= personA2.first)
					{
						finalList.InsertPerson(personA1);
						i = i + 1;
					}
					else
					{
						finalList.InsertPerson(personA2);
						j = j + 1;
					}
				}
				else
				{
					finalList.InsertPerson(personA1);
					i = i + 1;
				}
			}
			else {
				finalList.InsertPerson(personA2);
				j = j + 1;
			}
			break;
		case iPersonMotron::eSortType::DESC_BY_HEALTH:
			if (personA1.health >= personA2.health) {
				finalList.InsertPerson(personA1);
				i = i + 1;
			}
			else {
				finalList.InsertPerson(personA2);
				j = j + 1;
			}
			break;
		case iPersonMotron::eSortType::DESC_BY_ID:
			if (personA1.uniqueID >= personA2.uniqueID) {
				finalList.InsertPerson(personA1);
				i = i + 1;
			}
			else {
				finalList.InsertPerson(personA2);
				j = j + 1;
			}
			break;
		case iPersonMotron::eSortType::DESC_FIRST_THEN_LAST:
			if (personA1.first >= personA2.first)
			{
				if (personA1.first == personA2.first)
				{
					//If a tie for first names, compare last names
					if (personA1.last >= personA2.last)
					{
						finalList.InsertPerson(personA1);
						i = i + 1;
					}
					else
					{
						finalList.InsertPerson(personA2);
						j = j + 1;
					}
				}
				else
				{
					finalList.InsertPerson(personA1);
					i = i + 1;
				}
			}
			else 
			{
				finalList.InsertPerson(personA2);
				j = j + 1;
			}
			break;
		case iPersonMotron::eSortType::DESC_LAST_THEN_FIRST:
			if (personA1.last >= personA2.last)
			{
				if (personA1.last == personA2.last)
				{
					//If a tie for first names, compare last names
					if (personA1.first >= personA2.first)
					{
						finalList.InsertPerson(personA1);
						i = i + 1;
					}
					else
					{
						finalList.InsertPerson(personA2);
						j = j + 1;
					}
				}
				else
				{
					finalList.InsertPerson(personA1);
					i = i + 1;
				}
			}
			else {
				finalList.InsertPerson(personA2);
				j = j + 1;
			}
			break;
		default:
			break;
		}
	}

	//Get any remaining entries and add them to list in current order
	while (i < listA.GetSize())
	{
		sPerson personA1;
		listA.Begin();
		listA.TraverseList(i);
		listA.GetPersonAtCurrentIndex(personA1);
		finalList.InsertPerson(personA1);
		i++;
	}
	while (j < listB.GetSize())
	{
		sPerson personA2;
		listB.Begin();
		listB.TraverseList(j);
		listB.GetPersonAtCurrentIndex(personA2);
		finalList.InsertPerson(personA2);
		j++;
	}

	return finalList;
}