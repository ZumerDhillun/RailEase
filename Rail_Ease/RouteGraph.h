#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <map>
#include <limits>
#include <algorithm> // For reverse

using namespace std;

class RouteGraph {
private:
    map<string, vector<pair<string, double>>> adjList; // station -> (neighbor, distance)
    map<pair<string, string>, Train*> trainDetails;    // Route-to-Train mapping
public:
    void addStation(const string& station) {
        if (adjList.find(station) == adjList.end()) {
            adjList[station] = vector<pair<string, double>>();
        }
    }

    void addRoute(const string& source, const string& destination, double distance, Train* train) {
        addStation(source);
        addStation(destination);
        adjList[source].emplace_back(destination, distance);
        adjList[destination].emplace_back(source, distance);
        trainDetails[{source, destination}] = train;
        trainDetails[{destination, source}] = train; // Bidirectional route
    }

    void displayRoutes() {
        cout << "\t\t\t\t\t\t\tAvailable Routes:\n";
        for (const auto& station : adjList) {
            cout << "Station " << station.first << " -> ";
            for (const auto& neighbor : station.second) {
                cout << "(" << neighbor.first << ", Time/Distance: " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    void findShortestPath(const string& start, const string& end) {
        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
        map<string, double> dist;
        map<string, string> parent;

        // Initialize distances
        for (const auto& station : adjList) {
            dist[station.first] = numeric_limits<double>::infinity();
        }
        dist[start] = 0;

        pq.push({ 0, start });

        while (!pq.empty()) {
            double currentDist = pq.top().first;
            string currentStation = pq.top().second;
            pq.pop();

            if (currentStation == end) break;

            for (const auto& neighbor : adjList[currentStation]) {
                string neighborName = neighbor.first;
                double weight = neighbor.second;
                double newDist = currentDist + weight;
                if (newDist < dist[neighborName]) {
                    dist[neighborName] = newDist;
                    pq.push({ newDist, neighborName });
                    parent[neighborName] = currentStation;
                }
            }
        }

        if (dist[end] == numeric_limits<double>::infinity()) {
            cout << "\t\t\t\t\t\t\tNo path found from " << start << " to " << end << endl;
            return;
        }

        // Display the shortest path
        vector<string> path;
        for (string at = end; at != start; at = parent[at]) {
            path.push_back(at);
        }
        path.push_back(start);

        reverse(path.begin(), path.end());

        cout << "\t\t\t\t\t\t\tShortest path: ";
        for (const string& station : path) {
            cout << station << " -> ";
        }
        cout << "END" << endl;

        cout << "\t\t\t\t\t\t\tShortest Distance: " << dist[end] << " km" << endl;

        // Now find the train for the shortest path route
        Train* selectedTrain = nullptr;
        double shortestTrainDistance = numeric_limits<double>::infinity();

        for (size_t i = 0; i < path.size() - 1; ++i) {
            string currentStation = path[i];
            string nextStation = path[i + 1];

            // Check if a train exists for this route (either direction)
            auto trainIt = trainDetails.find({ currentStation, nextStation });
            if (trainIt != trainDetails.end()) {
                Train* train = trainIt->second;

                // If no train has been selected or we find a train with a shorter distance, select it
                if (train->getDistance() < shortestTrainDistance) {
                    selectedTrain = train;
                    shortestTrainDistance = train->getDistance();  // Update shortest distance

                    // Display the train details immediately
                    cout << "\t\t\t\t\t\t\tTrain ID: " << selectedTrain->getTrainID() << endl;
                    cout << "\t\t\t\t\t\t\tTrain Name: " << selectedTrain->getTrainName() << endl;
                    cout << "\t\t\t\t\t\t\tAvailable Classes: " << selectedTrain->getAvailableClasses() << endl;
                    cout << "\t\t\t\t\t\t\tSeats Available: " << selectedTrain->getAvailableSeats() << endl;
                }
            }
        }
    }

};