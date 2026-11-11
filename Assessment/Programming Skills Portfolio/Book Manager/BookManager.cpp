
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

// Class to store the details of each book
class Book {
public:
    string title, author, bookID, availability;
    int pages;

    // Constructor to create a book
    Book(string t, string a, int p, string id, string av) {
        title = t;
        author = a;
        pages = p;
        bookID = id;
        availability = av;
    }

    // Display the book information
    void display() const {
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nPages: " << pages;
        cout << "\nBook ID: " << bookID;
        cout << "\nAvailability: " << availability << "\n";
    }
};

// Convert text to lowercase for searching
string lowerText(string text) {
    transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c) { return tolower(c); });
    return text;
}

// Read the books from the text file
vector<Book> loadBooks() {
    vector<Book> books;
    ifstream file("bookData.txt");
    string line;

    if (!file) {
        cout << "Error: bookData.txt not found!\n";
        return books;
    }

    // Read each line and separate the book details
    while (getline(file, line)) {
        stringstream ss(line);
        string title, author, pages, id, available;

        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, pages, ',');
        getline(ss, id, ',');
        getline(ss, available);

        // Check that all fields contain information
        if (!title.empty() && !author.empty() &&
            !pages.empty() && !id.empty() &&
            !available.empty()) {
            try {
                books.emplace_back(title, author,
                    stoi(pages), id, available);
            }
            catch (...) {
                // Skip records with invalid page numbers
            }
        }
    }

    return books;
}

int main() {
    // Load the books into a vector
    vector<Book> books = loadBooks();
    string choice;

    if (books.empty()) {
        cout << "No books available to display.\n";
        return 1;
    }

    // Keep displaying the menu until the user exits
    while (true) {
        cout << "\n===== BOOK MANAGER =====\n";
        cout << "1. View all books\n";
        cout << "2. Search for a book\n";
        cout << "3. View available books\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        getline(cin, choice);

        if (choice == "1") {
            // Display every book
            for (const Book& book : books) {
                book.display();
            }
        }
        else if (choice == "2") {
            // Search without case sensitivity
            string search;
            bool found = false;

            cout << "Enter book title: ";
            getline(cin, search);

            for (const Book& book : books) {
                if (lowerText(book.title).find(
                    lowerText(search)) != string::npos) {
                    book.display();
                    found = true;
                }
            }

            if (!found) {
                cout << "Book not found.\n";
            }
        }
        else if (choice == "3") {
            // Display books marked as available
            bool found = false;

            for (const Book& book : books) {
                string status = lowerText(book.availability);

                if (status == "available" ||
                    status == "yes" || status == "true") {
                    book.display();
                    found = true;
                }
            }

            if (!found) {
                cout << "No available books found.\n";
            }
        }
        else if (choice == "4") {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
