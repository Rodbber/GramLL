/*
 * Linha.cpp
 *
 *  Created on: 17 de nov. de 2022
 *      Author: Rodrigo e Murilo
 */

#include "Linha.h"

Linha::Linha() {
	// TODO Auto-generated constructor stub

}

Linha::~Linha() {
	// TODO Auto-generated destructor stub
}


string removeEspacos(string s) {
	string str = s;
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

vector<string> split(string s, string d) {
	string str = s;
	vector<string> novoSplit;
	string token;
	size_t pos = 0;
	while ((pos = str.find(d)) != std::string::npos) {
		token = str.substr(0, pos);
		novoSplit.push_back(token);
		str.erase(0, pos + d.length());
	}
	novoSplit.push_back(str);
	return novoSplit;
}

vector<int> pontoInicial(string s) {
	int i, j;
	for (i = 0, j = 1; j < s.size(); i = j++) {
		if ((s[i] == '-' && s[j] == '>')) {
			return {i, j};
		} else if (s[j] == ':') {
			return {j};
		}
	}
	return {-1};
}

Linha::Linha(string linha) {
	string linhaSemEspaco = removeEspacos(linha);
	vector<int> pontoinicial = pontoInicial(linhaSemEspaco);
	string regrasLinha;
	vector<string> regrasSeparadas;
	if (pontoinicial.size() > 1) {
		int traco = pontoinicial[0];
		int fimtraco = pontoinicial[1];
		this->elementoSentencial = linhaSemEspaco.substr(0, traco);
		regrasLinha = linhaSemEspaco.substr(fimtraco + 1,
				linhaSemEspaco.length() - fimtraco);
	} else if (pontoinicial.size() == 1) {
		this->elementoSentencial = linhaSemEspaco.substr(0, pontoinicial[0]);
		regrasLinha = linhaSemEspaco.substr(pontoinicial[0],
				linhaSemEspaco.length() - pontoinicial[0]);
	} else {
		cout
				<< "Error, elemento inicial nao pode ser identificado, usar '->' ou ':'"
				<< endl;
	}
	regrasSeparadas = split(regrasLinha, "|");
	this->setRegras(regrasSeparadas);
}

void Linha::imprimir() {
	string elementoSentencial = this->getElementoSentencial();
	vector<string> regras = this->getRegras();
	//int i, j;
	cout << "Elemento sentencial: " << elementoSentencial << endl;
	cout << "Regras: " << endl;
	for (auto i = regras.begin(); i != regras.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
}
