#include <iostream>
#include "UFO_Sightings.h"


int main() {
    UFO_Sightings UFO_S;


    UFO_S.parse_csv("../data/ufo_sightings.csv");

    UFO_S.tester();

    return 0;
}