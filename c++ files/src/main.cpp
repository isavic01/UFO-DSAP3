#include <iostream>
#include "UFO_Sightings.h"

using namespace std;

void print_intro() {
    cout<<   "     _..-=*****=-.._       "     << '\n';
    cout<< R"( ,._/`.   ,   ,   .`\_.,  )"     << '\n';
    cout<<   "(.,    UFO Hunters    ,.)  "     << '\n';
    cout<<   "  `^-=-=-=*=*=*=-=-=-^`    "     << '\n';
    cout<< R"(          )/|\(           )"     << '\n';
    cout<< R"(_.._______)/|\(_____._____________,_____,_.___)"     << "\n";
    cout<< R"(____,_____)/|\(________,.__,__.____.___.______)"     << "\n";
    cout<< R"(_,_.,_______,.____.________,_____,____________)"     << "\n\n";
}
void print_exit() {
    cout<< "\n\n************=- exiting program! -=*************\n\n\n" ;
    cout<<   " .  _ -  __   -_ --_  -  _..-=*****=-.._       "     << '\n';
    cout<< R"(     .   - _ -  -.   ,._/`.   ,   ,   .`\_.,  )"     << '\n';
    cout<<   " -  .   _ -   -.__  (.,    UFO Hunters    ,.)  "     << '\n';
    cout<<   "    -     - __   _.-  `^-=-=-=*=*=*=-=-=-^`    "     << '\n';
    cout<< R"(                                              )"     << '\n';
    cout<< R"(_.._______,....,___._____________,_____,_.____)"     << "\n";
    cout<< R"(____,__ .` .,.  ; _____,.__,__.____.___.______)"     << "\n";
    cout<< R"(_,_.,___`,...,,`__.________,_____,____________)"     << "\n\n";
}

int prompt_menu() {
    cout<< "  0.) Exit program" << '\n';
    cout<< "  1.) Find CITIES with MOST alien sightings" << '\n';
    cout<< "  2.) Find TIMES with MOST alien sightings" << '\n';
    cout<< "  3.) Find CITIES with LEAST alien sightings" << '\n';
    cout<< "  4.) Find TIMES with LEAST alien sightings" << "\n";
    cout<< "  5.) Find CITIES & TIMES with MOST alien sightings" << '\n';
    cout<< "  6.) Find CITIES & TIMES with LEAST alien sightings" << "\n\n";
    cout<< "Please select an option from above (0-6) : ";
    int input;
    cin >> input;
    while (input < 0 || input > 6) {
        cout<<"  --Invalid input! please try again (0-6): ";
        cin >> input;
    }
    return input;
}
int prompt_year() {
    cout<<" >Enter a year to search (1942-2014) or search all time (0) : ";
    int year;
    cin >> year;
    while ( year!=0 && (year < 1942 || year > 2014) ) {
        cout<<"  --Invalid input! please try again (1942-2014 / 0) : ";
        cin >> year;
    }
    return year;
}
string prompt_sort_type() {
    cout<<" >Select whether to use Heap Sort (0) or Shell Sort (1) : ";
    int input;
    cin >> input;
    while (input!=1 && input!=0) {
        cout<<"  --Invalid input! please try again (0/1): ";
        cin >> input;
    }
    cout<<'\n';
    return input == 0 ? "Heap" : "Shell";
}

