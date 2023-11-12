#include<iostream>
#include<vector>
#include<string>

using namespace std;

// Function to initialize data structures for the start of the day
void initializeDay(vector<int>& availableSeats, vector<int>& totalPassengers, vector<int>& totalRevenue) {
    for (int i = 0; i < 8; ++i) {
        availableSeats.push_back(80); // 80 seats available for each journey
        totalPassengers.push_back(0);
        totalRevenue.push_back(0);
    }
}

// Function to purchase tickets
void purchaseTickets(vector<int>& availableSeats, vector<int>& totalPassengers, vector<int>& totalRevenue) {
    int journey, numTickets;
    cout << "Enter journey (1-8 for up and down trips): ";
    cin >> journey;

    // Validate journey input
    if (journey < 1 || journey > 8) {
        cout << "Invalid journey number. Please enter a number between 1 and 8." << endl;
        return;
    }

    // Display available seats
    if (availableSeats[journey - 1] <= 0) {
        cout << "Tickets for this journey are sold out. Closed." << endl;
        return;
    }

    cout << "Available seats for Journey " << journey << ": " << availableSeats[journey - 1] << endl;

    // Get number of tickets
    cout << "Enter the number of tickets to purchase: ";
    cin >> numTickets;

    // Validate number of tickets
    if (numTickets < 1 || numTickets > availableSeats[journey - 1]) {
        cout << "Invalid number of tickets. Please enter a number between 1 and " << availableSeats[journey - 1] << "." << endl;
        return;
    }

    // Calculate total price
    int totalPrice = numTickets * 25;
    int discount = (numTickets / 10) * 25;
    totalPrice -= discount;

    // Update data structures
    availableSeats[journey - 1] -= numTickets;
    totalPassengers[journey - 1] += numTickets;
    totalRevenue[journey - 1] += totalPrice;

    // Display confirmation
    cout << "Tickets purchased successfully! Total price: $" << totalPrice << endl;
}

// Function to display end-of-day statistics
void endOfDay(vector<int>& totalPassengers, vector<int>& totalRevenue) {
    int totalDayPassengers = 0;
    int totalDayRevenue = 0;
    int maxPassengersJourney = 0;

    // Display individual journey statistics
    for (int i = 0; i < 8; ++i) {
        cout << "Journey " << i + 1 << ": Passengers - " << totalPassengers[i] << ", Revenue - $" << totalRevenue[i] << endl;

        totalDayPassengers += totalPassengers[i];
        totalDayRevenue += totalRevenue[i];

        if (totalPassengers[i] > totalPassengers[maxPassengersJourney]) {
            maxPassengersJourney = i;
        }
    }

    // Display total day statistics
    cout << "Total Passengers for the Day: " << totalDayPassengers << endl;
    cout << "Total Revenue for the Day: $" << totalDayRevenue << endl;
    cout << "Journey with the Most Passengers: Journey " << maxPassengersJourney + 1 << endl;
}

int main() {
    vector<int> availableSeats;
    vector<int> totalPassengers;
    vector<int> totalRevenue;

    initializeDay(availableSeats, totalPassengers, totalRevenue);

    // Simulate ticket purchases
    purchaseTickets(availableSeats, totalPassengers, totalRevenue);
    purchaseTickets(availableSeats, totalPassengers, totalRevenue);

    // Display end-of-day statistics
    endOfDay(totalPassengers, totalRevenue);

    return 0;
}
