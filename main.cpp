#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "Node.h"

using namespace std;

int main(int argc, char const *argv[]) {

    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6) {

        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node>";
        return -1;

    }

    string program_name(argv[0]);
    cout << "Running " << program_name << " ... " << endl;

    //Abrindo arquivo de entrada
    ifstream input_file(argv[1]);

    //Criação do arquivo de saída
    ofstream output_file(argv[2]);

    //Leitura de arquivo:
    if(!input_file.is_open()){

        cout << "Unable to open " << argv[1];

    }

    //Criando objeto grafo
    Graph graph(atoi(argv[3]), argv[4], argv[5], argv[6]);

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;

    //Leitura de dados a partir de arquivo
    while(input_file >> idNodeSource >> idNodeTarget) {

        graph.insertNode(idNodeSource, idNodeTarget);

    }

    if(output_file.is_open()){

        //Imprimindo funções básicas
        output_file << "Ordem: " << graph.getOrder() << endl;
        output_file << "Direcionado: " << graph.getDirected() << endl;
        output_file << "Numero de arestas: " << graph.getNumberEdges() << endl;
        output_file << "No id = 7 esta no grafo? " << graph.searchNode(7) << endl;
        output_file << "No id = 4 esta no grafo? " << graph.searchNode(4) << endl;

        //Imprimindo o Grafo
        graph.printGraph(output_file);

        //Removendo um nó
        output_file << "Removendo nó id = 4" << endl;
        graph.removeNode(4);
        graph.printGraph(output_file);

    }else {

        cout << "Unable to open " << argv[2];

    }


    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();


    return 0;
}
