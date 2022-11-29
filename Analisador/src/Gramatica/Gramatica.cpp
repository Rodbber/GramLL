/*
 * Gramatica.cpp
 *
 *  Created on: 17 de nov. de 2022
 *      Author: Rodrigo e Murilo
 */

#include "Gramatica.h"

Gramatica::Gramatica() {
	// TODO Auto-generated constructor stub

}

Gramatica::~Gramatica() {
	// TODO Auto-generated destructor stub
}

int Gramatica::findFirstDoFollow(string followDe, string buscado,
		vector<Follow*> follows) {
	for (auto i = follows.begin(); i != follows.end(); ++i) {
		Follow *follow = *i;
		if (follow->getRegra()->getNumero() == 0) {
			continue;
		}
		string firstDoFollow = follow->getFirstDoFollow();
		string followDeFollowAtual = follow->getFollowDe();
		//cout << "follow de: " << followDe << " " << followDeFollowAtual << endl;
		//cout << "first do follow: " << firstDoFollow << " " << buscado << endl;
		if (followDe == followDeFollowAtual && firstDoFollow == buscado) {
			return 1;
		}
	}
	return -1;
}

vector<string> Gramatica::firstRecursivo(First *first, vector<First*> firsts) {
	vector<string> elementosFirstAtual;

	vector<string> firstsFirstVerificado;
	for (auto i = firsts.begin(); i != firsts.end(); ++i) {
		First *firstVerificado = *i;
		string naoTerminalFirst = first->getFirst();
		string sentencialFirstEncontrado = firstVerificado->getSentencial();

		if (sentencialFirstEncontrado == naoTerminalFirst) {

			int tipo = firstVerificado->getTipo();
			string firstFinal = firstVerificado->getFirstFinal();

			vector<string> firstEncontrado = this->firstRecursivo(
					firstVerificado, firsts);
			elementosFirstAtual = firstVerificado->getFirstTerminais();

			for (auto it = firstEncontrado.begin(); it != firstEncontrado.end();
					++it) {
				elementosFirstAtual.push_back(*it);

			}
			first->addFirstTerminais(elementosFirstAtual);
		}
	}

	//first->setFirstFinal(firstEncontrado);
	return elementosFirstAtual;
}

void Gramatica::startaFirstRecursivo() {
	vector<First*> firsts = this->getFirsts();
	for (auto i = firsts.begin(); i != firsts.end(); ++i) {
		First *first = *i;
		int tipo = first->getTipo();
		string firstFinal = first->getFirstFinal();
		if (tipo == 0 && firstFinal.empty()) {
			this->firstRecursivo(first, firsts);
		}
	}
}

vector<string> Gramatica::followRecursivo(Follow *follow,
		vector<Follow*> follows, vector<First*> firsts) {
	vector<string> elementoTerminal;
	string firstDoFollowDoVerificado = follow->getFirstDoFollow();

	vector<string> followsEncontrados = follow->getNaoTerminaisFollow();
	for (auto j = followsEncontrados.begin(); j != followsEncontrados.end();
			++j) {
		for (auto i = follows.begin(); i != follows.end(); ++i) {
			Follow *followVerificado = *i;
			string followDoVerificado = followVerificado->getFollow();
			elementoTerminal = followVerificado->getTerminaisFollow();

			string followDe = followVerificado->getFollowDe();
			if (followDe == *j) {
				vector<string> followsEncontrados = this->followRecursivo(
						followVerificado, follows, firsts);

				for (auto it = followsEncontrados.begin();
						it != followsEncontrados.end(); ++it) {

					elementoTerminal.push_back(*it);
				}
				follow->addTerminaisFollow(elementoTerminal);
			}

		}
	}

	return elementoTerminal;
}

void Gramatica::startaFollowRecursivo() {
	vector<Follow*> follows = this->getFollows();
	vector<First*> firsts = this->getFirsts();
	for (auto i = follows.begin(); i != follows.end(); ++i) {
		Follow *follow = *i;
		string firstDoFollowDoVerificado = follow->getFirstDoFollow();
		//if (!firstDoFollowDoVerificado.empty()) {
		vector<First*> firstsDoFollow;
		for (auto j = firsts.begin(); j != firsts.end(); ++j) {
			First *first = *j;
			string sentencialFirst = first->getSentencial();
			string firstTerminal = first->getFirstFinal();

//			if (sentencialFirst == firstDoFollowDoVerificado) {
//				firstsDoFollow.push_back(first);
//			}

			if (first->isDerivaEmVazio()
					&& sentencialFirst == follow->getFollowDe()) {
				follow->setDerivaEmVazio(first->getRegra()->getNumero());
			}

		}
		//follow->setFirsts(firstsDoFollow);
		//}

		Regra *regra = follow->getRegra();
		bool tipo = follow->getTipo() == 0;
		string followVerificadoTerminal = follow->getFollowTerminal();
		if (tipo && regra->getNumero() != 0) {
			this->followRecursivo(follow, follows, firsts);
		}
	}
}

Regra* Gramatica::getRegraByNumber(int numero) {
	vector<Regra*> regras = this->getRegras();
	auto it = find_if(regras.begin(), regras.end(),
			[numero](const Regra *obj) {
				return obj->getNumero() == numero;
			});
	if (it != regras.end()) {
		return *it;
	}
	return nullptr;
}

First* Gramatica::getFirstBySentencial(string sentencial) {
	vector<First*> firsts = this->getFirsts();
	auto it = find_if(firsts.begin(), firsts.end(),
			[sentencial](const First *obj) {
				return obj->getSentencial() == sentencial;
			});
	if (it != firsts.end()) {
		return *it;
	}
	return nullptr;
}

