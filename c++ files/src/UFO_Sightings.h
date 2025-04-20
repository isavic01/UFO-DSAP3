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
    bool parse_csv();

    // return a sorted list of cities based on # of sightings in year. if 0, all time. sort_type = "Heap" or "Shell"
    std::vector<std::pair<std::string, int>> get_sorted_city_freq(const std::string& sort_type, const int& year);
    std::vector<std::pair<std::string, int>> get_sorted_time_freq(const std::string& sort_type, const int& year);
    std::vector<std::pair<std::string, int>> get_sorted_city_time_freq(const std::string& sort_type, const int& year);

    // sort a frequency list vector<pair<string,int>> using shell sort
    void shell_sort(std::vector<std::pair<std::string,int>>& freq_list);  // insert sort for shell
    void insertion_sort(std::vector<std::pair<std::string,int>>& freq_list, int start, int increment, int n);

    // sort a frequency list vector<pair<string,int>> using heap sort
    void heap_sort(std::vector<std::pair<std::string,int>>& freq_list);
    void heapify(std::vector<std::pair<std::string,int>>& freq_list, int n, int i);

    // methods to get formatted strings
    std::string get_top_locations(const std::string &sort_type, const int &year);
    std::string get_top_times(const std::string &sort_type, const int &year);
    std::string get_top_locations_at_times(const std::string &sort_type, const int &year);

    // methods to convert sighting attributes to formatted strings
    static std::string sighting_to_string(const Sighting& s);
    static std::string location_to_string(const Sighting& s);
    static std::string coordinates_to_string(const Sighting& s);
    static std::string description_to_string(const Sighting& s);
    static std::string time_to_string(const Sighting& s);
    static std::string date_to_string(const Sighting& s);

    // dev method to test private methods & attributes
    void tester();
};