int main() {
    UFO_Sightings UFO_S;
    //UFO_S.tester();  // currently testing the 3 strings formatted for the frontend boxes
    UFO_S.parse_csv("../data/ufo_sightings.csv");

    print_intro();
    while ( true ) {
        int input = prompt_menu();

        if (input == 0) break;
        if (input == 1) {
            int year = prompt_year();
            string sort_type = prompt_sort_type();

            auto start = chrono::high_resolution_clock::now();
            auto sorted_cities = UFO_S.get_sorted_city_freq(sort_type, year);
            auto end = chrono::high_resolution_clock::now();
            auto duration = duration_cast<chrono::milliseconds>(end - start);
            cout<< sort_type << " sort took " << duration.count() << " milliseconds!\n";

            std::cout<<"Top 10 cities with most sightings: \n";
            for (int i = 1; i <= 10; i++) {
                if (i>sorted_cities.size()) break;  // check for years w/ less than 10 sightings
                std::cout<<"  " << i << ".) "<< sorted_cities[i-1].first << ", " <<
                    sorted_cities[i-1].second << " sightings\n";
            }
        }
        else if (input == 2) {
            int year = prompt_year();
            string sort_type = prompt_sort_type();

            auto start = chrono::high_resolution_clock::now();
            auto sorted_times = UFO_S.get_sorted_time_freq(sort_type, year);
            auto end = chrono::high_resolution_clock::now();
            auto duration = duration_cast<chrono::milliseconds>(end - start);
            cout<< sort_type << " sort took " << duration.count() << " milliseconds!\n";

            std::cout<<"Top 10 times with most sightings: \n";
            for (int i = 1; i <= 10; i++) {
                if (i>sorted_times.size()) break;  // check for years w/ less than 10 sightings
                std::cout<< i << ".) "<< sorted_times[i-1].first << ", " <<
                    sorted_times[i-1].second << " sightings\n";
            }
        }
        else if (input == 3) {
            int year = prompt_year();
            string sort_type = prompt_sort_type();

            auto start = chrono::high_resolution_clock::now();
            auto sorted_cities = UFO_S.get_sorted_city_freq(sort_type, year);
            auto end = chrono::high_resolution_clock::now();
            auto duration = duration_cast<chrono::milliseconds>(end - start);
            cout<< sort_type << " sort took " << duration.count() << " milliseconds!\n";

            std::cout<<"Top 10 cities with fewest sightings: \n";
            for (int i = 1; i <= 10; i++) {
                int n = sorted_cities.size();
                if (i>n) break;  // check for years w/ less than 10 sightings
                std::cout<<"  " << i << ".) "<< sorted_cities[n-i].first << ", " <<
                    sorted_cities[n-1].second << " sightings\n";
            }
        }
        else if (input == 4) {
            int year = prompt_year();
            string sort_type = prompt_sort_type();

            auto start = chrono::high_resolution_clock::now();
            auto sorted_times = UFO_S.get_sorted_time_freq(sort_type, year);
            auto end = chrono::high_resolution_clock::now();
            auto duration = duration_cast<chrono::milliseconds>(end - start);
            cout<<sort_type << " sort took " << duration.count() << " milliseconds!\n";

            std::cout<<"Top 10 times with fewest sightings: \n";
            for (int i = 1; i <= 10; i++) {
                int n = sorted_times.size();
                if (i>n) break;  // check for years w/ less than 10 sightings
                std::cout<< i << ".) "<< sorted_times[n-i].first << ", " <<
                    sorted_times[n-i].second << " sightings\n";
            }
        }
        else if (input == 5) {
            int year = prompt_year();
            string sort_type = prompt_sort_type();

            auto start = chrono::high_resolution_clock::now();
            auto sorted_city_times = UFO_S.get_sorted_city_time_freq(sort_type, year);
            auto end = chrono::high_resolution_clock::now();
            auto duration = duration_cast<chrono::milliseconds>(end - start);
            cout<< sort_type << " sort took " << duration.count() << " milliseconds!\n";

            std::cout<<"Top 10 cities & times with most sightings: \n";
            for (int i = 1; i <= 10; i++) {
                if (i>sorted_city_times.size()) break;  // check for years w/ less than 10 sightings
                std::cout<< i << ".) "<< sorted_city_times[i-1].first << ", " <<
                    sorted_city_times[i-1].second << " sightings\n";
            }
        }
        else if (input == 6) {
            int year = prompt_year();
            string sort_type = prompt_sort_type();

            auto start = chrono::high_resolution_clock::now();
            auto sorted_city_times = UFO_S.get_sorted_city_time_freq(sort_type, year);
            auto end = chrono::high_resolution_clock::now();
            auto duration = duration_cast<chrono::milliseconds>(end - start);
            cout<<sort_type << " sort took " << duration.count() << " milliseconds!\n";

            std::cout<<"Top 10 cities & times with fewest sightings: \n";
            for (int i = 1; i <= 10; i++) {
                int n = sorted_city_times.size();
                if (i>n) break;  // check for years w/ less than 10 sightings
                std::cout<< i << ".) "<< sorted_city_times[n-i].first << ", " <<
                    sorted_city_times[n-i].second << " sightings\n";
            }
        }
        cout<< "\n\n********************************************\n\n\n" ;
    }
    print_exit();

    return 0;
}
