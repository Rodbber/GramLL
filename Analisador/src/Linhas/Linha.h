/*
 * Linha.h
 *
 *  Created on: 17 de nov. de 2022
 *      Author: Rodrigo e Murilo
 */

#ifndef LINHAS_LINHA_H_
#define LINHAS_LINHA_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

class Linha {
private:
	string elementoSentencial;
	vector<string> regras;
public:
	Linha();
	virtual ~Linha();

	Linha(string linha);

	const string& getElementoSentencial() const {
		return elementoSentencial;
	}

	void setElementoSentencial(const string &elementoSentencial) {
		this->elementoSentencial = elementoSentencial;
	}

	const vector<string>& getRegras() const {
		return regras;
	}

	void setRegras(const vector<string> &regras) {
		this->regras = regras;
	}

	void imprimir();
};

#endif /* LINHAS_LINHA_H_ */
