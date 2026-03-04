#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <limits>

class Contact {
    std::string name_;
    std::string phone_;

    public:
    Contact(const std::string& name, const std::string& phone) : name_(name), phone_(phone){
    }

    Contact() : name_("Книга пуста"), phone_("0"){
    }

    const std::string& GetName() const {
        return name_;
    }

    const std::string& GetPhone() const {
        return phone_;
    }

    void SetPhone(const std::string& new_phone) {
        phone_ = new_phone;
    }

    bool operator<(const Contact& other) const {
        return name_ < other.name_;
    }

};

class AddressBook {
    std::vector<Contact> book_;
    std::string filename_;
    bool is_dirty_ = false;

   public:

    explicit AddressBook(const std::string& file) : filename_(file){
        LoadFromFile(file);
    }

    void AddContact(const std::string& name, const std::string& phone) {
        auto it = std::find_if(book_.begin(), book_.end(), [&name](const Contact& c) {
            return c.GetName() == name;
        });
        if(it == book_.end()){
            book_.emplace_back(name, phone);
        }
        else {
            it->SetPhone(phone);
        }
        is_dirty_ = true;
    }

    void FindName(const std::string& name) {
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

    void Remove(const std::string& name) {
        auto it = std::remove_if(book_.begin(), book_.end(), [&name](const Contact& c){
            return c.GetName() == name;
        });
        if(it != book_.end()) {
            book_.erase(it, book_.end());
            std::cout << "\nКонтакт " << name << " успешно удален.";
            is_dirty_ = true;
        }
        else {
            std::cout << "\nКонтакт не найден!";
        }
    }

    void RemoveAll() {
        book_.clear();
        std::cout << "\nВсе контакты успешно удалены";
        is_dirty_ = true;
    }

    size_t Size() const {
        return book_.size();
    }

    void Print() {
        std::cout << "\nСписок всех контактов: " << '\n';
        for(const Contact& c : book_) {
            std::cout << "ФИО: " << c.GetName() << "- Телефон: " << c.GetPhone() << '\n';
        }
        
    }

    bool LoadFromFile(const std::string& filename) {
        std::ifstream in(filename);
        if (!in) {
            std::cout << "\nНе удалось открыть файл\n";
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

    bool SaveToFile() {

      if (!is_dirty_) {
        return false;
      }
        std::ofstream out(filename_);

        if(!out) {
            return false;
        }

        std::sort(book_.begin(), book_.end());

        for (const auto& c : book_) {
            out << c.GetName() << '|' << c.GetPhone() << '\n';
        }
        is_dirty_ = false;
        return true;
    }

    ~AddressBook() {
        SaveToFile();
    }
};

class GUI {
    
    public:
    AddressBook& book;
    explicit GUI (AddressBook& b) : book(b) {
    }

    void Menu() {
        std::cout << "\nМеню: \n" <<
                "1. Добавить/обновить контакт\n" <<
                "2. Найти контакт\n" <<
                "3. Удалить контакт\n" <<
                "4. Вывести все контакты на экран\n" <<
                "5. Показать размер книги контактов\n" <<
                "6. Удалить все контакты\n" <<
                "7. Exit" << '\n';
    }

    void GAddContact() {
        std::cout << "\nВведите имя" << '\n';
        std::string name;
        std::getline(std::cin, name);
        std::cout << "Введите номер" << '\n';
        std::string phone;
        std::getline(std::cin, phone);
        book.AddContact(name, phone);
        std::cout << "\nУспешно добавлен контакт: " << name << " | " << phone;
    }

    void GFindContact() {
        std::cout << "Введите имя для поиска контакта: " << '\n';
        std::string name;
        std::getline(std::cin, name);
        book.FindName(name);
    }

    void GRemoveContact() {
        std::cout << "\nВведите имя удаляемого контакта: " << '\n';
        std::string name;
        std::getline(std::cin, name);
        book.Remove(name);
    }

    void GRemoveAll() {
        std::cout << "\nВы уверены, что хотите удалить все контакты? Введите 'y' или 'yes'." << '\n';
        std::string answer;
        std::getline(std::cin, answer);
        if (answer == "y" || answer == "yes") {
            book.RemoveAll();
        } else {
            std::cout << "\nВведен неверный символ";
        }

    }

    void GPrintAll() {
        book.Print();
    }

    void PrintSize() {
        std::cout << book.Size() << '\n';
    }
};

int main() {
    std::string filename = "contacts.txt";
    AddressBook book (filename);
    GUI input(book);

    while(true) {
        
        input.Menu();

        int enter = 0;
        std::cin >> enter;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (enter) {
        case 1:
            input.GAddContact();
            break;
        case 2:
            input.GFindContact();
            break;
        case 3:
            input.GRemoveContact();
            break;
        case 4:
            input.GPrintAll();
            break;
        case 5:
            std::cout << book.Size() << '\n';
            break;
        case 6:
            input.GRemoveAll();
            break;   
        case 7:
            return 0;
        default:
            std::cout << "\nНеверный ввод, попробуйте снова.\n";
            break;
        }
        std::cout << '\n';
    }

    return 0;
}