#include <iostream>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <fstream>
using namespace std;

int main() {

    double grand_total = 0;
    int total_customers = 0;
    char continue_choice;
    string order_summary = "";
    int water_inventory = 100, soda_inventory = 100, coffee_inventory = 100, tea_inventory = 100;

    do {

    string CustomerName;
    cout << "Enter customer's name: ";
    cin.ignore();
    getline(cin, CustomerName);

    cout << "\n--- Menu ---\n";
    cout << left << setw(15) << "Drink" << setw(15) << "Small (S)" << right << setw(15) << "Medium (M)" << setw(15) << "Large (L)" << endl;
    cout << string(60, '-') << endl;
    cout << left << setw(15) << "Water (W)" << setw(15) << "$1.00" << right << setw(10) << "$1.50" << setw(16) << "$2.00" << endl;
    cout << left << setw(15) << "Soda (S)" << setw(15) << "$2.00" << right << setw(10) << "$2.50" << setw(16) << "$3.00" << endl;
    cout << left << setw(15) << "Coffee (C)" << setw(15) << "$1.50" << right << setw(10) << "$2.00" << setw(16) << "$2.50" << endl;
    cout << left << setw(15) << "Tea (T)" << setw(15) << "$1.50" << right << setw(10) << "$2.00" << setw(16) << "$2.50" << endl;
    cout << string(60, '-') << endl;
    cout << left << "Type \"X\" to check out." << endl;
    cout << string(60, '-') << endl;

   
    string item_choice;
    string size_choice;
    string drink1, drink2, drink3, drink4;
    char drink1_code, drink2_code, drink3_code, drink4_code;
    double drink1_small, drink1_medium, drink1_large, drink2_small, drink2_medium, drink2_large, drink3_small, drink3_medium, drink3_large, drink4_small, drink4_medium, drink4_large;
    string food_name;
    char item_code;
    double unit_price;
    int quantity;
    double subtotal;
    double total = 0;
    stringstream price_stream;
    stringstream total_stream;
    //Variables are still case-sensitive

     do {
        cout << "Please make an item selection: ";
        cin >> item_choice;
        while (item_choice[0] != 'X' && item_choice[0] != 'W' && item_choice[0] != 'S' && item_choice[0] != 'C' && item_choice[0] != 'T') {
            cout << "Invalid item selection. Please try again: ";
            cin >> item_choice;
        }

        if (item_choice[0] != 'X') {
        cout << "Please select a size (S/M/L): ";
        cin >> size_choice;
        while (size_choice[0] != 'S' && size_choice[0] != 'M' && size_choice[0] != 'L') {
            cout << "Invalid size selection. Please try again: ";
            cin >> size_choice;
        }

    ifstream menu_file;
    menu_file.open("Lab_Menu.txt");
    if (menu_file.is_open()) {
        while (menu_file >> drink1 >> drink1_code >> drink1_small >> drink1_medium >> drink1_large >> drink2 >> drink2_code >> drink2_small >> drink2_medium >> drink2_large >> drink3 >> drink3_code >> drink3_small >> drink3_medium >> drink3_large >> drink4 >> drink4_code >> drink4_small >> drink4_medium >> drink4_large) {
            switch (item_choice[0]) {
                case 'W':
                    food_name = drink1;
                    item_code = drink1_code;
                    switch (size_choice[0]) {
                        case 'S':
                            unit_price = drink1_small;
                            break;
                        case 'M':
                            unit_price = drink1_medium;
                            break;
                        case 'L':
                            unit_price = drink1_large;
                            break;
                    }
                    break;
                case 'S':
                    food_name = drink2;
                    item_code = drink2_code;
                    switch (size_choice[0]) {
                        case 'S':
                            unit_price = drink2_small;
                            break;
                        case 'M':
                            unit_price = drink2_medium;
                            break;
                        case 'L':
                            unit_price = drink2_large;
                            break;
                    }
                    break;
                case 'C':
                    food_name = drink3;
                    item_code = drink3_code;
                    switch (size_choice[0]) {
                        case 'S':
                            unit_price = drink3_small;
                            break;
                        case 'M':
                            unit_price = drink3_medium;
                            break;
                        case 'L':
                            unit_price = drink3_large;
                            break;
                    }
                    break;
                case 'T':
                    food_name = drink4;
                    item_code = drink4_code;
                    switch (size_choice[0]) {
                        case 'S':
                            unit_price = drink4_small;
                            break;
                        case 'M':
                            unit_price = drink4_medium;
                            break;
                        case 'L':
                            unit_price = drink4_large;
                            break;
                    }
                    break;
                 } //end switch
        }
        menu_file.close();
    } else {
        cout << "Unable to open menu file." << endl;
    }

        do {
            cout << "Quantity: ";
            cin >> quantity;
        } while (quantity <= 0);

        switch (item_choice[0]) {
            case 'W':
                water_inventory -= quantity;
                break;
            case 'S':
                soda_inventory -= quantity;
                break;
            case 'C':
                coffee_inventory -= quantity;
                break;
            case 'T':
                tea_inventory -= quantity;
                break;
        }

        subtotal = quantity * unit_price;
        total += subtotal;
        price_stream.str("");
        price_stream << fixed << setprecision(2) << unit_price;
        total_stream.str("");
        total_stream << fixed << setprecision(2) << subtotal;
        order_summary += to_string(quantity) + " x " + food_name + " (" + size_choice + ") @ $" + price_stream.str() + " each - $" + total_stream.str() + " total" + "\n";
        }

    } while (item_choice[0] != 'X');
        

    cout << "Member? ";
    bool member;
    cin >> member;
    double discount = 0.0;
    if (member) {
       discount = total * 0.1; // 10% discount for members
}

double after_discount = total - discount;
const double ARKANSAS_TAX_RATE = 0.065;
const double FAULKNER_TAX_RATE = 0.005;
const double CONWAY_TAX_RATE = 0.02125;

double arkansas_tax = after_discount * ARKANSAS_TAX_RATE;
double faulkner_tax = after_discount * FAULKNER_TAX_RATE;
double conway_tax = after_discount * CONWAY_TAX_RATE;
double total_tax = arkansas_tax + faulkner_tax + conway_tax;
double tip_amount = 0.0;
int tip_choice;

cout << fixed << setprecision(2);
cout << "\n--- Tip Options ---\n";
cout << "1. 15% ($" << after_discount * 0.15 << ")\n";
cout << "2. 20% ($" << after_discount * 0.20 << ")\n";
cout << "3. 25% ($" << after_discount * 0.25 << ")\n";
cout << "4. Other Amount\n";
cout << "Select an option (1-4): ";
cin >> tip_choice;

switch (tip_choice) {
    case 1:
        tip_amount = after_discount * 0.15;
        break;
    case 2:
        tip_amount = after_discount * 0.20;
        break;
    case 3:
        tip_amount = after_discount * 0.25;
        break;
    case 4:
        cout << "Enter tip amount: $";
        cin >> tip_amount;
        break;
    default:
        cout << "Invalid option. No tip added.\n";
}

double order_total = after_discount + total_tax + tip_amount;

string cashier_note;
cin.ignore();
cout << "Cashier Note: ";
getline(cin, cashier_note);
// Ex: Customer requested extra sugar.
double loyalty_points = total / 3.0;

cout << left << "\n--- " << CustomerName << "'s " << "Receipt ---\n";
cout << order_summary;
cout << left << setw(25) << "Subtotal:" <<fixed << setprecision(2) << total << endl;
cout << left << setw(25) << "Member Discount:" <<fixed<< setprecision(2) << discount << endl; 
cout << left << setw(25) << "After Discount:" << fixed << setprecision(2) << after_discount << endl;
cout << left << setw(25) << "Arkansas Tax (6.5%):" << "$" << arkansas_tax << endl;
cout << left << setw(25) << "Faulkner Tax (0.5%):" << "$" << faulkner_tax << endl;
cout << left << setw(25) << "Conway Tax (2.125%):" << "$" << conway_tax << endl;
cout << left << setw(25) << "Total Tax:" << "$" << total_tax << endl;
cout << left << setw(25) << "Tip:" << "$" << tip_amount << endl;
cout << left << setw(25) << "Total:" << "$" << order_total << endl;
cout << left << setw(25) << "Loyalty Points: " << string(static_cast<int>(loyalty_points), '*') << endl;

ofstream receipt_fout("receipt.txt", ios::app);
receipt_fout << left << "\n--- " << CustomerName << "'s " << "Receipt ---\n";
receipt_fout << order_summary;
receipt_fout << left << setw(25) << "Subtotal:" <<fixed << setprecision(2) << total << endl;
receipt_fout << left << setw(25) << "Member Discount:" <<fixed<< setprecision(2) << discount << endl; 
receipt_fout << left << setw(25) << "After Discount:" << fixed << setprecision(2) << after_discount << endl;
receipt_fout << left << setw(25) << "Arkansas Tax (6.5%):" << "$" << arkansas_tax << endl;
receipt_fout << left << setw(25) << "Faulkner Tax (0.5%):" << "$" << faulkner_tax << endl;
receipt_fout << left << setw(25) << "Conway Tax (2.125%):" << "$" << conway_tax << endl;
receipt_fout << left << setw(25) << "Total Tax:" << "$" << total_tax << endl;
receipt_fout << left << setw(25) << "Tip:" << "$" << tip_amount << endl;
receipt_fout << left << setw(25) << "Total:" << "$" << order_total << endl;
receipt_fout << left << setw(25) << "Loyalty Points: " << string(static_cast<int>(loyalty_points), '*') << endl;
receipt_fout.close();

grand_total += order_total;
total_customers++;

cout << "Would you like to process another customer? (Y/N): ";
cin >> continue_choice;

} while (continue_choice == 'Y' || continue_choice == 'y');

cout << "Grand Total: $" << grand_total << " | Total Customers: " << total_customers << endl;

cout << "\n--- Inventory Audit ---\n";
cout << order_summary;
cout << string(52, '-') << endl;
cout << left << setw(15) << "Drink" << setw(20) << "Start Inventory" << setw(15) << "Change" << setw(15) << "End Inventory" << endl;
cout << string(52, '-') << endl;
cout << left << setw(15) << "Water" << setw(20) << 100 << setw(15) << water_inventory - 100 << setw(15) << water_inventory << endl;
cout << left << setw(15) << "Soda" << setw(20) << 100 << setw(15) << soda_inventory - 100 << setw(15) << soda_inventory << endl;
cout << left << setw(15) << "Coffee" << setw(20) << 100 << setw(15) << coffee_inventory - 100 << setw(15) << coffee_inventory << endl;
cout << left << setw(15) << "Tea" << setw(20) << 100 << setw(15) << tea_inventory - 100 << setw(15) << tea_inventory << endl;
cout << string(52, '-') << endl;

return 0;
}