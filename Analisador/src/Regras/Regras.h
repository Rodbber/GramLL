/*
 * Regras.h
 *
 *  Created on: 17 de nov. de 2022
 *      Author: Rodrigo e Murilo
 */

#ifndef REGRAS_REGRA_H_
#define REGRAS_REGRA_H_
#include <string>
#include <vector>
#include <map>
#include <regex>

#include "../Linhas/Linha.h"

using namespace std;

class Regra {
private:
	string regra;
	Linha *linha;
	string sentencial;
	int numero;
	bool vazio;
	vector<string> terminais;
	vector<string> naoTerminais;
public:
	Regra();
	virtual ~Regra();

	Regra(Linha *linha, int numero, string regra);

	Linha*& getLinha() {
			return linha;
		}

		void setLinha(Linha *&linha) {
			this->linha = linha;
		}

		int getNumero() const {
			return numero;
		}

		void setNumero(int numero) {
			this->numero = numero;
		}

		const string& getSentencial() const {
			return sentencial;
		}

		void setSentencial(const string &sentencial) {
			this->sentencial = sentencial;
		}

		const vector<string>& getNaoTerminais() const {
			return naoTerminais;
		}

		void setNaoTerminais(const vector<string> &naoTerminais) {
			this->naoTerminais = naoTerminais;
		}

		const string& getRegra() const {
			return regra;
		}

		void setRegra(const string &regra) {
			this->regra = regra;
		}

		const vector<string>& getTerminais() const {
			return terminais;
		}

		void setTerminais(const vector<string> &terminais) {
			this->terminais = terminais;
		}

		bool isVazio() const {
			return vazio;
		}

		void setVazio(bool vazio) {
			this->vazio = vazio;
		}

		void imprimir();
};

#endif /* REGRAS_REGRAS_H_ */
