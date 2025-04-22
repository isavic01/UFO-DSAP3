#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <unordered_map>

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

bool UFO_Sightings::parse_csv(const string& filepath) {
    auto file = ifstream(filepath);
    if (!file.is_open()) {
        cout<<"Could not open file! "<<'\n';
        return false;
    }

    if (!sightings.empty()) {
        cout<<"CSV already parsed! "<<'\n';
        return false;
    }

    string line;
    getline(file, line);  
    while(getline(file, line)) {
        auto ss = stringstream(line); 
        string data;
        Sighting sighting;

        getline(ss, data, ',');
        sighting.city = data.substr(1, data.size() - 2);
        getline(ss, data, ',');
        sighting.state = data.substr(1, data.size() - 2);
        getline(ss, data, ',');
        getline(ss, data, ',');
        sighting.shape = data.substr(1, data.size() - 2);
        getline(ss, data, ',');
        data = data.substr(1, data.size() - 2);
        sighting.duration = stof(data);
        getline(ss, data, ',');
        sighting.excerpt = data.substr(1, data.size() - 2);
        getline(ss, data, ',');
        data = data.substr(1, data.size() - 2);
        sighting.latitude = stof(data);
        getline(ss, data, ',');
        data = data.substr(1, data.size() - 2);
        sighting.longitude = stof(data);
        getline(ss, data, ',');
        data = data.substr(1, data.size() - 2);
        sighting.year = stoi(data);
        getline(ss, data, ',');
        data = data.substr(1, data.size() - 2);
        sighting.month = stoi(data);
        getline(ss, data, ',');
        data = data.substr(1, data.size() - 2);
        sighting.day = stoi(data);
        getline(ss, data, ',');
        data = data.substr(1, data.size() - 2);
        sighting.hour = stoi(data);
        getline(ss, data, ',');
        data = data.substr(1, data.size() - 2);
        sighting.minute = stoi(data);

        sightings.push_back(sighting);
    }

    file.close();
    return true;
}

bool UFO_Sightings::parse_csv() {
    return parse_csv("../data/ufo_sightings.csv");
} 

vector<pair<string, int>> UFO_Sightings::get_sorted_city_freq(const string& sort_type, const int& year) {
    unordered_map<string, int> freq;
    for (const auto& sighting: sightings) {
        if (year == 0 || sighting.year == year) {
            freq[location_to_string(sighting)]++;
        }
    }

    vector<pair<string, int>> result;
    for (const auto& city: freq) {
        result.push_back(city);
    }

    if (sort_type == "Shell") shell_sort(result);
    if (sort_type == "Heap") heap_sort(result);
    else {
        sort(result.begin(), result.end(), [](auto &left, auto &right) {
            return left.second > right.second;
        });
    }

    return result;
}

vector<pair<string, int>> UFO_Sightings::get_sorted_time_freq(const string &sort_type, const int &year) {
    unordered_map<string, int> freq;
    for (const auto& sighting: sightings) {
        if (year == 0 || sighting.year == year) {
            freq[time_to_string(sighting)]++;
        }
    }

    vector<pair<string, int>> result;
    for (const auto& time: freq) {
        result.push_back(time);
    }

    if (sort_type == "Shell") shell_sort(result);
    if (sort_type == "Heap") heap_sort(result);
    else {
        sort(result.begin(), result.end(), [](auto &left, auto &right) {
            return left.second > right.second;
        });
    }

    return result;
}

vector<pair<string, int>> UFO_Sightings::get_sorted_city_time_freq(const string &sort_type, const int &year) {
    unordered_map<string, int> freq;
    for (const auto& sighting: sightings) {
        if (year == 0 || sighting.year == year) {
            string city_time = location_to_string(sighting) + " at " + time_to_string(sighting);
            freq[city_time]++;
        }
    }

    vector<pair<string, int>> result;
    for (const auto& city_time: freq) {
        result.push_back(city_time);
    }

    if (sort_type == "Shell") shell_sort(result);
    if (sort_type == "Heap") heap_sort(result);
    else {
        sort(result.begin(), result.end(), [](auto &left, auto &right) {
            return left.second > right.second;
        });
    }

    return result;
}

void UFO_Sightings::shell_sort(vector<pair<string, int>>& freq_list) {
    int n = freq_list.size();
    for (int i = n/2; i > 2; i /= 2)  
        for (int j = 0; j < i; j++) 
            insertion_sort(freq_list, j, i, n);
    insertion_sort(freq_list, 0, 1, n);
}

void UFO_Sightings::insertion_sort(vector<pair<string, int>>& freq_list, int start, int increment, int n) {
    for (int i = start + increment; i < n; i += increment) {
        for (int j = i; (j >= increment) && (freq_list[j].second > freq_list[j - increment].second); j -= increment) {
            swap(freq_list[j], freq_list[j - increment]);
        }
    }
}

