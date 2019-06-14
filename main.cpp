#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include "Graph.h"
#include "Node.h"

using namespace std;

Graph* leitura(ifstream& input_file, int directed, int weightedEdge, int weightedNode){

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;

    //Pegando a ordem do grafo
    input_file >> order;

    //Criando objeto grafo
    Graph* graph = new Graph(order, directed, weightedEdge, weightedNode);

    //Leitura de arquivo

    if(!graph->getWeightedEdge() && !graph->getWeightedNode()){

        while(input_file >> idNodeSource >> idNodeTarget) {

            graph->makeGraph(idNodeSource, idNodeTarget, 0);

        }

    }else if(graph->getWeightedEdge() && !graph->getWeightedNode() ){

        float edgeWeight;

        while(input_file >> idNodeSource >> idNodeTarget >> edgeWeight) {

            graph->makeGraph(idNodeSource, idNodeTarget, edgeWeight);

        }

    }else if(graph->getWeightedNode() && !graph->getWeightedEdge()){

        float nodeSourceWeight, nodeTargetWeight;

        while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {

            graph->makeGraph(idNodeSource, idNodeTarget, 0);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);

        }

    }else if(graph->getWeightedNode() && graph->getWeightedEdge()){

        float nodeSourceWeight, nodeTargetWeight, edgeWeight;

        while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {

            graph->makeGraph(idNodeSource, idNodeTarget, edgeWeight);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);

        }

    }

    return graph;
}

int menu(){

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Complementar do grafo" << endl;
    cout << "[2] Imprimir caminhamento em largura" << endl;
    cout << "[3] Busca em profundidade" << endl;
    cout << "[4] Imprimir componentes conexas" << endl;
    cout << "[5] Imprimir componentes fortemente conexas" << endl;
    cout << "[6] Imprimir ordenacao topológica" << endl;
    cout << "[7] Guloso Randomizado Reativo" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Graph* graph, ofstream& output_file){

    switch (selecao) {

        //Complementar
        case 1:{
            output_file << "Complementar" << endl;
            Graph* gC = graph->getComplement();
            gC->printGraph(output_file);
            output_file << endl;
            break;
        }

        //BFS
        case 2:{
            output_file << "BFS" << endl;
            graph->breadthFirstSearch(output_file);
            output_file << endl;
            break;
        }

        //DFS
        case 3:{
            int initialId;
            int targetId;

            cout << "ID nó inicio: "; cin >> initialId;
            cout << "ID a ser buscado: "; cin >> targetId;

            output_file << "DFS" << endl;
            if(graph->depthFirstSearch(initialId, targetId))
                output_file << "Nó " << targetId << " encontrado partindo de " << initialId;
            else
                output_file << "Nó " << targetId << " não encontrado partindo de " << initialId;

            output_file << endl;
            break;
        }

        //Componentes Conexas
        case 4:{
            //Imprime as componentes conexas se o grafo for não direcionado
            if(!graph->getDirected()){
                output_file << "Connected Components" << endl;
                int* cc = graph->connectedComponents();

                output_file << "Node     ";
                for(Node* n = graph->getFirstNode(); n != nullptr; n = n->getNextNode())
                    output_file << n->getId() << " ";

                output_file << endl << "CC[Node] ";

                for(int i = 0; i < graph->getOrder(); i++)
                    output_file << cc[i] << " ";

                output_file << endl;

            }else{

                output_file << "Grafo direcionado não tem CC" << endl;

            }
            break;
        }

        //Componentes Fortementes Conexas
        case 5:{
            //Imprimindo as componentes fortemente conexas se o grafo for direcionado
            if(graph->getDirected()){

                int* scc = graph->stronglyConnectedComponents();
                if(scc != nullptr){

                    output_file << "Componentes Fortemente Conexas: "  << endl;

                    output_file << "Node      ";
                    for(Node* n = graph->getFirstNode(); n != nullptr; n = n->getNextNode())
                        output_file << n->getId() << " ";

                    output_file << endl << "SCC[Node] ";

                    for(int i = 0; i < graph->getOrder(); i++)
                        output_file << scc[i] << " ";

                    output_file << endl;

                }else{

                    output_file << "Grafo não conexo, sem componentes fortemente conexas" << endl;

                }

            }else{

                output_file << "Grafo não direcionado, não possui SCC" << endl;

            }
            break;
        }

        //Ordenação Topológica
        case 6:{
            if(graph->getDirected()){

                if(graph->connectedGraph()){
                    int* topSort = graph->topologicalSort();

                    if(topSort != nullptr){

                        output_file << "Ordenacao Topologica "  << endl;
                        for(int i = 0; i < graph->getOrder(); i++)
                            output_file << topSort[i] << " ";
                        output_file << endl;

                    }else{

                        output_file << "Grafo possui circuito(s), portanto não é um DAG para ter ordenação topológica" << endl;

                    }

                }else{

                    output_file << "Grafo não conexo, sem ordenação topológica" << endl;

                }
            }else{

                output_file << "Grafo não direcionado, não possui ordenação topológica" << endl;

            }
            break;
        }

        case 7:{

            if(graph->connectedGraph()){

                Graph* auxGraph;

                if(graph->getDirected()){

                    auxGraph = graph->getSubjacent();

                }else{

                    auxGraph = graph;

                }

                //Retorno de pair é dividido em duas variaveis
                list<Node*> cds;
                float** alphasInfo;

                float alphaStep;
                float alphaMax;

                cout << "Maior alfa: "; cin >> alphaMax;
                cout << "Passo alfa: "; cin >> alphaStep;

                tie(cds, alphasInfo) = auxGraph->reactiveRandomizedGreedy(alphaMax, alphaStep);

                output_file << "Subconjunto Dominante Minimo Conexo" << endl;
                output_file << "Tamanho: " << cds.size() << endl;

                output_file << "Viabilidade: " << graph->solutionViabilty(cds) << endl;

            }else{

                output_file << "Grafo não conexo, sem Subconjunto Dominante Minimo Conexo" << endl;

            }
            break;
        }

        default:
            cout << "Saindo..." << endl;
            break;

    }

}

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

    Graph* graph;

    if(input_file.is_open())
        //Criando grafo
        graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

    else
        cout << "Unable to open " << argv[1];

    int selecao = 1;

    while(selecao != 0){
        system("clear");
        selecao = menu();

        if(output_file.is_open())
            selecionar(selecao, graph, output_file);

        else
            cout << "Unable to open " << argv[2];

        output_file << endl;

    }

    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    system("clear");

    return 0;
}
