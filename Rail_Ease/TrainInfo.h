#pragma once
#include <iostream>
#include <iomanip> // For formatting output
using namespace std;

class Train
{
public:
    string trainID, trainName, source, destination, travelDate, departureTime, arrivalTime, availableClasses;
    int availableSeats;
    double Distance;
    Train* nextTrain; // Only nextTrain is needed in singly linked list
    string meridian;  // AM/PM for departure time
    Train* next;

    Train()
    {
        availableSeats = 0;
        nextTrain = nullptr;
        next = nullptr;
    }

    void decreaseSeats()
    {
        if (availableSeats > 0)
        {
            availableSeats--; // Decrease the available seats
        }
        else
        {
            cout << "\t\t\t\t\tNo available seats left!" << endl;
        }
    }

    // Setters and Getters
    void setTrainID(string ID) { trainID = ID; }
    void setTrainName(string name) { trainName = name; }
    void setSource(string src) { source = src; }
    void setDestination(string dest) { destination = dest; }
    void setDistance(double dis) { Distance = dis; }
    void setTravelDate(string date) { travelDate = date; }
    void setDepartureTime(string time) { departureTime = time; }
    void setArrivalTime(string time) { arrivalTime = time; }
    void setAvailableClasses(string classes) { availableClasses = classes; }
    void setAvailableSeats(int seats) { availableSeats = seats; }
    void setNextTrain(Train* next) { nextTrain = next; }
    void setMeridian(string m) { meridian = m; }

    string getTrainName() const { return trainName; }
    string getTrainID() const { return trainID; }
    string getSource() const { return source; }
    string getDestination() const { return destination; }
    double getDistance() const { return Distance; }
    string getTravelDate() const { return travelDate; }
    string getDepartureTime() const { return departureTime; }
    string getArrivalTime() const { return arrivalTime; }
    string getAvailableClasses() { return availableClasses; }
    int getAvailableSeats() { return availableSeats; }
    Train* getNextTrain() { return nextTrain; }
    string getMeridian() { return meridian; }

    // SET TRAIN DETAILS ///
    void setTrainDetails(Train* train)
    {
        trainID = train->getTrainID();
        trainName = train->getTrainName();
        source = train->getSource();
        destination = train->getDestination();
        travelDate = train->getTravelDate();
        departureTime = train->getDepartureTime();
        arrivalTime = train->getArrivalTime();
        Distance = train->getDistance();
    }
};






