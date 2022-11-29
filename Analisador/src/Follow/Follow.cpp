/*
 * Follow.cpp
 *
 *  Created on: 17 de nov. de 2022
 *      Author: Rodrigo e Murilo
 */

#include "Follow.h"

Follow::Follow() {
	// TODO Auto-generated constructor stub

}

Follow::~Follow() {
	// TODO Auto-generated destructor stub
}

void Follow::imprimir() {
	string sentencial = this->getSentencial();
	Regra *regra = this->getRegra();
	int numero = regra->getNumero();
	string followDe = this->getFollowDe();
	string follow = this->getFollow();
	string firstDoFollow = this->getFirstDoFollow();
	vector<First*> firsts = this->getFirsts();
	vector<string> followsTerminais = this->getTerminaisFollow();
	vector<string> followsNaoTerminais = this->getNaoTerminaisFollow();
	// 0 nao terminal, 1 terminal
	string tipo = this->getTipo() == 0 ? "Nao terminal" : "Terminal";

	cout << "Follow de: " << followDe << endl;
	cout << "Follow: " << follow << endl;
	cout << "FirstDoFollow: " << firstDoFollow << endl;
	cout << "Firsts: " << firsts.size() << endl;
	for (auto i = firsts.begin(); i != firsts.end(); ++i) {
		First *first = *i;
		cout << first->getFirstFinal() << " ";
	}
	cout << endl;
	if (this->getTipo() == 0) {
		cout << "Follow Terminal: " << this->getFollowTerminal() << endl;
	}
	cout << "Follows nao terminais: " << followsNaoTerminais.size() << endl;
	for (auto i = followsNaoTerminais.begin(); i != followsNaoTerminais.end();
			++i) {
		cout << *i << " ";
	}
	cout << endl;
	cout << "Follows terminais: " << followsTerminais.size() << endl;
	for (auto i = followsTerminais.begin(); i != followsTerminais.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
	cout << "Regra: " << numero << endl;
	cout << "Tipo: " << tipo << endl;
	string derivaEmVazio =
			this->getDerivaEmVazio() == -1 ?
					"Nao" : to_string(this->getDerivaEmVazio());
	cout << "Deriva em vazio: " << derivaEmVazio << endl;
	cout << endl;
}
