#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node){

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;

}

// Destructor
Graph::~Graph(){

    Node* next_node = this->first_node;

    while(next_node != nullptr){

        next_node->removeEdges();
        Node* aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;

    }

}

// Getters
int Graph::getOrder(){

    return this->order;

}
int Graph::getNumberEdges(){

    return this->number_edges;

}

bool Graph::getDirected(){

    return this->directed;

}


bool Graph::getWeightedEdge(){

    return this->weighted_edge;

}

bool Graph::getWeightedNode(){

    return this->weighted_node;

}

Node* Graph::getFirstNode(){

    return this->first_node;

}

Node* Graph::getLastNode(){

    return this->last_node;

}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/
void Graph::insertNode(int id){
    // Verifies if the graph has at least one node
    if(this->first_node != nullptr){

        if(!this->searchNode(id)){
            // Allocating the new node and setting it as the last node
            Node* new_node = new Node(id);
            this->last_node->setNextNode(new_node);
            this->last_node = new_node;

        }

    }
    else{
        // Setting the first and the last nodes with the new node
        this->first_node = this->last_node = new Node(id);

    }

}

void Graph::makeGraph(int id, int target_id, float weight){

    Node* source_node;
    Node* target_node;
    // Searching for the nodes in the graph
    bool source = this->searchNode(id);
    bool target = this->searchNode(target_id);

    // Verifies whether the source and the target nodes are in the graph
    if(source && target){
        // Getting the source and target nodes
        source_node = this->getNode(id);
        target_node = this->getNode(target_id);

    }
    // Verifies whether the source and the target nodes are in the graph
    else if(source || target){
        // Verifies whether the source node is in the graph
        if(source){
            // Getting the source node and allocating the target node
            source_node = this->getNode(id);
            this->insertNode(target_id);
            target_node = this->last_node;

        }
        // Verifies whether the target node is in the graph
        if(target){
            // Getting the target node and allocating the source node
            target_node = this->getNode(target_id);
            this->insertNode(id);
            source_node = this->last_node;

        }

    }
    // Occurs when the source and target nodes are not in the graph
    else{
        // Allocating both nodes - source and target
        this->insertNode(id);
        source_node = this->last_node;
        this->insertNode(target_id);
        target_node = this->last_node;

    }
    // Verifies whether the graph is directed
    if(this->directed){
        // Inserting an edge of the source node for the target node
        source_node->insertEdge(target_id, weight);
        source_node->incrementOutDegree();
        target_node->incrementInDegree();

    }
    else{
        // Inserting an edge in both nodes
        source_node->insertEdge(target_id, weight);
        target_node->insertEdge(id, weight);
        source_node->incrementOutDegree();
        target_node->incrementOutDegree();

    }
    // Incrementing the number of edges in the graph
    this->number_edges++;

}

