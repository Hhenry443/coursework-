//
// Created by Henry Barnes on 29/10/2026.
//

#ifndef C_COURSEWORK_EXOPLANET_H
#define C_COURSEWORK_EXOPLANET_H

typedef struct Exoplanet_Struct {
    char *name;
    char *system;
    char *method;
    int year;
    char *facility;
    double radius;
    double mass;
    int temperature;
    double habitability;
} Exoplanet;

Exoplanet *exoplanet_parse(const char *str);

void exoplanet_free(Exoplanet *planet);

const char* exoplanet_toString(const Exoplanet *planet);

const char* exoplanet_getName(const Exoplanet *planet);

const char* exoplanet_getSystem(const Exoplanet *planet);

const char* exoplanet_getMethod(const Exoplanet *planet);

int exoplanet_getYear(const Exoplanet *planet);

const char* exoplanet_getFacility(const Exoplanet *planet);

double exoplanet_getRadius(const Exoplanet *planet);

double exoplanet_getMass(const Exoplanet *planet);

int exoplanet_getTemperature(const Exoplanet *planet);

double exoplanet_getHabitability(const Exoplanet *planet);

void exoplanet_setHabitability(Exoplanet *planet, double habitability);

int exoplanet_descendingByHabitability(const Exoplanet *a, const Exoplanet *b);
#endif //C_COURSEWORK_EXOPLANET_H
