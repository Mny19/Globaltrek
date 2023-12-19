#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <climits>
#include <ctime>

using namespace std;

class Graph {
    unordered_map<string, vector<pair<string, int>>> g;

public:
    void addEdge(const string& start, const string& end, int wt) {
        g[start].push_back({end, wt});
        g[end].push_back({start, wt});
    }

    int shortestPath(const string& dep, const string& des, vector<string>& path) {
        unordered_map<string, int> dist;
        unordered_map<string, string> parent;
        for (const auto& x : g) {
            dist[x.first] = INT_MAX;
            parent[x.first] = "";
        }

        priority_queue<pair<int, string>> q;
        q.push({0, dep});
        dist[dep] = 0;

        while (!q.empty()) {
            string current = q.top().second;
            q.pop();

            if (current == des)
                break;

            for (const auto& neighbor : g[current]) {
                string next = neighbor.first;
                int weight = neighbor.second;
                int newDist = dist[current] + weight;
                if (newDist < dist[next]) {
                    dist[next] = newDist;
                    parent[next] = current;
                    q.push({-newDist, next});
                }
            }
        }

        if (dist[des] == INT_MAX) {
            cout << "No path found from " << dep << " to " << des << endl;
            return -1;
        }

        string current = des;
        while (current != "") {
            path.push_back(current);
            current = parent[current];
        }
        reverse(path.begin(), path.end());

        return dist[des];
    }

    int calculatePrice(int sp, int choice) {
        if (choice == 1)
            return sp * 7;
        if (choice == 2)
            return sp * 8;
        if (choice == 3)
            return sp * 3;
        if (choice == 4)
            return sp * 10;
        return 0;
    }
};

int main() {
    Graph g;
    ifstream infile("Data_Globaltrek.txt");

    if (!infile) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string start, dest;
    int distance;

    while (infile >> start >> dest >> distance) {
        g.addEdge(start, dest, distance);
    }

    system("cls");
    cout<<endl;
    cout << "\t\t__________________________________________________________________\n";
    cout << "\t\t\t\t\t WELCOME TO Globaltrek\n";
    cout << "\t\t__________________________________________________________________\n\n";
    cout << "\t\tGlobaltrek is a travel planning and route recommendation platform\n \t\tthat helps users discover and plan trips to various destinations\n \t\t\t\t\t across India.";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout << "Press any key to continue...";
    cin.ignore();
    system("cls");

    cout << "\n-----------------------------------------------\n";
    cout << " Enter the Departure City: ";
    cout << "\n-----------------------------------------------\n";
    string dep;
    cin >> dep;

    cout << "\n-----------------------------------------------\n";
    cout << " Enter the Destination City: ";
    cout << "\n-----------------------------------------------\n";
    string des;
    cin >> des;

    vector<string> path;
    int sp = g.shortestPath(dep, des, path);

    if (sp == -1) {
        cout << "No path found from " << dep << " to " << des << endl;
        return 0;
    }

    cout << "\n------------------------------------------\n";
    cout << "Select a choice of transport:\n";
    cout << "------------------------------------------\n";
    cout << "1. Bike\n";
    cout << "2. Cab\n";
    cout << "3. Train\n";
    cout << "4. Aeroplane\n";
    cout << "\n----------------------------------------\n";

    int choice;
    cin >> choice;

    system("cls");

    cout << "\t\t-----------------YOUR Globaltrek TICKET----------------\n";
    cout << "\t===============================================================\n";
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << "\t   The local date and time is: " << dt;
    cout << "\t\t\t Best Route: " << sp << " Km" << endl;
    cout << "\t\t\t Total Fare: Rs." << g.calculatePrice(sp, choice) << endl;
    cout << "\t===============================================================\n";

    return 0;
}
