
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


// CLASS: Patient
class Patient {
public:
    int id;
    string name;
    int age;
    string disease;
    string doctor;

    // Function to take input from user
    void registerPatient() {
        cout << "\n--- Register New Patient ---\n";
        cout << "Enter Patient ID   : "; cin >> id;
        cin.ignore();
        cout << "Enter Patient Name : "; getline(cin, name);
        cout << "Enter Age          : "; cin >> age;
        cin.ignore();
        cout << "Enter Disease      : "; getline(cin, disease);
        cout << "Enter Doctor Name  : "; getline(cin, doctor);
    }

    // Function to display patient info on screen
    void displayPatient() {
        cout << "\n-----------------------------\n";
        cout << "Patient ID   : " << id      << endl;
        cout << "Name         : " << name    << endl;
        cout << "Age          : " << age     << endl;
        cout << "Disease      : " << disease << endl;
        cout << "Doctor       : " << doctor  << endl;
        cout << "-----------------------------\n";
    }

    // Save patient data to file
    void saveToFile() {
        ofstream file("patients.txt", ios::app); // append mode
        if (file.is_open()) {
            file << id << "\n"
                 << name << "\n"
                 << age << "\n"
                 << disease << "\n"
                 << doctor << "\n"
                 << "---\n";
            file.close();
            cout << "\n[SUCCESS] Patient saved to patients.txt\n";
        } else {
            cout << "\n[ERROR] Could not open file!\n";
        }
    }
};


// FUNCTION: Search patient by ID from file
void searchPatientByID(int searchID) {
    ifstream file("patients.txt");

    if (!file.is_open()) {
        cout << "\n[ERROR] No records found. File not found.\n";
        return;
    }

    Patient p;
    bool found = false;
    string line;

    while (file >> p.id) {
        file.ignore();
        getline(file, p.name);
        file >> p.age;
        file.ignore();
        getline(file, p.disease);
        getline(file, p.doctor);
        getline(file, line); // read "---" separator

        if (p.id == searchID) {
            cout << "\n[FOUND] Patient Record:\n";
            p.displayPatient();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n[NOT FOUND] No patient with ID " << searchID << "\n";
    }

    file.close();
}


// FUNCTION: Display ALL patients from file
void displayAllPatients() {
    ifstream file("patients.txt");

    if (!file.is_open()) {
        cout << "\n[ERROR] No records found. File not found.\n";
        return;
    }

    Patient p;
    string line;
    int count = 0;

    cout << "\n===== ALL PATIENT RECORDS =====\n";

    while (file >> p.id) {
        file.ignore();
        getline(file, p.name);
        file >> p.age;
        file.ignore();
        getline(file, p.disease);
        getline(file, p.doctor);
        getline(file, line); // read "---" separator

        p.displayPatient();
        count++;
    }

    if (count == 0) {
        cout << "No patients registered yet.\n";
    } else {
        cout << "\nTotal Patients: " << count << "\n";
    }

    file.close();
}

// ============================================
// MAIN FUNCTION - Menu Driven Program
// ============================================
int main() {
    int choice;

    cout << "========================================\n";
    cout << "   Hospital Patient Registration System  \n";
    cout << "========================================\n";

    do {
        cout << "\n-------- MAIN MENU --------\n";
        cout << "1. Register New Patient\n";
        cout << "2. Search Patient by ID\n";
        cout << "3. Display All Patients\n";
        cout << "4. Exit\n";
        cout << "---------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Patient p;
                p.registerPatient();
                p.displayPatient();
                p.saveToFile();
                break;
            }
            case 2: {
                int id;
                cout << "\nEnter Patient ID to search: ";
                cin >> id;
                searchPatientByID(id);
                break;
            }
            case 3: {
                displayAllPatients();
                break;
            }
            case 4: {
                cout << "\nThank you! Exiting system...\n";
                break;
            }
            default: {
                cout << "\n[INVALID] Please enter 1-4 only.\n";
            }
        }

    } while (choice != 4);

    return 0;
}
// g++ hospital.cpp -o hospital
// ./hospital