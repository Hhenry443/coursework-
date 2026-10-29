/******************************************************************************

File        : main.c

Date        : Wednesday 14th October 2026

Author      : Gavin Cawley

Description : Prototype implementation of a program to identify the most
              habitable exoplanets, according to the Earth Similarity Index
              (ESI) [1]

              Note that this program is just a prototype system to be used to
              refine the project specifications.  There may be bugs and areas
              where the code is inefficient.  These issues will be addressed
              as the program is iteratively improved/refactored.

References  : [1] Dirk Schulze-Makuch, Abel Mendez, Alberto G. Fairen,
                  Philip von Paris, Carol Turse, GraysonBoyer, Alfonso F.
                  Davila, Marina Resendes de Sousa Antonio, David Catling,
                  and Louis N. Irwin, "A two-tiered approach to assessing the
                  habitability of exoplanets", Astrobiology, 11(10):1041–1052,
                  2011. doi:10.1089/ast.2010.0592 .

History     : 14/10/2026 - v1.00 Initial prototype
              29/10/2026 - v1.01 Initial bug fixes:
                  1. Added a comma between arguments on exoplanet_setHabitability() call
                  2. Changes list_end to list_begin as the order is decrementing
                  3. changes the 057 from the ESI_r equation to be 0.57
                  4. Added the sqrt operation to the return value of computeHabitability()

******************************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Exoplanet.h"
#include "List.h"
#include "TestExoplanet.h"

#define EARTH_MASS            (5.972E+24)   // mass of the Earth in kg
#define EARTH_RADIUS          (6.371E+6)    // radius of the Earth in m
#define EARTH_DENSITY         (5.51)        // Earth density in g/cm^3
#define EARTH_ESCAPE_VELOCITY (11186)       // Earth escape velocity in m/s
#define EARTH_TEMPERATURE     (288)         // Earth surface temp. in K
#define G_CONST               (6.674E-11)   // Gravitational constant

double computeHabitability(const Exoplanet *planet);

void describePlanet(const Exoplanet* planet, FILE *fd);

int main(void)
{
   // Unit test the exoplanet
   if (!testExoplanet()) {
      printf("Unit test failed.");
      exit(1);
   }

   // load list of exoplanets from file

   FILE *fd = fopen("exoplanets.txt", "r");

   List *planets = list_load(fd);

   fclose(fd);

   // assign habitability scores to each exoplanet

   for (Iterator i  = list_begin(planets);
                 i != list_end(planets);
                 i  = iterator_next(i))
   {
      Exoplanet *planet = iterator_get(i);

      // Missing Comma between arguments.
      exoplanet_setHabitability(planet, computeHabitability(planet));
   }


   // sort exoplanets in descending order of habitability. So we have the most habitable as the first element
   list_sort(planets, exoplanet_descendingByHabitability);

   // display most habitable exoplanet

   // If in descending order, then the value at the end of the list would be the least habitable.
   // Changed list_end to list_begin
   // This also makes sense in the context of the top 20 being gotten from the start in that portion of the code!
   Iterator mostHabitable = list_begin(planets);

   printf("\nThe most habitable known exoplanet is:\n\n");

   describePlanet(iterator_get(mostHabitable), stdout);

   // save top-20 most habitable planets

   fd = fopen("top20.txt", "w");

   int n = 0;

   for (Iterator i  = list_begin(planets);
                 i != list_end(planets);
                 i  = iterator_next(i))
   {
      Exoplanet *planet = iterator_get(i);

      describePlanet(planet, fd);

      fprintf(fd, "\n");

      if (++n >= 20)
      {
         break;
      }
   }

   fclose(fd);

   // free dynamically allocated memory

   list_free(planets);

   // all done...

   return EXIT_SUCCESS;
}

/******************************************************************************

Function    : computeHabitability

Parameters  : Planet& - const reference to a Planet object

Returns     : double - value of the Earth Similarity Index

Description : Estimate the habitability of an exoplanet, according to the
              Earth Similarity Index (ESI).

Notes       : More verbose than strictly necessary in order to remain
              maximally consistent with the notation used by Schulze-Makuch
              et al. [1].

******************************************************************************/

double BCSI(double x, double x0, double w)
{
   return pow(1 - abs(x - x0)/(x + x0), w);
}

double computeHabitability(const Exoplanet *planet)
{
   double r  = exoplanet_getRadius(planet)*EARTH_RADIUS;
   double m  = exoplanet_getMass(planet)*EARTH_MASS;
   int    Ts = exoplanet_getTemperature(planet);

   // derived properties

   double volume = 4.0*M_PI*pow(r*1.0E2, 3)/3.0;   // volume in cm^3
   double rho    = m/volume/0.001;                 // density in g/cm^3
   double ve     = sqrt(2.0*G_CONST*m/r);          // escape velocity in m/s

   ve = ve/EARTH_ESCAPE_VELOCITY;   // convert to Earth Units

   // compute Earth Similarity Index

   double ESI_r   = BCSI(r*1e-3, EARTH_RADIUS*1e-3, 0.57);   // computed in km
   double ESI_rho = BCSI(rho,    EARTH_DENSITY, 1.07);
   double ESI_ve  = BCSI(ve,     1, 0.70);                   // in Earth units
   double ESI_Ts  = BCSI(Ts,     EARTH_TEMPERATURE, 5.58);

   double ESI_I = sqrt(ESI_r*ESI_rho);
   double ESI_S = sqrt(ESI_ve*ESI_Ts);

   // printf("%f\n", ESI_I*ESI_S);
   return sqrt(ESI_I*ESI_S); // Need to sqrt the end result!
}

/******************************************************************************

Function    : describePlanet

Parameters  : const Exoplanet* - pointer to a const Exoplanet structure
              FILE*            - pointer to a file descriptor

Returns     : void

Description : Display information about an exoplanet on the specified output
              stream.

******************************************************************************/

void describePlanet(const Exoplanet* planet, FILE *fd)
{
   fprintf(fd, "Planet name             : %s\n",
      exoplanet_getName(planet));
   fprintf(fd, "System name             : %s\n",
      exoplanet_getSystem(planet));
   fprintf(fd, "Method of discovery     : %s\n",
      exoplanet_getMethod(planet));
   fprintf(fd, "Year of discovery       : %d\n",
      exoplanet_getYear(planet));
   fprintf(fd, "Facility                : %s\n",
      exoplanet_getFacility(planet));
   fprintf(fd, "Radius (Earth relative) : %.3f\n",
      exoplanet_getRadius(planet));
   fprintf(fd, "Mass (Earth relative)   : %.3f\n",
      exoplanet_getMass(planet));
   fprintf(fd, "Equilibrium temperature : %d\n",
      exoplanet_getTemperature(planet));
   fprintf(fd, "Habitability index      : %.4f\n",
      exoplanet_getHabitability(planet));
}

/*****************************************************************************/
