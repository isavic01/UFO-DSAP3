#include <iostream>
#include <vector>
#include <utility>
#include <chrono>

using namespace std;

class UFO_Sightings {
private:
    struct Sighting {                       
        string city, state;            
        string shape, excerpt;         
        float duration;                     
        float latitude, longitude;          
        int year, month, day, hour, minute; 
    };

    vector<Sighting> sightings;

public:
    bool parse_csv(const string& filepath);    
    bool parse_csv();

    vector<pair<string, int>> get_sorted_city_freq(const string& sort_type, const int& year);
    vector<pair<string, int>> get_sorted_time_freq(const string& sort_type, const int& year);
    vector<pair<string, int>> get_sorted_city_time_freq(const string& sort_type, const int& year);

    void shell_sort(vector<pair<string,int>>& freq_list);
    void insertion_sort(vector<pair<string,int>>& freq_list, int start, int increment, int n);

    void heap_sort(vector<pair<string,int>>& freq_list);
    void heapify(vector<pair<string,int>>& freq_list, int n, int i);

    string get_top_locations(const string &sort_type, const int &year);
    string get_top_times(const string &sort_type, const int &year);
    string get_top_locations_at_times(const string &sort_type, const int &year);

    static string sighting_to_string(const Sighting& s);
    static string location_to_string(const Sighting& s);
    static string coordinates_to_string(const Sighting& s);
    static string description_to_string(const Sighting& s);
    static string time_to_string(const Sighting& s);
    static string date_to_string(const Sighting& s);

    void tester();
};
