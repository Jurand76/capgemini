#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <iomanip> 
#include <cmath>

using namespace std;

struct Phone {
    string brand;
    string model;
    string form_factor;
    int year;
    float screen_size;
    float price;
};

vector<Phone> phones;
map<string, int> brand_count;

void emptyLine() {
    cout << endl;
}

void addPhone() {
    Phone p;
    emptyLine();
    cout << "Enter brand name                 : ";
    cin >> p.brand;
    cout << "Enter model name                 : ";
    cin >> p.model;
    cout << "Enter form factor (example: blue): ";
    cin >> p.form_factor;
    cout << "Enter year of issue              : ";
    cin >> p.year;
    cout << "Enter screen size (example: 5.2) : ";
    cin >> p.screen_size;
    cout << "Enter price (example: 140.8)     : ";
    cin >> p.price;
    phones.push_back(p);      // add phone parameters to vector
    brand_count[p.brand]++;   // add phone brand to brand list
    emptyLine();
    cout << "Phone added successfully!";
    emptyLine();
}

void deletePhone() {
    int index;
    cout << "Enter index of phone to delete: ";
    cin >> index;
    if (index < 0 || index >= phones.size()) {
        cout << "Invalid index!" << endl;
        return;
    }
    brand_count[phones[index].brand]--;
    phones.erase(phones.begin() + index);
    cout << "Phone deleted successfully!" << endl;
}

void showAllPhones() {
    string fullSpec, sizeText, priceText;
    int index = 0;
    cout << "LIST OF PHONES WITH INDEX" << endl << endl;
    for (Phone p : phones) {
        sizeText = to_string(p.screen_size).substr(0, to_string(p.screen_size).find(".") + 3);
        priceText = to_string(p.price).substr(0, to_string(p.price).find(".") + 3);
        fullSpec = p.brand + " " + p.model + " " + to_string(p.year) + " year, form factor: " + p.form_factor + ", screen size: " + sizeText + "', price: " + priceText + "$";
        cout << to_string(index) << ". " << (fullSpec);
        emptyLine();
        index++;
    }
}

void showAllByBrand() {
    string brand;
    string fullSpec, sizeText, priceText;
    cout << "Enter brand name: ";
    cin >> brand;
    cout << "Phones by brand " << brand << ":" << endl << endl;
    for (Phone p : phones) {
        if (p.brand == brand) {
            sizeText = to_string(p.screen_size).substr(0, to_string(p.screen_size).find(".") + 3);
            priceText = to_string(p.price).substr(0, to_string(p.price).find(".") + 3);
            fullSpec = p.brand + " " + p.model + " " + to_string(p.year) + " year, form factor: " + p.form_factor + ", screen size: " + sizeText + "', price: " + priceText + "$";
            cout << (fullSpec);
            emptyLine();
        }
    }
}

void showByFormFactorAndScreenSize() {
    string form_factor, fullSpec, sizeText, priceText;
    float screen_size;
    cout << "Enter form factor (example: gray): ";
    cin >> form_factor;
    cout << "Enter screen size (example: 5.2) : ";
    cin >> screen_size;
    cout << "Phones with form factor " << form_factor << " and screen size " << screen_size << ":" << endl;
    for (Phone p : phones) {
        if (p.form_factor == form_factor && p.screen_size == screen_size) {
            sizeText = to_string(p.screen_size).substr(0, to_string(p.screen_size).find(".") + 3);
            priceText = to_string(p.price).substr(0, to_string(p.price).find(".") + 3);
            fullSpec = p.brand + " " + p.model + " " + to_string(p.year) + " year, form factor: " + p.form_factor + ", screen size: " + sizeText + "', price: " + priceText + "$";
            cout << (fullSpec);
            emptyLine();
        }
    }
}

void showMaxBrand() {
    int max_count = 0;
    string max_brand;
    for (pair<string, int> p : brand_count) {
        if (p.second > max_count) {
            max_count = p.second;
            max_brand = p.first;
        }
    }
    cout << "Brand with maximum phones: " << max_brand << endl;
}

void showTop3ScreenSizes() {
    map<float, int> screen_count;
    for (Phone p : phones) {
        screen_count[p.screen_size]++;
    }
    vector<pair<float, int>> screen_vector(screen_count.begin(), screen_count.end());
    sort(screen_vector.begin(), screen_vector.end(), [](auto& a, auto& b) {
        return a.second > b.second;
        });
    cout << "Top 3 screen sizes:" << endl;
    
    for (int i = 0; i < screen_vector.size(); i++) {
        if (i < 3) {
            cout << screen_vector[screen_vector.size() - i - 1].first << endl;
        }
    }
}

void saveToFile() {
    ofstream file("phones.txt");
    for (Phone p : phones) {
        file << p.brand << "," << p.model << "," << p.form_factor << "," << p.year << "," << p.screen_size << "," << p.price << endl;
    }
    file.close();
    cout << "Data saved to file successfully!" << endl;
}

void loadFromFile() {
    ifstream file("phones.txt");
    string line;
    while (getline(file, line)) {
        Phone p;
        int index = line.find(",");
        p.brand = line.substr(0, index);
        line = line.substr(index + 1);
        index = line.find(",");
        p.model = line.substr(0, index);
        line = line.substr(index + 1);
        index = line.find(",");
        p.form_factor = line.substr(0, index);
        line = line.substr(index + 1);
        index = line.find(",");
        p.year = stoi(line.substr(0, index));
        line = line.substr(index + 1);
        index = line.find(",");
        p.screen_size = stof(line.substr(0, index));
        line = line.substr(index + 1);
        p.price = stof(line);
        phones.push_back(p);
        brand_count[p.brand]++;
    }
    file.close();
    cout << "Data loaded from file successfully!" << endl;
}

int main() {
    bool exit = true;
    while (exit) {
        cout << "1. Add phone" << endl;
        cout << "2. Delete phone" << endl;
        cout << "3. Show all phones" << endl;
        cout << "4. Show all phones by brand" << endl;
        cout << "5. Show all phones by form factor and screen size" << endl;
        cout << "6. Show brand with maximum quantity of phones" << endl;
        cout << "7. Show top-3 screen sizes" << endl;
        cout << "8. Save data to file" << endl;
        cout << "9. Load data from file" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            addPhone();
            emptyLine();
            break;
        case 2:
            system("cls");
            showAllPhones();
            deletePhone();
            break;
        case 3:
            system("cls");
            showAllPhones();
            emptyLine();
            break;
        case 4:
            showAllByBrand();
            emptyLine();
            break;
        case 5:
            showByFormFactorAndScreenSize();
            emptyLine();
            break;
        case 6:
            emptyLine();
            showMaxBrand();
            emptyLine();
            break;
        case 7:
            emptyLine();
            showTop3ScreenSizes();
            emptyLine();
            break;
        case 8:
            saveToFile();
            emptyLine();
            break;
        case 9:
            loadFromFile();
            emptyLine();
            break;
        case 0:
            exit = false;
            break;
        }
    }
}
