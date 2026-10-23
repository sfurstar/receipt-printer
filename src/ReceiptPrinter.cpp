#include <iostream>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <fstream>
using namespace std;

//

//Function retrieves the customer's name and returns it as a string for use on the receipt.
string get_name() {
    string customer_name;
    cout << "Enter customer's name: ";
    cin.ignore();
    getline(cin, customer_name);
    return customer_name;
}

//Function prints the menu to the console for the customer to view and make selections.
void print_menu() {
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
}

//Function retrieves the customer's item selection and returns it as a string.
char get_item(char &item_choice) {
    cout << "Please make an item selection: ";
    cin >> item_choice;
    while (item_choice != 'X' && item_choice != 'W' && item_choice != 'S' && item_choice != 'C' && item_choice != 'T') {
        cout << "Invalid item selection. Please try again: ";
            cin >> item_choice;
        }
    return item_choice;
}

//Function retrieves the customer's size selection if an item is chosen and returns it as a string.
char get_size(char &size_choice) {
    cout << "Please select a size (S/M/L): ";
    cin >> size_choice;
    while (size_choice != 'S' && size_choice != 'M' && size_choice != 'L') {
        cout << "Invalid size selection. Please try again: ";
        cin >> size_choice;
    }
    return size_choice;
}

//Function reads the menu file and retrieves the unit price, food name, and item code based on the customer's selections.
void read_menu(char item_choice, char size_choice, double &unit_price, string &food_name, char &item_code) {
    string drink1, drink2, drink3, drink4;
    char drink1_code, drink2_code, drink3_code, drink4_code;
    double drink1_small, drink1_medium, drink1_large, drink2_small, drink2_medium, drink2_large, drink3_small, drink3_medium, drink3_large, drink4_small, drink4_medium, drink4_large;

    ifstream menu_file;
    menu_file.open("Lab_Menu.txt");
    if (menu_file.is_open()) {
        while (menu_file >> drink1 >> drink1_code >> drink1_small >> drink1_medium >> drink1_large >> drink2 >> drink2_code >> drink2_small >> drink2_medium >> drink2_large >> drink3 >> drink3_code >> drink3_small >> drink3_medium >> drink3_large >> drink4 >> drink4_code >> drink4_small >> drink4_medium >> drink4_large) {
            //Switch reads in food name, item code, and unit price from the file based on the customer's item and size selection.
            switch (item_choice) {
                case 'W': //Water
                    food_name = drink1;
                    item_code = drink1_code;
                    switch (size_choice) {
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
                case 'S': //Soda
                    food_name = drink2;
                    item_code = drink2_code;
                    switch (size_choice) {
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
                case 'C': //Coffee
                    food_name = drink3;
                    item_code = drink3_code;
                    switch (size_choice) {
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
                case 'T': //Tea
                    food_name = drink4;
                    item_code = drink4_code;
                    switch (size_choice) {
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
                 } //End of menu reading switch.
        }
        menu_file.close();
    } else {
        cout << "Unable to open menu file." << endl;
    }
    return;
}

//Function retrieves the customer's quantity selection.
int amount() {
     int quantity;
    do { 
            cout << "Quantity: ";
            cin >> quantity;
        } while (quantity <= 0);
    return quantity;
 }

//Function updates the inventory based on the customer's item and quantity selection.
 void inventory_update(char item_choice, int quantity, int &water_inventory, int &soda_inventory, int &coffee_inventory, int &tea_inventory) {
    switch (item_choice) {
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
}

//Function prompts user for their item, size, and quantity selection, updates inventory and totals,
//then retrieves the customer's order summary and returns it as a string for use on the receipt.
string order_summary (char item_choice, char size_choice, double unit_price, string food_name, int quantity, double &subtotal, int water_inventory, int soda_inventory, int coffee_inventory, int tea_inventory) {
    stringstream order_summary;
    string order_summary = "";
    stringstream price_stream;
    stringstream total_stream;
    price_stream.str("");
    price_stream << fixed << setprecision(2) << unit_price;
    total_stream.str("");
    total_stream << fixed << setprecision(2) << subtotal;
    do {
        char item_choice = get_item(item_choice);
    
        if (item_choice != 'X') {
            char size_choice = get_size(size_choice);

            void read_menu(char item_choice, char size_choice, double &unit_price, string &food_name, char &item_code);

            int quantity = amount();

            inventory_update(item_choice, quantity, water_inventory, soda_inventory, coffee_inventory, tea_inventory);

        }
    subtotal = quantity * unit_price;
    double total = 0;
    total += subtotal;
    } while (item_choice != 'X');
    order_summary += to_string(quantity) + " x " + food_name + " (" + size_choice + ") @ $" + price_stream.str() + " each - $" + total_stream.str() + " total" + "\n";
    return order_summary;
}    

//Function retrieves the customer's membership status and returns the discount rate.
double member_discount(bool &member, double &total, double &discount) {
    cout << "Are you a member? ";
    cin >> member;
    discount = 0.0;
    if (member) {
       discount = total * 0.1; // 10% discount for members
    }
    return discount;
}

//Function calculates the various taxes for the state, county, & city.
void tax_calculation(double &total, double &discount, double &after_discount, double &arkansas_tax, double &faulkner_tax, double &conway_tax, double &total_tax, double &tip_amount, int &tip_choice, double &loyalty_points, double &order_total) {
    after_discount = total - discount;
    const double ARKANSAS_TAX_RATE = 0.065;
    const double FAULKNER_TAX_RATE = 0.005;
    const double CONWAY_TAX_RATE = 0.02125;

    arkansas_tax = after_discount * ARKANSAS_TAX_RATE; 
    faulkner_tax = after_discount * FAULKNER_TAX_RATE;
    conway_tax = after_discount * CONWAY_TAX_RATE;
    total_tax = arkansas_tax + faulkner_tax + conway_tax;
    return;
}

//Function asks the user for a tip amount (percentage-based or self-selected), then returns it.
double get_tip(double &after_discount, double &tip_amount, int tip_choice) {

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
}

/*

int water_inventory = 100, soda_inventory = 100, coffee_inventory = 100, tea_inventory = 100; //inventory management function

double loyalty_points = total / 3.0;

double order_total = after_discount + total_tax + tip_amount;
*/

//Retrieves any special requests within the cashier note and returns it. Ex: Customer requested extra sugar.
string note(string &cashier_note){
cin.ignore();
cout << "Cashier Note: ";
getline(cin, cashier_note);
return cashier_note;
}

//Function prints out the customer's receipt.
void receipt_print(string customer_name, string order_summary, double total, double discount, double after_discount, double arkansas_tax, double faulkner_tax, double conway_tax, double total_tax, double tip_amount, double loyalty_points, double order_total) {
cout << left << "\n--- " << customer_name << "'s " << "Receipt ---\n"; //receipt funtion
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
}

//Function prints out the customer's receipt to a text file (receipt.txt).
void receipt_file(string customer_name, string order_summary, double total, double discount, double after_discount, double arkansas_tax, double faulkner_tax, double conway_tax, double total_tax, double tip_amount, double loyalty_points, double order_total) {
ofstream receipt_fout("receipt.txt", ios::app);
receipt_fout << left << "\n--- " << customer_name << "'s " << "Receipt ---\n";
receipt_fout << order_summary;
receipt_fout << left << setw(25) << "Subtotal:" <<fixed << setprecision(2) << total << endl;
receipt_fout << left << setw(25) << "Member Discount:" <<fixed<< setprecision(2) << discount << endl; 
receipt_fout << left << setw(25) << "After Discount:" << fixed << setprecision(2) << after_discount << endl;
receipt_fout << left << setw(25) << "Arkansas Tax (6.5%):" << "$" << arkansas_tax << endl;
receipt_fout << left << setw(25) << "Faulkner Tax (0.5%):" << "$" << faulkner_tax << endl;
receipt_fout << left << setw(25) << "Conway Tax (2.125%):" << "$" << conway_tax << endl;
receipt_fout << left << setw(25) << "Total Tax:" << "$" << total_tax << endl;
receipt_fout << left << setw(25) << "Tip:" << "$" << tip_amount<< endl;
receipt_fout << left << setw(25) << "Total: "<< "$" << order_total << endl;
receipt_fout << left << setw(25) << "Loyalty Points: " << string(static_cast<int>(loyalty_points), '*') << endl;
receipt_fout.close();
}

void day_total_update (double & order_total, double &grand_total, int &total_customers) {
    grand_total += order_total;
    total_customers++;
}

char choice(char &continue_choice) {
cout << "Would you like to process another customer? (Y/N): ";
cin >> continue_choice;
return continue_choice;
}


void day_summary(double &grand_total, int &total_customers, string &order_summary, int &water_inventory, int &soda_inventory, int & coffee_inventory, int &tea_inventory) {

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
}

int main() {
    
    do {
        string customer_name = get_name();

        print_menu();

        //Order input

        //calculations

        receipt_print(customer_name, order_summary, total, discount, after_discount, arkansas_tax, faulkner_tax, conway_tax, total_tax, tip_amount, loyalty_points, order_total);
        receipt_file(customer_name, order_summary, total, discount, after_discount, arkansas_tax, faulkner_tax, conway_tax, total_tax, tip_amount, loyalty_points, order_total);

        char continue_choice = choice(continue_choice);

    } while (continue_choice == 'Y' || continue_choice == 'y');

//Summary

//Inventory Audit

return 0;
}