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
    << patient.height << "\n";
};

int main() {
// creating patients' info
    Patient pepe = {"Pepe", 20, 70, 170};
    Patient lisa = {"Lisa", 24, 62, 150};
    Patient live = {"Live", 30, 65, 180};
    
    // create defined size array with existing structs
    Patient patient_array[3] = {pepe, lisa, live};
    print_info(patient_array[0]);
    print_info(patient_array[1]);
    print_info(patient_array[2]);
}