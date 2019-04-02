/**************************************************************************************************
 * Implementation of the TAD Edge
**************************************************************************************************/

#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

using namespace std;

class Edge{

    private:
        int target_id;
        Edge* next_edge;
        float weight;

    public:
        Edge(int target_id, Edge* next_edge, float weight);
        ~Edge();
        int getTargetId();
        Edge* getNextEdge();
        float getWeight();
        void setNextEdge(Edge* edge);    

} 

#endif