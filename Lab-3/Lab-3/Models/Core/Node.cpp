#pragma once

#include <iostream>
#include <string>

using std::string;

template<class K, class V>
class Node {
public:
	K key;
	V value;
	Node<K, V>* parent;
	Node<K, V>* left;
	Node<K, V>* right;

	Node(K key, V value) {
		this->key = key;
		this->value = value;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}

	Node<K, V>* GetMinimumKey() {
		auto* current = this;
		while (current->left != nullptr) {
			current = current->left;
		}
		return current;
	}

	bool HasBothChildren() {
		return this->left && this->right;
	}

	friend std::ostream& operator<<(std::ostream& out, const Node<K, V>& node) {
		if (node.left != nullptr) out << *node.left;
		out << node.key << ": " << node.value << "\n";
		if (node.right != nullptr) out << *node.right;
		return out;
	}

	Node<K, V>* findByValue(V value) {
		if (this->left != nullptr) {
			Node<K, V>* left = this->left->findByValue(value);
			if (left != nullptr) return left;
		}
		if (this->value == value) return this;
		if (this->right != nullptr) {
			Node<K, V>* right = this->right->findByValue(value);
			if (right != nullptr) return right;
		}
		return nullptr;
	}

	string toString() {
		string text = "";
		if (this->left != nullptr) text += this->left->toString();
		text += std::to_string(std::stoi(this->key) - 10000) + ": " + (string)this->value + "\n";
		if (this->right != nullptr) text += this->right->toString();
		return text;
	}
};
