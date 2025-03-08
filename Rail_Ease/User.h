#pragma once
#include <iostream>
#include "TrainManager.h"
#include "TicketManager.h"
#include "Admin.h"

using namespace std;

void showUserOptions(TrainManager* train, TicketManager* ticket)
{
    int choice;
    do
    {
        cout << "\n\t\t\t*************************************** User Pannel ***************************************\n";
        cout << "\t\t\t\t\t\t\t1. Reserve a Ticket\n";
        cout << "\t\t\t\t\t\t\t2. View Your Reservation\n";
        cout << "\t\t\t\t\t\t\t3. Display All Tickets\n";
        cout << "\t\t\t\t\t\t\t4. Find Shortest Path\n";
        cout << "\t\t\t\t\t\t\t5. Cancel a Ticket\n";
        cout << "\t\t\t\t\t\t\t6. Edit Ticket Details\n";
        cout << "\t\t\t\t\t\t\t7. Return to Main Menu\n";
        cout << "\t\t\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            ticket->reserveTicket(train);
            break;
        case 2:
            ticket->viewTicket();
            break;
        case 3:
            ticket->displayAllTickets();
            break;
        case 4: {
            string start, end;
            cout << "\t\t\t\t\t\t\tEnter starting station: ";
            cin >> start;
            cout << "\t\t\t\t\t\t\tEnter destination station: ";
            cin >> end;
            train->findShortestPath(start,end);
            break;
        }

        case 5:
        {
            int ticketID;
            cout << "\t\t\t\t\t\t\tEnter Ticket ID to cancel: ";
            cin >> ticketID;
            ticket->cancelTicket(ticketID);
            break;
        }
        case 6:
            ticket->editDetails();
            break;
        case 7:
            cout << "\t\t\t\t\t\t\tReturning to Main Menu...\n";
            break;
        default:
            cout << "\t\t\t\t\t\t\tInvalid choice. Try again.\n";
        }
    } while (choice != 7);
};

