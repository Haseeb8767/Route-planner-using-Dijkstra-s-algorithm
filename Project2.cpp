 #include<bits/stdc++.h>
using namespace std;

class Graph {
public:
    unordered_map<string, unordered_map<string, int>> adjList;  // Adjacency list for the graph

    // Add a road between two locations with specified travel time or distance
    void addRoad(const string& from, const string& to, int time) {
        adjList[from][to] = time;
        adjList[to][from] = time;  // Assuming roads are bidirectional
    }

    // Dijkstra's Algorithm to find the shortest or fastest path from start to end
    pair<int, vector<string>> dijkstra(const string& start, const string& end) {
        unordered_map<string, int> distances;  // Stores the shortest distance or time to each node
        unordered_map<string, string> previous;  // For path reconstruction
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

        // Initialize distances with infinity
        for (const auto& node : adjList) {
            distances[node.first] = INT_MAX;
        }
        distances[start] = 0;  // Starting point has a distance of 0
        pq.push({0, start});  // Push the start node to the priority queue

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            string currentNode = pq.top().second;
            pq.pop();

            // If we have reached the destination, break the loop
            if (currentNode == end) {
                break;
            }

            // Process each neighboring node
            for (const auto& neighbor : adjList[currentNode]) {
                const string& neighborNode = neighbor.first;
                int edgeWeight = neighbor.second;

                int newDist = currentDistance + edgeWeight;
                // If a shorter path is found, update the distance and the previous node
                if (newDist < distances[neighborNode]) {
                    distances[neighborNode] = newDist;
                    previous[neighborNode] = currentNode;
                    pq.push({newDist, neighborNode});
                }
            }
        }

        // Reconstruct the shortest path
        vector<string> path;
        string currentNode = end;
        while (!currentNode.empty()) {
            path.push_back(currentNode);
            currentNode = previous[currentNode];
        }

        reverse(path.begin(), path.end());

        return {distances[end], path};
    }

    // For debugging: Print the graph
    void printGraph() {
        for (const auto& node : adjList) {
            cout << node.first << ": ";
            for (const auto& neighbor : node.second) {
                cout << neighbor.first << "(" << neighbor.second << " mins) ";
            }
            cout << endl;
        }
    }

    // Check if a location is valid (exists in the graph)
    bool isValidLocation(const string& location) {
        return adjList.find(location) != adjList.end();
    }

    // Display all valid locations in the graph
    void displayLocations() {
        cout << "Available locations for selecting as start and end points:" << endl;
        int index = 1;
        for (const auto& node : adjList) {
            cout << index++ << ". " << node.first << endl;
        }
    }
};

int main() {
    Graph g;

    // Adding roads to the graph
    g.addRoad("maingate", "DAVschool", 2);  // 2 minutes
    g.addRoad("DAVschool", "staffQuarters", 2);  // 2 minutes
    g.addRoad("staffQuarters", "conventioncentre", 2);   // 2 minutes
    g.addRoad("conventioncentre", "hospital", 2);  // 2 minutes
    g.addRoad("conventioncentre", "istara", 1);  // 1 minutes
    g.addRoad("conventioncentre", "marriedhostels", 2);   // 2 minutes
    g.addRoad("marriedhostels", "adminoffice", 1);   // 1 minutes
    g.addRoad("hospital", "marriedhostels", 2);   // 2 minutes
    g.addRoad("DAVschool", "marriedhostels", 4);   // 4 minutes
    g.addRoad("DAVschool", "hospital", 3);   // 3 minutes
    g.addRoad("adminoffice", "library", 0.5);   // 0.5 minutes
    g.addRoad("library", "LHC", 0.2);   // 0.5 minutes
    g.addRoad("academicblocks", "hostelcircle", 2);   // 2 minutes
    g.addRoad("LHC", "academicblocks", 0.5);   // 0.5 minutes
    g.addRoad("library", "RCC", 0.5);   // 0.5 minutes
    g.addRoad("RCC", "hostelcircle", 1);   // 1 minutes

    // Optional: Print the graph for debugging
    // g.printGraph();

    // Display all available locations for the user to select from
    g.displayLocations();

    string start, end;

    // Ask user for start and end locations
    cout << "Enter the start location: ";
    cin >> start;
    cout << "Enter the end location: ";
    cin >> end;

    // Check if both start and end locations are valid
    if (!g.isValidLocation(start)) {
        cout << "Invalid start location: " << start << endl;
        return 1; // Exit with error code
    }

    if (!g.isValidLocation(end)) {
        cout << "Invalid end location: " << end << endl;
        return 1; // Exit with error code
    }

    // Proceed with Dijkstra's algorithm to find the shortest path
    pair<int, vector<string>> result = g.dijkstra(start, end);

    cout << "Shortest (fastest) distance from " << start << " to " << end << " is: " << result.first << " minutes" << endl;
    cout << "Route: ";
    for (const string& location : result.second) {
        cout << location << " ";
    }
    cout << endl;

    return 0;
}
