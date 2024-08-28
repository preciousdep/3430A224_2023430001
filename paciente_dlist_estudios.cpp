#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// struct for patient with name and age
struct Patient {
    string name;
    int age;
    // in kg
    int weight;
    // in cm
    int height;
    double bmi = 0.0;
    Patient * next;
};

// print function
void printInfo(const Patient* head) {
    const Patient* current = head;
    while (current != nullptr) {
        cout << current->name << "\nAge: " << current->age 
        << "\nWeight: " << current->weight << "\nHeight: "
        << current->height << "\nBMI: " << current->bmi << "\n";
        current = current->next;
    }
};

// add to list function
void addPatient(Patient*& head, const string& name, int age, int weight, int height) {
    Patient* newPatient = new Patient;
    newPatient -> name = name;
    newPatient -> age = age;
    newPatient -> height = height;
    newPatient -> weight = weight;
    newPatient -> bmi;
    newPatient -> next = head;
    head = newPatient;
};

// remove patient searching by name. caps sensitive
void removePatient(Patient*& head, const string name){ 
    Patient* current = head;
    Patient* previous = nullptr;

    // moves the pointer if the name isn't the one in the search
    while(current != nullptr && current -> name != name){
        previous = current;
        current = current-> next;
    };
    // if the loop breaks, it means the name was found. deletes
    if (current != nullptr){
        if (previous == nullptr) {
            head = current-> next;
        } else {
            previous -> next = current -> next;
        };
        delete current;
    }
};

// calculates bmi for the structs
// using the predefined height and weight
double calculateBMI(Patient*& head){
    Patient* current = head;
    // bmi_total receives a sum of all bmis calculated in the loop
    // and total_people is just the number so that the average can
    // be calculated 
    double bmi_total = 0.0;
    int total_people = 0;
    while (current != nullptr) {
        // multiplied by 10000 because height is used in
        // cm instead of meters
        double bmi_temp = current->weight*10000 / (pow(current->height, 2));
        current->bmi = bmi_temp;
        bmi_total += bmi_temp;
        total_people += 1;
        current = current -> next;
    }
    double bmi_average = bmi_total/total_people;
    return bmi_average;
};

// calculates age average in the list
// using the same logic as the bmi function
double averageAge(Patient*& head){
    Patient* current = head;
    int total_ages = 0;
    int total_people = 0;

    while (current!=nullptr){
        total_ages += current->age;
        total_people += 1;
        current = current -> next;
    }

    double average_age = total_ages/total_people;
    return average_age;
};

// same code as averageAge
double averageWeight(Patient*& head){
    Patient* current = head;
    int total_weight = 0;
    int total_people = 0;

    while (current!=nullptr){
        total_weight += current->weight;
        total_people += 1;
        current = current -> next;
    }

    double average_weight = total_weight/total_people;
    return average_weight;
};

int main() {
    Patient* head = nullptr;
    // add to list
    addPatient(head,"Pepe", 20, 70, 170);
    addPatient(head,"Lisa", 24, 62, 150);
    addPatient(head,"Live", 30, 65, 180);
    
    double bmi_average = calculateBMI(head);
    double age_average = averageAge(head);
    double weight_average = averageWeight(head);

    // printing info
    printInfo(head);

    cout << "Average values:\n" << "BMI: " << bmi_average
    << "\nAge: " << age_average << "\nWeight: " << weight_average
    << "\n";

    // cout << "Insert patient name to delete from list: ";
    // string name_search;
    // cin >> name_search;
    // removePatient(head,name_search);

    // printInfo(head);

    // memory
    while (head != nullptr){
        Patient* temp = head;
        head = head->next;
        delete temp;
    }

}