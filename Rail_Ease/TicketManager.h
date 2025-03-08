#pragma once
#include "TicketInfo.h"
#include "TrainInfo.h"
#include "TrainManager.h"
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
#include <string>



class TicketManager
{
private:
    Ticket* head;  // Points to the start of the list
    Ticket* current;  // Used for traversing the list
    int ticketCount;  // Count of tickets in the list
    Train* train;
    Ticket* tail;

    const int rows = 10;
    const int cols = 3;
    string Seats[10][3] = {
        {"1", "11", "21"},
        {"2", "12", "22"},
        {"3", "13", "23"},
        {"4", "14", "24"},
        {"5", "15", "25"},
        {"6", "16", "26"},
        {"7", "17", "27"},
        {"8", "18", "28"},
        {"9", "19", "29"},
        {"10", "20", "30"}
    };



public:

    bool isValidCNIC(const string& cnic) {
        // CNIC should match the pattern XXXXX-XXXXXXX-X
        if (cnic.length() != 15 || cnic[5] != '-' || cnic[13] != '-') return false;
        for (int i = 0; i < cnic.length(); i++) {
            if (i == 5 || i == 13) continue;
            if (!isdigit(cnic[i])) return false;
        }
        return true;
    }

    bool isValidContact(const string& contact) {
        // Contact should match the pattern 03XXXXXXXXX
        if (contact.length() != 11 || contact.substr(0, 2) != "03") return false;
        for (char c : contact) {
            if (!isdigit(c)) return false;
        }
        return true;
    }


