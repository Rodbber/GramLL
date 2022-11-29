/*
 * Regras.cpp
 *
 *  Created on: 17 de nov. de 2022
 *      Author: Rodrigo e Murilo
 */

#include "Regras.h"

Regra::Regra() {
	// TODO Auto-generated constructor stub

}

Regra::~Regra() {
	// TODO Auto-generated destructor stub
}


Regra::Regra(Linha *linha, int numero, string regra) {
		this->linha = linha;
		this->numero = numero;
		this->sentencial = linha->getElementoSentencial();
		this->regra = regra;

		vector<string> terminais;
		vector<string> naoTerminais;

		string::iterator it;

		for (it = regra.begin(); it != regra.end(); it++) {
			string elemento = "";
			elemento += *it;
			if (isupper(*it)) {
				naoTerminais.push_back(elemento);
			} else {
				terminais.push_back(elemento);
			}
			this->vazio = elemento == "&";
			if (this->vazio) {
				break;
			}
//			if(elemento == "&"){
//				vazio = true;
//			}
		}
		this->vazio = vazio;
		this->terminais = terminais;
		this->naoTerminais = naoTerminais;
	}



	void Regra::imprimir() {
		string regra = this->getRegra();
		Linha *linha = this->getLinha();
		string sentencial = this->getSentencial();
		int numero = this->getNumero();
		vector<string> terminais = this->getTerminais();
		vector<string> naoTerminais = this->getNaoTerminais();

		cout << "Regra: " << regra << endl;
		cout << "Linha: " << linha->getElementoSentencial() << endl;
		cout << "Numero: " << numero << endl;
		if (this->vazio) {
			cout << "Vazio.";
			cout << endl;
			return;
		}
		cout << "Nao terminais: ";
		for (auto i = terminais.begin(); i != terminais.end(); ++i) {
			cout << *i << " ";
		}
		cout << endl;
		cout << "Terminais: ";
		for (auto i = naoTerminais.begin(); i != naoTerminais.end(); ++i) {
			cout << *i << " ";
		}
		cout << endl;
	}