void UFO_Sightings::heap_sort(vector<pair<string, int>>& freq_list) {
    int n = freq_list.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(freq_list, n, i);
    }
    for (int i = n - 1; i > 0; --i) {
        swap(freq_list[0], freq_list[i]);
        heapify(freq_list, i, 0);
    }
}

void UFO_Sightings::heapify(vector<pair<string, int>>& freq_list, int n, int i) {
    int max_index = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && freq_list[left].second < freq_list[max_index].second)
        max_index = left;
    if (right < n && freq_list[right].second < freq_list[max_index].second)
        max_index = right;

    if (max_index != i) {
        swap(freq_list[i], freq_list[max_index]);
        heapify(freq_list, n, max_index);
    }
}

string UFO_Sightings::get_top_locations(const string &sort_type, const int &year) {
    stringstream ss;
    auto start = chrono::high_resolution_clock::now();
    auto sorted_cities = get_sorted_city_freq(sort_type, year);
    auto end = chrono::high_resolution_clock::now();
    auto duration = duration_cast<chrono::milliseconds>(end - start);
    ss << "Time taken: " << duration.count() << " milliseconds!\n";
    for (int i = 1; i <= 10; i++) {
        if (i > sorted_cities.size()) break;
        ss << i << ".) " << sorted_cities[i - 1].first << ", " << sorted_cities[i - 1].second << " sightings\n";
    }
    return ss.str();
}

string UFO_Sightings::get_top_times(const string &sort_type, const int &year) {
    stringstream ss;
    auto start = chrono::high_resolution_clock::now();
    auto sorted_times = get_sorted_time_freq(sort_type, year);
    auto end = chrono::high_resolution_clock::now();
    auto duration = duration_cast<chrono::milliseconds>(end - start);
    ss << "Time taken: " << duration.count() << " milliseconds!\n";
    for (int i = 1; i <= 10; i++) {
        if (i > sorted_times.size()) break;
        ss << i << ".) " << sorted_times[i - 1].first << ", " << sorted_times[i - 1].second << " sightings\n";
    }
    return ss.str();
}

string UFO_Sightings::get_top_locations_at_times(const string &sort_type, const int &year) {
    stringstream ss;
    auto start = chrono::high_resolution_clock::now();
    auto sorted_city_times = get_sorted_city_time_freq(sort_type, year);
    auto end = chrono::high_resolution_clock::now();
    auto duration = duration_cast<chrono::milliseconds>(end - start);
    ss << "Time taken: " << duration.count() << " milliseconds!\n";
    for (int i = 1; i <= 10; i++) {
        if (i > sorted_city_times.size()) break;
        ss << i << ".) " << sorted_city_times[i - 1].first << ", " << sorted_city_times[i - 1].second << " sightings\n";
    }
    return ss.str();
}

string UFO_Sightings::sighting_to_string(const Sighting& s) {
    stringstream ss;
    ss << "Location: " << location_to_string(s) << '\n';
    ss << coordinates_to_string(s) << '\n';
    ss << date_to_string(s) << '\n';
    ss << description_to_string(s) << '\n';
    return ss.str();
}

string UFO_Sightings::location_to_string(const Sighting& s) {
    stringstream ss;
    ss << s.city << ", " << s.state;
    return ss.str();
}

string UFO_Sightings::coordinates_to_string(const Sighting& s) {
    stringstream ss;
    ss << "Latitude " << s.latitude << ", Longitude " << s.longitude;
    return ss.str();
}

string UFO_Sightings::description_to_string(const Sighting& s) {
    stringstream ss;
    ss << "UFO shape: " << s.shape << '\n';
    ss << "Duration: " << s.duration << " seconds\n";
    ss << "Excerpt: " << s.excerpt << '\n';
    return ss.str();
}

string UFO_Sightings::date_to_string(const Sighting& s) {
    stringstream ss;
    ss << "MM/DD/YYYY: " << s.month << " / " << s.day << " / " << s.year << ", ";
    ss << s.hour << ':' << setw(2) << setfill('0') << s.minute;
    return ss.str();
}

string UFO_Sightings::time_to_string(const Sighting& s) {
    stringstream ss;
    ss << s.hour << ':' << setw(2) << setfill('0') << s.minute;
    return ss.str();
}

void UFO_Sightings::tester() {
    cout << "Testing UFO_Sightings*************\n";
    parse_csv();
    cout << get_top_locations("Heap", 0) << '\n';
    cout << get_top_times("Heap", 0) << '\n';
    cout << get_top_locations_at_times("Heap", 0) << '\n';
    cout << "Done testing!*********************\n";
}