    TicketManager()
    {
        head = nullptr;
        train = new Train(); // Initialize the Train object
        tail = nullptr;
        ticketCount = 0;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    // Add a ticket to the list
    void addTicket(Ticket* newTicket)
    {
        if (head == nullptr)
        {
            head = newTicket;  // First ticket becomes the head
        }
        else
        {
            Ticket* temp = head;
            while (temp->getNextT() != nullptr)  // Traverse to the end of the list
            {
                temp = temp->getNextT();
            }
            temp->setNext(newTicket);  // Append the new ticket at the end
        }
        ticketCount++;
        cout << "\t\t\t\t\t\t\tTicket added successfully.\n";
    }

    // Cancel a ticket by ID
    void cancelTicket(int ticketID) {
        if (isEmpty()) {
            cout << "\t\t\t\t\t\t\tNo tickets available to cancel.\n";
            return;
        }

        Ticket* prev = nullptr;
        current = head;

        while (current != nullptr) {
            if (current->getTicketID() == ticketID) {
                if (prev == nullptr) {
                    head = current->getNextT(); // Removing head
                }
                else {
                    prev->setNext(current->getNextT());
                }

                delete current;
                ticketCount--;
                cout << "\t\t\t\t\t\t\tTicket with ID " << ticketID << " cancelled successfully.\n";
                return;
            }
            prev = current;
            current = current->getNextT();
        }

        cout << "\t\t\t\t\t\t\tTicket with ID " << ticketID << " not found.\n";
    }


    // Display all tickets
    void displayAllTickets()
    {
        if (isEmpty())
        {
            cout << "\t\t\t\t\t\t\tList is empty, nothing to display.\n";
            return;
        }
        current = head;
        cout << "\n\t\t\t\t\t\t\tTicket List:\n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

        while (current != nullptr)
        {
            cout << "\t\t\t\t\t\t\tTicket ID: " << current->getTicketID() << endl;
            cout << "\t\t\t\t\t\t\tPassenger Name: " << current->getPassengerName() << endl;
            cout << "\t\t\t\t\t\t\tAge: " << current->getAge() << endl;
            cout << "\t\t\t\t\t\t\tCNIC: " << current->getNIC() << endl;
            cout << "\t\t\t\t\t\t\tContact: " << current->getContact() << endl;
            cout << "\t\t\t\t\t\t\tTrain Name: " << current->getTrainName() << endl;
            cout << "\t\t\t\t\t\t\tTrain ID: " << current->getTicketID() << endl;
            cout << "\t\t\t\t\t\t\tSource: " << current->getSource() << endl;
            cout << "\t\t\t\t\t\t\tDestination: " << current->getDestination() << endl;
            cout << "\t\t\t\t\t\t\tTravel Date: " << current->getTravelDate() << endl;
            cout << "\t\t\t\t\t\t\tSeat Number: " << current->getSeatNumber() << endl;

            cout << "\t\t\t\t\t\t\tPrice: $" << current->getPrice() << endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

            current = current->getNextT();
        }
    }


    // Edit ticket details
    void editDetails() {
        string fName, lName, NIC, Contact;
        int search;

        cout << "\t\t\t\t\t\t\tEDIT DETAILS:\n\n";

        if (isEmpty()) {
            cout << "\t\t\t\t\t\t\tNo tickets available to edit.\n";
            return;
        }

        cout << "\t\t\t\t\t\t\tEnter ticket ID to edit: ";
        cin >> search;

        current = head;  // Start from the head of the list
        while (current != nullptr) {
            if (current->getTicketID() == search) {  // Found the ticket to edit
                cout << "\t\t\t\t\t\t\tTicket found. Enter new details:\n";

                // Editing passenger's name
                cout << "\t\t\t\t\t\t\tEnter First Name of Passenger: ";
                cin >> fName;
                cout << "\t\t\t\t\t\t\tEnter Last Name of Passenger: ";
                cin >> lName;
                string Name = fName + " " + lName;
                current->setPassengerName(Name);

                // Editing CNIC
                while (true) {
                    cout << "\t\t\t\t\t\t\tEnter CNIC Number (13 digits): ";
                    cin >> NIC;
                    if (NIC.length() == 13) {
                        current->setNIC(NIC);
                        break;  // Exit the loop if CNIC is valid
                    }
                    else {
                        cout << "\t\t\t\t\t\t\tInvalid CNIC! Please enter a valid 13-digit CNIC.\n";
                    }
                }

                // Editing Contact Number
                while (true) {
                    cout << "\t\t\t\t\t\t\tEnter Contact Number (11 digits): ";
                    cin >> Contact;
                    if (Contact.length() == 11) {
                        current->setContact(Contact);
                        break;  // Exit the loop if contact number is valid
                    }
                    else {
                        cout << "\t\t\t\t\t\t\tInvalid Phone Number! Please enter a valid 11-digit number.\n";
                    }
                }

                cout << "\t\t\t\t\t\t\tTicket details updated successfully.\n";
                return;  // Exit after updating
            }
            current = current->getNextT();  // Move to the next ticket
        }

        cout << "\t\t\t\t\t\t\tTicket ID not found.\n";  // Ticket with given ID not found
    }

    string SeatChoose() {
        cout << "\n\n\t\t\t\t\t\t\tDisplay the Sitting Arrangement" << endl;
        cout << "\n\n\t\t\t\t\t\t\tA" << "\t" << " B" << "\t" << " C" << "\t\n";
        for (int i = 0; i < rows; i++) {
            cout << "\n\n\t\t\t\t\t\t\t";
            for (int j = 0; j < cols; j++) {
                cout << Seats[i][j] << "\t";
            }
            cout << endl;
        }

        string SeatNum;
        bool found = false;

        // Seat validation loop
        while (!found) {
            cout << "\n\n\t\t\t\t\t\t\tEnter the seat number that you chose: ";
            cin >> SeatNum;

            // Ensure SeatNum is a valid number and between 1 and 30
            if (stoi(SeatNum) < 1 || stoi(SeatNum) > 30) {
                cout << "\n\n\t\t\t\t\t\t\tInvalid seat number, please enter a valid Seat Number between 1 and 30! \n";
                continue;  // Go back to the start of the loop
            }

            // Check if seat is available
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (Seats[i][j] == SeatNum) {
                        Seats[i][j] = "XX";  // Mark the seat as taken
                        found = true;  // Exit the loop after marking the seat
                        break;
                    }
                }
                if (found) break;  // Exit outer loop if the seat was found
            }

            // If seat was not found or was already taken
            if (!found) {
                cout << "\n\n\t\t\t\t\t\t\tSeat already taken or invalid! Please select another seat.\n";
            }
        }

