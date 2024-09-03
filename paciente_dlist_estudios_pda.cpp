#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <queue>
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
    double aic = 0.0;
    double priority= 0.0;
    Patient * next;
};

// print function
void printInfo(const Patient* head) {
    const Patient* current = head;
    while (current != nullptr) {
        cout << current->name << "\nAge: " << current->age 
        << "\nWeight: " << current->weight << "\nHeight: "
        << current->height << "\nBMI: " << current->bmi << "\n"
        << "A1C: " << current->aic << "\n";
        cout << "\n. . . . . . . . . . . . . . . . . .\n";
        current = current->next;
    }
};

// add to list function
void addPatient(Patient*& head, const string& name, int age, int weight, int height, double aic) {
    Patient* newPatient = new Patient;
    newPatient -> name = name;
    newPatient -> age = age;
    newPatient -> height = height;
    newPatient -> weight = weight;
    newPatient -> bmi;
    newPatient -> aic = aic;
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

// imports data from a default file
int importCsv(Patient*& head){
    // keep file in same directory
    string filePath = "patient_list.csv";
    ifstream allData;
    string line = "";
    allData.open(filePath);
    getline(allData,line);
    if (allData.is_open()) {
        while (getline(allData, line)) {
            string name;
            string age, weight, height,aic;
            stringstream ss(line);
            
            // importing in variables and sending them to
            // addPatient
            // the file was modified so that it works with the current
            // code's structure. cm was moved to m and the order was
            // inverted between height and weight
            if (getline(ss, name, ',') &&
                getline(ss, age, ',') &&
                getline(ss, weight, ',') &&
                getline(ss, height, ',') &&
                getline(ss, aic, ',')) {
                // Process the person struct
                addPatient(head,name,stoi(age),stoi(weight),stoi(height),stod(aic));
            }
            calculateBMI(head);
        }
        allData.close();
    } else {
        std::cerr << "Failed to open the file." << std::endl;
    }
    cout << "Imported file successfully!\n";
};

int calcPriority(Patient*& head){
    Patient* current = head;
    while (current != nullptr){
        if (current->aic < 5.7){
            // is used to multiply later and
            // conditioned to be left out so that
            // the priority is 0 if aic is under 5.7
            current -> priority = 0;
        } else if (current -> aic >= 5.7){
            // using their a1c as a starter to multiply by the other params
            // and differentiate between a patient with 5.8 and one with 6.9
            // the value alone defines the risk without a category
            current -> priority = current -> aic;
        };
        // multiplies the a1c value by the bmi and then sums the age
        // to differentiate between patients with the same values
        // but one is maybe 20 and the other is 80
        // and older has a higher priority

        if (current->priority != 0){
            current -> priority = current -> priority * current -> bmi;
            current -> priority += current -> age;
        } else {
            current -> priority = 0;
        }
        current = current -> next;
    }
};

int makeQueue(Patient*& head){
    Patient* current = head;
    int total_length = 0;

    // calculate queue length to iterate over it
    while (current != nullptr){
        total_length += 1;
        current = current->next;
    }

    queue<Patient*> orderedQueue;

    // iterate over the array with known length and add the
    // highest priority to the queue. the highest gets deleted
    // so that it keeps decreasing until there are no patients}
    // with high priority in the array
    for (int i = 0; i < total_length; i++) {
        current = head;
        Patient* prev = nullptr;
        Patient* maxPatient = nullptr;
        Patient* prevMaxPatient = nullptr;

        // this is used to find the patient with the
        // maximum priority
        while (current!= nullptr) {
            if (maxPatient == nullptr || current->priority > maxPatient->priority) {
                maxPatient = current;
                prevMaxPatient = prev;
            }
            prev = current;
            current = current->next;
        };

        // add current patient to the queue
        if (maxPatient != nullptr) {
            if (prevMaxPatient != nullptr) {
                prevMaxPatient->next = maxPatient->next;
            } else {
                // this deletes the max priority patient
                head = maxPatient->next;
            };
            maxPatient->next = nullptr;
            orderedQueue.push(maxPatient);
        };
    };

    //print queue while iterating. it's done in a temporal
    // queue to delete one (pop) by one after it's printed
    queue<Patient*> tempQueue;
    tempQueue = orderedQueue;
    int index = 1;
        while (!tempQueue.empty()) {
            Patient* patient = tempQueue.front();
            std::cout << index << ". " << patient->name 
                  << " | Priority: " << patient->priority 
                  << " | A1C: " << patient->aic << " | BMI: " << patient->bmi << "\n";
            
                  tempQueue.pop();
                  index++;
    }; 

};

int main() {
    Patient* head = nullptr;
    // add to list
    addPatient(head,"Pepe", 20, 70, 170,3.2);
    addPatient(head,"Lisa", 24, 62, 150,5.0);
    addPatient(head,"Live", 30, 65, 180,4.1);
    calculateBMI(head);

    int choice = 0;
    // menu
    while (choice != 0){
        cout << "Menu for list study. . . \n" <<
        "Enter number to choose an option\n" <<
        "1. Show list\n" << "2. Add Patient\n" <<
        "3. Remove Patient\n" << "4. Show Average Age\n"
        << "5. Show Average Weight\n" << "6. Show Average BMI\n"
        << "7. Import data\n" << "8. Calculate Priority and make queue\n" 
        << "9. Exit\n";

        cout << "Choice: \n";
        cin >> choice;

        // validating choice value
        // non-numeric breaks the code
        while (choice != 0 && choice != 1 && choice != 2 && choice != 3
        && choice != 4 && choice != 5 && choice != 6
        && choice != 7 && choice != 8 && choice != 9) {
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
            double aic_input;
            cout << "Enter patient's A1C value \n";
            cin >> aic_input;
            addPatient(head, name_input, age_input, weight_input, height_input, aic_input);
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
            importCsv(head);
        } else if (choice==8){
            calcPriority(head);
            makeQueue(head);
        } else if (choice == 0){
            break;
        };
        
        cout << "\n. . . . . . . . . . . . . . . . . .\n";

    };

    // memory
    while (head != nullptr){
        Patient* temp = head;
        head = head->next;
        delete temp;
    }

}