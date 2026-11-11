
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    // Open the file containing the jokes
    ifstream file("randomJokes.txt");

    if (!file) {
        cout << "Error: Could not open randomJokes.txt\n";
        return 1;
    }

    // Store questions and answers separately
    vector<string> questions, answers;
    string line;

    // Read each joke from the file
    while (getline(file, line)) {
        size_t pos = line.find('?');

        if (pos != string::npos) {
            string question = line.substr(0, pos + 1);
            string answer = line.substr(pos + 1);

            if (!question.empty() && !answer.empty()) {
                questions.push_back(question);
                answers.push_back(answer);
            }
        }
    }

    file.close();

    if (questions.empty()) {
        cout << "No jokes found!\n";
        return 1;
    }

    // Initialise random selection
    srand(time(0));

    string choice;

    // Keep running until the user quits
    while (true) {
        cout << "\nPress Enter for a joke or Q to quit: ";
        getline(cin, choice);

        if (choice == "Q" || choice == "q") {
            break;
        }

        // Select a random joke
        int index = rand() % questions.size();

        cout << "\n" << questions[index] << endl;
        cout << "Press Enter to see the answer...";
        getline(cin, choice);

        cout << answers[index] << endl;
    }

    cout << "\nGoodbye!\n";
    return 0;
}
