#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <set>

//defining headers
using namespace std;

class Graph {
public:
    unordered_map<string, vector<pair<string, int>>> adjList;

    void addEdge(const string& source, const string& target, int weight) {
        adjList[source].emplace_back(target, weight);
    }

    void printGraph() {
        cout << "Graph Structure:\n";

        unordered_map<string, vector<pair<string, int>>>::iterator nodeIt = adjList.begin();

        // Continue looping through all nodes until we reach the end of adjList
        while (nodeIt != adjList.end()) {
            //get the current node name (key in the adjacency list)
            string currentNode = nodeIt->first;
            //get the list of edges (neighbors with weights) for this node
            vector<pair<string, int>> edges = nodeIt->second;

            //print the current node followed by an arrow
            cout << currentNode << " -> ";

            //iterate over all edges for the current node
            //'edges' is a vector of pairs where each pair is a (neighbor, weight)
            vector<pair<string, int>>::iterator edgeIt = edges.begin();

            // Loop through each edge and print the neighbor and the weight
            while (edgeIt != edges.end()) {
                //'edgeIt->first' is the neighbor (destination node)
                //'edgeIt->second' is the weight of the edge to that neighbor
                cout << "(" << edgeIt->first << ", " << edgeIt->second << ") ";
                //move to the next edge in the list
                ++edgeIt;
            }

            //move to the next node in the adjacency list
            cout << "\n";
            ++nodeIt;
        }
    }
};

void readCSV(Graph& g, const string& filename) {
    ifstream file(filename);
    string line;

    //go through each line in the file
    while (getline(file, line)) {
        //skip lines that are empty or start with "Source"
        if (line == "" || line.find("Source") != string::npos) {
            continue;
        }

        //break the line into parts
        stringstream ss(line);
        string source;
        string target;
        string weightStr;

        getline(ss, source, ',');
        getline(ss, target, ',');
        getline(ss, weightStr, ',');

        //just making sure nothing is blank
        if (source != "" && target != "" && weightStr != "") {
            int weight = stoi(weightStr); //change string to int
            g.addEdge(source, target, weight); //add the edge to the graph
        }
    }
}

void greedyPath(Graph& g, const string& start) {
    set<string> visited;
    string current = start;
    int totalCost = 0;

    cout << endl << "Greedy Path starting from " << start << ": ";

    while (true) {
        visited.insert(current);
        cout << current;

        int minWeight = numeric_limits<int>::max();
        string nextNode;
        bool found = false;

        //loop through all edges in the adjacency list for the current node
        for (auto it = g.adjList[current].begin(); it != g.adjList[current].end(); ++it) {
            //get the destination node and the weight of the edge
            string destinationNode = it->first; //the destination node (neighbor)
            int edgeWeight = it->second;        //the weight of the edge to that neighbor

            //check if the destination node has not been visited and if the weight is less than the minimum weight found so far
            if (visited.find(destinationNode) == visited.end()) {   
                if (edgeWeight < minWeight) { 
                    minWeight = edgeWeight;     //update the minimum weight to this smaller weight
                    nextNode = destinationNode; //set the next node to this destination node
                    found = true;               //mark that we've found a new candidate for the next node
                }
            }
        }

        if (found == false) {
            //if we dont find what we were looking for, exit the loop
            break;
        }

        cout << " -> ";
        totalCost += minWeight;
        current = nextNode;
    }

    cout << " [Cost: " << totalCost << "]" << endl;
}

int main() {
    Graph graph;
    string filename = "Data.txt";
    readCSV(graph, filename);

    graph.printGraph();

    //for loop to go over every greedy path from every node
    cout << "\n--- Greedy Paths from Every Node ---" << endl;
    for (const auto& node : graph.adjList) {
        greedyPath(graph, node.first);
    }

    return 0; //return 0
}
