//============================================================================
// Name        : FirstsFollows.cpp
// Author      : Rodrigo e Murilo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <fstream>
#include <locale.h>
#include <locale>

#include "Gramatica/Gramatica.h"
#include "TabelaPreditiva/Tabela.h"
#include "TesteGramatica/Teste.h"

using namespace std;

void novaGramatica(vector<string> &gramatica) {
	string entrada = "";
	int contador = 1;
	while (entrada != ":wq") {
		cout << "linha " << contador++ << ": " << endl;
		getline(cin, entrada);
		if (entrada != ":wq") {
			gramatica.push_back(entrada);
		} else {
			break;
		}
	}
}

void criandoNovaGramatica(Gramatica *&gram, Tabela *&table,
		vector<string> gramatica) {
	gram = new Gramatica(gramatica);
	gram->startaFirstRecursivo();
	gram->startaFollowRecursivo();
	table = new Tabela(gram);
	table->organizaTabela();
}

void lendoArquivo(string nomeArquivo, vector<string> &gramatica) {
	fstream grammar_file;
	grammar_file.open(nomeArquivo, ios::in);
	if (!grammar_file) {
		cout << "Arquivo não existe" << endl;
	} else {
		cout << "Arquivo encontrado..." << endl;
		while (!grammar_file.eof()) {
			char buffer[50];
			grammar_file.getline(buffer, 49);
			string line = buffer;
			gramatica.push_back(line);
		}

	}
	grammar_file.close();
}

int main() {
	setlocale(LC_ALL, "");
	string entrada = "";
	vector<string> gramatica;
	Gramatica *gram;
	Tabela *table;

	while (entrada != ":exit") {
		cout << "selecione uma opcao: " << endl;
		cout << "0. Abrir gramatica do arquivo..." << endl;
		cout << "1. Nova gramatica" << endl;
		cout << "2. Gramatica" << endl;
		cout << "3. Firsts" << endl;
		cout << "4. Follows" << endl;
		cout << "5. Tabela preditiva" << endl;
		cout << "6. Teste de entrada" << endl;
		cout << "7. Help" << endl;
		cout << endl;
		cout << "Escolha: ";
		getline(cin, entrada);
		cout << endl;
		if (entrada == "0") {
			string nomeArquivo;
			cout << "O arquivo deve estar na raiz onde o programa esta,"
					<< endl;
			cout << "ou deve passar o caminho completo." << endl;
			cout << "Digite agora o nome e extensão do arquivo: ";
			getline(cin, nomeArquivo);
			lendoArquivo(nomeArquivo, gramatica);
			criandoNovaGramatica(gram, table, gramatica);
			cout << "gramatica salva." << endl;
		} else if (entrada == "1") {
			novaGramatica(gramatica);
			criandoNovaGramatica(gram, table, gramatica);
		} else if (entrada == "2") {
			gram->imprimirGramatica();
		} else if (entrada == "3") {
			gram->imprimirFirstsTerminais();
		} else if (entrada == "4") {
			gram->imprimirFollowsTerminais();
		} else if (entrada == "5") {
			table->imprimir();
		} else if (entrada == "6") {
			string entradaTeste;
			cout << "Digite a entrada para teste: ";
			getline(cin, entradaTeste);
			cout << endl;
			Teste *teste = new Teste(gram, table, entradaTeste);
			teste->verificaEntrada();
		} else if (entrada == "7") {
			cout << "Digite ':wq' para salvar e sair das entradas" << endl;
		} else {
			cout << "Opcao não encontrada." << endl;
		}
		cout << endl;
	}

	system("PAUSE");
	return 0;
}

