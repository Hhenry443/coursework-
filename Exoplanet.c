//
// Created by Henry Barnes on 29/10/2026.
//

#include "Exoplanet.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to parse a new exoplanet from a string like the one found in exoplanets.txt
// first, we will have to split the string into its respective parts.
Exoplanet *exoplanet_parse(const char *str) {
    // How do we split the string into digestible parts.
    // Opt 2: Custom loop

    // Example String:
    // "K2-34 b", "K2-34", "Transit", 2016, "K2", 15.132, 559.381, 1742, 0.0000

    // We could try to loop over the string, until we find a comma. we know that the comma will separate values.

    // How how how how how how how
    // if we keep track of the pointer that we start a word, and the pointer where we stop it,
    // would that give us the word? we put everything in that range.
    // arrays are contiguous chunks of memory
    bool in_word = false;
    bool in_number = false;

    char *first_char = 0;
    char *last_char;

    char *words[9];
    int word_count = 0;

    for (int i = 0; i < strlen(str); ++i) {
        // If we find a comma, and we are not in a number
        // we can assume we have come to the end of a string
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
            char *word = malloc((diff + 1) * sizeof(char));

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

    Exoplanet e = {
        .name = words[0],
        .system = words[1],
        .method = words[2],
        .year = (int)words[3],
        .facility = words[4],
        .radius = atof(words[5]),
        .mass = atof(words[6]),
        .temperature = (int)words[7],
        .habitability = 0
    };

    return &e;
}

void exoplanet_free(Exoplanet *planet) {
    free(planet);
}

const char* exoplanet_toString(const Exoplanet *planet) {
    return exoplanet_getName(planet);
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
    if (a->habitability > b->habitability) {
        return 1;
    }

    if (a->habitability < b->habitability) {
        return -1;
    }

    return 0;

}