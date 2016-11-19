/*
Coleman Warren, Section 8, coleman.warren@hotmail.com
Ready for grading
Purpose: To create an inventory system for a car dealership. Cars can be bought, sold and painted while the revenue balance is tracked. Data can be loaded from or saved to a file at any time.
Input:
    1. None - Shows the current inventory of cars
    2. None - Shows the current cash balance
    3. The name, color and price of the car to buy
    4. The name of the car to sell
    5. The name of the car to paint
        5.a. The new paint color
    6. The name of the file to load
    7. The name of the new file to create
    8. None - Quits the program
Output:
    1. The name, color and price of each car in the inventory, or a message that inventory is empty
    2. The current cash balance
    3. The car was bought successfully, or that car already exists in the inventory
    4. The car was sold successfully, or that care doesn't exist within the inventory
    5. The car was painted, or that car doesn't exist within the inventory
    6. The file was loaded successfully
    7. The file was saved succussefully
    8. Press any key to continue...
Test Case 1
    Menu: 3
    Input: Mustang, black, 5300
    Output: Congratulations, you purchased a Mustang!
Test Case 2
    Menu: 6
    Input: None
    Output: File loaded successfully!
    Menu(2): 1
    Output(2):
        Name: Navy
        Color: White
        Price: $6972.15

        Name: Kidney
        Color: Red
        Price: $3971.15

        Name: Refried
        Color: Brown
        Price: $9999.99

        Name: Garbanzo
        Color: White
        Price: $975.21

        Name: Black
        Color: Black
        Price: $7946.85

        Name: Edamame
        Color: Green
        Price: $555.55

        Name: Lima
        Color: White
        Price: $5873.15

        Name: Pinto
        Color: Brown
        Price: $12369
Test Case 3
    Menu: 6
    Input: None
    Output: File loaded successfully!
    Menu(2): 6
    Input(2): None
    Output(2): File loaded successfully!
    Menu(3): 7
    Input(3): cars3.txt
    Output(3): Your file was saved successfully!
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cctype>
#include "Car.h"
using namespace std;

const int INVENTORY_OPTION = 1;
const int BALANCE_OPTION = 2;
const int BUY_CAR_OPTION = 3;
const int SELL_CAR_OPTION = 4;
const int PAINT_CAR_OPTION = 5;
const int LOAD_FILE_OPTION = 6;
const int SAVE_FILE_OPTION = 7;
const int QUIT_OPTION = 8;
const double STARTING_BALANCE = 10000;
const int DOES_NOT_EXIST = -1;

/*
    Checks whether or not a car already exists within the inventory
    @param car_to_check - The car name that we're checking for in our existing inventory
    @param inventory - the vector of existing cars
    @param purchase - boolean of whether or not the car alraedy exists in the inventory
    @return exists
*/
int check_inventory(string car_to_check, vector<Car> inventory) {
    for (int i = 0; i < inventory.size(); i++) {
        if (car_to_check == inventory[i].getName()) {
            return i;
        }
    }
    return DOES_NOT_EXIST;
}

/*
    Purchases a car by adding it to the inventory vector and subtracting the price from the current balance
    @param new_car_name
    @param new_car_color
    @param new_car_price
    @param intentory
*/
void add_car(string new_car_name, string new_car_color, double new_car_price, vector<Car>& inventory) {
    Car new_car = Car(new_car_name, new_car_color, new_car_price);
    inventory.push_back(new_car);
}

/*
    Sells a car by adding the price to the balance and removing the car from the inventory vector
    @param car_to_sell
    @param inventory
    @param balance
*/
void sell_car(string car_to_sell, vector<Car> inventory, double balance) {
    for (int i = 0; i < inventory.size(); i++) {
        if (car_to_sell == inventory[i].getName()) {
            balance += inventory[i].getPrice();
            int last_position = inventory.size() - 1;
            inventory[i] = inventory[last_position];
            inventory.pop_back();
        }
    }
}