        // Display updated seating arrangement
        cout << "\n\n\t\t\t\t\t\t\tUpdated Sitting Arrangement" << endl;
        cout << "\n\n\t\t\t\t\t\t\tA" << "\t" << " B" << "\t" << " C" << "\t\n";
        for (int i = 0; i < rows; i++) {
            cout << "\n\n\t\t\t\t\t\t\t";
            for (int j = 0; j < cols; j++) {
                cout << Seats[i][j] << "\t";
            }
            cout << endl;
        }

        return SeatNum;  // Return the selected seat number
    }
    // Create a ticket

void reserveTicket(TrainManager* train) {
            string fName, lName, NIC, Contact;
            int age;
            Ticket* newTicket = new Ticket();  // Create a new ticket instance
    
            // Get passenger details
            cout << "\n\t\t\t\t\t\t\tEnter First Name: ";
            cin >> fName;
            cout << "\t\t\t\t\t\t\tEnter Last Name: ";
            cin >> lName;
            newTicket->setPassengerName(fName + " " + lName);  // Combine first and last name
    
            // Get passenger age with validation
            cout << "\t\t\t\t\t\t\tEnter Age: ";
            while (true) {
                cin >> age;
                if (age > 0) {
                    newTicket->setAge(age);  // Set the age of the passenger
                    break;
                }
                else {
                    cout << "\t\t\t\t\t\t\tInvalid age! Please enter a valid positive number.\n";
                }
            }
    
            // Get CNIC with validation
            cout << "\t\t\t\t\t\t\tEnter CNIC Number: ";
            while (true) {
                cin >> NIC;
                if (NIC.length() == 13) {
                    newTicket->setNIC(NIC);  // Set CNIC if it's valid
                    break;
                }
                else {
                    cout << "\t\t\t\t\t\t\tInvalid CNIC! Please enter a valid 13-digit CNIC.\n";
                }
            }
    
            // Get contact number with validation
            cout << "\t\t\t\t\t\t\tEnter Contact Number: ";
            while (true) {
                cin >> Contact;
                if (Contact.length() == 11) {
                    newTicket->setContact(Contact);  // Set contact number if valid
                    break;
                }
                else {
                    cout << "\t\t\t\t\t\t\tInvalid Phone Number! Please enter a valid 11-digit number.\n";
                }
            }
    
            string trainClass;
            cout << "\t\t\t\t\t\t\tChoose Train Class (Economy, AC Lower, AC Business): ";
            cin.ignore();
            getline(cin,trainClass);
           // Validate train class
                while (trainClass != "Economy" && trainClass != "AC Lower" && trainClass != "AC Business")
                { 
                    cout << "\t\t\t\t\t\t\tInvalid class! Please choose (Economy, AC Lower, AC Business): "; 
                    getline(cin, trainClass);
                }
            newTicket->setTicketClass(trainClass);
    
            newTicket->setTrainPrice(trainClass);
    
           
            // Get train details: Departure city and destination city
    
            string  trainID;
           
            train->displayTrainsByRoute();
    
            // Select a train by ID
            cout << "\n\t\t\t\t\t\t\tSelect a Train by ID: ";
            cin >> trainID;
    
            // Find the selected train
            Train* selectedTrain = train->getTrainByID(trainID); // Get the train by ID
    
            if (selectedTrain) {
                // Display selected train details
                cout << "\n\t\t\t\t\t\t\tSelected Train Details:\n";
                cout << "\t\t\t\t\t\t\tTrain ID: " << selectedTrain->getTrainID() << endl;
                cout << "\t\t\t\t\t\t\tTrain Name: " << selectedTrain->getTrainName() << endl;
                cout << "\t\t\t\t\t\t\tSource: " << selectedTrain->getSource() << endl;
                cout << "\t\t\t\t\t\t\tDestination: " << selectedTrain->getDestination() << endl;
                cout << "\t\t\t\t\t\t\tDeparture Time: " << selectedTrain->getDepartureTime() << endl;
                cout << "\t\t\t\t\t\t\tArrival Time: " << selectedTrain->getArrivalTime() << endl;
                cout << "\t\t\t\t\t\t\tDistance from Source to Destination Station: " << selectedTrain->getDistance() << endl;
                newTicket->setTrainDetails(*selectedTrain);  // Set the selected train details for the ticket
            }
            else {
                cout << "\t\t\t\t\t\t\tInvalid Train ID! Could not find the train.\n";
                return;  // Exit if the train ID is invalid
            }
    
            // Proceed with seat selection
            string seatNumber = SeatChoose();  // Assuming SeatChoose() allows the user to select a seat
            newTicket->setSeatNumber(seatNumber);  // Set the selected seat number
    
            // Process payment (assuming the Payment method is defined in the Ticket class)
            newTicket->Payment();
    
            // Generate and assign ticket ID
            srand(time(0));
            int ticketID = rand();  // Generate a random ticket ID
            newTicket->setTicketID(ticketID);  // Set the ticket ID for the new ticket
    
            // Display the confirmation message with the generated ticket ID
            cout << "\n\n\t\t\t\t\tTicket Reserved Successfully! Your Ticket ID is: " << ticketID << endl;
    
            // Now, add the ticket to the linked list
            if (head == nullptr) {
                // If the list is empty, the new ticket becomes the head
                head = newTicket;
            }
            else {
                // Traverse to the end of the list and add the new ticket
                Ticket* current = head;
                while (current->getNextT() != nullptr) {
                    current = current->getNextT();
                }
                // Link the new ticket to the last ticket
                current->setNext(newTicket);
            }
    
            ticketCount++;  // Increment the ticket count
        }



    void viewTicket()
    {
        int search;
        string choice;
        bool ticketFound = false;
        current = head;

        while (true)
        {
            cout << "\t\t\t\t\t\t\tDo You Want to View Your First Booking? Press 1\n";
            cout << "\t\t\t\t\t\t\tDo You Want to Search Other Bookings? Press 2\n";
            cout << "\t\t\t\t\t\t\tEnter Choice (1-2): ";
            cin >> choice;
            if (choice == "1")
            {
                if (head != nullptr)
                {
                    search = head->getTicketID();  // The first ticket (head) is considered the most recent
                    ticketFound = true;
                    break;
                }
                else
                {
                    cout << "\t\t\t\t\t\t\tNo tickets available.\n";
                    return;
                }
            }
            else if (choice == "2") {
                cout << "\t\t\t\t\t\t\tEnter Your Booking ID: ";
                cin >> search;
                ticketFound = true;
                break;
            }
            else {
                cout << "\t\t\t\t\t\t\tInvalid input. Please choose 1 or 2.\n";
            }

        }
        while (current != nullptr) {
            if (current->getTicketID() == search)
            {
                cout << "\n\t\t\t\t\t\t\tBooking Details:\n";
                cout << "\t\t\t\t\t\t\tBooking ID: " << current->getTicketID() << endl;
                cout << "\t\t\t\t\t\t\tName: " << current->getPassengerName() << endl;
                cout << "\t\t\t\t\t\t\tAge: " << current->getAge() << endl;
                cout << "\t\t\t\t\t\t\tNIC: " << current->getNIC() << endl;
                cout << "\t\t\t\t\t\t\tContact: " << current->getContact() << endl;
                cout << "\t\t\t\t\t\t\tTrain ID: " << current->getTrainID() << endl;
                cout << "\t\t\t\t\t\t\tTrain Name: " << current->getTrainName() << endl;
                cout << "\t\t\t\t\t\t\tTrain Class: " << current->getTicketClass() << endl;
                cout << "\t\t\t\t\t\t\tSeat Number: " << current->getSeatNumber() << endl;
                cout << "\t\t\t\t\t\t\tDate of Booking: " << current->getTravelDate() << endl;
                cout << "\t\t\t\t\t\t\tSource: " << current->getSource() << endl;
                cout << "\t\t\t\t\t\t\tDestination: " << current->getDestination() << endl;
                cout << "\t\t\t\t\t\t\tDistance from Source to Destination Station: " << current->getDistance() << endl;

                cout << endl << endl;
                return;  // Exit once ticket is found and details are displayed
            }
            current = current->getNextT();  // Move to the next ticket
        }

        // If no ticket was found
        if (!ticketFound) {
            cout << "\t\t\t\t\t\t\tNo Bookings Exist with the provided ID.\n";
        }
    }


};
