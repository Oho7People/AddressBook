#include "GUI.hpp"
#include <limits>
#include <iostream>

int main() {
    AddressBook book ("contacts.txt");
    GUI input(book);

    while(true) {
        
        input.Menu();

        int enter = 0;
        std::cin >> enter;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (enter) {
        case 1:
            input.GAddContact();
            input.Pause();
            break;
        case 2:
            input.GFindContact();
            input.Pause();
            break;
        case 3:
            input.GRemoveContact();
            input.Pause();
            break;
        case 4:
            input.GPrintAll();
            input.Pause();
            break;
        case 5:
            std::cout << book.Size() << '\n';
            input.Pause();
            break;
        case 6:
            input.GRemoveAll();
            input.Pause();
            break;   
        case 7:
            return 0;
        default:
            std::cout << "\nFailed input, check menu cases.\n";
            input.Pause();
            break;
        }
        std::cout << '\n';
    }

    return 0;
}