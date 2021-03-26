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
    vector<int> linhas = {};

};
struct Palavra{
    string letras;
    vector<struct Ocorrencia> ocorrencias = {};
};

struct Indice{
    vector<string> arquivos = {}; // Arquivos já lidos e QtdArquivos vai ser o size
    vector<struct Palavra> palavras = {};   // palavras do indice e QtdPalavras vai ser o size
};

//VERIFICA SE UM ARQUIVO JA FOI LIDO
bool JaFoiLido(vector<string> arquivos, string nomeArq){

    int sizeArqs = arquivos.size();
    for(int i = 0; i < sizeArqs; i++){
        if(arquivos[i] == nomeArq)
            return true;
    }

    return false;

}

//VERIFICA SE A PALAVRA JÁ EXISTE NA LISTA
bool ExistePalavra(vector<struct Palavra> lista, string palavra){
    int sizelist = lista.size();
    for(int i = 0; i<sizelist; i++){
        if(lista[i].letras == palavra)
            return true;
    }
    return false;
}


//VERIFICA SE O ARQUIVO JÁ ESTÁ NA LISTA DE OCORRÊNCIAS
bool ExisteArquivo(vector<struct Ocorrencia> ocorrencias, int arquivo){
    int sizelist = ocorrencias.size();
    for(int i = 0; i<sizelist; i++){
        if(ocorrencias[i].arquivo == arquivo)
            return true;
    }
    return false;
}

//INSERE UMA NOVA LINHA AO VETOR DE OCORRENCIAS CASO A PALAVRA JÁ TENHA APARECIDO NO ARQUIVO
void InsereOcorrencia(vector<struct Ocorrencia> &ocorrencias, int arquivo, int linha){
    int sizelist = ocorrencias.size();
    for(int i = 0; i < sizelist; i++){
        if(ocorrencias[i].arquivo == arquivo)
            ocorrencias[i].linhas.push_back(linha);
    }
}

//INSERE UM NOVO VALOR NO VETOR DE LINHAS DE UMA PALAVRA
void InsereLinha(vector<struct Palavra> &lista, string palavra, int linha, int arquivo){
    int sizelist = lista.size();
    for(int i = 0; i<sizelist; i++){
        if(lista[i].letras == palavra){
            if(ExisteArquivo(lista[i].ocorrencias, arquivo))
                InsereOcorrencia(lista[i].ocorrencias, arquivo, linha);
            else{
                struct Ocorrencia novo = {};
                novo.arquivo = arquivo;
                novo.linhas.push_back(linha);
                lista[i].ocorrencias.push_back(novo);
            }
        }
    }
}

//INSERE A NOVA PALAVRA EM ORDEM ALFABETICA NA LISTA
void InsereOrdem(struct Indice &indice, string palavra, int linha, int arquivo){

    struct Palavra nova = {};
    nova.letras = palavra;
    struct Ocorrencia ocorrencia = {};
    ocorrencia.arquivo = arquivo;
    ocorrencia.linhas.push_back(linha);
    nova.ocorrencias.push_back(ocorrencia);

    int sizelist = indice.palavras.size();
    int i;
    for(i = 0; i <sizelist; i ++){
        if(nova.letras < indice.palavras[i].letras)
            break;
    }

    indice.palavras.insert(indice.palavras.begin() + i, nova);

}

//LE AS PALAVRAS DE UM ARQUIVO
void LePalavras(struct Indice &indice, ifstream &arq){
    string linha;
    //LENDO CADA PALAVRA SEPARADAMENTE
    for(int i=1; getline(arq, linha); i++){
        string buf; // VARIAVEL PARA RECEBER AS PALAVRAS CONTIDAS EM CADA LINHA
        stringstream ss(linha); //TRANSFORMA A STRING EM UMA STREAM

        while (ss >> buf){
            if(ExistePalavra(indice.palavras, buf))
                InsereLinha(indice.palavras, buf, i, indice.arquivos.size());
            else
                InsereOrdem(indice, buf, i, indice.arquivos.size());
        }
    }
}

void ProcessaArq(struct Indice &indice){
    //RECEBE O NOME DO ARQUIVO TEXTO
    ifstream arq;
    string nomeArq;
    cout << "Digite o nome do arquivo texto com extensao: ";
    cin >> nomeArq;
    arq.open(nomeArq);
    if(!arq.is_open())
        cout << "Erro ao tentar abrir arquivo!" << "\n";
    else{
        //SE FOI LIDO
        if(JaFoiLido(indice.arquivos, nomeArq)){
            cout << "Arquivo ja foi lido e se encontra na lista de arquivos do indice" << "\n";
        //SE NÃO FOI LIDO
        }else{
            indice.arquivos.push_back(nomeArq); //INSERE O NOME DO ARQUIVO NA LISTA DE ARQUIVOS DO INDICE
            LePalavras(indice, arq);
        }
    }
    arq.close();
}

/*void GeraArqBin(vector<struct Palavra> &palavras){
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

*/
int main(){
    int op;
    struct Indice indice = {};

    //MENU
    do{
        cout << "Escolha a opcao desejada\n" << "1-Processar um arquivo texto;\n" << "2-Utilizar um indice existente para realizar buscas por palavras;\n" << "3-Encerrar o programa." << "\n\n";
        cout << "Opcao: ";
        cin >> op;
        if(op != 1 && op != 2 && op != 3)
            cout << "Digite uma opcao existente!" << "\n";

        switch (op){
            case 1:
                ProcessaArq(indice);
                break;


            case 2:
                //palavras = {};
                //LerArqBin(palavras);
                break;
        }

    }while(op != 3);

    /*for(int i = 0; i < indice.arquivos.size(); i++){
        cout << indice.arquivos[i] << "\n";
    }*/
    for(int i = 0; i < indice.palavras.size(); i ++){
        cout << "Palavra: " << indice.palavras[i].letras << " ";
        for(int j = 0; j < indice.palavras[i].ocorrencias.size(); j++){
            cout << "Arquivo: ";
            cout << indice.palavras[i].ocorrencias[j].arquivo << " Linhas: ";
            for(int k = 0; k < indice.palavras[i].ocorrencias[j].linhas.size(); k++){
                cout << indice.palavras[i].ocorrencias[j].linhas[k] << " ";
            }
        }
        cout << "\n\n";
    }
    return 0;
}
