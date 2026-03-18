    #include "AddressBook.hpp"
    #include <algorithm>
    #include <iomanip>
    #include <fstream>    
    
    AddressBook::AddressBook(const std::string& file) : filename_(file){
        LoadFromFile(file);
    }

    void AddressBook::AddContact(const std::string& name, const std::string& phone) {
        auto it = std::find_if(book_.begin(), book_.end(), [&name](const Contact& c) {
            return c.GetName() == name;
        });
        if(it == book_.end()){
            book_.emplace_back(name, phone);
        }
        else {
            it->SetPhone(phone);
        }

        std::sort(book_.begin(), book_.end());

        is_dirty_ = true;
    }

    void AddressBook::FindName(const std::string& name) {
        auto it = std::find_if(book_.begin(), book_.end(), [&name](const Contact& c) {
            return c.GetName() == name;
        });

        if(it != book_.end()) {
            std::cout << "\nFounded: " <<it->GetName() << ": " << it->GetPhone() << '\n';
        }
        else {
            std::cout << "\nContact not found" << '\n';
        }
    }

    void AddressBook::Remove(const std::string& name) {
        auto it = std::remove_if(book_.begin(), book_.end(), [&name](const Contact& c){
            return c.GetName() == name;
        });
        if(it != book_.end()) {
            book_.erase(it, book_.end());
            std::cout << "\nContact " << name << " has been deleted succesfully.";
            is_dirty_ = true;
        }
        else {
            std::cout << "\nContact not found!";
        }
    }

    void AddressBook::RemoveAll() {
        book_.clear();
        std::cout << "\nAll contacts have been deleted succesfully";
        is_dirty_ = true;
    }

    size_t AddressBook::Size() const {
        return book_.size();
    }

    void AddressBook::Print() {

        if (book_.empty()) {
            std::cout << "\nAddress Book is empty";
        }
        else {
            std::cout << std::left
            << std::setw(25) << "\nName"
            << std::setw(15) << "Phone" << '\n';

            std::cout << "----------------------------------------\n";

            for (const Contact& c : book_) {
                std::cout << std::left
                << std::setw(20) << c.GetName()
                << std::setw(15) << c.GetPhone()
                << '\n';
            }
        }
    }

    bool AddressBook::LoadFromFile(const std::string& filename) {
        book_.clear();

        std::ifstream in(filename);
        if (!in) {
            std::cout << "\nFailed to open file\n";
            return false;
        }

        std::string line;

        while(std::getline(in, line)) {
            if(line.empty()) {
                continue;
            }
            auto sep = line.find('|');
            if(sep == std::string::npos) {
                continue;
            }

            std::string name = line.substr(0, sep);
            std::string phone = line.substr(sep + 1);

            if(name.empty() || phone.empty()) {
                continue;
            }

            book_.emplace_back(name, phone);
        }
        is_dirty_ = false;

        return true;

    }

    bool AddressBook::SaveToFile() {

      if (!is_dirty_) {
        return false;
      }
        std::ofstream out(filename_);

        if(!out) {
            return false;
        }

        for (const auto& c : book_) {
            out << c.GetName() << '|' << c.GetPhone() << '\n';
        }
        is_dirty_ = false;
        return true;
    }

    AddressBook::~AddressBook() {
        SaveToFile();
    }