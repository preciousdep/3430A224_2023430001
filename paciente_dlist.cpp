#include <iostream>
#include <string>
using namespace std;

// struct for patient with name and age
struct Patient {
    string name;
    int age;
    // in kg
    int weight;
    // in cm
    int height;
    Patient * next;
};


// print function
void printInfo(const Patient* head) {
    const Patient* current = head;
    while (current != nullptr) {
        cout << current->name << "\nAge: " << current->age 
        << "\nWeight: " << current->weight << "\nHeight: "
        << current->height << "\n";
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
    newPatient -> next = head;
    head = newPatient;
};

// remove patient searching by name 
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

int main() {
    Patient* head = nullptr;
    // add to list
    addPatient(head,"Pepe", 20, 70, 170);
    addPatient(head,"Lisa", 24, 62, 150);
    addPatient(head,"Live", 30, 65, 180);

    // printing info
    printInfo(head);

    cout << "Insert patient name to delete from list: ";
    string name_search;
    cin >> name_search;
    removePatient(head,name_search);

    printInfo(head);

    // memory
    while (head != nullptr){
        Patient* temp = head;
        head = head->next;
        delete temp;
    }

}