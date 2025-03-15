#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

typedef unordered_map<string, vector<pair<string, int>>> Graph;
unordered_map<string, int> straightLineDistanceToBucharest = {
        {"Arad", 366}, {"Bucharest", 0}, {"Craiova", 160}, {"Dobreta", 242}, {"Eforie", 161},
        {"Fagaras", 176}, {"Giurgiu", 77}, {"Hirsova", 151}, {"Iasi", 226}, {"Lugoj", 244},
        {"Mehadia", 241}, {"Neamt", 234}, {"Oradea", 380}, {"Pitesti", 101},
        {"Rimnicu Vilcea", 193}, {"Sibiu", 253}, {"Timisoara", 329}, {"Urziceni", 80},
        {"Vaslui", 199}, {"Zerind", 374}};

void addEdge(Graph& graph, const string& from, const string& to, int weight) {
    graph[from].push_back({to, weight});
    graph[to].push_back({from, weight}); // undirected graph
}

void mapInit(Graph& graph) {
    addEdge(graph, "Arad", "Zerind", 75);
    addEdge(graph, "Arad", "Timisoara", 118);
    addEdge(graph, "Zerind", "Oradea", 71);
    addEdge(graph, "Oradea", "Sibiu", 151);
    addEdge(graph, "Arad", "Sibiu", 140);
    addEdge(graph, "Timisoara", "Lugoj", 111);
    addEdge(graph, "Lugoj", "Mehadia", 70);
    addEdge(graph, "Mehadia", "Dobreta", 75);
    addEdge(graph, "Dobreta", "Craiova", 120);
    addEdge(graph, "Craiova", "Rimnicu Vilcea", 146);
    addEdge(graph, "Rimnicu Vilcea", "Sibiu", 80);
    addEdge(graph, "Sibiu", "Fagaras", 99);
    addEdge(graph, "Rimnicu Vilcea", "Pitesti", 97);
    addEdge(graph, "Pitesti", "Bucharest", 101);
    addEdge(graph, "Fagaras", "Bucharest", 211);
    addEdge(graph, "Bucharest", "Giurgiu", 90);
    addEdge(graph, "Bucharest", "Urziceni", 85);
    addEdge(graph, "Urziceni", "Hirsova", 98);
    addEdge(graph, "Hirsova", "Eforie", 86);
    addEdge(graph, "Urziceni", "Vaslui", 142);
    addEdge(graph, "Vaslui", "Iasi", 92);
    addEdge(graph, "Iasi", "Neamt", 87);
}

vector<string> aStarSearch(Graph& graph, const string& start, const string& goal) {
    // Priority queue to store nodes based on heuristic
    // Heuristic = traveled distance + straight line distance to goal
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> openList;
    unordered_set<string> visited;
    unordered_map<string, int> gScore;   // Cost from start to each node
    unordered_map<string, string> cameFrom; // For path reconstruction

    // Initialize gScore
    for (const auto& node : graph) {
        gScore[node.first] = 114514;
    }
    gScore[start] = 0;

    openList.push({straightLineDistanceToBucharest[start], start});

    while (!openList.empty()) {
        string current = openList.top().second;
        openList.pop();

        if (current == goal) { // Goal reached
            vector<string> path;
            while (current != "") {
                path.push_back(current);
                current = cameFrom[current];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        visited.insert(current);

        for (const auto& neighbor : graph[current]) {
            string neighborCity = neighbor.first;
            int weight = neighbor.second;

            if (visited.find(neighborCity) != visited.end()) {
                continue; // Skip already visited nodes
            }

            int tentativeGScore = gScore[current] + weight;

            if (tentativeGScore < gScore[neighborCity]) {
                // Update scores and parent
                gScore[neighborCity] = tentativeGScore;
                int fScore = tentativeGScore + straightLineDistanceToBucharest[neighborCity];
                openList.push({fScore, neighborCity});
                cameFrom[neighborCity] = current;
            }
        }
    }

    return {}; // No path found
}

vector<string> greedySearch(Graph& graph, const string& start, const string& goal){
    vector<string> path = {start};
    unordered_set<string> visited = {start};

    while (path.back() != goal) {
        string current = path.back();
        int minDistance = 114514;
        string nextCity = "";
        // search all neighbors
        for (const auto &neighbor: graph[current]) {
            string neighborCity = neighbor.first;
            if (visited.find(neighborCity) == visited.end()) {
                if (straightLineDistanceToBucharest[neighborCity] < minDistance) {
                    minDistance = straightLineDistanceToBucharest[neighborCity];
                    nextCity = neighborCity;
                }
            }
        }
        if (nextCity.empty()) {
            return {}; // No path found
        }
        // if next city is goal
        if (nextCity == goal) {
            path.push_back(nextCity);
            visited.insert(nextCity);
            break;
        }
        // add next city to path
        path.push_back(nextCity);
        visited.insert(nextCity);
    }
    return path;
}

int main() {
    Graph graph;
    mapInit(graph);

    string start = "Arad";
    string goal = "Bucharest";

    vector<string> AStarPath = aStarSearch(graph, start, goal);
    cout << "A* Path: ";
    for (const string& city : AStarPath) {
        cout << city << " -> ";
    }
    cout << "\b\b\b\b" <<endl;

    vector<string> greedyPath = greedySearch(graph, start, goal);
    cout << "Greedy Path: ";
    for (const string& city : greedyPath) {
        cout << city << " -> ";
    }
    cout << "\b\b\b\b" <<endl;

}