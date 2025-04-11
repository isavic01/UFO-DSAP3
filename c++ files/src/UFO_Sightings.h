#include <iostream>
#include <vector>
#include <utility>
#include <chrono>


class UFO_Sightings {
private:
    // stores sighting data
    struct Sighting {                       // csv order
        std::string city, state;            // 0,1
        std::string shape, excerpt;         // 3, 5
        float duration;                     // 4
        float latitude, longitude;          // 6, 7
        int year, month, day, hour, minute; // 8, 9, 10, 11, 12
    };

    // stores all sightings   (60,632)
    std::vector<Sighting> sightings;


public:
    // populate sightings list from csv. returns true if successful, false otherwise.
    bool parse_csv(const std::string& filepath);    // o ( n )

    // return a sorted list of cities based off of # of sightings. if given, limit to year
    std::vector<std::pair<std::string, int>> get_sorted_city_freq(int year);
    std::vector<std::pair<std::string, int>> get_sorted_city_freq();

    // methods to convert sighting attributes to formatted strings
    static std::string sighting_to_string(const Sighting s);
    static std::string location_to_string(const Sighting s);
    static std::string coordinates_to_string(const Sighting s);
    static std::string description_to_string(const Sighting s);
    static std::string time_to_string(const Sighting s);

    // dev method to test private methods & attributes
    void tester();
};


