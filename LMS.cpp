#include<iostream>
#include<string>
#include<cstring>

using namespace std;

const int MAX_BOOKS = 100;

struct Book {
    int id;
    char title[100];
    char author[100];
    bool isAvailable;
    char issuedTo[100];
};

class Library {
private:
    Book books[MAX_BOOKS];
    int bookCount;

public:
    Library() : bookCount(0) {}

    void addBook(const Book& newBook) {
        if (bookCount < MAX_BOOKS) {
            books[bookCount++] = newBook;
            cout << "Book added successfully.\n";
        } else {
            cout << "Error: Library is full.\n";
        }
    }

    Book* searchBook(int id) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].id == id) {
                return &books[i];
            }
        }
        return 0;
    }

    Book* searchBook(const char* title) {
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(books[i].title, title) == 0) {
                return &books[i];
            }
        }
        return 0;
    }

    void issueBook(int id, const char* studentName) {
        Book* book = searchBook(id);
        if (book && book->isAvailable) {
            book->isAvailable = false;
            strcpy(book->issuedTo, studentName);
            cout << "Book issued successfully.\n";
        } else if (book) {
            cout << "Book is already issued.\n";
        } else {
            cout << "Book not found.\n";
        }
    }

    void returnBook(int id) {
        Book* book = searchBook(id);
        if (book && !book->isAvailable) {
            book->isAvailable = true;
            book->issuedTo[0] = '\0';
            cout << "Book returned successfully.\n";
        } else if (book) {
            cout << "Book was not issued.\n";
        } else {
            cout << "Book not found.\n";
        }
    }

    void listBooks() {
        if (bookCount == 0) {
            cout << "No books in the library.\n";
            return;
        }
        
        cout << "Library Books:\n";
        for (int i = 0; i < bookCount; i++) {
            cout << "ID: " << books[i].id << ", Title: " << books[i].title 
                 << ", Author: " << books[i].author << ", Status: " 
                 << (books[i].isAvailable ? "Available" : "Issued to ") 
                 << (books[i].isAvailable ? "" : books[i].issuedTo) << "\n";
        }
    }

    void deleteBook(int id) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].id == id) {
                for (int j = i; j < bookCount - 1; j++) {
                    books[j] = books[j + 1];
                }
                bookCount--;
                cout << "Book deleted successfully.\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }
};

int main() {
    Library library;
    int choice;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. List All Books\n";
        cout << "6. Delete Book\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                Book newBook;
                cout << "Enter book ID: ";
                cin >> newBook.id;
                cin.ignore();
                cout << "Enter book title: ";
                cin.getline(newBook.title, 100);
                cout << "Enter book author: ";
                cin.getline(newBook.author, 100);
                newBook.isAvailable = true;
                newBook.issuedTo[0] = '\0';
                library.addBook(newBook);
                break;
            }
            case 2: {
                int searchChoice;
                cout << "Search by:\n1. Title\n2. ID\nEnter your choice: ";
                cin >> searchChoice;
                if (searchChoice == 1) {
                    char title[100];
                    cin.ignore();
                    cout << "Enter book title: ";
                    cin.getline(title, 100);
                    Book* book = library.searchBook(title);
                    if (book) {
                        cout << "Book found:\nID: " << book->id << "\nTitle: " << book->title
                             << "\nAuthor: " << book->author << "\nStatus: " 
                             << (book->isAvailable ? "Available" : "Issued") << "\n";
                    } else {
                        cout << "Book not found.\n";
                    }
                } else if (searchChoice == 2) {
                    int id;
                    cout << "Enter book ID: ";
                    cin >> id;
                    Book* book = library.searchBook(id);
                    if (book) {
                        cout << "Book found:\nID: " << book->id << "\nTitle: " << book->title
                             << "\nAuthor: " << book->author << "\nStatus: " 
                             << (book->isAvailable ? "Available" : "Issued") << "\n";
                    } else {
                        cout << "Book not found.\n";
                    }
                } else {
                    cout << "Invalid choice.\n";
                }
                break;
            }
            case 3: {
                int id;
                char studentName[100];
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter student name: ";
                cin.getline(studentName, 100);
                library.issueBook(id, studentName);
                break;
            }
            case 4: {
                int id;
                cout << "Enter book ID: ";
                cin >> id;
                library.returnBook(id);
                break;
            }
            case 5:
                library.listBooks();
                break;
            case 6: {
                int id;
                cout << "Enter book ID to delete: ";
                cin >> id;
                library.deleteBook(id);
                break;
            }
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
