#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct Contact {
    std::string name;
    std::string phone;
    std::string email;
};

class ContactManager {
public:
    void addContact(const Contact& contact) {
        contacts.push_back(contact);
    }

    void deleteContact(const std::string& name) {
        contacts.erase(std::remove_if(contacts.begin(), contacts.end(),
            [&name](const Contact& c) { return c.name == name; }), contacts.end());
    }

    Contact* findContact(const std::string& name) {
        for (auto& contact : contacts) {
            if (contact.name == name) {
                return &contact;
            }
        }
        return nullptr;
    }

    void updateContact(const std::string& name, const Contact& updatedContact) {
        for (auto& contact : contacts) {
            if (contact.name == name) {
                contact = updatedContact;
                break;
            }
        }
    }

    void saveToFile(const std::string& filename) {
        std::ofstream outFile(filename);
        for (const auto& contact : contacts) {
            outFile << contact.name << ',' << contact.phone << ',' << contact.email << '\n';
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        Contact contact;
        while (inFile >> contact.name >> contact.phone >> contact.email) {
            contacts.push_back(contact);
        }
    }

    void showContacts() const {
        for (const auto& contact : contacts) {
            std::cout << "Имя: " << contact.name << ", Телефон: " << contact.phone << ", Email: " << contact.email << '\n';
        }
    }

private:
    std::vector<Contact> contacts;
};

void showMenu() {
    std::cout << "1. Добавить контакт\n";
    std::cout << "2. Удалить контакт\n";
    std::cout << "3. Найти контакт\n";
    std::cout << "4. Изменить контакт\n";
    std::cout << "5. Показать все контакты\n";
    std::cout << "6. Сохранить контакты в файл\n";
    std::cout << "7. Загрузить контакты из файла\n";
    std::cout << "0. Выход\n";
}

int main() {
    ContactManager manager;
    int choice;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Contact contact;
                std::cout << "Введите имя, телефон и email: ";
                std::cin >> contact.name >> contact.phone >> contact.email;
                manager.addContact(contact);
                break;
            }
            case 2: {
                std::string name;
                std::cout << "Введите имя контакта для удаления: ";
                std::cin >> name;
                manager.deleteContact(name);
                break;
            }
            case 3: {
                std::string name;
                std::cout << "Введите имя контакта для поиска: ";
                std::cin >> name;
                Contact* contact = manager.findContact(name);
                if (contact) {
                    std::cout << "Найден контакт: Имя: " << contact->name << ", Телефон: " << contact->phone << ", Email: " << contact->email << '\n';
                } else {
                    std::cout << "Контакт не найден.\n";
                }
                break;
            }
            case 4: {
                std::string name;
                std::cout << "Введите имя контакта для изменения: ";
                std::cin >> name;
                Contact* contact = manager.findContact(name);
                if (contact) {
                    Contact updatedContact;
                    std::cout << "Введите новое имя, телефон и email: ";
                    std::cin >> updatedContact.name >> updatedContact.phone >> updatedContact.email;
                    manager.updateContact(name, updatedContact);
                } else {
                    std::cout << "Контакт не найден.\n";
                }
                break;



            }
            case 5:
                manager.showContacts();
                break;
            case 6: {
                manager.saveToFile("contacts.txt");
                std::cout << "Контакты сохранены в файл.\n";
                break;
            }
            case 7: {
                manager.loadFromFile("contacts.txt");
                std::cout << "Контакты загружены из файла.\n";
                break;
            }
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор.\n";
        }
    } while (choice != 0);

    return 0;
}
