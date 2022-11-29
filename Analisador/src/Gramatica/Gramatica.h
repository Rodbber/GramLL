/*
 * Gramatica.h
 *
 *  Created on: 17 de nov. de 2022
 *      Author: Rodrigo e Murilo
 */

#ifndef GRAMATICA_GRAMATICA_H_
#define GRAMATICA_GRAMATICA_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

#include "../Linhas/Linha.h"
#include "../Regras/Regras.h"
#include "../First/First.h"
#include "../Follow/Follow.h"

using namespace std;

class Gramatica {
private:
	vector<string> gramatica;
	vector<Linha*> linhas;
	vector<Regra*> regras;
	vector<First*> firsts;
	vector<Follow*> follows;
	vector<string> terminais;
	vector<string> naoTerminais;
public:
	Gramatica();
	virtual ~Gramatica();

	Gramatica(vector<string> gramatica) {
		this->gramatica = gramatica;
		vector<Linha*> linhas;
		vector<Regra*> regrasGram;
		vector<First*> firstsRegras;
		vector<string> terminais;
		vector<string> naoTerminais;

		int regraNumber = 1;
		for (auto i = gramatica.begin(); i != gramatica.end(); ++i) {
			Linha *linha = new Linha(*i);
			if (find(naoTerminais.begin(), naoTerminais.end(),
					linha->getElementoSentencial()) == naoTerminais.end()) {
				naoTerminais.push_back(linha->getElementoSentencial());
			}
			vector<string> regras = linha->getRegras();
			for (auto j = regras.begin(); j != regras.end(); ++j) {
				Regra *regra = new Regra(linha, regraNumber++, *j);
//				First *first = new First(regra);
//				firstsRegras.push_back(first);
				regrasGram.push_back(regra);
				vector<string> terminaisRegra = regra->getTerminais();
				vector<string> naoTerminaisRegra = regra->getNaoTerminais();
				for (auto k = terminaisRegra.begin(); k != terminaisRegra.end();
						++k) {
					string elemento = "";
					elemento += *k;
					if (find(terminais.begin(), terminais.end(), elemento)
							== terminais.end() && elemento != "&") {
						terminais.push_back(elemento);
					}
				}
				for (auto k = naoTerminaisRegra.begin();
						k != naoTerminaisRegra.end(); ++k) {
					string elemento = "";
					elemento += *k;

					if (find(naoTerminais.begin(), naoTerminais.end(), elemento)
							== naoTerminais.end()) {
						naoTerminais.push_back(elemento);
					}
				}

			}
			linhas.push_back(linha);
		}
		Regra *regra0 = new Regra(linhas[0], 0, "$");

		regrasGram.push_back(regra0);
		this->linhas = linhas;
		this->regras = regrasGram;
		//this->firsts = firstsRegras;
		terminais.push_back("$");
		this->terminais = terminais;
		this->naoTerminais = naoTerminais;
		int tamanhoRegras = regrasGram.size();
		vector<Follow*> follows;
		for (auto i = naoTerminais.begin(); i != naoTerminais.end(); ++i) {
			for (auto j = 0; j < tamanhoRegras; j++) {
				Regra *regraAtual = regrasGram[j];
				if (regraAtual->getSentencial() == *i
						&& regraAtual->getNumero() != 0) {
					First *first = new First(regraAtual);
					firstsRegras.push_back(first);
				}
			}
		}
		this->firsts = firstsRegras;
		for (auto i = naoTerminais.begin(); i != naoTerminais.end(); ++i) {

			vector<Regra*> regrasDoNaoTerminal;

			Follow *primeiroFollow = new Follow(regrasGram.back(), *i,
					this->firsts);
			follows.push_back(primeiroFollow);
			for (auto j = regrasGram.begin(); j != regrasGram.end(); ++j) {
				Regra *regra = *j;
				vector<string> naoTerminaisRegra = regra->getNaoTerminais();
				bool buscaNaoTerminais = find(naoTerminaisRegra.begin(),
						naoTerminaisRegra.end(), *i) != naoTerminaisRegra.end();
				if (buscaNaoTerminais) {
					Follow *follow = new Follow(regra, *i, this->firsts);
					string followStr = follow->getFollow();
					string followDe = follow->getFollowDe();
					string firstDoFollow = follow->getFirstDoFollow();
					//follow->imprimir();
					//cout << followStr << endl;
					//					cout << *i << endl;
					//cout << findFirstDoFollow(follow->getFollowDe(), follow->getFirstDoFollow(),follows) << endl;
					if (followStr != followDe) {
						follows.push_back(follow);
					}

				}
			}
		}
		//this->firsts = firstsRegras;
		this->follows = follows;
	}

	const vector<Linha*>& getLinhas() const {
		return linhas;
	}

	void setLinhas(const vector<Linha*> &linhas) {
		this->linhas = linhas;
	}

	const vector<string>& getGramatica() const {
		return gramatica;
	}

	void setGramatica(const vector<string> &gramatica) {
		this->gramatica = gramatica;
	}

	const vector<Regra*>& getRegras() const {
		return regras;
	}

	void setRegras(const vector<Regra*> &regras) {
		this->regras = regras;
	}

	const vector<First*>& getFirsts() const {
		return firsts;
	}

	void setFirsts(vector<First*> &firsts) {
		this->firsts = firsts;
	}

	const vector<Follow*>& getFollows() const {
		return follows;
	}

	void setFollows(const vector<Follow*> &follows) {
		this->follows = follows;
	}

	const vector<string>& getNaoTerminais() const {
		return naoTerminais;
	}

	void setNaoTerminais(const vector<string> &naoTerminais) {
		this->naoTerminais = naoTerminais;
	}

	const vector<string>& getTerminais() const {
		return terminais;
	}

	void setTerminais(const vector<string> &terminais) {
		this->terminais = terminais;
	}

	int findFirstDoFollow(string followDe, string buscado,
			vector<Follow*> follows);

	vector<string> firstRecursivo(First *first, vector<First*> firsts);

	void startaFirstRecursivo();

	vector<string> followRecursivo(Follow *follow, vector<Follow*> follows,
			vector<First*> firsts);

	void startaFollowRecursivo();

	First *getFirstBySentencial(string sentencial);

	Regra *regraComPrimeiraCondicao(string sentencial, string s);

	Regra *getRegraByNumber(int numero);

	void imprimirGramatica();

	void imprimirLinhas();

	void imprimirRegras();

	void imprimirFirsts();

	void imprimirFirstsTerminais();

	void imprimirFollows();

	void imprimirFollowsTerminais();

	void imprimirTerminais();

	void imprimirNaoTerminais();

	void imprimir();
};

#endif /* GRAMATICA_GRAMATICA_H_ */
