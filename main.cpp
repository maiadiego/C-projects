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
    vector<struct Palavra> palavras = {};   // Palavras do indice e QtdPalavras vai ser o size
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

void SalvaIndice(struct Indice &indice){
    ofstream outfile;
    outfile.open("indice.dat", ios :: binary | ios :: out);
    if(!outfile.is_open())
        cout << "Erro ao abrir o arquivo" << "\n";

    else{
        int qtdArquivos = indice.arquivos.size();
        outfile.write (reinterpret_cast<char*>(&qtdArquivos), sizeof (qtdArquivos));
        for(int i=0; i<qtdArquivos; i++){
            int qtdLetrasArq = indice.arquivos[i].size();
            outfile.write (reinterpret_cast<char*>(&qtdLetrasArq), sizeof (qtdLetrasArq));
            for(int l = 0; l < qtdLetrasArq; l++){
                outfile.write(&indice.arquivos[i][l], sizeof(char));
            }
        }
        // palavras diferentes que foram encontradas
        int qtdPalavras = indice.palavras.size();
        outfile.write (reinterpret_cast<char*>(&qtdPalavras), sizeof (qtdPalavras));

        for(int j=0; j<qtdPalavras; j++){
            int qtdLetrasPalavra = indice.palavras[j].letras.size();
            outfile.write (reinterpret_cast<char*>(&qtdLetrasPalavra), sizeof (qtdLetrasPalavra));
            //int qtdOcorrencias = indice.palavras[j].ocorrencias.size();
            for(int l = 0; l < qtdLetrasPalavra; l++){
                outfile.write(&indice.palavras[j].letras[l], sizeof(char));
            }

            int arqs = indice.palavras[j].ocorrencias.size();
            int qtdOcorrencias = 0;
            for(int y = 0; y < arqs; y++){
                qtdOcorrencias += indice.palavras[j].ocorrencias[y].linhas.size();
            }
            outfile.write (reinterpret_cast<char*>(&qtdOcorrencias), sizeof (qtdOcorrencias));

            for(int k=0; k<arqs; k++){
                int idArq = indice.palavras[j].ocorrencias[k].arquivo;
                int size_linhas = indice.palavras[j].ocorrencias[k].linhas.size();
                outfile.write (reinterpret_cast<char*>(&idArq), sizeof (idArq));
                outfile.write (reinterpret_cast<char*>(&size_linhas), sizeof (size_linhas));

                for(int x=0; x<size_linhas; x++){
                    int linha = indice.palavras[j].ocorrencias[k].linhas[x];
                    outfile.write (reinterpret_cast<char*>(&linha), sizeof (linha));
                }
            }
        }
    }

    outfile.close();
}

void LeIndice(){
    ifstream infile;
    infile.open("indice.dat", ios :: binary);
    if(!infile.is_open())
        cout << "Erro ao abrir o arquivo" << "\n";

    else{
        int n, aux, aux2, aux3;

        //LE QUANTIDADE DE ARQUIVOS E SUAS QUANTIDADES DE LETRAS E NOMES
        infile.read(reinterpret_cast<char*>(&n), sizeof(int));
        cout << "Quantidade de arquivos: " << n << "\n\n";
        for(int i=0; i<n; i++){
            infile.read(reinterpret_cast<char*>(&aux), sizeof(int));
            cout << "Quantidade de letras: " << aux << " - ";
            char cstr[aux];
            for(int l = 0; l < aux; l++){
                infile.read(&cstr[l], sizeof(char));
                cout << cstr[l];
            }
            cout << "\n";
        }
        cout << "\n";

        //LE AS PALAVRAS DO INDICE
        infile.read(reinterpret_cast<char*>(&n), sizeof(int));
        cout << "Numero de palavras no indice " << n << "\n\n";
        for(int j=0; j<n; j++){
            infile.read(reinterpret_cast<char*>(&aux), sizeof(int));
            cout << "Quantidade de letras da palavra: " << aux << " - ";
            cout << "Palavra: ";
            char cstr[aux];
            for(int l = 0; l < aux; l++){
                infile.read(&cstr[l], sizeof(char));
                cout << cstr[l];
            }
            cout << "\n";

            infile.read(reinterpret_cast<char*>(&aux), sizeof(int));
            cout << "Ocorrencias: " << aux << "\n";
            for(int k = 0; k <= aux; k++){
                infile.read(reinterpret_cast<char*>(&aux2), sizeof(int));
                cout << "No arquivo " << aux2 << ": ";
                infile.read(reinterpret_cast<char*>(&aux2), sizeof(int));
                cout << aux2 << " veze(s). Linha(s): ";
                aux -=aux2;

                for(int x=0; x<aux2; x++){
                    infile.read(reinterpret_cast<char*>(&aux3), sizeof(int));
                    cout << aux3 << " ";
                }
            }
            cout << "\n\n";
        }
    }
    infile.close();
}

int main(){
    int op;
    struct Indice indice = {};

    //MENU
    do{
        cout << "Escolha a opcao desejada\n" << "1-Processar um arquivo texto;\n" << "2-Salvar o indice atual;\n" << "3-Encerrar o programa." << "\n\n";
        cout << "Opcao: ";
        cin >> op;
        if(op != 1 && op != 2 && op != 3)
            cout << "Digite uma opcao existente!" << "\n";

        switch (op){
            case 1:
                ProcessaArq(indice);
                break;

            case 2:
                SalvaIndice(indice);
                //TESTE PARA LER TODOS OS DADOS DO ARQUIVO BINARIO
                LeIndice();
                break;
        }

    }while(op != 3);
	
	//TESTE NOME DOS ARQUIVOS NO VETOR DO INDICE
    /*for(int i = 0; i < indice.arquivos.size(); i++){
        cout << indice.arquivos[i] << "\n";
    }*/

    /* TESTE PALAVRAS EM ORDEM
    for(int i = 0; i < indice.palavras.size(); i ++){
        cout << "Palavra: " << indice.palavras[i].letras << " \n";
        for(int j = 0; j < indice.palavras[i].ocorrencias.size(); j++){
            cout << "Arquivo: ";
            cout << indice.palavras[i].ocorrencias[j].arquivo << "\nLinhas: ";
            for(int k = 0; k < indice.palavras[i].ocorrencias[j].linhas.size(); k++){
                cout << indice.palavras[i].ocorrencias[j].linhas[k] << " ";
            }
        }
        cout << "\n\n";
    }

    */

    return 0;
}
