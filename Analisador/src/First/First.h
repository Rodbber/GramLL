/*
 * First.h
 *
 *  Created on: 17 de nov. de 2022
 *      Author: Rodrigo e Murilo
 */

#ifndef FIRST_FIRST_H_
#define FIRST_FIRST_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

#include "../Regras/Regras.h"

using namespace std;

class First {
private:
	string first;
	string firstFinal;
	string sentencial;
	Regra *regra;
	vector<string> firstTerminais;
	vector<string> firstNaoTerminalStr;
	//First *firstNaoTerminal;
	vector<string> firsts;
	bool derivaEmVazio;
	// 0 nao terminal, 1 terminal
	int tipo;
public:
	First();
	virtual ~First();

	First(Regra *regra) {
		this->derivaEmVazio = regra->isVazio();
		this->regra = regra;
		this->sentencial = regra->getSentencial();
		string regraStr = regra->getRegra();
		this->first = regraStr[0];
		this->tipo = isupper(regraStr[0]) ? 0 : 1;
		if (this->tipo == 1) {
			this->firstFinal = regraStr[0];
			//vector<string> terminais = {regraStr[0]};
			this->addFirstTerminais({this->firstFinal});
		}
	}

	const string& getFirst() const {
		return first;
	}

	void setFirst(const string &first) {
		this->first = first;
	}

	Regra*& getRegra() {
		return regra;
	}

	void setRegra(Regra *&regra) {
		this->regra = regra;
	}

	const string& getSentencial() const {
		return sentencial;
	}

	void setSentencial(const string &sentencial) {
		this->sentencial = sentencial;
	}

	int getTipo() const {
		return tipo;
	}

	void setTipo(int tipo) {
		this->tipo = tipo;
	}

	const string& getFirstFinal() const {
		return firstFinal;
	}

	void setFirstFinal(const string &firstFinal) {
		this->firstFinal = firstFinal;
	}

	bool isDerivaEmVazio() const {
		return derivaEmVazio;
	}

	void setDerivaEmVazio(bool derivaEmVazio) {
		this->derivaEmVazio = derivaEmVazio;
	}

	const vector<string>& getFirstNaoTerminalStr() const {
		return firstNaoTerminalStr;
	}

	void setFirstNaoTerminalStr(const vector<string> &firstNaoTerminalStr) {
		this->firstNaoTerminalStr = firstNaoTerminalStr;
	}

	void addFirstNaoTerminalStr(string firstNaoTerminalStr) {
		vector<string> firstNaoTerminalStrvec = this->getFirstNaoTerminalStr();
		if (find(firstNaoTerminalStrvec.begin(), firstNaoTerminalStrvec.end(),
				firstNaoTerminalStr) != firstNaoTerminalStrvec.end()) {
			this->firstNaoTerminalStr.push_back(firstNaoTerminalStr);
		}
		//this->firstNaoTerminalStr = firstNaoTerminalStr;
	}

	const vector<string>& getFirsts() const {
		return firsts;
	}

	void setFirsts(const vector<string> &firsts) {
		this->firsts = firsts;
	}

	const vector<string>& getFirstTerminais() const {
		return firstTerminais;
	}

	void setFirstTerminais(const vector<string> &firstTerminal) {
		this->firstTerminais = firstTerminal;
	}

	void addFirstTerminais(vector<string> firstTerminal) {

		for (auto it = firstTerminal.begin(); it != firstTerminal.end(); ++it) {
			//cout << "terminal: " << *it << endl;
			vector<string> firstTerminais = this->getFirstTerminais();
			if (find(firstTerminais.begin(), firstTerminais.end(),
					*it) == firstTerminais.end()) {
				this->firstTerminais.push_back(*it);
			}
		}

	}

	void imprimir();

	void imprimeSoTerminais();

};

#endif /* FIRST_FIRST_H_ */
