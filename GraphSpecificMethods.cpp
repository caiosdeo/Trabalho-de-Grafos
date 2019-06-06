#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <random>
#include <utility>

using namespace std;

/**************************************************************************************************
 * Defining some Graph's specific methods
**************************************************************************************************/

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

// Kahn's algorithm adapted
int *Graph::topologicalSort()
{
    int *vec = new int(this->order); // Allocating the vector that will contains the topological sort
    // Verifies if the graph has a circuit or not
    if (this->hasCircuit())
        return nullptr;

    else
    {
        int i = 0;
        Edge *aux_edge;
        Node *aux_node;
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

//This function is just to decide which way the greey will act if is a graph is directed or not
list<Node*> Graph::greedyMinimumConnectedDominantSet(Node** nodesSortedByOutDegree, float alpha){

    if(!this->connectedGraph()){
        list<Node*> empty;
        return empty;

    }else{
        if(this->directed){
            Graph* gS = this->getSubjacent();
            list<Node*> MCDS = gS->auxGreedyMinimumConnectedDominantSetByTree(nodesSortedByOutDegree, alpha);
            return MCDS;

        }else{
            list<Node*> MCDS = this->auxGreedyMinimumConnectedDominantSetByTree(nodesSortedByOutDegree, alpha);
            return MCDS;

        }

    }

}

// This function returns the Minimum Connected Dominant Set
list<Node*> Graph::auxGreedyMinimumConnectedDominantSet(Node** nodesSortedByOutDegree, float alpha){

    int respectiveId, targetId; // Declares auxiliar variables to work with indexes
    //List for the Minimum Connected Dominant Set
    list<Node*> minimun_connected_dominant_set;
    //Queue for visiting nodes
    queue<Node*> toVisit;
    //Vector to know if a node was visited and marking all as unvisited
    bool *visited = new bool[this->order];
    for(int i = 0; i < this->order; i++)
        visited[i] = false;

    Node* auxNode;

    // Get the alpha node which is already selected via rand and a given alpha
    Node* alphaNode = this->getAlphaNode(nodesSortedByOutDegree, alpha);

    //The alphaNode is already visited and is our root for the BFS
    visited[this->indexForNodes(alphaNode->getId())] = true;
    toVisit.push(alphaNode);

    while(!toVisit.empty()){

        //Auxilar to the node in the queue front
        auxNode = toVisit.front();
        // Adding the node id in the solution list
        minimun_connected_dominant_set.push_front(auxNode);
        //Then its is removed from the queue
        toVisit.pop();

        //Recur all of his adjacents
        for(Edge* auxEdge = auxNode->getFirstEdge(); auxEdge != nullptr; auxEdge = auxEdge->getNextEdge()){

            targetId = auxEdge->getTargetId();
            respectiveId = this->indexForNodes(targetId);
            //If a adjacent was not visited it is marked as visited and added to the queue
            if(!visited[respectiveId]){

                visited[respectiveId] = true;
                auxNode = this->getNode(targetId);
                if(!this->isLeafNode(auxNode, visited))
                    toVisit.push(auxNode);

            }

        }

    }

    return minimun_connected_dominant_set;

}

// This function returns the Minimum Connected Dominant Set by tree

list<Node*> Graph::auxGreedyMinimumConnectedDominantSetByTree(Node** nodesSortedByOutDegree, float alpha){

    Graph* tree = new Graph(this->order, true, false, false);
    //List for the Minimum Connected Dominant Set
    list<Node*> minimun_connected_dominant_set;
    //Queue for visiting nodes
    queue<Node*> toVisit;
    //Vector to know if a node was visited and marking all as unvisited
    bool *visited = new bool[this->order];
    for(int i = 0; i < this->order; i++)
        visited[i] = false;

    Node* auxNode;

    // Get the alpha node which is already selected via rand and a given alpha
    Node* alphaNode = this->getAlphaNode(nodesSortedByOutDegree, alpha);

    //The alphaNode is already visited and is our root for the BFS
    visited[this->indexForNodes(alphaNode->getId())] = true;
    toVisit.push(alphaNode);

    while(!toVisit.empty()){

        //Auxilar to the node in the queue front
        auxNode = toVisit.front();
        //Then its is removed from the queue
        toVisit.pop();

        //Recur all of his adjacents
        int sourceId = auxNode->getId();
        for(Edge* auxEdge = auxNode->getFirstEdge(); auxEdge != nullptr; auxEdge = auxEdge->getNextEdge()){

            int targetId = auxEdge->getTargetId();
            int respectiveId = this->indexForNodes(targetId);

            //If a adjacent was not visited it is marked as visited and added to the queue
            if(!visited[respectiveId]){

                visited[respectiveId] = true;
                tree->makeGraph(sourceId, targetId, 0);
                auxNode = this->getNode(targetId);
                toVisit.push(auxNode);

            }

        }

    }

    for(Node* aux = tree->getFirstNode(); aux != nullptr; aux = aux->getNextNode())
        if(aux->getOutDegree() != 0)
            minimun_connected_dominant_set.push_front(aux);
 
    return minimun_connected_dominant_set;    

}

list<Node*> Graph::randomizedGreedy(Node** nodesSortedByOutDegree, int iterations, float alpha){

    //The best solution is initialized with the greedy solution
    list<Node*> starList = this->greedyMinimumConnectedDominantSet(nodesSortedByOutDegree, 0);

    list<Node*> auxList;

    //The best solution is the one with lesser size
    for(int i = 0; i < iterations; i++){

        auxList = this->greedyMinimumConnectedDominantSet(nodesSortedByOutDegree, alpha);

        if(auxList.size() < starList.size())
            starList = auxList;

    }

    return starList;

}

pair<list<Node*>, float**> Graph::reactiveRandomizedGreedy(float maxAlpha, float alphaStep){

    /*
        alphasInfo matrix description

        0 - alpha values
        1 - alpha occurrences
        2 - alpha solutions sizes sum
        3 - alpha average of the sum solutions sizes in occurrences
        4 - alpha q - relation between star solution size and 3
        5 - alpha probability

    */

    Node** nodesSortedByOutDegree = this->sortNodesByOutDegree();
    int vectorsSize = ceil(maxAlpha / alphaStep);
    int maxIterations = vectorsSize * 1000;

    // Alocatting the alphasInfo matrix
    float** alphasInfo = new float*[6];
    for(int i = 0; i < 6; i++)
        alphasInfo[i] = new float[vectorsSize];

    // Starting the starList with the randomized greedy solution
    list<Node*> starList = this->randomizedGreedy(nodesSortedByOutDegree, 1, 0.0);
    list<Node*> auxList;

    float auxAlphaStep = alphaStep;

    // Loop to initialize the elements of the alphasInfo matrix
    for(int i = 0; i < vectorsSize; i++, auxAlphaStep += alphaStep){

        alphasInfo[0][i] = auxAlphaStep;
        auxList = this->randomizedGreedy(nodesSortedByOutDegree, 1, alphasInfo[0][i]);
        alphasInfo[1][i] = 1;
        alphasInfo[2][i] = (float)(auxList.size());
        alphasInfo[3][i] = alphasInfo[2][i] / alphasInfo[1][i];
        alphasInfo[4][i] = 0;
        alphasInfo[5][i] = 1 / vectorsSize;

        if(auxList.size() < starList.size())
            starList = auxList;

    }

    // External loop to run the randomized greedy for each alpha
    for(int i = 1; i < maxIterations; i++){

        int randProbability = rand() % 100;
        int alphadId = this->roulette(alphasInfo[5], randProbability, vectorsSize);
        auxList = this->randomizedGreedy(nodesSortedByOutDegree, 1, alphasInfo[0][alphadId]);
        alphasInfo[1][alphadId]++;
        alphasInfo[2][alphadId] += (float)(auxList.size());
        alphasInfo[3][alphadId] = alphasInfo[2][alphadId] / alphasInfo[1][alphadId];

        // Updating the star solution
        if(auxList.size() < starList.size())
            starList = auxList;

        // Updating the q and p vector for each block of 100
        if(i % 100 == 0){

            float sumQ = this->updateQ(alphasInfo[4], alphasInfo[3], vectorsSize, starList.size());
            this->updateP(alphasInfo[5], alphasInfo[4], vectorsSize, sumQ);

        }

    }

    return make_pair(starList, alphasInfo);

}
