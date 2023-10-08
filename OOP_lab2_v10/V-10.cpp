#include <iostream>
#include <string>
#include <map>

// klas SIMCard predstavlyaye sim-kartu dlya telefonu
class SIMCard {
private:
    std::string number; // nomer sim karty
    double balance;    // balans sim karty

public:
    // konstruktor klasu SIMCard
    SIMCard(const std::string& num, double bal) : number(num), balance(bal) {}

    // metod dlya otrymannya balansu sim karty
    double get_balance() {
        return balance;
    }

    // metod dlya popovnennya balansu sim karty na yakusʹ sumu
    void top_up_balance(double amount) {
        balance += amount;
    }

    // metod podzvonyty z sim karty
    void make_call(const std::string& recipient_number, double duration) {
        if (balance >= duration) {
            balance -= duration;
            std::cout << "Dzvinok " << recipient_number << " tryvalostyu " << duration << " khvylyn..." << std::endl;
        }
        else {
            std::cout << "Nedostatnʹo balansu dlya zdiysnennya dzvinka." << std::endl;
        }
    }
};

// klas PhoneBook predstavlyaye telefonnu knyhu dlya zberihannya kontaktiv
class PhoneBook {
private:
    std::map<std::string, std::string> contacts; // kontakty z imenamy ta nomeramy

public:
    // metod dlya dodavannya kontaktu do telefonnoyi knyhy
    void add_contact(const std::string& name, const std::string& number) {
        contacts[name] = number;
    }

    // metod dlya redahuvannya nomera kontaktu
    void edit_contact(const std::string& name, const std::string& new_number) {
        if (contacts.find(name) != contacts.end()) {
            contacts[name] = new_number;
            std::cout << "kontakt " << name << " onovleno novym nomerom: " << new_number << std::endl;
        }
        else {
            std::cout << "kontakt " << name << " ne znaydeno v telefonniy knyzi." << std::endl;
        }
    }

    // metod dlya otrymannya nomera kontaktu za imenem
    std::string get_contact_number(const std::string& name) {
        if (contacts.find(name) != contacts.end()) {
            return contacts[name];
        }
        else {
            return "";
        }
    }
};

// klas Account predstavlyaye bankivsʹkyy rakhunok korystuvacha
class Account {
private:
    std::string account_number; // nomer rakhunku
    double balance;            // balans rakhunku

public:
    // konstruktor klasu Account
    Account(const std::string& acc_num, double initial_balance) : account_number(acc_num), balance(initial_balance) {}

    // metod dlya otrymannya balansu rakhunku
    double get_balance() {
        return balance;
    }

    // metod popovnennya balansu rakhunku na pevnu sumu
    void top_up_balance(double amount) {
        balance += amount;
    }
};

// klas MobilePhone predstavlyaye mobilʹnyy telefon iz sim kartoyu telefonnoyu knyhoyu ta bankivsʹkym rakhunkom
class MobilePhone {
private:
    SIMCard sim_card;      // sim karta telefonu
    PhoneBook phone_book;  // telefonna knyha
    Account account;       // bankivsʹkyy rakhunok

public:
    // konstruktor klasu MobilePhone
    MobilePhone(SIMCard sim, PhoneBook book, Account acc) : sim_card(sim), phone_book(book), account(acc) {}

    // metod dlya zdiysnennya dzvinka za im'yam kontaktu
    void make_call(const std::string& recipient_name, double duration) {
        std::string recipient_number = phone_book.get_contact_number(recipient_name);
        if (!recipient_number.empty()) {
            sim_card.make_call(recipient_number, duration);
        }
        else {
            std::cout << "kontakt " << recipient_name << " ne znaydeno v telefonniy knyzi." << std::endl;
        }
    }

    // metod dlya perevirky balansu sim karty
    double check_balance() {
        return sim_card.get_balance();
    }

    // metod popovnennya balansu bankivsʹkoho rakhunku ta sim karty
    void top_up_balance(double amount) {
        account.top_up_balance(amount);
        sim_card.top_up_balance(amount);
        std::cout << "Balans rakhunku popovneno na " << amount << "." << std::endl;
    }
};

int main() {
    SIMCard sim_card("123456789", 50);
    PhoneBook phone_book;
    phone_book.add_contact("Yaroslav", "+380931755115");
    phone_book.add_contact("Olya", "+380931755422");
    Account account("12345", 100);

    MobilePhone mobile_phone(sim_card, phone_book, account);

    mobile_phone.make_call("Yaroslav", 5);
    mobile_phone.make_call("Mykhaylo", 10);  // neisnuyuchyy kontakt

    std::cout << "Balans na rakhunku: $" << mobile_phone.check_balance() << std::endl;
    mobile_phone.top_up_balance(20);
    std::cout << "Balans rakhunku pislya popovnennya: $" << mobile_phone.check_balance() << std::endl;

    return 0;
}
