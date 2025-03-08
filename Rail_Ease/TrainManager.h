#pragma once
#include "TrainInfo.h"
#include "RouteGraph.h"
#include <sstream> // For time conversion
#include <iomanip> // For formatting

class TrainManager {
private:
    Train* front;
    Train* rear;
    Train* current;
    int trainCount;
    RouteGraph routeGraph;


public:
    TrainManager() : front(nullptr), rear(nullptr), trainCount(0) {}
    Train* getTrainByStation(const string& station) {
        current = front;
        while (current != nullptr) {
            if (current->getSource() == station || current->getDestination() == station) {
                return current;
            }
            current = current->getNextTrain();
        }
        return nullptr;
    }
    // Helper methods for validation
    bool isValidDate(const string& date) {
        if (date.size() != 10 || date[2] != '/' || date[5] != '/')
            return false;

        int day = stoi(date.substr(0, 2));
        int month = stoi(date.substr(3, 2));
        int year = stoi(date.substr(6, 4));

        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 2024)
            return false;

        if (month == 2 && day > 29)
            return false;
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
            return false;

        return true;
    }

    bool isValidTime(const string& time) {
        if (time.size() != 5 || time[2] != ':')
            return false;

        int hours = stoi(time.substr(0, 2));
        int minutes = stoi(time.substr(3, 2));

        return !(hours < 0 || hours > 12 || minutes < 0 || minutes > 59);
    }



    Train* getTrainByID(const string& trainID)
    {
        if (isEmpty())
        {
            return nullptr; // No trains available
        }

        current = front; // Start from the front of the queue

        while (current != nullptr)
        {
            if (current->getTrainID() == trainID)
            {
                return current; // Train found
            }
            current = current->getNextTrain(); // Move to the next train
        }

        return nullptr; // Train not found
    }

    void addTrains() {
        string choice;
        double distance;  // Declare the distance variable as double
        do {
            Train* newTrain = new Train();
            string input;
            int seats;

            cin.ignore(); // Clear leftover input buffer at the start of the loop
            cout << "\t\t\t\t\t\t\tEnter Train Information:" << endl;

            cout << "\t\t\t\t\t\t\tTrain ID: ";
            getline(cin, input);
            newTrain->setTrainID(input);

            cout << "\t\t\t\t\t\t\tTrain Name: ";
            getline(cin, input);
            newTrain->setTrainName(input);

            cout << "\t\t\t\t\t\t\tSource Station: ";
            getline(cin, input);
            newTrain->setSource(input);

            cout << "\t\t\t\t\t\t\tDestination Station: ";
            getline(cin, input);
            newTrain->setDestination(input);

            // Ask for the distance from source to destination
            cout << "\t\t\t\t\t\t\tEnter distance from source to destination:(in km) ";
            cin >> distance;
            newTrain->setDistance(distance);  // Set the distance in the Train object
            routeGraph.addRoute(newTrain->getSource(), newTrain->getDestination(), distance, newTrain);  // Add the route with distance

            cin.ignore();
            // Travel Date Input
            while (true)
            {
                cout << "\t\t\t\t\t\t\tTravel Date (DD/MM/YYYY): ";
                getline(cin, input);

                if (isValidDate(input))
                {
                    newTrain->setTravelDate(input);
                    break;
                }
                cout << "\t\t\t\t\t\t\tError: Invalid Date Format. Please enter in DD/MM/YYYY.\n";
            }

            // Departure Time Input
            while (true) {
                cout << "\t\t\t\t\t\t\tDeparture Time (HH:MM): ";
                getline(cin, input);
                if (isValidTime(input)) {
                    string meridian;
                    cout << "\t\t\t\t\t\t\tAM or PM? ";
                    getline(cin, meridian); // Only prompt once
                    newTrain->setDepartureTime(input + " " + meridian);
                    break;
                }
                cout << "\t\t\t\t\t\t\tError: Invalid Time Format. Please enter in HH:MM.\n";
            }

            // Arrival Time Input
            while (true) {
                cout << "\t\t\t\t\t\t\tArrival Time (HH:MM): ";
                getline(cin, input);
                if (isValidTime(input)) {
                    string meridian;
                    cout << "\t\t\t\t\t\t\tAM or PM? ";
                    getline(cin, meridian); // Only prompt once
                    newTrain->setArrivalTime(input + " " + meridian);
                    break;
                }
                cout << "\t\t\t\t\t\t\tError: Invalid Time Format. Please enter in HH:MM.\n";
            }

            // Available Classes Input
            cout << "\t\t\t\t\t\t\tAvailable Classes (Economy, AC Lower, AC Business): ";
            getline(cin, input);
            newTrain->setAvailableClasses(input);

            // Available Seats Input
            while (true) {
                cout << "\t\t\t\t\t\t\tNumber of Available Seats: ";
                cin >> seats;
                if (seats > 0) {
                    newTrain->setAvailableSeats(seats);
                    break;
                }
                cout << "\t\t\t\t\t\t\tError: Number of seats must be positive.\n";
            }

            // Add train to queue and route graph
            routeGraph.addRoute(newTrain->getSource(), newTrain->getDestination(), distance, newTrain);

            // Add the new train to the train list (linked list)
            if (rear == nullptr) {
                front = rear = newTrain;
            }
            else {
                rear->setNextTrain(newTrain);
                rear = newTrain;
            }

            trainCount++;
            cout << "\t\t\t\t\t\t\tTrain added successfully!" << endl;

            // Ask if the admin wants to add another train
            cout << "\t\t\t\t\t\t\tDo you want to add another train? (Y/N): ";
            cin >> choice;

        } while (choice != "N" && choice != "n");
    }

    // Train departs the station (removes from the front)
    void departTrain()
    {
        if (isEmpty())
        {
            cout << "\n\t\t\t\t\t\t\tNo trains available to depart." << endl;
            return;
        }

        // Take the train at the front of the queue
        current = front;

        // Move the front pointer to the next train
        front = front->getNextTrain();

        // If the queue becomes empty after removing the front train
        if (front == nullptr)
        {
            rear = nullptr; // Set rear to null as well
        }

        // Display the details of the departing train
        cout << "\n\t\t\t\t\t\t\tTrain Departure Information:" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

        cout << "\t\t\t\t\t\t\tTrain ID: " << current->getTrainID() << endl;
        cout << "\t\t\t\t\t\t\tTrain Name: " << current->getTrainName() << endl;
        cout << "\t\t\t\t\t\t\tSource Station: " << current->getSource() << endl;
        cout << "\t\t\t\t\t\t\tDestination Station: " << current->getDestination() << endl;
        cout << "\t\t\t\t\t\t\tDistance from Source to Destination Station: " << current->getDestination() << endl;
        cout << "\t\t\t\t\t\t\tTravel Date: " << current->getTravelDate() << endl;
        cout << "\t\t\t\t\t\t\tDeparture Time: " << current->getDepartureTime() << endl;
        cout << "\t\t\t\t\t\t\tArrival Time: " << current->getArrivalTime() << endl;
        cout << "\t\t\t\t\t\t\tAvailable Classes: " << current->getAvailableClasses() << endl;
        cout << "\t\t\t\t\t\t\tAvailable Seats: " << current->getAvailableSeats() << endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;


        trainCount--;
        delete current; // Deallocate memory of the train node that has been removed
    }

    // Search for a train by its ID
    void searchTrainByID(string trainID)
    {
        if (isEmpty())
        {
            cout << "\n\t\t\t\t\t\t\tNo trains available to search.\n";
            return;
        }

        current = front; // Start from the front of the queue

        while (current != nullptr)
        {
            if (current->getTrainID() == trainID)
            {
                // Train found, display its details
                cout << "\n\t\t\t\t\t\t\tTrain Found:" << endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

                cout << "\t\t\t\t\t\t\tTrain ID: " << current->getTrainID() << endl;
                cout << "\t\t\t\t\t\t\tTrain Name: " << current->getTrainName() << endl;
                cout << "\t\t\t\t\t\t\tSource Station: " << current->getSource() << endl;
                cout << "\t\t\t\t\t\t\tDestination Station: " << current->getDestination() << endl;
                cout << "\t\t\t\t\t\t\tDistance from Source to Destination Station: " << current->getDestination() << endl;
                cout << "\t\t\t\t\t\t\tTravel Date: " << current->getTravelDate() << endl;
                cout << "\t\t\t\t\t\t\tDeparture Time: " << current->getDepartureTime() << endl;
                cout << "\t\t\t\t\t\t\tArrival Time: " << current->getArrivalTime() << endl;
                cout << "\t\t\t\t\t\t\tAvailable Classes: " << current->getAvailableClasses() << endl;
                cout << "\t\t\t\t\t\t\tAvailable Seats: " << current->getAvailableSeats() << endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

                return;
            }
            current = current->getNextTrain(); // Move to the next train
        }

        cout << "\n\t\t\t\t\t\t\tTrain with ID " << trainID << " not found.\n\n";
        cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

    }


    void displayAllTrainRecords()
    {
        if (isEmpty())
        {
            cout << "\n\t\t\t\t\t\t\tNo trains available to display.\n";
            return;
        }

        current = front;
        cout << "\n\t\t\t\t\t\t\tTrain List:" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

        while (current != nullptr)
        {
            cout << "\t\t\t\t\t\t\tTrain ID: " << current->getTrainID() << endl;
            cout << "\t\t\t\t\t\t\tTrain Name: " << current->getTrainName() << endl;
            cout << "\t\t\t\t\t\t\tSource Station: " << current->getSource() << endl;
            cout << "\t\t\t\t\t\t\tDestination Station: " << current->getDestination() << endl;
            cout << "\t\t\t\t\t\t\tDistance From source to Destination Station: " << current->getDistance() << endl;
            cout << "\t\t\t\t\t\t\tDeparture Time: " << current->getDepartureTime() << endl;
            cout << "\t\t\t\t\t\t\tArrival Time: " << current->getArrivalTime() << endl;
            cout << "\t\t\t\t\t\t\tAvailable Classes: " << current->getAvailableClasses() << endl;
            cout << "\t\t\t\t\t\t\tAvailable Seats: " << current->getAvailableSeats() << endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

            current = current->getNextTrain();
        }
    }



    void displayTrainsByRoute()
    {
        string departureCity, destinationCity;
        bool trainFound = false;
        cin.ignore();
        // Keep asking for input until trains are found or the user exits
        do {
            cout << "\n\t\t\t\t\t\t\tEnter Departure City: ";
            getline(cin, departureCity);

            cout << "\t\t\t\t\t\t\tEnter Destination City: ";
            getline(cin, destinationCity);

            if (isEmpty()) {
                cout << "\n\t\t\t\t\t\t\tNo trains available to search by route.\n";
                return;
            }

            current = front; // Start from the front of the queue
            cout << "\n\t\t\t\t\t\t\tTrains Available on Route from " << departureCity << " to " << destinationCity << ":" << endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

            // Search for trains on the specified route
            while (current != nullptr)
            {
                if (current->getSource() == departureCity && current->getDestination() == destinationCity)
                {
                    // Train found, display its details
                    cout << "\t\t\t\t\t\t\tTrain ID: " << current->getTrainID() << endl;
                    cout << "\t\t\t\t\t\t\tTrain Name: " << current->getTrainName() << endl;
                    cout << "\t\t\t\t\t\t\tSource Station: " << current->getSource() << endl;
                    cout << "\t\t\t\t\t\t\tDestination Station: " << current->getDestination() << endl;
                    cout << "\t\t\t\t\t\t\tDistance from Source to Destination Station: " << current->getDistance() << endl;
                    cout << "\t\t\t\t\t\t\tTravel Date: " << current->getTravelDate() << endl;
                    cout << "\t\t\t\t\t\t\tDeparture Time: " << current->getDepartureTime() << endl;
                    cout << "\t\t\t\t\t\t\tArrival Time: " << current->getArrivalTime() << endl;
                    cout << "\t\t\t\t\t\t\tAvailable Classes: " << current->getAvailableClasses() << endl;
                    cout << "\t\t\t\t\t\t\tAvailable Seats: " << current->getAvailableSeats() << endl;
                    cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;

                    trainFound = true;
                }
                current = current->getNextTrain(); // Move to the next train
            }

            // If no train is found, ask the user if they want to try again
            if (!trainFound) {
                cout << "\n\t\t\t\t\t\t\tNo trains found on this route.\n";
                cout << "\t\t\t\t\t\t\tWould you like to search for another route? (Y/N): ";
                char choice;
                cin >> choice;
                cin.ignore(); // Clear the input buffer before the next getline

                if (choice != 'Y' && choice != 'y') {
                    cout << "\n\t\t\t\t\t\t\tExiting search.\n";
                    return; // Exit if the user doesn't want to search again
                }
            }

        } while (!trainFound); // Repeat the process until a valid route is found
    }

    // Find the shortest path between stations
    void findShortestPath(const string& start, const string& end) {
        routeGraph.findShortestPath(start,end);
    }


    bool isEmpty() {
        return front == nullptr;
    }

    int getTrainCount() const {
        return trainCount;
    }
};
