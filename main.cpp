#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <string.h>

using namespace std;

struct Palavra{

    string letras;
    vector<int> linhas = {};

};

//VERIFICA SE A PALAVRA JÁ EXISTE NA LISTA
bool Existe(vector<struct Palavra> lista, string palavra){
    int sizelist = lista.size();
    for(int i = 0; i<sizelist; i++){
        if(lista[i].letras == palavra)
            return true;
    }

    return false;
}

//ORDENA A LISTA EM ORDEM ALFABETICA
void Ordena(vector<struct Palavra> &lista){
    int sizelist = lista.size();
    for(int i = 0; i < sizelist; i++){

        for(int j = i+1; j < sizelist; j++){

            if(lista[j].letras < lista[i].letras){

                lista[i].letras.swap(lista[j].letras);
                lista[i].linhas.swap(lista[j].linhas);
            }
        }
    }
}
//INSERE A NOVA PALAVRA EM ORDEM ALFABETICA NA LISTA
void InsereOrdem(vector<struct Palavra> &lista, string palavra, int linha){

    struct Palavra nova;
    nova.letras = palavra;
    nova.linhas.push_back(linha);
    lista.push_back(nova);
    Ordena(lista);

}

//INSERE UM NOVO VALOR NO VETOR DE LINHAS DE UMA PALAVRA
void InsereLinha(vector<struct Palavra> &lista, string palavra, int linha){
    int sizelist = lista.size();
    for(int i = 0; i<sizelist; i++){

        if(lista[i].letras == palavra)
            lista[i].linhas.push_back(linha);
    }
}

//LE AS PALAVRAS DO ARQUIVO
void LePalavras(ifstream &arq, vector<struct Palavra> &palavras){

    string linha;

    //LENDO CADA PALAVRA SEPARADAMENTE
    for(int i=1; getline(arq, linha); i++){

        string buf; // VARIAVEL PARA RECEBER AS PALAVRAS CONTIDAS EM CADA LINHA
        stringstream ss(linha); //TRANSFORMA A STRING EM UMA STREAM

        while (ss >> buf){

            if(Existe(palavras, buf))
                InsereLinha(palavras, buf, i);
            else
                InsereOrdem(palavras, buf, i);
        }
    }
}

void GeraArqBin(vector<struct Palavra> &palavras, ofstream &outfile){

    int n = palavras.size();
    outfile.write (reinterpret_cast<char*>(&n), sizeof (n)); // qtd de palavras

    for(int i=0; i<n; i++){
        int sizeWord = palavras[i].letras.size();
        string word = palavras[i].letras;
        int sizeVet = palavras[i].linhas.size();

        cout << "na gera: ";
        outfile.write(reinterpret_cast<char*>(&sizeWord), sizeof(int)); // qtd caracteres
        for(int j = 0; j < sizeWord; j++){
            outfile.write(&palavras[i].letras[j], sizeof(char)); //escreve a palavra
            cout << palavras[i].letras[j];
        }
        cout << "\n";

        outfile.write(reinterpret_cast<char*>(&sizeVet), sizeof(int)); // qtd ocorrências
        for(int k=0; k<sizeVet; k++){
            outfile.write(reinterpret_cast<char*>(&(palavras[i].linhas[k])), sizeof(int)); // vetor de linhas
            cout << palavras[i].linhas[k] << " ";
        }
        cout << "\n";
    }
    outfile.close();
}

void LerArqBin(vector<struct Palavra> &lista, ifstream &infile){
    int n;
    struct Palavra nova;

    infile.read(reinterpret_cast<char*>(&n), sizeof(int));  //  qtd palavras

    for(int i = 0; i < n; i++){
        int qtdChar, qtdOcorrencias;
        nova = {};

        infile.read (reinterpret_cast<char*>(&qtdChar), sizeof(int));    // qtdcaracteres

        char cstr[qtdChar];
        for(int j = 0; j < qtdChar; j++){
            infile.read (&cstr[j], sizeof(char));
            nova.letras.push_back(cstr[j]);
        }

        infile.read (reinterpret_cast<char*>(&qtdOcorrencias), sizeof(int));

        for(int k=0; k<qtdOcorrencias; k++){
            int linha;
            infile.read(reinterpret_cast<char*>(&linha), sizeof(int));
            nova.linhas.push_back(linha);
        }

        lista.push_back(nova);

    }
}


int main(){
    //DECLARACAO DE VARIAVEIS
    int op, op2, sizelist;
    string nomeTexto;
    ifstream arq;
    ofstream outfile;
    ifstream infile;
    string palavra;
    vector<struct Palavra> palavras = {};


    //MENU
    do{
        cout << "Escolha a opcao desejada\n" << "1-Criar um indice para um arquivo texto;\n" << "2-Utilizar um indice existente para realizar buscas por palavras;\n" << "3-Encerrar o programa." << "\n\n";
        cout << "Opcao: ";
        cin >> op;
        if(op != 1 && op != 2 && op != 3)
            cout << "Digite uma opcao existente!" << "\n";

        switch (op){
            //CRIAR UM INDICE
            case 1:
                cout << "Digite o nome do arquivo texto com extensao: ";
                cin >> nomeTexto;
                arq.open(nomeTexto);
                if(!arq.is_open())
                    cout << "Erro ao abrir arquivo!" << "\n";
                else{
                    palavras = {};
                    LePalavras(arq, palavras);

                    // CRIANDO ARQ BINÁRIO
                    outfile.open ("indice.dat", ios :: binary | ios :: out);
                    if(!outfile.is_open())
                        cout << "Erro ao abrir arquivo!" << "\n";

                    GeraArqBin(palavras, outfile);

                    //TESTE
                    /*for(int j = 0; j < palavras.size(); j++){
                        cout << palavras[j].letras << "-> ";
                        for(int k = 0; k < palavras[j].linhas.size(); k++)
                            cout << palavras[j].linhas[k] << " ";
                        cout << "\n";
                    }*/
                    }
                break;


            case 2:
                palavras = {};

                infile.open ("indice.dat", ios :: binary | ios :: out);
                if(!infile.is_open())
                    cout << "Erro ao abrir arquivo!" << "\n";

                LerArqBin(palavras, infile);

                //TESTE
                cout << "Testando: " << "\n";
                for(int i = 0; i < palavras.size(); i++){
                    cout << palavras[i].letras << " -> ";
                    for(int j = 0; j < palavras[i].linhas.size(); j++)
                        cout << palavras[i].linhas[j] << " ";
                    cout << "\n";
                }

                do{
                    cout << "\n1: Buscar palavra \n";
                    cout << "2: Sair \n";
                    cout << "Opcao: ";
                    cin >> op2;
                    cout << "\n";

                    if(op2 == 1){
                        cout << "Digite a palavra a ser buscada: ";
                        cin >> palavra;
                        cout << "\n";

                            sizelist = palavras.size();

                            if(Existe(palavras, palavra)){
                                for(int i=0; i<sizelist; i++){   // percorre a lista
                                    if(palavras[i].letras == palavra){ // achou a posição da palavra
                                        cout << "Qtd de ocorrencias --> " << palavras[i].linhas.size() << endl;

                                        for(int j=0; j<palavras[i].linhas.size(); j++){
                                            cout << "Linhas --> " << palavras[i].linhas[j] << endl;
                                        }
                                    }
                                }

                            }else{
                                cout << "Palavra nao encontrada! \n\n";
                            }
                    }

                }while(op2 != 2);
                break;
        }

    }while(op != 3);

    arq.close();
    infile.close();

    return 0;
}