int main() {
    double balance = STARTING_BALANCE;
    vector<Car> inventory;
    cout << fixed << setprecision(2);
    bool run_program = true;

    while (run_program) {
        int menu_selection = 0;
        cout << "Please select an option:" << endl;
        cout << "1 - Show Current Inventory" << endl;
        cout << "2 - Show Current Balance" << endl;
        cout << "3 - Buy a Car" << endl;
        cout << "4 - Sell a Car" << endl;
        cout << "5 - Paint a Car" << endl;
        cout << "6 - Load File" << endl;
        cout << "7 - Save File" << endl;
        cout << "8 - Quit Program" << endl;
        cin >> menu_selection;

        if (menu_selection == INVENTORY_OPTION) {
            if (inventory.size() == 0) {
                cout << "Your inventory is empty." << endl << endl;
            }
            for (int i = 0; i < inventory.size(); i++) {
                cout << inventory[i].toString() << endl;
            }
        }

        if (menu_selection == BALANCE_OPTION) {
            cout << "Your current balance is: $" << balance << endl << endl;
        }

        if (menu_selection == BUY_CAR_OPTION) {
            string new_car_name;
            string new_car_color;
            double new_car_price = 0;
            cout << "Name: ";
            cin >> new_car_name;
            cout << "Color: ";
            cin >> new_car_color;
            cout << "Price: ";
            cin >> new_car_price;
            cout << endl;

            if (new_car_price > balance) {
                cout << "You can't afford this car!" << endl << endl;
                continue;
            }

            int position = 0;
            position = check_inventory(new_car_name, inventory);

            if (position == DOES_NOT_EXIST) {
                add_car(new_car_name, new_car_color, new_car_price, inventory);
                balance -= new_car_price;
                cout << "Congratulations, you purchased a " << new_car_name << "!" << endl << endl;
            }
            else {
                cout << "This car is already in your inventory!" << endl << endl;
            }
        }

        if (menu_selection == SELL_CAR_OPTION) {
            cout << "Which car would you like to sell? ";
            string car_to_sell;
            cin >> car_to_sell;

            int position = 0;
            position = check_inventory(car_to_sell, inventory);

            if (position != DOES_NOT_EXIST) {
                balance += inventory[position].getPrice();
                int last_position = inventory.size() - 1;
                inventory[position] = inventory[last_position];
                inventory.pop_back();
                cout << endl << "You successfully sold the " << car_to_sell << "!" << endl << endl;
            }
            else if (position == DOES_NOT_EXIST) {
                cout << endl << "That car is not in your inventory." << endl << endl;
            }
        }

        if (menu_selection == PAINT_CAR_OPTION) {
            cout << "Which car would you like to paint? ";
            string car_to_paint;
            cin >> car_to_paint;

            int position = 0;
            position = check_inventory(car_to_paint, inventory);

            if (position != DOES_NOT_EXIST) {
                cout << "What is the new color of the " << car_to_paint << "? ";
                string new_color;
                cin >> new_color;
                inventory[position].paint(new_color);
                cout << endl << "Your " << car_to_paint << " was painted " << new_color << "." << endl << endl;
            }
            else if (position == DOES_NOT_EXIST) {
                cout << endl << "That car is not in your inventory." << endl << endl;
            }
        }

        if (menu_selection == LOAD_FILE_OPTION) {
            cout << "Please enter the name of the file: ";
            string file_name;
            cin >> file_name;
            fstream file;
            file.open(file_name.c_str());

            if (!file.fail()) {
                cout << endl << "File loaded successfully!" << endl << endl;

                double additional_balance = 0;
                file >> additional_balance;
                balance += additional_balance;

                string name;
                string color;
                double price = 0;

                while (true) {
                    if (file.eof()) {
                        break;
                    }
                    file >> name;
                    file >> color;
                    file >> price;
                    add_car(name, color, price, inventory);
                }
            }
            file.close();
        }

        if (menu_selection == SAVE_FILE_OPTION) {
            cout << "Please enter a file name: ";
            string save_file;
            cin >> save_file;
            cout << endl;
            ofstream file;
            file.open(save_file.c_str());
            file << balance;
            for (int i = 0; i < inventory.size(); i++) {
                file << endl << inventory[i].getName() << " " << inventory[i].getColor() << " " << inventory[i].getPrice();
            }
            file.close();
            cout << endl << "Your file was saved successfully!" << endl << endl;
        }

        if (menu_selection == QUIT_OPTION) {
            run_program = false;
        }
    }
    system("pause");
    return 0;
}
