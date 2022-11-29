/*
 * Follow.h
 *
 *  Created on: 17 de nov. de 2022
 *      Author: Rodrigo e Murilo
 */

#ifndef FOLLOW_FOLLOW_H_
#define FOLLOW_FOLLOW_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

#include "../Regras/Regras.h"
#include "../First/First.h"

using namespace std;

class Follow {
private:
	string sentencial;
	Regra *regra;
	string followDe;
	string follow;
	Follow *followObj;
	string firstDoFollow;
	vector<string> terminaisFollow;
	vector<string> naoTerminaisFollow;
	vector<string> firstsDosFollows;
	vector<First*> firsts;
	string followTerminal;
	int derivaEmVazio;
	// 0 nao terminal, 1 terminal
	int tipo;
public:
	Follow();
	virtual ~Follow();
	Follow(Regra *regra, string followDe, vector<First*> firsts) {
		this->derivaEmVazio = -1;
		this->regra = regra;
		this->followDe = followDe;
		string sentencialRegra = regra->getSentencial();
		this->sentencial = sentencialRegra;
		this->followObj = nullptr;
		string follow = followDe;
		vector<string> firstsDosFollows;
		vector<First*> firstsDoFollow;
		string regraGramatica = regra->getRegra();
		vector<string> naoTerminaisRegra = regra->getNaoTerminais();
		if (regraGramatica == "$") {
			this->addTerminaisFollow({regraGramatica});
			return;
		}
		string::iterator it;
		for (it = regraGramatica.begin(); it != regraGramatica.end(); ++it) {
			string elementoFollow = "";
			string verificadoAtual = "";
			verificadoAtual += *it;
			bool derivaEmVazio = false;
			//cout << follow << endl;
			if (follow == verificadoAtual) {
				bool isLast = next(it) == regraGramatica.end();
				if (isLast) {
					//cout << sentencialRegra << " " << follow << endl;
					this->follow = sentencialRegra;
					this->addNaoTerminaisFollow( { sentencialRegra });
					this->tipo = 0;
				} else {
					elementoFollow = *next(it);
					//cout << elementoFollow << endl;
					if (find(naoTerminaisRegra.begin(), naoTerminaisRegra.end(),
							elementoFollow) != naoTerminaisRegra.end()) {
						for (auto i = firsts.begin(); i != firsts.end(); ++i) {
							First *first = *i;
							if (first->getSentencial() == elementoFollow) {
								//cout << "caiu aqui" << endl;
								//this->addNaoTerminaisFollow( { sentencialRegra });
								vector<string> firstTerminais =
										first->getFirstTerminais();
								this->addTerminaisFollow(firstTerminais);
//								for(auto j = firstTerminais.begin(); j != firstTerminais.end(); ++j){
//
//								}
								firstsDoFollow.push_back(first);
								if (first->isDerivaEmVazio()) {
									derivaEmVazio = true;
								}
							}
						}
						this->addNaoTerminaisFollow( { elementoFollow });
					} else {
						this->addTerminaisFollow( { elementoFollow });
					}
				}
				if (!derivaEmVazio) {
					break;
				}
				follow = *next(it);
			}
		}
		//cout << firstsDoFollow.size() << endl;
		this->firsts = firstsDoFollow;
		//cout << this->firsts.size() << endl;
	}

	const string& getFollowDe() const {
		return followDe;
	}

	void setFollowDe(const string &followDe) {
		this->followDe = followDe;
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

	string getFollow() {
		return follow;
	}

	void setFollow(const string &follow) {
		this->follow = follow;
	}

	const string& getFirstDoFollow() const {
		return firstDoFollow;
	}

	void setFirstDoFollow(const string &firstDoFollow) {
		this->firstDoFollow = firstDoFollow;
	}

	const string& getFollowTerminal() const {
		return followTerminal;
	}

	void setFollowTerminal(const string &followTerminal) {
		this->followTerminal = followTerminal;
	}

	vector<First*> getFirsts() {
		return firsts;
	}

	void setFirsts(vector<First*> firsts) {
		this->firsts = firsts;
	}

	const vector<string>& getFirstsDosFollows() const {
		return firstsDosFollows;
	}

	void setFirstsDosFollows(const vector<string> &firstsDosFollows) {
		this->firstsDosFollows = firstsDosFollows;
	}

	Follow* getFollowObj() {
		return followObj;
	}

	int getDerivaEmVazio() const {
		return derivaEmVazio;
	}

	void setDerivaEmVazio(int derivaEmVazio) {
		this->derivaEmVazio = derivaEmVazio;
	}

	const vector<string>& getTerminaisFollow() const {
		return terminaisFollow;
	}

	void setTerminaisFollow(const vector<string> &terminaisFollow) {
		this->terminaisFollow = terminaisFollow;
	}

	void addTerminaisFollow(vector<string> terminaisFollow) {
		for (auto it = terminaisFollow.begin(); it != terminaisFollow.end();
				++it) {
			if (*it == "&") {
				continue;
			}
			vector<string> followTerminais = this->getTerminaisFollow();
			if (find(followTerminais.begin(), followTerminais.end(), *it)
					== followTerminais.end()) {
				this->terminaisFollow.push_back(*it);
			}
		}

	}

	const vector<string>& getNaoTerminaisFollow() const {
		return naoTerminaisFollow;
	}

	void setNaoTerminaisFollow(const vector<string> &naoTerminaisFollow) {
		this->naoTerminaisFollow = naoTerminaisFollow;
	}

	void addNaoTerminaisFollow(vector<string> naoTerminaisFollow) {
		for (auto it = naoTerminaisFollow.begin();
				it != naoTerminaisFollow.end(); ++it) {

			vector<string> followNaoTerminais = this->getNaoTerminaisFollow();
			if (find(followNaoTerminais.begin(), followNaoTerminais.end(), *it)
					== followNaoTerminais.end()) {
				this->naoTerminaisFollow.push_back(*it);
			}
		}
	}

	bool findFirstInFollow(string elementoSentencial, string firstFinal) {
		vector<First*> firsts = this->getFirsts();
		for (auto it = firsts.begin(); it != firsts.end(); ++it) {
			First *first = *it;
			if (first->getSentencial() == elementoSentencial
					&& firstFinal == first->getFirstFinal()) {
				return true;
			}
		}
		return false;
	}

	int retornaAregraDaDerivaEmVazio() {
		vector<First*> firsts = this->getFirsts();
		for (auto it = firsts.begin(); it != firsts.end(); ++it) {
			First *first = *it;
			if (first->isDerivaEmVazio()) {
				return first->getRegra()->getNumero();
			}
		}
		return -1;
	}

	void setFollowObj(Follow *followObj) {
		this->followObj = followObj;
		vector<First*> firstsDoFollow = followObj->getFirsts();
		vector<First*> firsts = this->getFirsts();
		for (auto it = firstsDoFollow.begin(); it != firstsDoFollow.end();
				++it) {
			First *first = *it;
			bool existe = findFirstInFollow(first->getSentencial(),
					first->getFirstFinal());
			if (!existe) {
				firsts.push_back(first);
			}

			if (first->isDerivaEmVazio()) {
				this->derivaEmVazio = first->getRegra()->getNumero();
			}
		}
	}

	void imprimir();
};

#endif /* FOLLOW_FOLLOW_H_ */
