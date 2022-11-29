/*
 * Teste.h
 *
 *  Created on: 19 de nov. de 2022
 *      Author: Rodrigo e Murilo
 */

#ifndef TESTEGRAMATICA_TESTE_H_
#define TESTEGRAMATICA_TESTE_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <stack>
#include <cstring>

#include "../Gramatica/Gramatica.h"
#include "../TabelaPreditiva/Tabela.h"
#include "../Regras/Regras.h"

class Teste {
	Gramatica *gramatica;
	Tabela *tabelaPreditiva;
	string entrada;
public:
	Teste();
	virtual ~Teste();

	Teste(Gramatica *gramatica, Tabela *tabela, string entrada) {
		this->gramatica = gramatica;
		this->tabelaPreditiva = tabela;
		//entrada += "$";
		this->entrada = entrada;
	}

	Gramatica* getGramatica() {
		return gramatica;
	}

	void setGramatica(Gramatica *gramatica) {
		this->gramatica = gramatica;
	}

	Tabela*& getTabelaPreditiva() {
		return tabelaPreditiva;
	}

	void setTabelaPreditiva(Tabela *tabelaPreditiva) {
		this->tabelaPreditiva = tabelaPreditiva;
	}

	const string& getEntrada() const {
		return entrada;
	}

	void setEntrada(const string &entrada) {
		this->entrada = entrada;
	}

	void verificaEntrada() {
		string entrada = this->getEntrada();
		entrada += "$";
		Gramatica *gramatica = this->getGramatica();
		vector<string> naoTerminais = gramatica->getNaoTerminais();
		vector<Regra*> regrasDaGramatica = gramatica->getRegras();
		vector<First*> firsts = gramatica->getFirsts();
		vector<Follow*> follows = gramatica->getFollows();
		Tabela *table = this->getTabelaPreditiva();
		string sentencialGramatica = regrasDaGramatica.front()->getSentencial();
		bool aceita = false;
		string finalStack;

		vector<string> guardaEntrada;
		vector<string> grardaAcao;
		vector<string> guardaPilha;
		string desempilha = "$" + sentencialGramatica;
		stack<string> stackTeste;
		cout << "  Pilha  " << "  Entrada  " << "  Acao  " << endl;
		while (!aceita) {
			cout << desempilha << "         " << entrada << "           ";
			string topo = string(1, desempilha.back());
			desempilha.pop_back();
			//cout << desempilha << " " << topo << " " << entrada << endl;
			if (find(naoTerminais.begin(), naoTerminais.end(), topo)
					!= naoTerminais.end()) {
				vector<int> combinacao = table->indiceCombinacao(topo,
						string(1, entrada.front()));
				if (combinacao[0] == -1 && combinacao[1] == -1) {
					vector<int> combinacao2 = table->indiceCombinacao(topo,
							"$");
					if (combinacao2[0] == -1 && combinacao2[1] == -1) {
						cout << "Err." << endl;
						break;
					} else {
						cout << "Err." << endl;
						continue;
					}
				}

				int x = combinacao[0];
				int y = combinacao[1];
				int numeroRegra = table->getTabela()[x][y];
				cout << numeroRegra << ". " << topo << " -> ";
				if (numeroRegra == 0) {

					vector<int> combinacao2 = table->indiceCombinacao(topo,
							"$");
					if (combinacao2[0] == -1 && combinacao2[1] == -1) {
						cout << "Err." << endl;
						break;
					} else {
						//desempilha += "$";
						cout << endl;
						continue;
					}
				}

				Regra *regraEncontrada = gramatica->getRegraByNumber(
						numeroRegra);

				if (regraEncontrada == nullptr) {
					break;
				}

				string regraStr = regraEncontrada->getRegra();
				cout << regraStr << endl;
				for (auto it = regraStr.begin(); it != regraStr.end(); ++it) {
					stackTeste.push(string(1, *it));
				}

				stack<string> stack2 = stackTeste;
				while (!stackTeste.empty()) {
					desempilha += stackTeste.top();
					stackTeste.pop();
				}
			} else {
				string topoDaEntrada = string(1, entrada.front());
				if (topo == "&") {
					cout << "Vazio" << endl;
					continue;
				}
				if (topo == string(1, entrada.front())) {
					if (entrada.length() == 1 && desempilha.length() == 0
							&& topo == "$" && topoDaEntrada == "$") {
						cout << "Ac." << endl;

					} else {
						cout << "Rec('" << topo << "')" << endl;
					}

					entrada.erase(0, 1);
				} else {
					cout << "Err." << endl;
					break;
				}

			}

			if (desempilha.empty() && entrada.empty()) {
				aceita = true;
			}
		}

		string entradaAceita = aceita ? "Aceita." : "Não aceita.";
		cout << "Palavra: " << this->getEntrada() << endl;
		cout << entradaAceita << endl;
	}
};

#endif /* TESTEGRAMATICA_TESTE_H_ */
