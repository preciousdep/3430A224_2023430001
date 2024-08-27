#include <iostream>
#include <string>
using namespace std;

// struct for patient with name and age
struct Patient {
    std::string name;
    int age;
    // in kg
    int weight;
    // in cm
    int height;
};

void print_info(Patient patient) {
    cout << "Patient \n Name: " 
    << patient.name << "\n Age: " 
    << patient.age << "\n Weight in kg: " 
    << patient.weight << "\n Height in cm: "
    << patient.height;
};

int main() {
// creating patients' info
    Patient pepe = {"Pepe", 20, 70, 170};
    print_info(pepe);
    Patient lisa = {"Lisa", 24, 62, 150};
    print_info(lisa);
    Patient live = {"Live", 30, 65, 180};
    print_info(live);
}