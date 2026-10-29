//
// Created by Henry Barnes on 29/10/2026.
//

#include "Exoplanet.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exoplanet_free(Exoplanet *planet) {
    free(planet->name);
    free(planet->system);
    free(planet->method);
    free(planet->facility);
    free(planet);
}

/******************************************************************************

Function    : exoplanet_parse

Parameters  : str& - const reference to a string object

Returns     : Exoplanet - Newly created exoplanet

Description : Takes in a string of input, and generates an exoplanet struct from that

Notes       : This is probably not the best way of doing this. Loops over the string, and
              sets up pointers to first and last characters of words as it finds them, then adds
              them to an array as the word finishes. This was done to circumvent having to "neaten up"
              the string, as we can track if we are in a word or number using flags and changing them
              based on what characters we come across. (e.g, a string starts with a ")

              We then use malloc to allocate enough memory on the heap to store our new object. If we didn't do this
              the newly craeted object would be lost with the end of the funciton call as the stack frame would be
              discarded

******************************************************************************/
Exoplanet *exoplanet_parse(const char *str) {
    bool in_word = false;
    bool in_number = false;

    char *first_char;
    char *last_char;

    char *words[9]; // This is where we will store the 9 values.
    int word_count = 0;

    for (int i = 0; i < strlen(str); ++i) {
        // If we find a comma, and we are not in a number
        // we can assume we have come to the end of a word2
        if (str[i] == ',' && !in_number) {
            in_word = false;
            continue;
        }

        // If we find a space, and we are not in a word, we have come to the end of the string
        // this avoids stopping mid way through a string with a space
        if (str[i] == ' ' && !in_word) {
            in_word = false;
            continue;
        }

        // If we find a digit, we are not in a word and we are not in a number,
        // we have found a new number,
        if (isdigit(str[i]) && !in_word && !in_number) {
            // find a starting number
            first_char = &str[i];
            in_number = true;
        }

        // If we find a " and we aren't in a word, we have found a new word
        if (str[i] != '"' && !in_word) {
            // now we are in a word, keep track of this letter!
            first_char = &str[i];
            in_word = true;
        }

        // If we find a " and  we are in a word, its the end of the word, if we find a , and we are in a number,
        // its the end of the number!
        if ((str[i] == '"' && in_word) || (str[i] == ',' && in_number)) {
            // we are at the end! Stop tracking!
            last_char = &str[i-1];
            in_word = false;
            in_number = false;

            // how do we add the range of values between
            long diff = last_char - first_char;

            // Now we have a pointer to the first and last character, we need to add all of the characters between to a string

            // MALLOC USED BECASE WE NEED A NEW POINTER FOR EACH STRING IMPORTANT !!!!
            char *word = malloc((diff + 2) * sizeof(char));

            int count = 0;

            while (first_char <= last_char) {
                word[count] = *first_char;
                first_char++;
                count++;
            }

            word[diff + 1] = '\0';

            words[word_count] = word;
            word_count++;
        }
    }

    // Did we succeed in making it?
    if (word_count < 8) {
        for (int k = 0; k < word_count; ++k) free(words[k]); // free all of the strings !
        return NULL;
    }

    char *end_year;
    char *end_radius;
    char *end_mass;
    char *end_temp;

    int year = strtol(words[3], &end_year, 10);
    double radius = strtod(words[5], &end_radius);
    double mass = strtod(words[6], &end_mass);
    int temp = strtol(words[7], &end_temp, 10);

    Exoplanet *e = malloc(sizeof(Exoplanet));

    if (e == NULL) {
        return NULL;
    }

    e->name = words[0];
    e->system = words[1];
    e->method = words[2];
    e->year = year;
    e->facility = words[4];
    e->radius = radius;
    e->mass = mass;
    e->temperature = temp;
    e->habitability = 0;

    return e;
}

const char* exoplanet_toString(const Exoplanet *planet) {
    char buff[1000];

    // "LV426", "Zeta Reticuli", "Deep Space Probe", 2039, "Weyland-Yutani Corporation", 0.772, 0.410, 288, 0.0000
    sprintf(buff, "\"%s\", \"%s\", \"%s\", %d, \"%s\", %f, %f, %d, %f", exoplanet_getName(planet), exoplanet_getSystem(planet),
        exoplanet_getMethod(planet), exoplanet_getYear(planet), exoplanet_getFacility(planet), exoplanet_getRadius(planet),
        exoplanet_getMass(planet), exoplanet_getTemperature(planet), exoplanet_getHabitability(planet));

    return buff;
}

const char* exoplanet_getName(const Exoplanet *planet) {
    return planet->name;
}

const char* exoplanet_getSystem(const Exoplanet *planet) {
    return planet->system;
}

const char* exoplanet_getMethod(const Exoplanet *planet) {
    return planet->method;
}

int exoplanet_getYear(const Exoplanet *planet) {
    return planet->year;
}

const char* exoplanet_getFacility(const Exoplanet *planet) {
    return planet->facility;
}

double exoplanet_getRadius(const Exoplanet *planet) {
    return planet->radius;
}

double exoplanet_getMass(const Exoplanet *planet) {
    return planet->mass;
}

int exoplanet_getTemperature(const Exoplanet *planet) {
    return planet->temperature;
}

double exoplanet_getHabitability(const Exoplanet *planet) {
    return planet->habitability;
}

void exoplanet_setHabitability(Exoplanet *planet, double habitability) {
    planet->habitability = habitability;
}

int exoplanet_descendingByHabitability(const Exoplanet *a, const Exoplanet *b) {
    // If a has a lower habitability, it goes after b
    if (a->habitability < b->habitability) {
        return 1;
    }

    // If a has a better habitability it goes before b
    if (a->habitability > b->habitability) {
        return -1;
    }

    return 0;
}