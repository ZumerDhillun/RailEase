#pragma once
#include "TrainInfo.h"
#include <iostream>
#include <string>
using namespace std;

class Ticket
{
private:
    int ticketID, age;
    string passengerName, NIC, contact;
    string trainName, trainID;
    string source, destination, travelDate, seatNumber, ticketClass;
    float price;
    double Distance;
    string departureTime;
    string arrivalTime;
    Ticket* next;
    Ticket* head;
    int ticketCount;

public:
    Ticket* nextTicket;
    Ticket() : nextTicket(nullptr), ticketID(0), price(0.0f), head(nullptr), ticketCount(0) {}

    void setNext(Ticket* newNext) { next = newNext; }
    Ticket* getNextT() { return next; }

    void setTicketID(int id) { ticketID = id; }
    int getTicketID() { return ticketID; }

    void setPassengerName(string name) { passengerName = name; }
    string getPassengerName() { return passengerName; }

    void setAge(int a) { age = a; }
    int getAge() { return age; }

    void setNIC(string n) { NIC = n; }
    string getNIC() { return NIC; }

    void setDistance(double dis) { Distance = dis; }
    double getDistance() const { return Distance; }

    void setContact(string c) { contact = c; }
    string getContact() { return contact; }

    void setTrainName(string t) { trainName = t; }
    string getTrainName() { return trainName; }

    void setTrainID(string t) { trainID = t; }
    string getTrainID() { return trainID; }

    void setSource(string s) { source = s; }
    string getSource() { return source; }

    void setDestination(string d) { destination = d; }
    string getDestination() { return destination; }

    void setTravelDate(string d) { travelDate = d; }
    string getTravelDate() { return travelDate; }

    void setSeatNumber(string s) { seatNumber = s; }
    string getSeatNumber() { return seatNumber; }

    void setTicketClass(string c) { ticketClass = c; }
    string getTicketClass() { return ticketClass; }

    void setPrice(float p) { price = p; }
    float getPrice() { return price; }

    void setDepartureTime(const string& time) { departureTime = time; }
    void setArrivalTime(const string& time) { arrivalTime = time; }

    string getDepartureTime() const { return departureTime; }
    string getArrivalTime() const { return arrivalTime; }

    void addTicket(Ticket* newTicket)
    {
        if (head == nullptr)
        {
            head = newTicket; // First ticket becomes the head
        }
        else
        {
            Ticket* temp = head;
            while (temp->getNextT() != nullptr) // Traverse to the end of the list
            {
                temp = temp->getNextT();
            }
            temp->setNext(newTicket); // Append the new ticket at the end
        }
        ticketCount++;
        cout << "\t\t\t\t\t\t\tTicket added successfully.\n";
    }


    void setTrainPrice(const string& trainClass)
    {
        if (trainClass == "Economy")
        {
            price = 2500;
            setPrice(price);
            ticketClass = "Economy [No Berth]";
        }
        else if (trainClass == "AC Lower")
        {
            price = 3500;
            setPrice(price);
            ticketClass = "AC Lower [Berth Included]";
        }
        else if (trainClass == "AC Business")
        {
            price = 4500;
            setPrice(price);
            ticketClass = "AC Business [Berth Included]";
        }
        else
        {
            cout << "Invalid class selected!\n";
            return;
        }

        cout << "\n\t\t\t\t\t\t\tTicket Class: " << ticketClass << "\n";
        cout << "\t\t\t\t\t\t\tTicket Price: " << price << " PKR\n";
    }


    void setTrainDetails(const Train& train)
    {
        setTrainName(train.getTrainName());
        setTrainID(train.getTrainID());
        setSource(train.getSource());
        setDestination(train.getDestination());
        setTravelDate(train.getTravelDate());
        setDepartureTime(train.getDepartureTime());
        setArrivalTime(train.getArrivalTime());
        setDistance(train.getDistance());

    }

    void Payment()
    {
        string cardNumber, securityCode, dob;
        string accNum, accHolderFName, accHolderLName;
        int payChoice;
        bool valid = false;

        cout << "\n\n\t\t\t\t\t=============== PAYMENT DETAILS ===============\n";
        cout << "\t\t\t\t\tChoose Payment Method:\n";
        cout << "\t\t\t\t\t1. JazzCash\n";
        cout << "\t\t\t\t\t2. EasyPaisa\n";
        cout << "\t\t\t\t\t3. Credit/Debit Card\n";
        cout << "\n\n\t\t\t\t\tEnter Choice (1-3): ";
        cin >> payChoice;

        while (payChoice < 1 || payChoice > 3)
        {
            cout << "\t\t\t\t\tInvalid choice. Please try again: ";
            cin >> payChoice;
        }

        // Use switch statement based on the valid choice
        switch (payChoice)
        {
        case 1:
        { // JazzCash Payment
            do
            {
                cout << "\n\n\t\t\t\t\tEnter JazzCash Mobile Account Number: ";
                cin >> accNum;
                if (accNum.length() == 11)
                {
                    valid = true;
                }
                else
                {
                    cout << "\t\t\t\t\tInvalid number! Please enter a valid 11-digit number.\n";
                }
            } while (!valid);

            cout << "\t\t\t\t\tEnter Account Holder's First Name: ";
            cin >> accHolderFName;
            cout << "\t\t\t\t\tEnter Account Holder's Last Name: ";
            cin >> accHolderLName;
            break;
        }

        case 2:
        { // EasyPaisa Payment
            do
            {
                cout << "\n\n\t\t\t\t\tEnter EasyPaisa Mobile Account Number: ";
                cin >> accNum;
                if (accNum.length() == 11)
                {
                    valid = true;
                }
                else
                {
                    cout << "\t\t\t\t\tInvalid number! Please enter a valid 11-digit number.\n";
                }
            } while (!valid);

            cout << "\t\t\t\t\tEnter Account Holder's First Name: ";
            cin >> accHolderFName;
            cout << "\t\t\t\t\tEnter Account Holder's Last Name: ";
            cin >> accHolderLName;
            break;
        }

        case 3:
        { // Credit/Debit Card Payment
            do
            {
                cout << "\n\n\t\t\t\t\tEnter Credit/Debit Card Number (16 digits): ";
                cin >> cardNumber;
                if (cardNumber.length() == 16)
                {
                    valid = true;
                }
                else
                {
                    cout << "\t\t\t\t\tInvalid card number! Please enter a valid 16-digit number.\n";
                }
            } while (!valid);

            valid = false;
            do
            {
                cout << "\n\n\t\t\t\t\tEnter CVV (3 digits): ";
                cin >> securityCode;
                if (securityCode.length() == 3)
                {
                    valid = true;
                }
                else
                {
                    cout << "\\t\t\t\t\t\t\tInvalid Card Verification Value / Security Code! Please enter a valid 3-digit.\n";
                }
            } while (!valid);

            cout << "\n\n\t\t\t\t\tEnter Expiry Date (DD/MM/YYYY): ";
            cin >> dob;
            break;
        }

        default:
            cout << "\t\t\t\t\tInvalid choice.\n";
            break;
        }

        cout << "\n\n\t\t\t\t\tPayment successful! Thank you for using our service.\n";
    }
};





