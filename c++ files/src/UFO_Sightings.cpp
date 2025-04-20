#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

#include "UFO_Sightings.h"

#include <unordered_map>


bool UFO_Sightings::parse_csv(const std::string& filepath) {
    //verify file opened properly
    auto file = std::ifstream(filepath);
    if (!file.is_open()) {
        std::cout<<"Could not open file! "<<'\n';
        return false;
    }

    if (!sightings.empty()) {
        std::cout<<"CSV already parsed! "<<'\n';
        return false;
    }
    //parse every sighting in csv
    std::string line;
    std::getline(file,line);  //(skip header)
    while(std::getline(file,line)) {
        auto ss = std::stringstream(line);  //parse line into sighting
        std::string data;
        Sighting sighting;

        // set sighting values, stripping double quotes & converting to numerical where needed
        std::getline(ss, data, ',');
            sighting.city= data.substr(1, data.size()-2);
        std::getline(ss,data, ',');
            sighting.state= data.substr(1, data.size()-2);
        std::getline(ss,data, ',');
            //skip line, unnecessary data
        std::getline(ss, data, ',');
            sighting.shape= data.substr(1, data.size()-2);
        std::getline(ss,data, ',');
            data = data.substr(1, data.size()-2);
            sighting.duration = std::stof(data);
        std::getline(ss,data, ',');
            sighting.excerpt= data.substr(1, data.size()-2);
        std::getline(ss,data, ',');
            data = data.substr(1, data.size()-2);
            sighting.latitude = std::stof(data);
        std::getline(ss,data, ',');
            data = data.substr(1, data.size()-2);
            sighting.longitude = std::stof(data);
        std::getline(ss,data, ',');
            data = data.substr(1, data.size()-2);
            sighting.year = std::stoi(data);
        std::getline(ss,data, ',');
            data = data.substr(1, data.size()-2);
            sighting.month = std::stoi(data);
        std::getline(ss,data, ',');
            data = data.substr(1, data.size()-2);
            sighting.day = std::stoi(data);
        std::getline(ss,data, ',');
            data = data.substr(1, data.size()-2);
            sighting.hour = std::stoi(data);
        std::getline(ss,data, ',');
            data = data.substr(1, data.size()-2);
            sighting.minute = std::stoi(data);

        sightings.push_back(sighting);
    }

    file.close();
    return true;
}
bool UFO_Sightings::parse_csv() {
    return parse_csv("../data/ufo_sightings.csv");
} // default parse address

std::vector<std::pair<std::string, int>> UFO_Sightings::get_sorted_city_freq(const std::string& sort_type, const int& year) {
    // traverse sightings list and count # sightings in each city for specified year
    // year 0 = all time
    std::unordered_map<std::string, int> freq;
    for (const auto& sighting: sightings) {
        if (year == 0 || sighting.year == year) {
            freq[location_to_string(sighting)]++;
        }
    }

    // save to sortable type
    std::vector<std::pair<std::string, int>> result;
    for (const auto city: freq) {
        result.push_back(city);
    }

    // sort list based on frequency

    if (sort_type == "Shell") shell_sort(result);
    if (sort_type == "Heap") heap_sort(result);
    else {      // default std sort for comparison
        std::sort(result.begin(), result.end(),[] ( auto &left, auto &right){
            return left.second > right.second;
        });
    }

    return result;
}

std::vector<std::pair<std::string, int>> UFO_Sightings::get_sorted_time_freq(const std::string &sort_type, const int &year) {
    // traverse sightings list and count # sightings at any time for specified year
    // year 0 = all time
    std::unordered_map<std::string, int> freq;
    for (const auto& sighting: sightings) {
        if (year == 0 || sighting.year == year) {
            freq[time_to_string(sighting)]++;
        }
    }

    // save to sortable type
    std::vector<std::pair<std::string, int>> result;
    for (const auto time: freq) {
        result.push_back(time);
    }

    // sort list based on frequency
    if (sort_type == "Shell") shell_sort(result);
    if (sort_type == "Heap") heap_sort(result);

    else {      //default sort for comparison
        std::sort(result.begin(), result.end(),[] ( auto &left, auto &right){
            return left.second > right.second;
        });
    }

    return result;
}

std::vector<std::pair<std::string, int>> UFO_Sightings::get_sorted_city_time_freq(const std::string &sort_type, const int &year) {
    // traverse sightings list and count # sightings at any time and city pair for specified year
    // year 0 = all time
    std::unordered_map<std::string, int> freq;
    for (const auto& sighting: sightings) {
        if (year == 0 || sighting.year == year) {
            std::string city_time = location_to_string(sighting) + " at " +time_to_string(sighting);
            freq[city_time]++;
        }
    }

    // save to sortable type
    std::vector<std::pair<std::string, int>> result;
    for (const auto city_time: freq) {
        result.push_back(city_time);
    }

    // sort list based on frequency
    if (sort_type == "Shell") shell_sort(result);
    if (sort_type == "Heap") heap_sort(result);

    else {      //default sort for comparison
        std::sort(result.begin(), result.end(),[] ( auto &left, auto &right){
            return left.second > right.second;
        });
    }

    return result;
}

