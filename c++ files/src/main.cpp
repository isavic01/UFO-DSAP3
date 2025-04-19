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
    cout<<"Thank you! \n";
    cout<<   " .  _ -  __   -_ --_  -  _..-=*****=-.._       "     << '\n';
    cout<< R"(     .   - _ -  -.   ,._/`.   ,   ,   .`\_.,  )"     << '\n';
    cout<<   " -  .   _ -   -.__  (.,    UFO Hunters    ,.)  "     << '\n';
    cout<<   "    -     - __   _.-  `^-=-=-=*=*=*=-=-=-^`    "     << '\n';
    cout<< R"(                                              )"     << '\n';
    cout<< R"(_.._______,....,___._____________,_____,_.___)"     << "\n";
    cout<< R"(____,__ .` .,.  ; _____,.__,__.____.___.______)"     << "\n";
    cout<< R"(_,_.,___`,...,,`__.________,_____,____________)"     << "\n\n";
}

int prompt_menu() {
    cout<< "  0.) Exit program" << '\n';
    cout<< "  1.) Find CITIES with MOST alien sightings" << '\n';
    cout<< "  2.) Find TIMES with MOST alien sightings" << '\n';
    cout<< "  3.) Find CITIES with LEAST alien sightings" << '\n';
    cout<< "  4.) Find TIMES with LEAST alien sightings" << '\n';
    cout<< "Please select an option from above (0-4) :  ";
    int input;
    cin >> input;
    while (input < 0 || input > 4) {
        cout<<"    Invalid input! please try again (0-4): ";
        cin >> input;
    }
    return input;
}
int prompt_year() {
    cout<<"  Enter a year to search (1942-2014) or search all time (0) : ";
    int year;
    cin >> year;
    while ( year!=0 && (year < 1942 || year > 2014) ) {
        cout<<"    Invalid input! please try again (1942-2014 / 0) : ";
        cin >> year;
    }
    return year;
}
string prompt_sort_type() {
    cout<<"  Select whether to use Heap Sort (0) or Shell Sort (1) : ";
    int input;
    cin >> input;
    while (input!=1 && input!=0) {
        cout<<"    Invalid input! please try again (0/1): ";
        cin >> input;
    }
    return input == 0 ? "Heap" : "Shell";
}

int main() {
    UFO_Sightings UFO_S;
    UFO_S.parse_csv("../data/ufo_sightings.csv");
    //UFO_S.tester();

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
            cout<<"  " << sort_type << " sort took " << duration.count() << " milliseconds!\n";

            std::cout<<"Top 10 cities with most sightings: \n";
            for (int i = 1; i <= 10; i++) {
                if (i>sorted_cities.size()) break;
                std::cout<<"  " << i << ".) "<< sorted_cities[i-1].first << ", " <<
                    sorted_cities[i-1].second << " sightings\n";
            }
        }
        else if (input == 2) {

        }
        else if (input == 3) {

        }
        else if (input == 4) {

        }
        else {

        }
        cout<< R"(____________________________________________)"     << "\n\n";
    }
    print_exit();

    return 0;
}
