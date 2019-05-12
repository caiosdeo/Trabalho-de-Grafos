#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node)
{

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {

        next_node->removeEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

// Getters
int Graph::getOrder()
{

    return this->order;
}
int Graph::getNumberEdges()
{

    return this->number_edges;
}

bool Graph::getDirected()
{

    return this->directed;
}

bool Graph::getWeightedEdge()
{

    return this->weighted_edge;
}

bool Graph::getWeightedNode()
{

    return this->weighted_node;
}

Node *Graph::getFirstNode()
{

    return this->first_node;
}

Node *Graph::getLastNode()
{

    return this->last_node;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/
void Graph::insertNode(int id)
{
    // Verifies if the graph has at least one node
    if (this->first_node != nullptr)
    {

        if (!this->searchNode(id))
        {
            // Allocating the new node and setting it as the last node
            Node *new_node = new Node(id);
            this->last_node->setNextNode(new_node);
            this->last_node = new_node;
        }
    }
    else
    {
        // Setting the first and the last nodes with the new node
        this->first_node = this->last_node = new Node(id);
    }
}

void Graph::makeGraph(int id, int target_id, float weight)
{

    Node *source_node;
    Node *target_node;
    // Searching for the nodes in the graph
    bool source = this->searchNode(id);
    bool target = this->searchNode(target_id);

    // Verifies whether the source and the target nodes are in the graph
    if (source && target)
    {
        // Getting the source and target nodes
        source_node = this->getNode(id);
        target_node = this->getNode(target_id);
    }
    // Verifies whether the source and the target nodes are in the graph
    else if (source || target)
    {
        // Verifies whether the source node is in the graph
        if (source)
        {
            // Getting the source node and allocating the target node
            source_node = this->getNode(id);
            this->insertNode(target_id);
            target_node = this->last_node;
        }
        // Verifies whether the target node is in the graph
        if (target)
        {
            // Getting the target node and allocating the source node
            target_node = this->getNode(target_id);
            this->insertNode(id);
            source_node = this->last_node;
        }
    }
    // Occurs when the source and target nodes are not in the graph
    else
    {
        // Allocating both nodes - source and target
        this->insertNode(id);
        source_node = this->last_node;
        this->insertNode(target_id);
        target_node = this->last_node;
    }
    // Verifies whether the graph is directed
    if (this->directed)
    {
        // Inserting an edge of the source node for the target node
        source_node->insertEdge(target_id, weight);
        source_node->incrementOutDegree();
        target_node->incrementInDegree();
    }
    else
    {
        // Inserting an edge in both nodes
        source_node->insertEdge(target_id, weight);
        target_node->insertEdge(id, weight);
        source_node->incrementOutDegree();
        target_node->incrementOutDegree();
    }
    // Incrementing the number of edges in the graph
    this->number_edges++;
}

void Graph::removeNode(int id)
{
    // Verifies whether there are at least one node in the graph
    if (this->first_node != nullptr)
    {
        // Verifies whether the node to remove is in the graph
        if (this->searchNode(id))
        {
            // Necessary attributes
            int count_edges_removed = 0;
            Node *aux_node = this->first_node;
            Node *previous_node = nullptr;
            Node *target_node = nullptr;
            // Searching for the node to be removed
            while (aux_node->getId() != id)
            {

                previous_node = aux_node;
                aux_node = aux_node->getNextNode();
            }
            // Keeping the integrity of the node list
            previous_node->setNextNode(aux_node->getNextNode());
            // Getting the first edge of the node to be removed
            Edge *aux_edge = aux_node->getFirstEdge();
            // Traversing the edges of the node to be removed
            while (aux_edge != nullptr)
            {
                // Getting the node in the edges of the node to be removed
                target_node = this->getNode(aux_edge->getTargetId());
                // Counting the number of edges removed and removing them if there are any
                count_edges_removed += target_node->removeEdge(id, this->directed, target_node);
                // Getting the next edge of the node to be removed
                aux_edge = aux_edge->getNextEdge();
            }

            // Incrementing the number of edges removed of the graph with the outdegree of the node to be removed
            count_edges_removed += aux_node->getOutDegree();
            // Removing all edges of the node to be removed
            aux_node->removeEdges();
            // Keeping the integrity of the node list
            if (this->last_node = aux_node)
                this->last_node = previous_node;

            previous_node->setNextNode(aux_node->getNextNode());

            delete aux_node;
            // Verifies whether the graph is directed
            if (this->directed)
            {

                aux_node = this->first_node;
                // Visiting all nodes in the list of nodes
                while (aux_node != nullptr)
                {
                    // Counting the number of edges removed and removing them if there are any
                    count_edges_removed += aux_node->removeEdge(id, this->directed, aux_node);
                    aux_node = aux_node->getNextNode();
                }
            }
            else
                count_edges_removed /= 2;
            // Decrementing the number of edges in the graph
            this->number_edges -= count_edges_removed;
        }
        // Decrementing the order of the graph
        this->order--;
    }
}

bool Graph::searchNode(int id)
{
    // Verifies whether there are at least one node in the graph
    if (this->first_node != nullptr)
    {
        // Searching for a specific node of id equal to id
        for (Node *aux = this->first_node; aux != nullptr; aux = aux->getNextNode())
            if (aux->getId() == id)
                return true;
    }

    return false;
}

Node *Graph::getNode(int id)
{

    Node *aux = first_node;

    while (aux != NULL)
    {

        if (aux->getId() == id)
        {
            return aux;
        }

        aux = aux->getNextNode();
    }

    return aux;
}

void Graph::printGraph(ofstream &output_file)
{

    if (!this->weighted_edge && !this->weighted_node)
    {

        output_file << "Nodes | Edges " << endl;
        for (Node *p = this->first_node; p != nullptr; p = p->getNextNode())
        {
            output_file << p->getId() << "     | ";
            for (Edge *e = p->getFirstEdge(); e != nullptr; e = e->getNextEdge())
            {
                output_file << " " << e->getTargetId();
            }
            output_file << endl;
        }
    }
    else if (this->weighted_edge && !this->weighted_node)
    {

        output_file << "Nodes | Edges[Weight] " << endl;
        for (Node *p = this->first_node; p != nullptr; p = p->getNextNode())
        {
            output_file << p->getId() << "     | ";
            for (Edge *e = p->getFirstEdge(); e != nullptr; e = e->getNextEdge())
            {
                output_file << " " << e->getTargetId() << "[" << e->getWeight() << "]";
            }
            output_file << endl;
        }
    }
    else if (this->weighted_node && !this->weighted_edge)
    {

        output_file << "Nodes[Weight] | Edges " << endl;
        for (Node *p = this->first_node; p != nullptr; p = p->getNextNode())
        {
            output_file << p->getId() << "[" << p->getWeight() << "]"
                        << " | ";
            for (Edge *e = p->getFirstEdge(); e != nullptr; e = e->getNextEdge())
            {
                output_file << " " << e->getTargetId();
            }
            output_file << endl;
        }
    }
    else if (this->weighted_node && this->weighted_edge)
    {

        output_file << "Nodes[Weight] | Edges[Weight] " << endl;
        for (Node *p = this->first_node; p != nullptr; p = p->getNextNode())
        {
            output_file << p->getId() << "[" << p->getWeight() << "]"
                        << " | ";
            for (Edge *e = p->getFirstEdge(); e != nullptr; e = e->getNextEdge())
            {
                output_file << " " << e->getTargetId() << "[" << e->getWeight() << "]";
            }
            output_file << endl;
        }
    }
}

//Function that verifies if there is a path between two nodes
bool Graph::depthFirstSearch(int initialId, int targetId)
{
    //Creating a bool vector to verify visited nodes
    bool *visited = new bool[order];
    //Verifying if the nodes really exist
    if (getNode(initialId) == nullptr || getNode(targetId) == nullptr)
    {
        return false;
    }
    //Mark all nodes as unvisited before start the dfs
    for (int i = 0; i < order; i++)
    {
        visited[i] = false;
    }
    //Returning the result of the auxiliar method of this function
    return auxDepthFirstSearch(initialId, targetId, visited);
}

//Used Kosaraju Algorithm
int* Graph::stronglyConnectedComponents(){

    if(!this->connectedGraph()){
        return nullptr;

    }else{

        //Stack for visited nodes
        stack<int> explored;
        bool *visited = new bool[order];
        //Vector with the stronglyConnectedComponents
        int *sc = new int[this->order];
        //Int to label the SCCs
        int label = 0;

        if (this->first_node == nullptr || this->last_node == nullptr){
            return 0;
        }

        //Begin the DFS with every node as unvisited
        for (int i = 0; i < order; i++){
            visited[i] = false;
        }

        //Function to fill the stack with DFS visited nodes in post order
        exploreOrder(this->first_node->getId(), this->first_node->getId(), visited, &explored);

        //Confirms that all the nodes were included in the stack
        for (Node *n = this->first_node; n != nullptr; n = n->getNextNode())
            if (visited[indexForNodes(n->getId())] == false)
                exploreOrder(n->getId(), n->getId(), visited, &explored);

        //Create a reverse graph
        Graph *gT = this->getTranspose();

        //Define every node as unvisited for the second DFS
        for (int i = 0; i < order; i++)
        {
            visited[i] = false;
        }

        //DFS on the reverse graph by the stack order as its is running we find the SCCs of the graph
        while (explored.empty() == false)
        {

            int v = explored.top();
            explored.pop();

            //DFS on the reverse graph that will find the SCCs
            if (visited[gT->indexForNodes(v)] == false){

                gT->auxComponents(v, v, visited, sc, label);
                label++;

            }

        }

        return sc;

    }

}

void Graph::breadthFirstSearch(ofstream &output_file)
{
    int i = 0;
    Node *auxNode = this->getFirstNode();
    Edge *auxEdge = auxNode->getFirstEdge();
    int *visited = new int[this->getOrder()]; // vector to keep the ids that are already analysed.
    for (; auxNode != nullptr; auxNode = auxNode->getNextNode())
    {                                                                                 //Start the analysis of the nodes from the graph
        if (this->auxBreadthFirstSearchVerify(visited, i, auxNode->getId()) == false) //checks if the node is already verified
        {
            output_file << auxNode->getId() << " "; //print the Id of the Node
            visited[i] = auxNode->getId();          // Add the node to visited
            i++;                                    //increase the range of the visited array.
        }
        for (; auxEdge != nullptr; auxEdge = auxEdge->getNextEdge())
        {                                                                                       //Checks every edge of this node.
            if (this->auxBreadthFirstSearchVerify(visited, i, auxEdge->getTargetId()) == false) //checks if the node is already verified
            {
                output_file << auxEdge->getTargetId() << " "; //print the Id of the Node
                visited[i] = auxEdge->getTargetId();          // Add the node to visited
                i++;                                          //increase the range of the visited array.
            }
        }
    }
}

Graph *Graph::getComplement()
{
    // Creating the complement graph to be returned and coping the nodes from the orignal graph
    Graph *complement = new Graph(this->order, this->directed, this->weighted_edge, this->weighted_node);

    for (Node *nodeI = this->first_node; nodeI != nullptr; nodeI = nodeI->getNextNode())
    {
        complement->insertNode(nodeI->getId());
    }

    // Comparing the target edges in each node with every other node
    // Inserting edges to the complement graph whenever they don't exist in the original graph
    Node *nodeComplement = complement->first_node;

    for (Node *nodeI = this->first_node; nodeI != nullptr;
         nodeI = nodeI->getNextNode(), nodeComplement = nodeComplement->getNextNode())
    {
        for (Node *nodeJ = this->first_node; nodeJ != nullptr; nodeJ = nodeJ->getNextNode())
        {
            if (nodeI != nodeJ && !nodeI->searchEdge(nodeJ->getId()))
                nodeComplement->insertEdge(nodeJ->getId(), 0);
        }
    }

    return complement;
}

int* Graph::degreeSequence(){
    int* sequence = new int [this->getOrder()]; // create array for the sequence.
    Node* auxNode = this->getFirstNode(); // auxiliar node to pass on the nodes of the graph.
    for(int i = 0; auxNode != nullptr; i++)
    {
        //The variable will control the position of the degrees int the array,
        //while auxNode will move in the graph picking all Nodes
        //and stops when all nodes has been visited.
        sequence[i] = auxNode->getOutDegree(); // adds the degree to the array
        int j = 0;
        while(sequence[i-j] > sequence[i-(j+1)] || i-j == 0)
        {
            // checks if the array is already descending, if not, the degree will change position until its degreed,
            // if yes, it will go back to the for.
            int aux = sequence[i-j];
            sequence[i-j] = sequence[i-(j+1)];
            sequence[i-(j+1)] = aux;
            j++;
        }
        auxNode = auxNode->getNextNode(); //Moving to the next node.
    }
    return sequence;
    //return the sequence of degrees in descending order.
}

bool Graph::connectedGraph()
{
    if (this->directed)
    {
        Graph *gS = getSubjacent();
        Node *aux = gS->getFirstNode()->getNextNode();
        while (aux != nullptr)
        {
            if (gS->depthFirstSearch(gS->getFirstNode()->getId(), aux->getId()))
            {
                aux = aux->getNextNode();
            }
            else
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        Node *aux = this->getFirstNode();
        aux = aux->getNextNode();
        while (aux != nullptr)
        {
            if (depthFirstSearch(this->first_node->getId(), aux->getId()))
            {
                aux = aux->getNextNode();
            }
            else
            {
                return false;
            }
        }
        return true;
    }
}

//function that finds the connected component of a node
int* Graph::connectedComponents(){

    bool *visited = new bool[this->order];
    //Vector with the connectedComponents
    int *cc = new int[this->order];
    //Int to label the CCs
    int label = 0;

    //Begin the DFS with every node as unvisited
    for (int i = 0; i < order; i++){
        visited[i] = false;
    }

    //Label all nodes from the beginning
    for (Node* aux = this->getFirstNode(); aux != nullptr; aux = aux->getNextNode()){

        if(visited[indexForNodes(aux->getId())] == false){

            this->auxComponents(aux->getId(), this->getLastNode()->getId(), visited, cc, label);
            label++;

        }

    }
    return cc;
}

//Auxiliar methods
bool Graph::hasCircuit()
{

    int *scc = this->stronglyConnectedComponents();
    list<int> aux;

    //We get the graph SCCs and add it to a list
    for (int i = 0; i < this->order; i++)
    {
        aux.push_back(scc[i]);
    }

    //Then the list is sorted
    aux.sort();

    //
    for (list<int>::iterator i = aux.begin(); i != aux.end();)
    {
        int prev = *i;
        i++;
        //If there are equals labels SCCs the graph is cyclic,
        //in this manner is returned that this graph has a circuit
        if (prev == *i)
            return true;
    }

    //If all the labels are different among them, this graph does not have a circuit
    return false;
}
//A function that returns a reverse graph, which is a graph which the arcs have opposite directions to the original graph
Graph* Graph::getTranspose(){

    //Create the reverse as the same order
    Graph *gT = new Graph(this->order, this->directed, this->weighted_edge, this->weighted_node);

    for (Node *n = this->first_node; n != nullptr; n = n->getNextNode())
    {
        for (Edge *e = n->getFirstEdge(); e != nullptr; e = e->getNextEdge())
        {
            gT->makeGraph(e->getTargetId(), n->getId(), e->getWeight());
        }
    }
    return gT;
}

//A function that returns a subjacent of a directed graph, which is a graph which the arcs have opposite directions to the original graph
Graph* Graph::getSubjacent()
{

    //Create the subjacent with the same order
    Graph *gS = new Graph(this->order, 0, this->weighted_edge, this->weighted_node);

    for (Node *n = this->first_node; n != nullptr; n = n->getNextNode())
    {
        for (Edge *e = n->getFirstEdge(); e != nullptr; e = e->getNextEdge())
        {
            gS->makeGraph(n->getId(), e->getTargetId(), e->getWeight());
        }
    }
    return gS;
}

//A function that fixate ordinal indexes for a node list
int Graph::indexForNodes(int id)
{
    int i = 0;
    Node *aux = first_node;
    //Based on the node id, the function will find and return its position on the list
    while (aux != nullptr)
    {
        if (aux->getId() == id)
        {
            return i;
        }
        aux = aux->getNextNode();
        i++;
    }
    //Returning -1 in case of invalid id
    return -1;
}

bool Graph::auxDepthFirstSearch(int initialId, int targetId, bool visited[])
{
    //First mark the current node as visited in the vector
    visited[indexForNodes(initialId)] = true;
    //Base case: see if there is an Edge that connects the current node to the target node
    if (getNode(initialId)->searchEdge(targetId))
    {
        //Mark the target node as visited and return the answer
        visited[indexForNodes(targetId)] = true;
        return true;
    }
    else
    {
        //Try to search in every unvisited node for the target node
        Edge *aux = getNode(initialId)->getFirstEdge();
        while (aux != nullptr)
        {
            if (visited[indexForNodes(aux->getTargetId())] == false)
            {
                if (auxDepthFirstSearch(aux->getTargetId(), targetId, visited))
                {
                    return true;
                }
            }
            aux = aux->getNextEdge();
        }
        //In case there is no path for the target node, return false
        return false;
    }
}

void Graph::exploreOrder(int initialId, int targetId, bool visited[], stack<int> *explored)
{

    //The node is marked that it was visited
    visited[indexForNodes(initialId)] = true;

    //Every node adjacent to it is stacked before
    for (Edge *aux = getNode(initialId)->getFirstEdge(); aux != nullptr; aux = aux->getNextEdge())

        if (visited[indexForNodes(aux->getTargetId())] == false)

            exploreOrder(aux->getTargetId(), targetId, visited, explored);

    //After all the edges of a node are visited, it is stacked
    (*explored).push(initialId);

}

void Graph::auxComponents(int initialId, int targetId, bool visited[], int c[], int label)
{

    //As soon a node is visited, it is labeled with the current component id;
    visited[indexForNodes(initialId)] = true;
    c[indexForNodes(initialId)] = label;

    //And the same is done for every node adjacent to it
    for (Edge *aux = getNode(initialId)->getFirstEdge(); aux != nullptr; aux = aux->getNextEdge())

        if (visited[indexForNodes(aux->getTargetId())] == false)

            auxComponents(aux->getTargetId(), targetId, visited, c, label);


}

bool Graph ::auxBreadthFirstSearchVerify(int *verify, int size, int targetId)
{
    bool verified = false; // not found yet
    for (int i = 0; i < size; i++)
    {
        if (verify[i] == targetId)
        {                    // check if the id has been already analysed
            verified = true; //node founded
            return verified; //no need to check the rest.
        }
    }
    return verified; //Node not founded
}

// Kahn's algorithm adapted
int *Graph::topologicalSort()
{

    // Verifies if the graph has a circuit or not
    if (this->hasCircuit())
        return nullptr;

    else
    {

        int i = 0;
        Edge *aux_edge;
        Node *aux_node;
        int *vec = new int(this->order); // Allocating the vector that will contains the topological sort
        queue<Node *> topological_queue; // Declaring the auxiliar queue for the source nodes
        // Searching for nodes with indegree equal to zero
        for (aux_node = this->first_node; aux_node != nullptr; aux_node = aux_node->getNextNode())
        {
            // Verifies whether the indegree is equal to zero
            if (aux_node->getInDegree() == 0)
                topological_queue.push(aux_node); // Pushing the correct nodes in the queue
        }
        // Verifies if the queue is empty
        while (!topological_queue.empty())
        {

            vec[i] = topological_queue.front()->getId();          // Pushing the id of the node to be popped of the queue
            aux_edge = topological_queue.front()->getFirstEdge(); // Getting the first edge of the node to be popped
            topological_queue.pop();                              // Popping the node
            // Verifies whether an edge exists
            while (aux_edge != nullptr)
            {

                aux_node = this->getNode(aux_edge->getTargetId()); // Picking up the neighboring node
                aux_node->decrementInDegree();                     // Decrementing indegree
                // Verifies whether the indegree is equal to zero
                if (aux_node->getInDegree() == 0)
                    topological_queue.push(aux_node);

                aux_edge = aux_edge->getNextEdge();
            }

            i++;
        }

        return vec; // Returning the indexes correlated to the topological sort in a vector
    }
}

// This function returns the Minimum Connected Dominant Set
list<int> Graph::greedyMinimumConnectedDominantSet(){

    /*
    //Pointer with the node of the bigger degree 
    Node* sortedOutdegree = this->sortByOutDegree();
    */

    //List for the Minimum Connected Dominant Set
    list<int> minimun_connected_dominant_set;
    //Queue for visiting nodes
    queue<Node*> toVisit;
    //Vector to know if a node was visited and marking all as unvisited
    bool *visited = new bool[this->order];
    for(int i = 0; i < this->order; i++)
        visited[i] = false;

    Node* auxNode;

    //The first node (change it to major outdegree, it is the first node at sortedOutdegree) is already visited
    visited[this->indexForNodes(this->getFirstNode()->getId())] = true;
    toVisit.push(this->getFirstNode());

    while(!toVisit.empty()){

        //Auxilar to the node in the queue front
        auxNode = toVisit.front();
        // Adding the node id in the solution list
        list.insert(auxNode->getId());
        //Then its is removed from the queue
        toVisit.pop();

        //Recur all of his adjacents
        for(Edge* auxEdge = auxNode->getFirstEdge(); auxEdge != nullptr; auxEdge = auxEdge->getNextEdge()){

            int targetId = auxEdge->getTargetId();

            //If a adjacent was not visited it is marked as visited and added to the queue
            if(!visited[indexForNodes(targetId)]){

                visited[indexForNodes(targetId)] = true;
                aux_node = this->getNode(targetId); 
                if(!aux_node->isLeaf(visited))
                    toVisit.push(aux_node);

            }

        }

    }

    return minimun_connected_dominant_set;

}