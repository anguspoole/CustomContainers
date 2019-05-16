#ifndef _MERGE_SORT_HG_
#define _MERGE_SORT_HG_

#include "cList.h"
#include "iPersonMotron.h"

void TopDownMergeSort(cPersonList &listA, cPersonList &listB, int n, iPersonMotron::eSortType sortType);
cPersonList MergeSort(cPersonList &listA, iPersonMotron::eSortType sortType);
cPersonList Merge(cPersonList &listA, cPersonList &listB, iPersonMotron::eSortType sortType);

#endif // !_MERGE_SORT_HG_
