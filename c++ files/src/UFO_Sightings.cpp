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

std::vector<std::pair<std::string, int>> UFO_Sightings::get_sorted_city_freq(int year) {
    // traverse sightings list and count # sightings in each city for specified year
    std::unordered_map<std::string, int> freq;
    for (const auto& sighting: sightings) {
        if (sighting.year == year) {
            freq[location_to_string(sighting)]++;
        }
    }

    // sort list based on frequency
    std::vector<std::pair<std::string, int>> result;
    for (const auto city: freq) {
        result.push_back(city);
    }
    // ******************* CHANGE SORT FOR COMPARISON
    std::sort(result.begin(), result.end(),[] ( auto &left, auto &right){
        return left.second > right.second;
    });
    return result;
}
std::vector<std::pair<std::string, int>> UFO_Sightings::get_sorted_city_freq() {
    // traverse sightings list and count # sightings in each city
    std::unordered_map<std::string, int> freq;
    for (const auto& sighting: sightings) {
        freq[location_to_string(sighting)]++;
    }

    // sort list based on frequency
    std::vector<std::pair<std::string, int>> result;
    for (const auto city: freq) {
        result.push_back(city);
    }
    // ******************* CHANGE SORT FOR COMPARISON
    std::sort(result.begin(), result.end(),[] ( auto &left, auto &right){
        return left.second > right.second;
    });
    return result;
}


std::string UFO_Sightings::sighting_to_string(const Sighting s) {
    std::stringstream ss;
    ss<<"Location: " << location_to_string(s)<<'\n';
    ss<<coordinates_to_string(s)<<'\n';
    ss<<time_to_string(s)<<'\n';
    ss<<description_to_string(s)<<'\n';
    return ss.str();
}
std::string UFO_Sightings::location_to_string(const Sighting s) {
    std::stringstream ss;
    ss<<s.city<<", " <<s.state;
    return ss.str();
}
std::string UFO_Sightings::coordinates_to_string(const Sighting s) {
    std::stringstream ss;
    ss<<"Latitude " << s.latitude <<", Longitude " <<s.longitude;;
    return ss.str();
}
std::string UFO_Sightings::description_to_string(const Sighting s) {
    std::stringstream ss;
    ss<<"UFO shape: " << s.shape <<'\n';
    ss<<"Duration: " << s.duration << " seconds\n";
    ss<<"Excerpt: " << s.excerpt <<'\n';
    return ss.str();
}
std::string UFO_Sightings::time_to_string(const Sighting s) {
    std::stringstream ss;
    ss<<"MM/DD/YYYY: " << s.month<< " / "<< s.day <<" / "<< s.year <<", ";
    ss<< s.hour <<':' << std::setw(2) << std::setfill('0')<< s.minute;
    return ss.str();
}


void UFO_Sightings::tester() {
    std::cout<<"Testing UFO_Sightings*************\n";

    std::cout<<"top 10 cities: \n";     //add year arg to limit, [1998 - 2014]
    auto test = get_sorted_city_freq();
    for (int i = 1; i <= 10; i++) {
        std::cout<<i<< ".) "<< test[i].first << " " << test[i].second << '\n';
    }
    std::cout<<"unique cities found: " << test.size()<<'\n';

    std::cout<<"Done testing!*********************\n";
}
