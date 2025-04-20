#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>


using namespace std;

// This is the graph class to perform all graph functions
class Graph {
private:
    map<string, vector<pair<string, int>>> adjList; //This will create a node with a list of neighbor and weight

public:
    void addEdge(string u, string v, int weight) { //this function will add an undirected edge between nodes a and b with a weight value of w
        adjList[u].push_back({ v, weight });
        adjList[v].push_back({ u, weight });  // Undirected graph
    }

    void dfsUtil(string node, set<string>& visited) { //This is a function for recursive depth first search traversal
        cout << "Visiting: " << node << endl; //this will log the current visit
        visited.insert(node); //this will mark the node as visited 

        for (auto neighbor : adjList[node]) { //this for loop traverses all neighbors
            if (visited.find(neighbor.first) == visited.end()) {
                cout << "Going deeper from " << node << " to " << neighbor.first << endl;
                dfsUtil(neighbor.first, visited); //this will revurse if the neighbor or node has not yet beeen visited
            }
        }
    }

    void dfs(string start) {
        cout << "DFS Traversal from " << start << " -----" << endl;
        set<string> visited; //set to track the visited nodes
        dfsUtil(start, visited); //start dfs from teh start node
        cout << endl;
    }

    void bfs(string start) { //This will perform breadth first search from a given starting node
        cout << "BFS Traversal from " << start << " -----" << endl;
        set<string> visited; //track visited nodes
        queue<string> q; //queue from breadth first search

        visited.insert(start); //mark start as visited
        q.push(start); //enqueue the start node 

        while (!q.empty()) {
            string current = q.front(); //this will get the current node
            q.pop(); //removes the current node from queue
            cout << "Visiting: " << current << endl; //outpyts the current node

            vector<pair<string, int>> neighbors = adjList[current];  // Get the list of neighbors for the current node from the adjacency list

            // Loop through the neighbor list using a traditional for loop with index
            for (int i = 0; i < neighbors.size(); i++) {

                // Get the current neighbor from the list using the index
                string neighborNode = neighbors[i].first;

                // Check if this neighbor has already been visited
                if (visited.find(neighborNode) == visited.end()) {

                    // If not visited, log that we're adding it to the BFS queue
                    cout << "Queueing: " << neighborNode << " (from " << current << ")" << endl;

                    // Mark this neighbor as visited so we don't visit again
                    visited.insert(neighborNode);

                    // Add it to the queue to be processed later
                    q.push(neighborNode);
                }
            }
        }
        cout << endl;
    }

    bool checkCycleUtil(string node, string parent, set<string>& visited) {
        visited.insert(node); //mark the current node ass visisted 
      
        vector<pair<string, int>> neighbors = adjList[node]; // Get the list of neighbors for the current node

       
        for (int i = 0; i < neighbors.size(); i++) { // Loop through each neighbor using a traditional indexed for loop
            
            string neighborNode = neighbors[i].first;   // Get the current neighbor node

            if (visited.find(neighborNode) == visited.end()) { // If the neighbor hasn't been visited
                cout << "DFS to " << neighborNode << " from " << node << endl; // Log the DFS step
                if (checkCycleUtil(neighborNode, node, visited)) { // Recursively check for cycles
                    return true; // Cycle found, return true
                }
            }
            else if (neighborNode != parent) { // If the neighbor is visited and not the parent
                cout << "Cycle detected via " << node << " and " << neighborNode << endl; // Log cycle detection
                return true; // Cycle found, return true
            }
        }
        return false; // No cycle found, return false
    }

    void checkCycle() {
        cout << "----- Cycle Detection -----" << endl;
        set<string> visited;
        
        vector<pair<string, vector<pair<string, int>>>> adjListVector(adjList.begin(), adjList.end()); // Convert the adjList to a vector of pairs to use with indexed loop

        for (int i = 0; i < adjListVector.size(); i++) {

            string node = adjListVector[i].first; // Get the node from the current pair

            if (visited.find(node) == visited.end()) {  // If the node has not been visited
                if (checkCycleUtil(node, "", visited)) {  // Check for a cycle starting from this node
                    cout << "Graph has a cycle." << endl << endl;  // If cycle is found, print and exit
                    return;
                }
            }
        }

        cout << "No cycles detected in the graph." << endl << endl;
    }
};

int main() {
    Graph g1;

    // Graph 1 edges
    g1.addEdge("A", "B", 2);
    g1.addEdge("A", "C", 5);
    g1.addEdge("B", "D", 1);
    g1.addEdge("B", "E", 3);
    g1.addEdge("C", "F", 4);
    g1.addEdge("E", "F", 2);

    cout << "Graph 1:" << endl;
    g1.dfs("A");
    g1.bfs("A");
    g1.checkCycle();

    // Graph 2 edges
    Graph g2;
    g2.addEdge("1", "2", 1);
    g2.addEdge("1", "3", 4);
    g2.addEdge("2", "4", 2);
    g2.addEdge("2", "5", 7);
    g2.addEdge("3", "6", 3);
    g2.addEdge("4", "7", 6);
    g2.addEdge("5", "8", 5);
    g2.addEdge("6", "9", 8);
    g2.addEdge("7", "10", 9);

    cout << "Graph 2:" << endl;
    g2.dfs("1");
    g2.bfs("1");
    g2.checkCycle();

    // Graph 3 edges
    Graph g3;
    g3.addEdge("A", "B", 1);
    g3.addEdge("B", "C", 2);
    g3.addEdge("C", "D", 3);
    g3.addEdge("E", "F", 1);
    g3.addEdge("F", "G", 4);
    g3.addEdge("H", "I", 6);
    g3.addEdge("I", "J", 2);
    g3.addEdge("L", "M", 5);
    g3.addEdge("M", "N", 2);
    g3.addEdge("N", "O", 3);

    cout << "Graph 3:" << endl;
    g3.dfs("A");
    g3.bfs("A");
    g3.checkCycle();

    return 0;



    
}