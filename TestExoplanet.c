//
// Created by Henry Barnes on 29/10/2026.
//

#include "TestExoplanet.h"
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Exoplanet.h"

static bool doubles_equal(double a, double b) {
    return abs(a - b) < 1e-6;
}

// Helper function to compare the two
static bool exoplanet_equals(const Exoplanet *a, const Exoplanet *b) {
    return strcmp(a->name, b->name) == 0
        && strcmp(a->system, b->system) == 0
        && strcmp(a->method, b->method) == 0
        && a->year == b->year
        && strcmp(a->facility, b->facility) == 0
        && doubles_equal(a->radius, b->radius)
        && doubles_equal(a->mass, b->mass)
        && doubles_equal(a->temperature, b->temperature)
        && doubles_equal(a->habitability, b->habitability);
}

bool testExoplanet() {
    // Testing successful parsing of a exoplanet from a sample string
    Exoplanet planet1 = {
        .name = "LV426",
        .system ="Zeta Reticuli",
        .method = "Deep Space Probe",
        .year = 2039,
        .facility = "Weyland-Yutani Corporation",
        .radius = 0.772,
        .mass = 0.410,
        .temperature = 288,
        .habitability = 0.0000
    };

    Exoplanet *planet2 = exoplanet_parse("\"LV426\", \"Zeta Reticuli\", \"Deep Space Probe\", 2039, \"Weyland-Yutani Corporation\", 0.772, 0.410, 288, 0.0000");

    // Parsing a proper string
    if (!exoplanet_equals(&planet1, planet2)) {
        return false;
    }
    exoplanet_free(planet2);

    planet2 = exoplanet_parse("This is not how we pass in a string");

    // Passing an improper string should result in null
    if (planet2 != NULL) {
        return false;
    }

    // Now check that we output the correct string
    const char *planet_string = exoplanet_toString(&planet1);

    if (!strcmp("\"LV426\", \"Zeta Reticuli\", \"Deep Space Probe\", 2039, \"Weyland-Yutani Corporation\", 0.772, 0.410, 288, 0.0000", planet_string)) {
        printf("String Fail\n");

        return false;
    }


    // Check that we get the correct values from getters
    if (strcmp("LV426", exoplanet_getName(&planet1))) {
        printf("Name Fail\n");

        return false;
    }

    if (strcmp("Zeta Reticuli", exoplanet_getSystem(&planet1))) {
        printf("System Fail\n");

        return false;
    }

    if (strcmp("Deep Space Probe", exoplanet_getMethod(&planet1))) {
        printf("Method Fail\n");


        return false;
    }

    if (2039 != exoplanet_getYear(&planet1)) {
        printf("Year Fail\n");

        return false;
    }

    if (strcmp("Weyland-Yutani Corporation", exoplanet_getFacility(&planet1))) {
        printf("Facility Fail\n");

        return false;
    }

    if (0.772 != exoplanet_getRadius(&planet1)) {
        printf("Radius Fail\n");

        return false;
    }

    if (0.410 != exoplanet_getMass(&planet1)) {
        printf("Mass Fail\n");

        return false;
    }

    if (288 != exoplanet_getTemperature(&planet1)) {
        printf("Temperature Fail\n");
        return false;
    }

    if (0.0000 != exoplanet_getHabitability(&planet1)) {
        printf("Habitability Fail\n");
        return false;
    }

    // Now we test for the habitability comparison
    Exoplanet DreamPlanet = {
        .name = "LV426",
        .system ="Zeta Reticuli",
        .method = "Deep Space Probe",
        .year = 2039,
        .facility = "Weyland-Yutani Corporation",
        .radius = 0.772,
        .mass = 0.410,
        .temperature = 288,
        .habitability = 0.9999
    };

    Exoplanet NightmarePlanet = {
        .name = "LV426",
        .system ="Zeta Reticuli",
        .method = "Deep Space Probe",
        .year = 2039,
        .facility = "Weyland-Yutani Corporation",
        .radius = 0.772,
        .mass = 0.410,
        .temperature = 288,
        .habitability = 0.0000
    };

    // a is worse than b. Should return 1
    if (1 != exoplanet_descendingByHabitability(&NightmarePlanet, &DreamPlanet)) {
        return false;
    }

    // a is better than b. Should return -1
    if (-1 != exoplanet_descendingByHabitability(&DreamPlanet, &NightmarePlanet)) {
        return false;
    }

    // a and b are the same. Should return 0
    if (0 != exoplanet_descendingByHabitability(&DreamPlanet, &DreamPlanet)) {
        return false;
    }

    return true;
}