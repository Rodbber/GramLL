/*
 * Tabela.cpp
 *
 *  Created on: 17 de nov. de 2022
 *      Author: Rodrigo e Murilo
 */

#include "Tabela.h"

Tabela::Tabela() {
	// TODO Auto-generated constructor stub

}

Tabela::~Tabela() {
	// TODO Auto-generated destructor stub
}

void Tabela::organizaTabela() {

	vector<vector<int>> tabela = this->getTabela();

	Gramatica *gramatica = this->getGramatica();

	vector<First*> firsts = gramatica->getFirsts();
	vector<Follow*> follows = gramatica->getFollows();

	vector<string> naoTerminais = gramatica->getNaoTerminais();
	vector<string> terminais = gramatica->getTerminais();

	vector<vector<int>> guardaAsRegrasFirst;
	vector<vector<int>> guardaAsRegrasFollow;
	int i, j, k, x;
	for (i = 0; i < naoTerminais.size(); i++) {

		for (k = 0; k < terminais.size(); k++) {
			for (j = 0; j < firsts.size(); j++) {
				First *first = firsts[j];
				vector<string> firstsTerminais = first->getFirstTerminais();
				if (first->getSentencial() == naoTerminais[i]
						&& find(firstsTerminais.begin(), firstsTerminais.end(),
								terminais[k]) != firstsTerminais.end()) {
					guardaAsRegrasFirst.push_back(
							{ i, k, first->getRegra()->getNumero() });
				}
			}

			for (j = 0; j < follows.size(); j++) {
				Follow *follow = follows[j];
				if (follow->getFollowDe() == naoTerminais[i]
						&& follow->getDerivaEmVazio() != -1
						&& follow->getRegra()->getNumero() != 0) {
					int derivacao = follow->getDerivaEmVazio();

					vector<string> followsStr = follow->getTerminaisFollow();
					for (x = 0; x < followsStr.size(); x++) {
						if (find(followsStr.begin(), followsStr.end(),
								terminais[k]) != followsStr.end()) {
							int lastIndiceTerminals = terminais.size() - 1;
							guardaAsRegrasFollow.push_back(
									{ i, k, derivacao });
							guardaAsRegrasFollow.push_back( { i,
									lastIndiceTerminals, derivacao });
						}
					}
				}
			}
		}
	}

	for (i = 0; i < guardaAsRegrasFirst.size(); i++) {
		for (j = 0; j < guardaAsRegrasFirst[i].size(); j++) {
			if (guardaAsRegrasFirst[i].size() == 3
					&& guardaAsRegrasFirst[i][2] != -1) {
				vector<int> indicesTabela = this->indiceCombinacao(
						naoTerminais[guardaAsRegrasFirst[i][0]],
						terminais[guardaAsRegrasFirst[i][1]]);
				if (indicesTabela[0] != -1 && indicesTabela[1] != -1) {
					tabela[indicesTabela[0]][indicesTabela[1]] =
							guardaAsRegrasFirst[i][2];
				}
			}
		}
	}

	for (i = 0; i < guardaAsRegrasFollow.size(); i++) {
		for (j = 0; j < guardaAsRegrasFollow[i].size(); j++) {
			if (guardaAsRegrasFollow[i].size() == 3
					&& guardaAsRegrasFollow[i][2] != -1) {
				vector<int> indicesTabela = this->indiceCombinacao(
						naoTerminais[guardaAsRegrasFollow[i][0]],
						terminais[guardaAsRegrasFollow[i][1]]);
				if (indicesTabela[0] != -1 && indicesTabela[1] != -1) {
					tabela[indicesTabela[0]][indicesTabela[1]] =
							guardaAsRegrasFollow[i][2];
				}
			}
		}
	}

	this->setTabela(tabela);
}

vector<int> Tabela::indiceCombinacao(string naoTerminal, string terminal) {
	vector<string> naoTerminais = this->getGramatica()->getNaoTerminais();
	vector<string> terminais = this->getGramatica()->getTerminais();
	int i, j;
	for (i = 0; i < naoTerminais.size(); i++) {
		for (j = 0; j < terminais.size(); j++) {
			if (naoTerminais[i] == naoTerminal && terminais[j] == terminal) {
				return {i, j};
			}
		}
	}
	return {-1, -1};
}

void Tabela::imprimir() {
	vector<vector<int>> tabela = this->getTabela();
	int numeroUltimaRegra =
			this->getGramatica()->getRegras().back()->getNumero();
	int tamanho = to_string(numeroUltimaRegra).length();
	cout << "TABELA PREDITIVA" << endl;
	int i, j;
	vector<string> terminais = this->getGramatica()->getTerminais();
	vector<string> naoTerminais = this->getGramatica()->getNaoTerminais();
	cout << "  ";
	for (auto it = terminais.begin(); it != terminais.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	for (auto i = 0; i < tabela.size(); i++) {
		cout << naoTerminais[i] << " ";
		for (j = 0; j < tabela[i].size(); j++) {
			cout << tabela[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
