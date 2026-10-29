/******************************************************************************

File        : List.h

Date        : Wednesday 21st October 2026

Author      : Gavin Cawley

Description : Implementation of a basic singly-linked list of pointers to
              Exoplanet structures.

History     : 14/10/2026 - v1.00 Initial prototype
              21/10/2026 - v1.10 Updated documention comments

******************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <stdio.h>

#include "Exoplanet.h"

typedef struct LinkStruct Link;

typedef struct LinkStruct* Iterator;

typedef struct ListStruct List;

/******************************************************************************

Function    : list_new

Parameters  : void

Returns     : List * - pointer to dynamically allocated List structure.

Description : Dynamically allocate the memory on the heap for a List structure
              and initialise it as an empty list.  Note that as the structure
              is allocated on the heap, call list_free to de-allocate the
              memory once it is no longer required.

******************************************************************************/

List* list_new();

/******************************************************************************

Function    : list_add

Parameters  : List*      - pointer to List structure
              Exoplanet* - pointer to Exoplanet structure to be added

Returns     : void

Description : Add an Exoplanet to the start of a List.

******************************************************************************/

void list_add(List *list, Exoplanet *planet);

/******************************************************************************

Function    : list_free

Parameters  : List* - pointer to a List structure that is no longer needed

Returns     : void

Description : De-allocate all memory allocated to a List.  Note this does not
              de-allocate the memory allocated to the Exoplanet structures
              contained in the List.

******************************************************************************/

void list_free(List *list);

/******************************************************************************

Function    : list_print

Parameters  : List* - pointer to a List structure
              FILE* - desriptor of output stream

Returns     : void

Description : Display the contents of a linked list of Exoplanet objects on
              the specified output stream (e.g. stdout).  Note this uses the
              exoplanet_toString interface function of the Exoplanet ADT.

******************************************************************************/

void list_print(const List *list, FILE *fd);

/******************************************************************************

Function    : list_load

Parameters  : FILE* - file descriptor

Returns     : List* - pointer to List of Exoplanets

Description : Load a List of Exoplanet structures from an input stream
              specified by a file descriptor.  The format of the file is
              demonstrated by the supplied exoplanets.txt file.

******************************************************************************/

List *list_load(FILE *fd);

/******************************************************************************

Function    : list_sort

Parameters  : List*      - pointer to a List structure to be sorted
              Comparetor - pointer to a fuction defining the sort order

Returns     : void

Description : Basic implementation of bubble sort - not very efficient for
              large colections, but fine for prototyping with small datasets.
              The compare function returns positive integer if a pair of
              adjacent elements should be swapped and zero or a negative
              integer otherwise.

******************************************************************************/

// defining the type of function pointer used to compare Exoplanets

typedef int (*Comparator)(const Exoplanet *a, const Exoplanet *b);

void list_sort(List *list, Comparator compare);

/******************************************************************************

Function    : list_begin

Parameters  : List* - pointer to List structure

Returns     : Iterator - representing the start of the List

Description : Provide an Iterator for iterating over a List of Exoplanets,
              the iterator is initialised to refer to the first element of
              the list.

******************************************************************************/

Iterator list_begin(const List *list);

/******************************************************************************

Function    : list_end

Parameters  : List* - pointer to a List of Exoplanets

Returns     : Iterator - representing one past the end of a List

Description : Returns an Iterator used to check whether iterating through
              the elements of a List of Exoplanets has completed.

******************************************************************************/

Iterator list_end(const List *list);

/******************************************************************************

Function    : ieterator_next

Parameters  : const Iterator - iterator

Returns     : Iterator

Description : Returns an Iterator referring to the next element of a List of
              Exoplanets.

******************************************************************************/

Iterator iterator_next(const Iterator iterator);

/******************************************************************************

Function    : iterator_get

Parameters  : Iterator - iterator pointing at a valid element of a List

Returns     : Exoplanet* - pointer to an Exoplanet structure

Description : Return a pointer to the Exoplanet at the current position in
              a List of Exoplanets.

******************************************************************************/

Exoplanet* iterator_get(const Iterator i);

#endif // LIST_H

/*****************************************************************************/
