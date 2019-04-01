#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"

using namespace std;

int main(int argc, char const *argv[]) {

    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6) {

        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node>"
        return -1;

    }

    string program_name(argv[0]);
    cout << "Running " << program_name << " ... " << endl;

    //Abrindo arquivo de entrada
    ifstream input_file(argv[1]);

    //Criação do arquivo de saída
    ofstream output_file(argv[2]);

    //Verificando se o grafo é direcionado
    if (argv[3] == 0) {

        bool directed = false;

    }else {

        bool directed = true;

    }

    //Verificando se as arestas são ponderadas
    if (argv[4] == 0) {

        bool weighted_edge = false;

    }else {

        bool weighted_edge = true;
    }

    //Verificando se os nós são ponderados
    if (argv[5] == 0) {

        bool weighted_node = false;

    }else {

        bool weighted_node = true;
    }

    //Leitura de arquivo:
    if(input_file.is_open()){

        //Variável para pegar número de vértices
        int order;
        getline(input_file, order);

    }else {

        cout << "Unable to open " << argv[1];

    }

    //Criando objeto grafo
    Graph graph(order, directed, weighted_edge, weighted_node);

    /*
    Escrita em arquivo (exemplo):
    if(output_file.is_open()){

        output_file << "Hello World!" << endl;

    }else {

        cout << "Unable to open " << argv[2];

    }
    */

    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    return 0;
}
