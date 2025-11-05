#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdexcept>    
#include <limits>      
using namespace std;

class Product {
public:
    int id;
    string name;
    int quantity;
    float price;

    Product() {}
    Product(int i, string n, int q, float p) {
        id = i;
        name = n;
        quantity = q;
        price = p;
    }

    void display() const {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(10) << quantity
             << setw(10) << fixed << setprecision(2) << price << endl;
    }
};

vector<Product> inventory;

void saveToFile() {
    ofstream file("inventory.txt");
    if (!file) throw runtime_error("Error saving to file!");
    for (const auto &p : inventory) {
        file << p.id << " " << p.name << " " << p.quantity << " " << p.price << endl;
    }
    file.close();
}

void loadFromFile() {
    ifstream file("inventory.txt");
    if (!file) return; // File not yet created
    inventory.clear();
    Product p;
    while (file >> p.id >> p.name >> p.quantity >> p.price) {
        inventory.push_back(p);
    }
    file.close();
}

int getIntInput(string msg) {
    int value;
    while (true) {
        cout << msg;
        try {
            if (!(cin >> value)) {
                throw invalid_argument("Invalid input! Please enter a number.");
            }
            return value;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

float getFloatInput(string msg) {
    float value;
    while (true) {
        cout << msg;
        try {
            if (!(cin >> value)) {
                throw invalid_argument("Invalid input! Please enter a decimal number.");
            }
            return value;
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void addProduct() {
    try {
        int id = getIntInput("Enter Product ID: ");
        string name;
        cout << "Enter Product Name: ";
        cin >> name;
        int quantity = getIntInput("Enter Quantity: ");
        float price = getFloatInput("Enter Price: ");

        for (auto &p : inventory) {
            if (p.id == id)
                throw runtime_error("Product with this ID already exists!");
        }

        inventory.emplace_back(id, name, quantity, price);
        cout << "Product added successfully!\n";
    } catch (const exception &e) {
        cout << " Error: " << e.what() << endl;
    }
}

void displayAll() {
    if (inventory.empty()) {
        cout << "No products found.\n";
        return;
    }
    cout << left << setw(10) << "ID" << setw(20) << "Name"
         << setw(10) << "Qty" << setw(10) << "Price" << endl;
    cout << string(50, '-') << endl;
    for (const auto &p : inventory) p.display();
}

void searchProduct() {
    int id = getIntInput("Enter Product ID to search: ");
    auto it = find_if(inventory.begin(), inventory.end(),
                      [id](const Product &p) { return p.id == id; });
    if (it != inventory.end()) {
        cout << "Product found:\n";
        it->display();
    } else {
        cout << "Product not found!\n";
    }
}

void updateProduct() {
    int id = getIntInput("Enter Product ID to update: ");
    for (auto &p : inventory) {
        if (p.id == id) {
            cout << "Enter new Quantity: ";
            p.quantity = getIntInput("");
            cout << "Enter new Price: ";
            p.price = getFloatInput("");
            cout << " Product updated successfully!\n";
            return;
        }
    }
    cout << "Product not found!\n";
}

void deleteProduct() {
    int id = getIntInput("Enter Product ID to delete: ");
    auto it = remove_if(inventory.begin(), inventory.end(),
                        [id](const Product &p) { return p.id == id; });
    if (it != inventory.end()) {
        inventory.erase(it, inventory.end());
        cout << " Product deleted successfully!\n";
    } else {
        cout << "Product not found!\n";
    }
}

void generateReport() {
    if (inventory.empty()) {
        cout << "No products available.\n";
        return;
    }

    float totalValue = 0;
    for (const auto &p : inventory) {
        totalValue += p.quantity * p.price;
    }

    cout << "Total Products: " << inventory.size() << endl;
    cout << " Total Inventory Value: ₹" << fixed << setprecision(2) << totalValue << endl;
}

int main() {
    loadFromFile();
    int choice;

    while (true) {
        cout << "\n========== INVENTORY MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Product\n";
        cout << "2. Display All Products\n";
        cout << "3. Search Product\n";
        cout << "4. Update Product\n";
        cout << "5. Delete Product\n";
        cout << "6. Generate Report\n";
        cout << "7. Save & Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << " Invalid choice! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: addProduct(); break;
            case 2: displayAll(); break;
            case 3: searchProduct(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 6: generateReport(); break;
            case 7:
                try {
                    saveToFile();
                    cout << "Data saved successfully. Exiting...\n";
                } catch (const exception &e) {
                    cout << " " << e.what() << endl;
                }
                return 0;
            default:
                cout << "Invalid option! Try again.\n";
        }
    }
}
