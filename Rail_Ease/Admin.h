#pragma once
#include <iostream>
#include "TrainManager.h"
#include "TicketManager.h"

using namespace std;

bool validateCredentials(string user, string password)
{
    return (user == "AfiaAziz" && password == "Afia231561") || (user == "ZumerDhillun" && password == "Zumer231597") || (user == "ZoyaAzad" && password == "Zoya231579") || (user == "DuaaDara" && password == "Duaa232481");
}

void showAdminOptions()
{

    cout << "\t\t\t\t\t\t\t1. View all Booked Tickets\n";
    cout << "\t\t\t\t\t\t\t2. Add Trains\n";
    cout << "\t\t\t\t\t\t\t3. Depart Train\n";
    cout << "\t\t\t\t\t\t\t4. Search Train\n";
    cout << "\t\t\t\t\t\t\t5. View Train By route\n";
    cout << "\t\t\t\t\t\t\t6. Display Train Records\n";
    cout << "\t\t\t\t\t\t\t7. Return to Main Menu\n";
}

void adminPanel(TrainManager* train)
{
    TicketManager* ticket = new TicketManager();
    string user, password;
    bool loggedIn = false;

    while (!loggedIn)
    {
        cout << "\n\t\t\t*************************************** Admin Pannel ***************************************\n";
        cout << "\t\t\t\t\t\t\tUsername: ";
        cin >> user;
        cout << "\t\t\t\t\t\t\tPassword: ";
        cin >> password;

        if (validateCredentials(user, password))
        {
            loggedIn = true;
            cout << "\t\t\t\t\t\t\tLogin Successful!\n\n";
        }
        else
        {
            cout << "\t\t\t\t\t\t\tInvalid credentials, try again.\n";
        }
    }

    int choice;
    do
    {
        showAdminOptions();
        cout << "\t\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            
            ticket->displayAllTickets();
            break;
        case 2:
            train->addTrains();
            break;
        case 3:
            train->departTrain();
            break;
        case 4:
        {
            string ID;
            cout << "\t\t\t\t\t\t\tEnter Train ID to search: ";
            cin >> ID;
            train->searchTrainByID(ID);
            break;
        }
        case 5:
            train->displayTrainsByRoute();
            break;

        case 6:
            train->displayAllTrainRecords();
            break;
        case 7:
            cout << "\t\t\t\t\t\t\tReturning to main menu";
            break;
        default:
            cout << "\t\t\t\t\t\t\tInvalid choice. Try again.\n";
        }
    } while (choice != 7);

    delete ticket; // Clean up
};





