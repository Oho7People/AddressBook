#include "GUI.hpp"    

    GUI::GUI (AddressBook& b) : book(b) {
    }

    void GUI::Menu() {
        std::cout << "\nMenu: \n" <<
                "1. Add/Update contact\n" <<
                "2. Find contact\n" <<
                "3. Delete contact\n" <<
                "4. Show all contacts on screen\n" <<
                "5. Show Address Book size\n" <<
                "6. Delete all contacts\n" <<
                "7. Exit" << '\n';
    }

    void GUI::GAddContact() {
        std::cout << "\nInput a name" << '\n';
        std::string name;
        std::getline(std::cin, name);
        std::cout << "Input a phone number" << '\n';
        std::string phone;
        std::getline(std::cin, phone);
        book.AddContact(name, phone);
        std::cout << "\nContact has been added succesfully: " << name << " | " << phone;
    }

    void GUI::GFindContact() {
        std::cout << "Input a name to find contact: " << '\n';
        std::string name;
        std::getline(std::cin, name);
        book.FindName(name);
    }

    void GUI::GRemoveContact() {
        std::cout << "\nInput a name to delete: " << '\n';
        std::string name;
        std::getline(std::cin, name);
        book.Remove(name);
    }

    void GUI::GRemoveAll() {
        std::cout << "\nAre you sure to delete ALL contacts? Input 'y' or 'yes'. To cancel, input 'b'" << '\n';
        std::string answer;
        std::getline(std::cin, answer);
        if (answer == "y" || answer == "yes") {
            book.RemoveAll();
        } else if (answer == "b") {
            return;
        }
        else {
            std::cout << "\nFailed input";
        }

    }

    void GUI::GPrintAll() {
        book.Print();
    }

    void GUI::Pause() {
        std::cout << "\nPress Enter to continue..." << '\n';
        std::cin.get();
    }

