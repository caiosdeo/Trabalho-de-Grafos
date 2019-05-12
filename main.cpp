#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "Node.h"

using namespace std;

int main(int argc, char const *argv[]) {

    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6) {

        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
        return 0;

    }

    string program_name(argv[0]);
    cout << "Running " << program_name << " ... " << endl;

    //Abrindo arquivo de entrada
    ifstream input_file;
    input_file.open(argv[1], ios::in);

    //Criação do arquivo de saída
    ofstream output_file;
    output_file.open(argv[2], ios::out | ios::trunc);

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;

    int order;

    if(input_file.is_open()){

        input_file >> order;

    }


    //Criando objeto grafo
    Graph graph(order, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

    //Leitura de arquivo:
    if(input_file.is_open()){

        if(!graph.getWeightedEdge() && !graph.getWeightedNode()){

            while(input_file >> idNodeSource >> idNodeTarget) {

                graph.makeGraph(idNodeSource, idNodeTarget, 0);

            }

        }else if(graph.getWeightedEdge() && !graph.getWeightedNode() ){

            float edgeWeight;

            while(input_file >> idNodeSource >> idNodeTarget >> edgeWeight) {

                graph.makeGraph(idNodeSource, idNodeTarget, edgeWeight);

            }

        }else if(graph.getWeightedNode() && !graph.getWeightedEdge()){

            float nodeSourceWeight, nodeTargetWeight;

            while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {

                graph.makeGraph(idNodeSource, idNodeTarget, 0);
                graph.getNode(idNodeSource)->setWeight(nodeSourceWeight);
                graph.getNode(idNodeTarget)->setWeight(nodeTargetWeight);

            }

        }else if(graph.getWeightedNode() && graph.getWeightedEdge()){

            float nodeSourceWeight, nodeTargetWeight, edgeWeight;

            while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {

                graph.makeGraph(idNodeSource, idNodeTarget, edgeWeight);
                graph.getNode(idNodeSource)->setWeight(nodeSourceWeight);
                graph.getNode(idNodeTarget)->setWeight(nodeTargetWeight);

            }

        }

    }else{

        cout << "Unable to open " << argv[1];

    }

    if(output_file.is_open()){

        //Imprimindo funções básicas
        output_file << "Ordem: " << graph.getOrder() << endl;
        output_file << "Direcionado: " << graph.getDirected() << endl;
        output_file << "Ponderado Arestas: " << graph.getWeightedEdge() << endl;
        output_file << "Ponderado Nós: " << graph.getWeightedNode() << endl;
        output_file << "Conexo: " << graph.connectedGraph() << endl;
        output_file << "Numero de arestas: " << graph.getNumberEdges() << endl;
        output_file << "No com id = 7 esta no grafo? " << graph.searchNode(7) << endl;
        output_file << "No com id = 4 esta no grafo? " << graph.searchNode(4) << endl;
        output_file << "Busca em profundidade id = 6 apartir do primeiro nó inserido? " << graph.depthFirstSearch(1,6) << endl;
        output_file << endl;

        //Imprimindo o Grafo
        graph.printGraph(output_file);
        output_file << endl;

        //Teste Greedy
        list<int> mcds = graph.greedyMinimumConnectedDominantSet();
        for (list<int>::iterator i = mcds.begin(); i != mcds.end(); i++){

            cout << *i << " ";

        }

        //Teste sequencia de graph
        output_file << "Sequencia de grau" << endl;
        int* seqDeg = graph.degreeSequence();
        for(int i = 0; i < graph.getOrder(); i++)
            output_file << seqDeg[i] << " ";
        output_file << endl << endl;

        //Teste BFS
        output_file << "BFS" << endl;
        graph.breadthFirstSearch(output_file);
        output_file << endl << endl;

        //Teste CC
        //Imprime as componentes conexas se o grafo for não direcionado
        if(!graph.getDirected()){
            output_file << "Connected Components" << endl;
            int* cc = graph.connectedComponents();

            output_file << "Node     ";
            for(Node* n = graph.getFirstNode(); n != nullptr; n = n->getNextNode())
                output_file << n->getId() << " ";

            output_file << endl << "CC[Node] ";

            for(int i = 0; i < graph.getOrder(); i++)
                output_file << cc[i] << " ";

            output_file << endl << endl;

        }else{

            output_file << "Grafo direcionado não tem CC" << endl << endl;

        }

        //Imprimindo as componentes fortemente conexas se o grafo for direcionado
        if(graph.getDirected()){

            int* scc = graph.stronglyConnectedComponents();
            if(scc != nullptr){

                output_file << "Componentes Fortemente Conexas: "  << endl;

                output_file << "Node      ";
                for(Node* n = graph.getFirstNode(); n != nullptr; n = n->getNextNode())
                    output_file << n->getId() << " ";

                output_file << endl << "SCC[Node] ";

                for(int i = 0; i < graph.getOrder(); i++)
                    output_file << scc[i] << " ";

                output_file << endl << endl;

                output_file << "Graph has circuit: " << graph.hasCircuit() << endl;

                int* topSort = graph.topologicalSort();

                if(topSort != nullptr){

                    output_file << "Ordenacao Topologica "  << endl;
                    for(int i = 0; i < graph.getOrder(); i++)
                        output_file << topSort[i] << " ";
                    output_file << endl;

                }else{

                    output_file << "Grafo possui circuito(s), portanto não é um DAG para ter ordenção Topológica" << endl;

                }

                output_file << endl;

            }else{

                output_file << "Grafo não conexo, sem componentes fortemente conexas" << endl << endl;

            }

        }else{

            output_file << "Grafo não direcionado, não possui SCC" << endl << endl;

        }

        //Imprimindo o complementar
        output_file << "Complement" << endl;
        Graph* gC = graph.getComplement();
        gC->printGraph(output_file);
        output_file << endl;

        //Removendo um nó
        output_file << "Removendo nó id = 4" << endl;
        graph.removeNode(4);
        graph.printGraph(output_file);
        output_file << "Numero de arestas: " << graph.getNumberEdges() << endl;
        output_file << endl;

    }else {

        cout << "Unable to open " << argv[2];

    }

    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();


    return 0;
}
