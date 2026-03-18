#include "AddressBook.hpp"

class GUI {
    
    public:
    AddressBook& book;

    explicit GUI (AddressBook& b);

    void Menu();
    void GAddContact();
    void GFindContact();
    void GRemoveContact();
    void GRemoveAll();
    void GPrintAll();
    void Pause();
};