/*
 * First.cpp
 *
 *  Created on: 17 de nov. de 2022
 *      Author: Rodrigo e Murilo
 */

#include "First.h"

First::First() {
	// TODO Auto-generated constructor stub

}

First::~First() {
	// TODO Auto-generated destructor stub
}

void First::imprimir() {
	string first = this->getFirst();
	string sentencial = this->getSentencial();
	vector<string> firstTerminais = this->getFirstTerminais();
	Regra *regra = this->getRegra();
	int numeroRegra = regra->getNumero();
	// 0 nao terminal, 1 terminal
	string tipo = this->getTipo() == 0 ? "Nao terminal" : "Terminal";

	string firstFinal = this->getFirstFinal();

	cout << "Sentencial: " << sentencial << endl;
	cout << "First: " << first << endl;
	if (this->getTipo() == 0) {
		cout << "First terminal: " << firstFinal << endl;
	}

	cout << "Firsts desse sentencial: " << firstTerminais.size() << endl;
	for (auto it = firstTerminais.begin(); it != firstTerminais.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	cout << "Regra: " << numeroRegra << endl;
	cout << "Tipo: " << tipo << endl;
}

void First::imprimeSoTerminais() {
	//First *first = this->getFirst();
	vector<string> terminais = this->getFirstTerminais();
	cout << this->getSentencial() << " -> ";
	for (auto it = terminais.begin(); it != terminais.end(); ++it) {
		cout << "{ ";
		if (next(it) == terminais.end()) {
			cout << *it << " }";
		} else {
			cout << *it << ", ";
		}
	}
	cout << endl;
}
