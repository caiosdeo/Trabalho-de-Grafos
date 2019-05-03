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
        output_file << "Numero de arestas: " << graph.getNumberEdges() << endl;
        output_file << "No com id = 7 esta no grafo? " << graph.searchNode(7) << endl;
        output_file << "No com id = 4 esta no grafo? " << graph.searchNode(4) << endl;
        output_file << "Busca de profundidade id = 6 " << graph.depthFirstSearch(1,6) << endl;
        output_file << "Busca de profundidade id = 8 " << graph.depthFirstSearch(1,8) << endl;
        output_file << endl;

        //Imprimindo o Grafo
        graph.printGraph(output_file);
        output_file << endl;

        //Imprimindo grafo transposto
        Graph* gT = graph.getTranspose();
        output_file << "Transpose " << endl;
        gT->printGraph(output_file);
        output_file << endl;

        //Imprimindo as componentes fortemente conexas se o grafo for direcionado
        if(graph.getDirected()){

            output_file << "Componentes Fortemente Conexas: "  << endl;
            int* scc = graph.stronglyConnectedComponents();

            output_file << "Node      ";
            for(Node* n = gT->getFirstNode(); n != nullptr; n = n->getNextNode())
                output_file << n->getId() << " ";

            output_file << endl << "SCC[Node] ";

            for(int i = 0; i < graph.getOrder(); i++)
                output_file << scc[i] << " ";

            output_file << endl << endl;
        }

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
