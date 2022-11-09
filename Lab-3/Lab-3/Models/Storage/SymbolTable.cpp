#pragma once

#include "../Core/BinarySearchTree.cpp"
#include <string>

using std::string;

class SymbolTable {
private:
	int index = 9999;
	BinarySearchTree<string, string> tree;

public:
	SymbolTable() {
		this->tree = BinarySearchTree<string, string>();
	}

	void Add(string value) {
		if (FindByValue(value) != nullptr) return;
		this->tree.Add(std::to_string(++index), value);
	}

	void Delete(string key) {
		this->tree.Delete(key);
	}

	Node<string, string>* FindByKey(string key) {
		return this->tree.FindByKey(key);
	}

	Node<string, string>* FindByValue(string value) {
		return this->tree.FindByValue(value);
	}

	string toString() {
		return tree.toString();
	}
};