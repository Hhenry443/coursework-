/******************************************************************************

File        : List.c

Date        : Wednesday 14th October 2026

Author      : Gavin Cawley

Description : Implementation of a basic singly-linked list of pointers to
              Exoplanet structures.

History     : 14/10/2026 - v1.00 Initial prototype

******************************************************************************/

#include <stdlib.h>

#include "List.h"

// Missing bool macro
#include <stdbool.h>

typedef struct LinkStruct
{
   Exoplanet *planet;

   struct LinkStruct *next;
}
Link;

typedef struct ListStruct
{
   Link *first;
}
List;

Link* link_new(Exoplanet *planet, Link *next)
{
   Link *link = (Link*)malloc(sizeof(Link));

   link->planet = planet;
   link->next   = next;

   return link;
}

void link_free(Link *link)
{
   free(link);
}

List* list_new()
{
   List *list = (List*)malloc(sizeof(List));

   list->first = NULL;

   return list;
}

void list_add(List *list, Exoplanet *planet)
{
   list->first = link_new(planet, list->first);
}

void list_free(List *list)
{
   while (list->first != NULL)
   {
      Link *link = list->first;

      list->first = link->next;

      link_free(link);
   }

   free(list);
}

void list_print(const List *list, FILE *fd)
{
   for (Link *link = list->first; link != NULL; link = link->next)
   {
      fprintf(fd, "%s\n", exoplanet_toString(link->planet));
   }
}

List *list_load(FILE *fd)
{
   const int BUFFER_SIZE = 1024;

   char buffer[BUFFER_SIZE];

   List *list = list_new();

   while (fgets(buffer, BUFFER_SIZE, fd) != NULL)
   {
      Exoplanet *planet = exoplanet_parse(buffer);

      list_add(list, planet);
   }

   return list;
}

void list_sort(List *list, Comparator compare)
{

   if (list->first == NULL || list->first->next == NULL)
   {
      return;
   }

   bool sorted;

   do
   {
      sorted = false;

      for (Link *link = list->first; link->next != NULL; link=link->next)
      {
         if (compare(link->planet, link->next->planet) > 0)
         {
            Exoplanet *planet  = link->planet;
            link->planet       = link->next->planet;
            link->next->planet = planet;

            sorted = true;
         }
      }
   }
   while (!sorted);
}

Iterator list_begin(const List *list)
{
   return list->first;
}

Iterator list_end(const List *list)
{
   // We get the list, we need to get the last one?
   Iterator current = list_begin(list);

   while (current->next != NULL) {
      current = iterator_next(current);
   }

   return current;
}

Iterator iterator_next(const Iterator iterator)
{
   return iterator->next;
}

Exoplanet* iterator_get(const Iterator iterator)
{
   return iterator->planet;
}

/*****************************************************************************/
