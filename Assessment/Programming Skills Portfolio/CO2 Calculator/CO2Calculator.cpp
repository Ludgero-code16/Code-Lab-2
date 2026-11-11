
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    // Approximate emission factors in kg CO2e per unit
    const double transport[] = {0.20, 0.10, 0.04, 0.25};
    const string names[] = {"Car", "Bus", "Train", "Flight"};

    string choice, type;
    double amount, factor;

    // Main menu repeats until the user exits
    while (true) {
        cout << "\n===== CO2 CALCULATOR =====\n";
        cout << "1. Transport emissions\n";
        cout << "2. Electricity emissions\n";
        cout << "3. Book printing emissions\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        getline(cin, choice);

        if (choice == "4") {
            cout << "Goodbye!\n";
            break;
        }

        // Select the correct emission factor
        if (choice == "1") {
            cout << "\n1. Car\n2. Bus\n3. Train\n4. Flight\n";
            cout << "Choose transport: ";
            getline(cin, type);

            if (type.size() != 1 ||
                type[0] < '1' || type[0] > '4') {
                cout << "Invalid transport choice.\n";
                continue;
            }

            int index = type[0] - '1';
            factor = transport[index];
            cout << "Enter distance in km: ";
        }
        else if (choice == "2") {
            factor = 0.40;
            cout << "Enter electricity usage in kWh: ";
        }
        else if (choice == "3") {
            factor = 0.0007;
            cout << "Enter number of pages: ";
        }
        else {
            cout << "Invalid option. Try again.\n";
            continue;
        }

        // Read and validate the amount entered
        string input;
        getline(cin, input);

        try {
            size_t pos;
            amount = stod(input, &pos);

            if (pos != input.size() || amount < 0 ||
                (choice == "3" && amount != (int)amount)) {
                cout << "Invalid amount.\n";
                continue;
            }
        }
        catch (...) {
            cout << "Please enter a valid number.\n";
            continue;
        }

        // Calculate and display estimated emissions
        double result = amount * factor;

        cout << fixed << setprecision(4);
        cout << "Estimated emissions: "
             << result << " kg CO2e\n";
    }

    return 0;
}
