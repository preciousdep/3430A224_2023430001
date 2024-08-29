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
void removePatient(Patient*& head){ 
    Patient* current = head;
    Patient* previous = nullptr;
    string name;
    cout << "Enter the name of the patient to remove... \n";
    cin >> name;

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
    calculateBMI(head);
    
    int choice = 0;
    // menu
    while (choice != 7){
        cout << "Menu for list study. . . \n" <<
        "Enter number to choose an option\n" <<
        "1. Show list\n" << "2. Add Patient\n" <<
        "3. Remove Patient\n" << "4. Show Average Age\n"
        << "5. Show Average Weight\n" << "6. Show Average BMI\n"
        << "7. Exit\n";

        cout << "Choice: \n";
        cin >> choice;

        // validating choice value
        // non-numeric breaks the code
        while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7) {
            cout << "Enter the desired option: \n";
            cin >> choice;
        }

        if (choice == 1){   
            printInfo(head);
        } else if (choice ==2){
            // receives input for a new struct
            cout << "Enter patient's name...\n";
            string name_input;
            cin >> name_input;
            cout << "Enter patient's age...\n";
            int age_input;
            cin >> age_input;
            cout << "Enter patient's weight in kg...\n";
            int weight_input;
            cin >> weight_input;
            cout << "Enter patient's height in cm...\n";
            int height_input;
            cin >> height_input;
            addPatient(head, name_input, age_input, weight_input, height_input);
            cout << "Added!\n";
        } else if (choice ==3){
            removePatient(head);
        } else if (choice == 4) {
            double average_age = averageAge(head);
            // calls the function and then prints it
            cout << "Average age in list: " << average_age << "\n";
        } else if (choice ==5) {
            double average_weight = averageWeight(head);
            cout << "Average weight in list: " << average_weight << "\n";
        } else if (choice == 6) {
            double average_bmi = calculateBMI(head);
            cout << "Average BMI in list: " << average_bmi << "\n";
        } else if (choice == 7) {
            break;
        };

    };



    // memory
    while (head != nullptr){
        Patient* temp = head;
        head = head->next;
        delete temp;
    }

}