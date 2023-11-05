#include <bits/stdc++.h>

using namespace std;

map<string, double> menu;
class Restaurant
{
private:
	// menu item name -> price
	map<string, int> orders; // customer name -> number of items ordered
public:
	// function to take customer orders
	void takeOrder(string customer, string itemName, int quantity)
	{
		ifstream infile("menu.txt");

		if (!infile)
		{
			cerr << "Error: could not open menu file." << endl;
			return;
		}

		string name;
		double price;
		while (infile >> name >> price)
		{
			menu[name] = price;
		}

		if (menu.find(itemName) == menu.end())
		{
			cout << "Error: " << itemName << " is not on the menu" << endl;
			return;
		}

		// order[customer]=457345

		double itemPrice = menu[itemName];
		orders[customer] += quantity;
		cout << "\n\n"
			 << customer << " ordered " << quantity << " " << itemName << "(s) at $" << itemPrice << " each" << endl;
	}

	// function to display items
	int displayOrder(string customer, string item)
	{
		double totalCost = 0;

		ifstream menuFile("menu.txt");
		if (menuFile.is_open())
		{
			string itemName;
			double price;

			cout << "*****************************************************" << endl;
			cout << "*              " << customer << " order details:           *" << endl;
			cout << "*                                             *" << endl;

			if (orders[customer] > 0)
			{
				while (menuFile >> itemName >> price)
				{
					if (itemName == item)
					{
						cout << "*              " << setw(15) << left << item << "- $" << price << " x " << orders[customer] << "      *" << endl;
						totalCost += price * orders[customer];
						break;
					}
				}
			}

			double taxRate = 0.07; // 7% tax rate
			double taxAmount = totalCost * taxRate;
			double finalCost = totalCost + taxAmount;

			cout << "*                                             *" << endl;
			cout << fixed << setprecision(2);
			cout << "*              " << setw(15) << left << "Subtotal:"
				 << "$" << setw(9) << right << totalCost << "      *" << endl;
			cout << "*              " << setw(15) << left << "Tax:"
				 << "$" << setw(9) << right << taxAmount << "      *" << endl;
			cout << "*              " << setw(15) << left << "Total cost:"
				 << "$" << setw(9) << right << finalCost << "      *" << endl;
			cout << "*                                             *" << endl;
			cout << "*                THANKS FOR YOUR ORDER        *" << endl;
			cout << "*                                             *" << endl;
			cout << "*                    order taken by: jannatul *" << endl;
			cout << "*                                             *" << endl;

			cout << "*****************************************************" << endl;

			menuFile.close();
		}
		else
		{
			cout << "Error: Unable to open file" << endl;
		}
		return 0;
	};
};

// add menu function
void addMenuItemToFile(string fileName, string itemName, double price)
{
	ofstream menuFile(fileName, ios::app);
	if (menuFile.is_open())
	{
		menuFile << itemName << " " << price << "\n";
		cout << "Item added to file successfully!" << endl;
	}
	else
	{
		cout << "Error: Unable to open file" << endl;
	}
	menuFile.close();
};

// delete item functions
void deleteMenuItemFromFile(string fileName, string itemName)
{
	ifstream inputFile(fileName);
	ofstream tempFile("temp.txt");
	bool found = false;

	if (inputFile.is_open() && tempFile.is_open())
	{
		string line;

		while (getline(inputFile, line))
		{
			// split the line into item name and price
			stringstream ss(line);
			string name;
			double price;
			ss >> name >> price;

			// check if the item name matches the one we want to delete
			if (name == itemName)
			{
				found = true;
				cout << "Item deleted successfully!" << endl;
			}
			else
			{
				// write the line to the temporary file
				tempFile << line << endl;
			}
		}

		inputFile.close();
		tempFile.close();

		// remove the original file and rename the temporary file
		if (found)
		{
			remove(fileName.c_str());
			rename("temp.txt", fileName.c_str());
		}
		else
		{
			// delete the temporary file if no item was found
			remove("temp.txt");
			cout << "Error: Item not found in file" << endl;
		}
	}
	else
	{
		cout << "Error: Unable to open file" << endl;
	}
}

// function to display menu
void displayMenu(string fileName)
{
	ifstream menuFile(fileName);
	if (menuFile.is_open())
	{
         
		cout << "***************************************           *************************************\n";
		cout << "                                         MENU\n";
		cout << "***************************************           *************************************\n\n";
			cout << setw(30);
		cout << "MENU" << "  ----------------------   " << "PRICE\n" << endl;

		string itemName;
		double price;
		while (menuFile >> itemName >> price)
		{
			cout << setw(30);
			cout << itemName << "  ----------------------   $" << price << endl;
		}
		menuFile.close();
	}
	else
	{
		cout << "Error: Unable to open file" << endl;
	}
};

int main()
{
	Restaurant myRestaurant;
	while (true)
	{
		cout << "********************************************************************************\n";
		cout << "                             WELCOME TO OUR RESTAURANT\n";
		cout << "********************************************************************************\n\n";
		cout << "1. Display Full Menu" << endl;
		cout << "2. Add new menu item" << endl;
		cout << "3. Delete item from menu " << endl;
		cout << "4. Place an order" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter your choice (1-5): ";

		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			cout << "\nAvailable Menu Items:" << endl;
			displayMenu("menu.txt");
			break;
		}
		case 2:
		{
			cout << "\nEnter the details of the new menu item: " << endl;
			string itemName;
			int price;
			cout << "Name: ";
			cin >> itemName;
			cout << "Price: $";
			cin >> price;

			transform(itemName.begin(), itemName.end(), itemName.begin(), ::toupper);
			addMenuItemToFile("menu.txt", itemName, price);
			cout << "\nNew item has been added to the menu." << endl;
			break;
		}

		case 3:
		{
			cout << "\nEnter the item name from the menu: ";
			string itemName;
			cin >> itemName;
			transform(itemName.begin(), itemName.end(), itemName.begin(), ::toupper);
			deleteMenuItemFromFile("menu.txt", itemName);
			break;
		}
		case 4:
		{
			cout << "\nAvailable Menu Items:" << endl;
			displayMenu("menu.txt");

			string customer, itemName;
			int quantity;

			cout << "\nEnter your name: ";
			cin >> customer;
			cout << "Enter the name of the item you want to order: ";
			cin >> itemName;
			transform(itemName.begin(), itemName.end(), itemName.begin(), ::toupper);
			cout << "Enter the quantity you want to order: ";
			cin >> quantity;

			myRestaurant.takeOrder(customer, itemName, quantity);
			myRestaurant.displayOrder(customer, itemName);
			break;
		}

		case 5:
		{
			cout << "\nThank you for using MyRestaurant. Goodbye!" << endl;
			return 0;
		}

		default:
		{
			cout << "\nInvalid choice. Please enter a number between 1 and 3." << endl;
			break;
		}
		}
	}
}