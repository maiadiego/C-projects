#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <string.h>

using namespace std;

struct Ocorrencia{
    int arquivo;
    int qtdOcorrencias;
    vector<int> linhas = {};
    
}
struct Palavra{
    string letras;
    //vector<int> linhas = {};
    vector<struct Ocorrencia> ocorrencias = {};
    int qtdOcorrencias; // quantidade de arquivos que possuem essa palavra
};

struct Indice{
    int qtdArquivos;  // qtd de arquivos lidos até então 
    vector<string> arquivos = {}; // lista contendo o nome dos arquivos já processados (struct Arquivo virou isso eu acho)
    int qtdPalavras;
    vector<struct Palavra> palavras = {};   // lista contendo todas as palavras já processadas
} 

int ProcessaArq(vector<string> &arquivos, vector<struct Palavra> &palavras){ // essas duas listas estão dentro de Struct Indice 
    ifstream arq;
    cout << "Digite o nome do arquivo texto com extensao: ";
    cin >> nomeArq;
    
    // verifica se o arquivo já foi lido
    int sizeArqs = arquivos.size();
    for(int i=0; i<sizeArqs; i++){
        if(arquivos[i] == nomeArq){
            return 0;
        }
    }
    // se não foi lido insere
    arquivos.push_back(nomeArq)
    arq.open(nomeTexto);
    if(!arq.is_open())
        cout << "Erro ao abrir arquivo!" << "\n";
    
    string linha;
    for(int i=1; getline(arq, linha); i++){
        string buf; // VARIAVEL PARA RECEBER AS PALAVRAS CONTIDAS EM CADA LINHA
        stringstream ss(linha); //TRANSFORMA A STRING EM UMA STREAM
        while (ss >> buf){
            if(Existe(palavras, buf))
                InsereLinha(palavras, buf, i);
                // falta incrementar a lista de ocorrências dentro de struct Palavra
            else
                InsereOrdem(palavras, buf, i);
                // falta incrementar a lista de ocorrências dentro de struct Palavra
        }
    }
    
    return 1; // arquivo foi processado 
}
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
void LePalavras(vector<struct Palavra> &palavras){
    ifstream arq;
    string nomeTexto;
    cout << "Digite o nome do arquivo texto com extensao: ";
    cin >> nomeTexto;
    arq.open(nomeTexto);
    if(!arq.is_open())
        cout << "Erro ao abrir arquivo!" << "\n";
    else{
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
    arq.close();
}

void GeraArqBin(vector<struct Palavra> &palavras){
    ofstream outfile;
    outfile.open ("indice.dat", ios :: binary | ios :: out);
    if(!outfile.is_open())
        cout << "Erro ao abrir arquivo!" << "\n";
    else{
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
    }
    outfile.close();
}

void LerArqBin(vector<struct Palavra> &lista){
    ifstream infile;
    infile.open ("indice.dat", ios :: binary | ios :: out);
    if(!infile.is_open())
        cout << "Erro ao abrir arquivo!" << "\n";
    else{
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
            
        // loop para buscar palavras
        do{
            int op;
            cout << "\n1: Buscar palavra \n";
            cout << "2: Sair \n";
            cout << "Opcao: ";
            cin >> op;
            cout << "\n";
            if(op == 1){
                string palavra;
                cout << "Digite a palavra a ser buscada: ";
                cin >> palavra;
                cout << "\n";
                
                int sizelist = lista.size();

                if(Existe(lista, palavra)){
                    for(int i=0; i<sizelist; i++){   // percorre a lista
                        if(lista[i].letras == palavra){ // achou a posição da palavra
                            cout << "Qtd de ocorrencias --> " << lista[i].linhas.size() << endl;

                            for(int j=0; j<lista[i].linhas.size(); j++){
                                cout << "Linhas --> " << lista[i].linhas[j] << endl;
                            }
                        }
                    }

                }else{
                    cout << "Palavra nao encontrada! \n\n";
                    }
                }

            }while(op != 2);
    }
    
    infile.close();
}


int main(){
    int op;
    vector<struct Palavra> palavras = {};

    //MENU
    do{
        cout << "Escolha a opcao desejada\n" << "1-Criar um indice para um arquivo texto;\n" << "2-Utilizar um indice existente para realizar buscas por palavras;\n" << "3-Encerrar o programa." << "\n\n";
        cout << "Opcao: ";
        cin >> op;
        if(op != 1 && op != 2 && op != 3)
            cout << "Digite uma opcao existente!" << "\n";

        switch (op){
            case 1: //CRIAR UM INDICE
                palavras = {};
                LePalavras(palavras);
                GeraArqBin(palavras);
                break;


            case 2:
                palavras = {};
                LerArqBin(palavras);
                break;
        }

    }while(op != 3);

    return 0;
}
