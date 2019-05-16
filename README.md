# CustomContainers
This project contains custom vector/map/list classes alongside stl versions of those classes

## AUTHOR
This project was made by Angus Poole

## COMPILING/RUNNING THE PROGRAM
I believe it should compile/run in all configurations.

## MAINTEST FILE
The file mainTest.cpp contains code I used to test out the various container classes and their functions.
It has a main() function that can be commented out under the assumption you'll be using your own when you test the code yourself.

## THE CLASSES TO TEST
The container classes to test are STLVector, STLMap, STLList, DIYVector, DIYMap, and DIYList. Each of these containers inherits from iPersonMotron.

Simply creating an object of that class type will allow you to call the appropriate functions.
Example: 
	STLVector* test = new STLVector();
	test->LoadDataFilesIntoContainer("female.txt", "male.txt", "last.txt");

## DIY IMPLEMENTATION DETAILS
* The DIYVector uses the cVector class to create a dynamic array, that expands as we add elements to it.
* The DIYMap uses an AVLTree, the code being based on here: https://en.wikipedia.org/wiki/AVL_tree and here: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
* The DIYList uses a doubly Linked List, where each node is linked to the next node and the previous node. It also uses the MergeSort algorithm for sorting, found here: https://en.wikipedia.org/wiki/Merge_sort