void UFO_Sightings::shell_sort(std::vector<std::pair<std::string,int>>& freq_list){
    int n = freq_list.size();
    for (int i = n/2; i > 2; i /= 2)  //For each increment
        for (int j = 0; j < i; j++)  //Sort each sublist
            insertion_sort(freq_list, j, i, n);
    insertion_sort(freq_list, 0, 1, n);
} //modified from opendsa textbook
void UFO_Sightings::insertion_sort(std::vector<std::pair<std::string,int>>& freq_list, int start, int increment, int n){
    for (int i = start+increment; i<n ; i+=increment) {
        for (int j = i; ((j>=increment) && (freq_list[j].second > freq_list[j-increment].second)); j-=increment) {
            std::swap(freq_list[j], freq_list[j-increment]);
        }
    }
}   // modified from opendsa texbook

void UFO_Sightings::heap_sort(std::vector<std::pair<std::string, int>> &freq_list) {
    int n = freq_list.size();

    // build heap inplace
    for (int i = n/2 - 1; i >= 0; --i) {
        heapify(freq_list, n, i);
    }

    // extract elements
    for (int i = n - 1; i > 0; --i) {
        std::swap(freq_list[0], freq_list[i]);
        heapify(freq_list, i, 0);
    }
}
void UFO_Sightings::heapify(std::vector<std::pair<std::string, int>> &freq_list, int n, int i) {
    int max_index = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && freq_list[left].second < freq_list[max_index].second)
        max_index = left;

    if (right < n && freq_list[right].second < freq_list[max_index].second)
        max_index = right;

    // if root not max, swap w/ max and keep heapifying
    if (max_index != i) {
        std::swap(freq_list[i], freq_list[max_index]);
        heapify(freq_list, n, max_index);
    }
}

std::string UFO_Sightings::get_top_locations(const std::string &sort_type, const int &year) {
    std::stringstream ss;

    auto start = std::chrono::high_resolution_clock::now();
    auto sorted_cities = get_sorted_city_freq(sort_type, year);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(end - start);
    ss<<"Time taken: " << duration.count() << " milliseconds!\n";

    for (int i = 1; i <= 10; i++) {
        if (i>sorted_cities.size()) break;  // check for years w/ less than 10 sightings
        ss<<i << ".) "<< sorted_cities[i-1].first << ", " <<sorted_cities[i-1].second << " sightings\n";
    }
    
    return ss.str();
}
std::string UFO_Sightings::get_top_times(const std::string &sort_type, const int &year) {
    std::stringstream ss;

    auto start = std::chrono::high_resolution_clock::now();
    auto sorted_times = get_sorted_time_freq(sort_type, year);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(end - start);
    ss<<"Time taken: " << duration.count() << " milliseconds!\n";

    for (int i = 1; i <= 10; i++) {
        if (i>sorted_times.size()) break;  // check for years w/ less than 10 sightings
        ss<< i << ".) "<< sorted_times[i-1].first << ", " <<sorted_times[i-1].second << " sightings\n";
    }

    return ss.str();
}
std::string UFO_Sightings::get_top_locations_at_times(const std::string &sort_type, const int &year) {
    std::stringstream ss;

    auto start = std::chrono::high_resolution_clock::now();
    auto sorted_city_times = get_sorted_city_time_freq(sort_type, year);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(end - start);
    ss<<"Time taken: " << duration.count() << " milliseconds!\n";

    for (int i = 1; i <= 10; i++) {
        if (i>sorted_city_times.size()) break;  // check for years w/ less than 10 sightings
        ss<< i << ".) "<< sorted_city_times[i-1].first << ", " <<sorted_city_times[i-1].second << " sightings\n";
    }

    return ss.str();
}

std::string UFO_Sightings::sighting_to_string(const Sighting& s) {
    std::stringstream ss;
    ss<<"Location: " << location_to_string(s)<<'\n';
    ss<<coordinates_to_string(s)<<'\n';
    ss<<date_to_string(s)<<'\n';
    ss<<description_to_string(s)<<'\n';
    return ss.str();
}
std::string UFO_Sightings::location_to_string(const Sighting& s) {
    std::stringstream ss;
    ss<<s.city<<", " <<s.state;
    return ss.str();
}
std::string UFO_Sightings::coordinates_to_string(const Sighting& s) {
    std::stringstream ss;
    ss<<"Latitude " << s.latitude <<", Longitude " <<s.longitude;;
    return ss.str();
}
std::string UFO_Sightings::description_to_string(const Sighting& s) {
    std::stringstream ss;
    ss<<"UFO shape: " << s.shape <<'\n';
    ss<<"Duration: " << s.duration << " seconds\n";
    ss<<"Excerpt: " << s.excerpt <<'\n';
    return ss.str();
}
std::string UFO_Sightings::date_to_string(const Sighting&  s) {
    std::stringstream ss;
    ss<<"MM/DD/YYYY: " << s.month<< " / "<< s.day <<" / "<< s.year <<", ";
    ss<< s.hour <<':' << std::setw(2) << std::setfill('0')<< s.minute;
    return ss.str();
}
std::string UFO_Sightings::time_to_string(const Sighting&  s) {
    std::stringstream ss;
    ss<< s.hour <<':' << std::setw(2) << std::setfill('0')<< s.minute;
    return ss.str();
}


void UFO_Sightings::tester() {
    std::cout<<"Testing UFO_Sightings*************\n";

    parse_csv();

    std::cout<<get_top_locations("Heap", 0)<<'\n';
    std::cout<<get_top_times("Heap", 0)<<'\n';
    std::cout<<get_top_locations_at_times("Heap", 0)<<'\n';

    std::cout<<"Done testing!*********************\n";
}
