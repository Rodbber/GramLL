/*
 * Tabela.h
 *
 *  Created on: 17 de nov. de 2022
 *      Author: Rodrigo e Murilo
 */

#ifndef TABELAPREDITIVA_TABELA_H_
#define TABELAPREDITIVA_TABELA_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

#include "../Gramatica/Gramatica.h"
#include "../First/First.h"
#include "../Follow/Follow.h"

using namespace std;

class Tabela {
	vector<vector<int>> tabela;
	Gramatica *gramatica;
public:
	Tabela();
	virtual ~Tabela();

	Tabela(Gramatica *gramatica) {
		this->gramatica = gramatica;
		vector<string> terminais = gramatica->getTerminais();
		vector<string> naoTerminais = gramatica->getNaoTerminais();

		vector<vector<int>> tabela;

		int i, j;
		for (i = 0; i < naoTerminais.size(); i++) {
			vector<int> linha(terminais.size());
			fill(linha.begin(), linha.begin() + terminais.size(), 0);
			tabela.push_back(linha);
		}

		this->tabela = tabela;
	}

	Gramatica*& getGramatica() {
		return gramatica;
	}

	void setGramatica(Gramatica *&gramatica) {
		this->gramatica = gramatica;
	}

	const vector<vector<int> >& getTabela() const {
		return tabela;
	}

	void setTabela(const vector<vector<int> > &tabela) {
		this->tabela = tabela;
	}

	void organizaTabela();

	vector<int> indiceCombinacao(string naoTerminal, string terminal);

	void imprimir();



};

#endif /* TABELAPREDITIVA_TABELA_H_ */
