/* Question 3 (25 pts) In a graph, a square is a cycle of length 4. 
    Provide an algorithm that decides if a graph contains a 
    square in O(n3) time. Hint: use adjacency matrix representation. 
 */

#include <iostream>
#include <unordered_set>
#include <vector>
#include <map>

struct Route 
{
    int origin;
    int destination;
};

struct Node 
{
    int vertex;
    std::unordered_set<Node*> adjacencyList;
    std::unordered_set<Node*> reachableList;
    Node(int v) : vertex(v) {}
};

struct Graph 
{
    std::map<int, Node*> vertices;

    void addEdge(const Route& route) 
    {
        if (!containsVertex(route.origin))
            vertices.insert({route.origin, new Node(route.origin)});
        if (!containsVertex(route.destination))
            vertices.insert({route.destination, new Node(route.destination)});
        getVertex(route.origin)->adjacencyList.insert(getVertex(route.destination));
    }

    bool containsVertex(const int vertex) {
        return vertices.find(vertex) != vertices.end();
    }

    Node* getVertex(const int vertex) {
        auto it = vertices.find(vertex);
        if (it != vertices.end()) {
            return it->second;
        }
        return nullptr;
    }
};

void printGraph(Graph& graph) {
    for (auto const& row : graph.vertices) {  // row is a pair in the graph with row.first as keys (node strings) and row.second as values (node Objects)
        std::string adjacents = "";
        Node* node = row.second; // get each node object of graph 
        for (Node* adjacent : node->adjacencyList) { // build int of adjacents by using each entry in the directRoutes vector
            adjacents += " " + std::to_string(adjacent->vertex) + " ";
        }
        std::cout << row.first << ": " <<  "[" << adjacents << "]" << std::endl;
    }
}

// We have determined a node is part of cycle... now we have to check if there are exactly four nodes in our reachables that contain
// this same node
bool countSquare(Node* node)
{
    int cycleSize = 0;
    for (const auto reachableNode : node->reachableList)
    {
        if (reachableNode->reachableList.count(node))
        {
            cycleSize++;
        }
    }
    return cycleSize==4;
}

// Each recursion stack has fresh visited. For each node in visited, we want to add the adjacents of current node to its reachables
// 1->2->3->4->1 for example if we have these nodes, we add 1 to visited, then we add its adjacent (2) to its reachables
// When we go to 2, we add 3 to its reachables. HOWEVER, we also add 3 to the reachables of 1 because since 2 can get to 3 and 1 can 
// get to 2, 1 can get to 3. We do this for all nodes we can reach recursively. If at same point we see ourselves in our own reachables
// we know we hit a cycle. For example, 4 will try to add 1(its adjacency) to the reachables of all the visited nodes. 1 will try to 
// add 1 to its reachables (since 1 is in visited), which will make it realize its in a cycle. It will check if that cycle is a square
// and return true if so
bool squareDFS(Node* node, std::unordered_set<Node*> visited) {

    visited.insert(node); // prevent infinite loop
    for (const auto adjacentNode : node->adjacencyList)
    {
        for (const auto visitedNode : visited)
        {
            if (visitedNode->reachableList.count(visitedNode))  // If we saw ourself in our own reachables, we know there's a cycle, now we just have to check if it's a square
            {
                if (countSquare(visitedNode))
                    return true;
            }
            visitedNode->reachableList.insert(adjacentNode);
        }
    }
    for (const auto adjacentNode : node->adjacencyList)
    {
        squareDFS(adjacentNode, visited);
    }
    return false;
}

bool containsSquare(Graph& graph)
{
    for (const auto& [value, node] : graph.vertices)
    {
        if (squareDFS(node, std::unordered_set<Node*>{})) 
            return true;
    }
    return false;
}

int main() {
   
    Graph squareGraph;
    squareGraph.addEdge(Route{1,2});
    squareGraph.addEdge(Route{3,4});
    squareGraph.addEdge(Route{4,5});
    squareGraph.addEdge(Route{5,6});
    squareGraph.addEdge(Route{6,3});
    printGraph(squareGraph);
    if (containsSquare(squareGraph)) {
        std::cout << "The graph contains a square." << std::endl;
    } else {
        std::cout << "The graph does not contain a square." << std::endl;
    }

    Graph notSquareGraph;
    notSquareGraph.addEdge(Route{1,2});
    notSquareGraph.addEdge(Route{3,4});
    notSquareGraph.addEdge(Route{4,5});
    notSquareGraph.addEdge(Route{5,6});
    notSquareGraph.addEdge(Route{6,2});
    printGraph(notSquareGraph);
    if (containsSquare(notSquareGraph)) {
        std::cout << "The graph contains a square." << std::endl;
    } else {
        std::cout << "The graph does not contain a square." << std::endl;
    }
    
    Graph pentagonGraph;
    pentagonGraph.addEdge(Route{1,2});
    pentagonGraph.addEdge(Route{2,3});
    pentagonGraph.addEdge(Route{3,4});
    pentagonGraph.addEdge(Route{4,5});
    pentagonGraph.addEdge(Route{5,6});
    printGraph(pentagonGraph);
    if (containsSquare(pentagonGraph)) {
        std::cout << "The graph contains a square." << std::endl;
    } else {
        std::cout << "The graph does not contain a square." << std::endl;
    }

    return 0;
}


/* OUTPUT
 *
 *   g++ square.cpp -o "s"
 *   ./s
 *   1: [ 2 ]
 *   2: []
 *   3: [ 4 ]
 *   4: [ 5 ]
 *   5: [ 6 ]
 *   6: [ 3 ]
 *   The graph contains a square.
 *   1: [ 2 ]
 *   2: []
 *   3: [ 4 ]
 *   4: [ 5 ]
 *   5: [ 6 ]
 *   6: [ 2 ]
 *   The graph does not contain a square.
 *   1: [ 2 ]
 *   2: [ 3 ]
 *   3: [ 4 ]
 *   4: [ 5 ]
 *   5: [ 6 ]
 *   6: []
 *   The graph does not contain a square.
 *
 */