void Graph::removeNode(int id){
    // Verifies whether there are at least one node in the graph
    if(this->first_node != nullptr){
        // Verifies whether the node to remove is in the graph
        if(this->searchNode(id)){
            // Necessary attributes
            int count_edges_removed = 0;
            Node* aux_node = this->first_node;
            Node* previous_node = nullptr;
            Node* target_node = nullptr;
            // Searching for the node to be removed
            while(aux_node->getId() != id){

                previous_node = aux_node;
                aux_node = aux_node->getNextNode();

            }
            // Keeping the integrity of the node list
            previous_node->setNextNode(aux_node->getNextNode());
            // Getting the first edge of the node to be removed
            Edge* aux_edge = aux_node->getFirstEdge();
            // Traversing the edges of the node to be removed
            while(aux_edge != nullptr){
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
            if(this->last_node = aux_node)
                this->last_node = previous_node;

            previous_node->setNextNode(aux_node->getNextNode());

            delete aux_node;
            // Verifies whether the graph is directed
            if(this->directed){

                aux_node = this->first_node;
                // Visiting all nodes in the list of nodes
                while(aux_node != nullptr){
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

bool Graph::searchNode(int id){
    // Verifies whether there are at least one node in the graph
    if(this->first_node != nullptr){
        // Searching for a specific node of id equal to id
        for(Node* aux = this->first_node; aux != nullptr; aux = aux->getNextNode())
            if(aux->getId() == id)
                return true;

    }

    return false;

}

Node* Graph::getNode(int id){


    Node *aux = first_node;

    while(aux != NULL){

        if(aux->getId() == id){
            return aux;
        }

        aux = aux->getNextNode();
    }

    return aux;
}

void Graph::printGraph(ofstream& output_file){

    if(!this->weighted_edge && !this->weighted_node){

        output_file << "Nodes | Edges " << endl;
        for(Node* p = this->first_node; p != nullptr; p = p->getNextNode()){
            output_file << p->getId() << "     | ";
            for(Edge* e = p->getFirstEdge(); e != nullptr; e = e->getNextEdge()){
                output_file << " " << e->getTargetId();
            }
            output_file << endl;
        }

    }else if(this->weighted_edge && !this->weighted_node){

        output_file << "Nodes | Edges[Weight] " << endl;
        for(Node* p = this->first_node; p != nullptr; p = p->getNextNode()){
            output_file << p->getId() << "     | ";
            for(Edge* e = p->getFirstEdge(); e != nullptr; e = e->getNextEdge()){
                output_file << " " << e->getTargetId() << "[" << e->getWeight() << "]";
            }
            output_file << endl;
        }

    }else if(this->weighted_node && !this->weighted_edge){

        output_file << "Nodes[Weight] | Edges " << endl;
        for(Node* p = this->first_node; p != nullptr; p = p->getNextNode()){
            output_file << p->getId() << "[" << p->getWeight() << "]" << " | ";
            for(Edge* e = p->getFirstEdge(); e != nullptr; e = e->getNextEdge()){
                output_file << " " << e->getTargetId();
            }
            output_file << endl;
        }

    }else if(this->weighted_node && this->weighted_edge){

        output_file << "Nodes[Weight] | Edges[Weight] " << endl;
        for(Node* p = this->first_node; p != nullptr; p = p->getNextNode()){
            output_file << p->getId() << "[" << p->getWeight() << "]" << " | ";
            for(Edge* e = p->getFirstEdge(); e != nullptr; e = e->getNextEdge()){
                output_file << " " << e->getTargetId() << "[" << e->getWeight() << "]";
            }
            output_file << endl;
        }

    }

}

//Function that verifies if there is a path between two nodes
bool Graph::depthFirstSearch(int initialId,int targetId)
{
    //Creating a bool vector to verify visited nodes
    bool *visited = new bool[order];
    //Verifying if the nodes really exist
    if(getNode(initialId)==nullptr||getNode(targetId)==nullptr)
    {
        return false;
    }
    //Mark all nodes as unvisited before start the dfs
    for(int i = 0;i < order;i++)
    {
        visited[i] = false;
    }
    //Returning the result of the auxiliar method of this function
    return auxDepthFirstSearch(initialId,targetId,visited);

}

//Used Kosaraju Algorithm
int* Graph::stronglyConnectedComponents(){

    //Stack for visited nodes
    stack <int> explored;
    bool *visited = new bool[order];
    //Vector with the stronglyConnectedComponents
    int *sc = new int[this->order];
    //Int to label the SCCs
    int label = 0;

    if(this->first_node == nullptr || this->last_node == nullptr){
        return 0;
    }

    //Begin the DFS with every node as unvisited
    for(int i = 0; i < order; i++){
        visited[i] = false;
    }

    //Function to fill the stack with DFS visited nodes
    exploreOrder(this->first_node->getId(), this->first_node->getId(), visited, &explored);

    //Confirms that all the nodes were included in the stack
    for(Node* n = this->first_node; n != nullptr; n = n->getNextNode())
        if(visited[indexForNodes(n->getId())] == false)
            exploreOrder(n->getId(), n->getId(), visited, &explored);

    //Create a reverse graph
    Graph* gT = this->getTranspose();

    //Define every node as unvisited for the second DFS
    for(int i = 0; i < order; i++){
        visited[i] = false;
    }

    //DFS on the reverse graph by the stack order as its is running we find the SCCs of the graph
    while(explored.empty() == false){

        int v = explored.top();
        explored.pop();

        //If a node has outdegree equal to 0, means that it is impossible to exit that node, so if it
        //was already visited, it will mark as unvisited in that manner, the function will correctly define
        //it as a strongly connected component with itself only
        if(gT->getNode(v)->getOutDegree() == 0){

            visited[gT->indexForNodes(v)] = false;

        }

        //If a node has indegree equals to 0, means that it is impossible to reach this node,
        //so automatically it is marked as visited and belongs to an SCC which has only itself
        if(gT->getNode(v)->getInDegree() == 0){

            visited[gT->indexForNodes(v)] = true;
            sc[gT->indexForNodes(v)] = label;
            label++;

        }

        //DFS on the reverse graph that will find the SCCs
        if(visited[gT->indexForNodes(v)] == false){

            gT->auxStronglyConnectedComponents(v, v, visited, sc, label);
            label++;

        }

    }

    return sc;
}

void Graph::breadthFirstSearch(){
    int i = 0;
    int* visited = new int[this->getOrder()]; // vector to keep the ids that are already analysed.
    for(Node* auxNode = this->getFirstNode(); auxNode == nullptr; auxNode = auxNode->getNextNode())
    {   //Start the analysis of the nodes from the graph
        if(this->auxBreadthFirstSearchVerify(visited, i, auxNode->getId()) == false) //checks if the node is already verified
        {
            cout << auxNode->getId() << " "; //print the Id of the Node
            visited[i] = auxNode->getId(); // Add the node to visited
            i++; //increase the range of the visited array.
        }
        for(Edge* auxEdge = auxNode->getFirstEdge(); auxEdge == nullptr; auxEdge = auxEdge->getNextEdge())
        {   //Checks every edge of this node.
            if(this->auxBreadthFirstSearchVerify(visited, i, auxEdge->getTargetId()) == false)//checks if the node is already verified
            {
                cout << auxEdge->getTargetId() << " "; //print the Id of the Node
                visited[i] = auxEdge->getTargetId(); // Add the node to visited
                i++; //increase the range of the visited array.
            }
        }
    }
}

Graph* Graph::getComplement()
{
    // Creating the complement graph to be returned and coping the nodes from the orignal graph
    Graph* complement = new Graph(this->order, this->directed, this->weighted_edge, this->weighted_node);

    for(Node* nodeI = this->first_node; nodeI != nullptr; nodeI = nodeI->getNextNode()) {
        complement->insertNode(nodeI->getId());
    }

    // Comparing the target edges in each node with every other node
    // Inserting edges to the complement graph whenever they don't exist in the original graph
    Node* nodeComplement = complement->first_node;

    for(Node* nodeI = this->first_node; nodeI != nullptr;
    nodeI = nodeI->getNextNode(), nodeComplement = nodeComplement->getNextNode()) {
        for(Node* nodeJ = this->first_node; nodeJ != nullptr; nodeJ = nodeJ->getNextNode()) {
            if(nodeI != nodeJ && !nodeI->searchEdge(nodeJ->getId()))
                nodeComplement->insertEdge(nodeJ->getId(), 0);
        }
    }

    return complement;

}

int* Graph::degreeDescendingSequence(){
    int* sequence = new int [this->getOrder()]; // create array for the sequence
    for(Node* auxNode = this->getFirstNode(), int i = 0; aux != nullptr; aux = aux->getNextNode(), i++)
    {
        //The variable will control the position of the degrees int the array,
        //while auxNode will move in the graph picking all Nodes
        //and stops when all nodes has been visited.
        sequence[i] = aux->getOutDegree(); // adds the degree to the array
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
    }
    return sequence;
    //return the sequence of degrees in descending order.
}

//Auxiliar methods

//A function that returns a reverse graph, which is a graph with the arcs have opposite directions to the original graph
Graph* Graph::getTranspose(){

    //Create the reverse as the same order
    Graph* gT = new Graph(this->order, this->directed, this->weighted_edge, this->weighted_node);

    for(Node* n = this->first_node; n != nullptr; n = n->getNextNode()){
        for(Edge* e = n->getFirstEdge(); e != nullptr; e = e->getNextEdge()){
            gT->makeGraph(e->getTargetId(), n->getId(), e->getWeight());
        }
    }
    return gT;
}

//A function that fixate ordinal indexes for a node list
int Graph::indexForNodes(int id)
{
    int i = 0;
    Node *aux = first_node;
    //Based on the node id, the function will find and return its position on the list
    while(aux!=nullptr)
    {
        if(aux->getId()==id)
        {
            return i;
        }
        aux = aux->getNextNode();
        i++;
    }
    //Returning -1 in case of invalid id
    return -1;

}

bool Graph::auxDepthFirstSearch(int initialId,int targetId,bool visited[])
{
    //First mark the current node as visited in the vector
    visited[indexForNodes(initialId)] = true;
    //Base case: see if there is an Edge that connects the current node to the target node
    if(getNode(initialId)->searchEdge(targetId))
    {
        //Mark the target node as visited and return the answer
        visited[indexForNodes(targetId)] = true;
        return true;
    }
    else
    {
        //Try to search in every unvisited node for the target node
        Edge *aux = getNode(initialId)->getFirstEdge();
        while(aux!=nullptr)
        {
            if(visited[indexForNodes(aux->getTargetId())] == false)
            {
                if(auxDepthFirstSearch(aux->getTargetId(),targetId,visited))
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

void Graph::exploreOrder(int initialId, int targetId, bool visited[], stack<int>* explored){

    //As soon a node is visited, it is stacked
    visited[indexForNodes(initialId)] = true;
    (*explored).push(initialId);

    //If a node has an edge to the targetNode, then the targetNode
    //is marked as visited and it is also stacked. Otherwise,
    //it will keep searching for it on the adjacents nodes
    if(getNode(initialId)->searchEdge(targetId)){

        if(!visited[indexForNodes(targetId)]){

            visited[indexForNodes(targetId)] = true;
            (*explored).push(targetId);

        }

        return;

    }else{

        //Here we ensure that we are walking through all the edges of a node
        for(Edge *aux = getNode(initialId)->getFirstEdge(); aux != nullptr; aux = aux->getNextEdge()){

            if(visited[indexForNodes(aux->getTargetId())] == false){

                exploreOrder(aux->getTargetId(), targetId, visited, explored);
                return;

            }

        }

        return;

    }

}

void Graph::auxStronglyConnectedComponents(int initialId, int targetId, bool visited[], int sc[], int label){

    //As soon a node is visited, it is labeled with the current SCC id;
    visited[indexForNodes(initialId)] = true;
    sc[indexForNodes(initialId)] = label;

    //If a node has an edge to the targetNode, it is verified if any other
    //adjacent node has also a path to the targetNode. Otherwise it will
    //keep searching the targetNode
    if(getNode(initialId)->searchEdge(targetId)){

        for(Edge *aux = getNode(initialId)->getFirstEdge(); aux != nullptr; aux = aux->getNextEdge()){

            if(visited[indexForNodes(aux->getTargetId())] == false){

                auxStronglyConnectedComponents(aux->getTargetId(), targetId, visited, sc, label);
                return;

            }

        }

        return;

    }else{

        for(Edge *aux = getNode(initialId)->getFirstEdge(); aux != nullptr; aux = aux->getNextEdge()){

            if(visited[indexForNodes(aux->getTargetId())] == false){

                auxStronglyConnectedComponents(aux->getTargetId(), targetId, visited, sc, label);
                return;

            }

        }

        return;

    }

}

bool Graph :: auxBreadthFirstSearchVerify(int *verify, int size, int targetId){
    bool verified = false; // not found yet
    for(int i = 0; i < size; i++)
    {
        if(verify[i] == targetId){ // check if the id has been already analysed
            verified = true; //node founded
            return verify; //no need to check the rest.
        }
    }
    return verify; //Node not founded
}

int* Graph::topologicalSort(){
    // Verifies if the graph has a circuit or not
    if(this->hasCircuit())
        return nullptr;

    else{

        int *vec = new int(this->order); // Allocating the vector that will contains the topological sort
        queue<int> topologial_queue; // Declaring the auxiliar queue for the source nodes
        // Searching for nodes with indegree equal to zero
        for(Node* aux_node = this->first_node; aux_node != nullptr; aux_node = aux_node->getNextNode()){

            if(aux_node->getInDegree() == 0)
                topologial_queue.push(aux_node->getId()); // Pushing the correct nodes in the queue

        }

    }

}