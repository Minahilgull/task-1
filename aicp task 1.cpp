#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int NUM_CATEGORIES = 7;
const int NUM_ITEMS[] = {2, 3, 3, 2, 3, 2, 2};
const string CATEGORIES[] = {"Case", "RAM", "Main Hard Disk Drive", "Solid State Drive", "Second Hard Disk Drive", "Optical Drive", "Operating System"};
const string ITEM_CODES[][3] = {{"A1", "Compact", "75.00"}, {"A2", "Tower", "150.00"}, {"B1", "8 GB", "79.99"}, {"B2", "16 GB", "149.99"}, {"B3", "32 GB", "299.99"}, {"C1", "1 TB HDD", "49.99"}, {"C2", "2 TB HDD", "89.99"}, {"C3", "4 TB HDD", "129.99"}, {"D1", "240 GB SSD", "59.99"}, {"D2", "480 GB SSD", "119.99"}, {"E1", "1 TB HDD", "49.99"}, {"E2", "2 TB HDD", "89.99"}, {"E3", "4 TB HDD", "129.99"}, {"F1", "DVD/Blu-Ray Player", "50.00"}, {"F2", "DVD/Blu-Ray Re-writer", "100.00"}, {"G1", "Standard Version", "100.00"}, {"G2", "Professional Version", "175.00"}};

struct Item {
    string code;
    string description;
    double price;
};

// Function to display available items
void displayItems(int categoryIndex) {
    for (int i = 0; i < NUM_ITEMS[categoryIndex]; ++i) {
        cout << ITEM_CODES[i + categoryIndex * 3][0] << ": " << ITEM_CODES[i + categoryIndex * 3][1] << " - $" << ITEM_CODES[i + categoryIndex * 3][2] << endl;
    }
}

// Function to get user input for an item
Item getOrderItem(string category) {
    Item item;
    cout << "Choose a " << category << " item by entering its code: ";
    cin >> item.code;

    // Validate the input
    bool validInput = false;
    for (int i = 0; i < NUM_CATEGORIES; ++i) {
        for (int j = 0; j < NUM_ITEMS[i]; ++j) {
            if (item.code == ITEM_CODES[j + i * 3][0]) {
                validInput = true;
                item.description = ITEM_CODES[j + i * 3][1];
                item.price = stod(ITEM_CODES[j + i * 3][2]);
                break;
            }
        }
    }

    if (!validInput) {
        cerr << "Invalid item code. Please try again." << endl;
        exit(1);
    }

    return item;
}

int main() {
    // Initialize basic components
    double basicComponentsPrice = 200.0;

    // Order Case
    Item selectedCase = getOrderItem("Case");

    // Order RAM
    Item selectedRAM = getOrderItem("RAM");

    // Order Main Hard Disk Drive
    Item selectedHDD = getOrderItem("Main Hard Disk Drive");

    // Calculate the total price
    double totalPrice = basicComponentsPrice + selectedCase.price + selectedRAM.price + selectedHDD.price;

    // Display the order summary
    cout << "\nOrder Summary:" << endl;
    cout << "Case: " << selectedCase.description << " - $" << selectedCase.price << endl;
    cout << "RAM: " << selectedRAM.description << " - $" << selectedRAM.price << endl;
    cout << "Main Hard Disk Drive: " << selectedHDD.description << " - $" << selectedHDD.price << endl;
    cout << "Total Price: $" << totalPrice << endl;
    //TASK 2
    // Allow the customer to choose additional items
    char addMore;
    do {
        cout << "\nDo you want to purchase additional items? (Y/N): ";
        cin >> addMore;

        if (toupper(addMore) == 'Y') {
            int categoryIndex;
            cout << "\nChoose a category to add items from (1-6): ";
            cin >> categoryIndex;
            
            // Validate the input
            if (categoryIndex < 1 || categoryIndex > 6) {
                cerr << "Invalid category. Please try again." << endl;
                exit(1);
            }

            displayItems(categoryIndex - 1);

            Item additionalItem = getOrderItem(CATEGORIES[categoryIndex - 1]);
            totalPrice += additionalItem.price;

            cout << "\nAdditional item added: " << additionalItem.description << " - $" << additionalItem.price << endl;
            cout << "New Total Price: $" << totalPrice << endl;
        }
    } while (toupper(addMore) == 'Y');

    
    //TASK 3

    // Offer discounts based on the number of additional items
    int numAdditionalItems = 0;
    cout << "\nEnter the number of additional items purchased: ";
    cin >> numAdditionalItems;

    double discount = 0.0;
    if (numAdditionalItems == 1) {
        discount = 0.05;
    } else if (numAdditionalItems >= 2) {
        discount = 0.10;
    }

    double discountAmount = totalPrice * discount;
    totalPrice -= discountAmount;

    // Display the discount information and final price
    cout << "\nDiscount applied: " << fixed << setprecision(2) << (discount * 100) << "%" << endl;
    cout << "Amount saved: $" << discountAmount << endl;
    cout << "Final Price after Discount: $" << totalPrice << endl;

    return 0;
}

