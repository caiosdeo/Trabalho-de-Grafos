#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(){
    this->first_node = this->last_node = nullptr;
}

Graph::Graph(int order){
    this->order = order;
    this->first_node = this->last_node = nullptr;
}

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
void Graph::insertNode(int id, int target_id, float weight){

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
            target_node = new Node(target_id);
            this->last_node->setNextNode(target_node);
            this->last_node = target_node;

        }
        // Verifies whether the target node is in the graph
        if(target){
            // Getting the target node and allocating the source node
            target_node = this->getNode(target_id);
            source_node = new Node(id);
            this->last_node->setNextNode(source_node);
            this->last_node = source_node;

        }

    }
    // Occurs when the source and target nodes are not in the graph
    else{
        // Allocating both nodes - source and target
        source_node = new Node(id);
        target_node = new Node(target_id);
        // Occurs when there are no nodes in the graph
        if(this->first_node == nullptr){

            this->first_node = source_node;
            this->last_node = target_node;
            this->first_node->setNextNode(target_node);

        }
        // Occurs when there are nodes in the graph
        else{

            this->last_node->setNextNode(source_node);
            source_node->setNextNode(target_node);
            this->last_node = target_node;

        }

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
        source_node->incrementInDegree();
        target_node->incrementInDegree();

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

bool Graph::depthFirstSearch(int initialId,int targetId)
{
    bool *visited = new bool[order];
    if(getNode(initialId)==nullptr||getNode(targetId)==nullptr)
    {
        return false;
    }
    for(int i = 0;i < order;i++)
    {
        visited[i] = false;
    }
    return auxDepthFirstSearch(initialId,targetId,visited);

}

//Used KosaraJU Algorithm
int* Graph::stronglyConnectedComponents(){

    //Stack for visited nodes
    stack <int> explored;
    bool *visited = new bool[order];
    //Vector with the stronglyConnectedComponents
    int *sc = new int[this->order];
    //Int to indentify the SCCs
    int rot = 0;

    if(this->first_node == nullptr || this->last_node == nullptr){
        return 0;
    }

    //Begin the DFS with every node as unvisited
    for(int i = 0; i < order; i++){
        visited[i] = false;
    }

    //Function to fill the stack with DFS visited nodes
    exploreOrder(this->first_node->getId(), this->last_node->getId(), visited, &explored);

    //Confirms that all the nodes were included in the stack
    for(int i = 0; i < order; i++)
        if(visited[indexForNodes(i)] == false)
            exploreOrder(i, this->last_node->getId(), visited, &explored);

    //Create a reverse graph
    Graph gT = this->getTranspose();

    //Define every node as univisited for the second DFS
    for(int i = 0; i < order; i++){
        visited[i] = false;
    }

    //DFS on the reverse graph by the stack order as its is running we find the SCCs of the graph
    while(explored.empty() == false){

        int v = explored.top();
        explored.pop();

        if (visited[indexForNodes(v)] == false){
            auxStronglyConnectedComponents(v, gT.getLastNode()->getId(), visited, sc, rot);
            rot++;
        }
    }

    return sc;
}

//Auxiliar methods

//A function that returns a reverse graph, which is a graph with the arcs have opposite directions to the original graph
Graph Graph::getTranspose(){

    //Create the reverse as the same order
    int V = this->order;
    Graph gT(V);

    for(Node* n = this->first_node; n != nullptr; n = n->getNextNode()){
        for(Edge* e = n->getFirstEdge(); e != nullptr; e = e->getNextEdge()){
            gT.insertNode(e->getTargetId(), n->getId(), e->getWeight());
        }
    }
    return gT;
}

int Graph::indexForNodes(int id)
{
    int i = 0;
    Node *aux = first_node;
    while(aux!=nullptr)
    {
        if(aux->getId()==id)
        {
            return i;
        }
        aux = aux->getNextNode();
        i++;
    }

}

bool Graph::auxDepthFirstSearch(int initialId,int targetId,bool visited[])
{
    visited[indexForNodes(initialId)] = true;
    if(getNode(initialId)->searchEdge(targetId))
    {
        visited[indexForNodes(targetId)] = true;
        return true;
    }
    else
    {
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
        return false;
    }
}

bool Graph::exploreOrder(int initialId, int targetId, bool visited[], stack<int>* explored){

    //As soon a node is visited, it is stacked
    visited[indexForNodes(initialId)] = true;
    (*explored).push(initialId);

    if(initialId == targetId){
        if(!visited[indexForNodes(targetId)]){
            visited[indexForNodes(targetId)] = true;
            (*explored).push(targetId);
        }
        return true;

    }else{

        for(Edge *aux = getNode(initialId)->getFirstEdge(); aux != nullptr; aux = aux->getNextEdge()){

            if(visited[indexForNodes(aux->getTargetId())] == false){

                if(exploreOrder(aux->getTargetId(), targetId, visited, explored)){

                    return true;
                }

            }

        }

        return false;
    }
}

bool Graph::auxStronglyConnectedComponents(int initialId, int targetId, bool visited[], int sc[], int rot){

    visited[indexForNodes(initialId)] = true;
    sc[indexForNodes(initialId)] = rot;

    if(getNode(initialId)->searchEdge(targetId)){
        if(!visited[indexForNodes(targetId)]){
            visited[indexForNodes(targetId)] = true;
            cout << targetId;
        }
        return true;

    }else{

        for(Edge *aux = getNode(initialId)->getFirstEdge(); aux != nullptr; aux = aux->getNextEdge()){

            if(visited[indexForNodes(aux->getTargetId())] == false){

                if(auxStronglyConnectedComponents(aux->getTargetId(), targetId, visited, sc, rot)){

                    return true;
                }

            }

        }

        return false;
    }
}