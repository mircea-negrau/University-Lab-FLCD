#pragma once

#include <string>
#include <tuple>

#include "../Core/Node.cpp"
#include "../Core/BinarySearchTree.cpp"
#include "../Core/Tuple.cpp"

using std::string;
using std::tuple;

class ProgramInternalForm {
private:
	int index = 9999;
	BinarySearchTree<string, Tuple> tree;

public:
	ProgramInternalForm() {
		this->tree = BinarySearchTree<string, Tuple>();
	}

	void Add(Tuple value) {
		this->tree.Add(std::to_string(++index), value);
	}

	void Delete(string key) {
		this->tree.Delete(key);
	}

	Node<string, Tuple>* FindByKey(string key) {
		return this->tree.FindByKey(key);
	}

	Node<string, Tuple>* FindByValue(Tuple value) {
		return this->tree.FindByValue(value);
	}

	string toString() {
		return tree.toString();
	}
};