void Gramatica::imprimirGramatica() {
	vector<string> gramatica = this->getGramatica();
	cout << "Gramatica: " << endl;
	for (auto i = gramatica.begin(); i != gramatica.end(); ++i) {
		cout << *i << endl;
	}
	cout << endl;
}

void Gramatica::imprimirLinhas() {
	vector<Linha*> linhas = this->getLinhas();
	cout << "Linhas: " << endl;
	for (auto i = linhas.begin(); i != linhas.end(); ++i) {
		Linha *linha = *i;
		linha->imprimir();
	}
	cout << endl;
}

void Gramatica::imprimirRegras() {
	vector<Regra*> regras = this->getRegras();
	cout << "Regras: " << endl;
	for (auto i = regras.begin(); i != regras.end(); ++i) {
		Regra *regras = *i;
		regras->imprimir();
	}
	cout << endl;
}

void Gramatica::imprimirFirsts() {
	vector<First*> firsts = this->getFirsts();
	cout << "Firsts: " << endl;
	for (auto i = firsts.begin(); i != firsts.end(); ++i) {
		First *first = *i;
		first->imprimir();
	}
	cout << endl;
}

void Gramatica::imprimirFirstsTerminais() {
	vector<First*> firsts = this->getFirsts();
	map<string, vector<string>> separando;

	typedef map<string, vector<string>> MapType;

	for (auto it = firsts.begin(); it != firsts.end(); ++it) {
		First *first = *it;
		MapType::iterator lb = separando.lower_bound(first->getSentencial());
		if (lb != separando.end()
				&& !(separando.key_comp()(first->getSentencial(), lb->first))) {
			for (auto i = first->getFirstTerminais().begin();
					i != first->getFirstTerminais().end(); ++i) {
				//cout << *i << endl;
				if (find(lb->second.begin(), lb->second.end(), *i)
						== lb->second.end()) {
					lb->second.push_back(*i);
				}
			}

		} else {
			// the key does not exist in the map
			// add it to the map
			vector<string> firstsStr;
			for (auto i = first->getFirstTerminais().begin();
					i != first->getFirstTerminais().end(); ++i) {
				if (find(firstsStr.begin(), firstsStr.end(), *i)
						== firstsStr.end()) {
					firstsStr.push_back(*i);
				}
			}
			separando.insert(lb,
					MapType::value_type(first->getSentencial(), firstsStr)); // Use lb as a hint to insert,										 // so it can avoid another lookup
		}
	}

	cout << "Firsts: " << endl;
	for (auto i = separando.begin(); i != separando.end(); ++i) {
		cout << i->first << " -> ";
		for (auto j = i->second.begin(); j != i->second.end(); ++j) {
			if (j == i->second.begin()) {
				cout << "{ ";
			}
			cout << *j;
			if (next(j) != i->second.end()) {
				cout << ", ";
			}
			if (next(j) == i->second.end()) {
				cout << " }";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void Gramatica::imprimirFollowsTerminais() {
	vector<Follow*> follows = this->getFollows();
	map<string, vector<string>> separando;

	typedef map<string, vector<string>> MapType;

	for (auto it = follows.begin(); it != follows.end(); ++it) {
		Follow *follow = *it;
		MapType::iterator lb = separando.lower_bound(follow->getFollowDe());
		if (lb != separando.end()
				&& !(separando.key_comp()(follow->getFollowDe(), lb->first))) {
			for (auto i = follow->getTerminaisFollow().begin();
					i != follow->getTerminaisFollow().end(); ++i) {
				//cout << *i << endl;
				if (find(lb->second.begin(), lb->second.end(), *i)
						== lb->second.end()) {
					lb->second.push_back(*i);
				}
			}

		} else {
			// the key does not exist in the map
			// add it to the map
			vector<string> firstsStr;
			for (auto i = follow->getTerminaisFollow().begin();
					i != follow->getTerminaisFollow().end(); ++i) {
				if (find(firstsStr.begin(), firstsStr.end(), *i)
						== firstsStr.end()) {
					firstsStr.push_back(*i);
				}
			}
			separando.insert(lb,
					MapType::value_type(follow->getFollowDe(), firstsStr)); // Use lb as a hint to insert,										 // so it can avoid another lookup
		}
	}

	cout << "Follows: " << endl;
	for (auto i = separando.begin(); i != separando.end(); ++i) {
		cout << i->first << " -> ";
		for (auto j = i->second.begin(); j != i->second.end(); ++j) {
			if (j == i->second.begin()) {
				cout << "{ ";
			}
			cout << *j;
			if (next(j) != i->second.end()) {
				cout << ", ";
			}
			if (next(j) == i->second.end()) {
				cout << " }";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void Gramatica::imprimirFollows() {
	vector<Follow*> follows = this->getFollows();
	cout << "Follows: " << endl;
	for (auto i = follows.begin(); i != follows.end(); ++i) {
		Follow *follow = *i;
		follow->imprimir();
	}
	cout << endl;
}

void Gramatica::imprimirTerminais() {
	vector<string> terminais = this->getTerminais();
	cout << "Terminais: ";
	for (auto i = terminais.begin(); i != terminais.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
}

void Gramatica::imprimirNaoTerminais() {
	vector<string> naoTerminais = this->getNaoTerminais();
	cout << "Nao terminais: ";
	for (auto i = naoTerminais.begin(); i != naoTerminais.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
}

void Gramatica::imprimir() {
	this->imprimirLinhas();
	this->imprimirRegras();
	this->imprimirTerminais();
	this->imprimirNaoTerminais();
	this->imprimirFirsts();
	this->imprimirFollows();
}
