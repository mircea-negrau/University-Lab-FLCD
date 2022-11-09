#pragma once

#include <iostream>
#include <string>

using std::string;

#include "Node.cpp"

template<class K, class V>
class BinarySearchTree {
public:
	Node<K, V>* head;

	BinarySearchTree() = default;

	void Add(K key, V value) {
		if (this->IsEmpty())
			return this->AddHead(key, value);
		this->AddElement(key, value);
	}

	Node<K, V>* FindByValue(V value) {
		if (this->head != nullptr) {
			return this->head->findByValue(value);
		}
		return nullptr;
	}

	Node<K, V>* FindByKey(K key) {
		Node<K, V>* currentNode = this->head;

		while (currentNode != nullptr) {
			if (currentNode->key == key) return currentNode;
			if (currentNode->key >= key) currentNode = currentNode->left;
			else currentNode = currentNode->right;
		}

		return nullptr;
	}

	bool Delete(K key, Node<K, V>* node = nullptr) {
		Node<K, V>* currentNode;
		currentNode = node == nullptr ? FindByKey(key) : node;
		if (currentNode == nullptr) return false;

		if (currentNode->HasBothChildren()) DeleteNodeWithBothChildren(currentNode);
		else if (currentNode->left) DeleteNodeWithLeftChild(currentNode);
		else if (currentNode->right) DeleteNodeWithRightChild(currentNode);
		else DeleteLeafNode(currentNode);

		return true;
	}

	string toString() {
		if (this->head != nullptr) {
			string headString = this->head->toString();
			headString.append(" ");
			return headString;
		}
		return "";
	}

	friend std::ostream& operator<<(std::ostream& out, const BinarySearchTree<K, V>& symbolTable) {
		if (symbolTable.head != nullptr) out << *symbolTable.head << " ";
		return out;
	}

private:
	bool IsEmpty() {
		return this->head == nullptr;
	}

	bool IsHead(Node<K, V>* element) {
		return this->head == element;
	}

	void AddHead(K key, V value) {
		this->head = new Node<K, V>(key, value);
	}

	Node<K, V>* FindElementParent(K key) {
		Node<K, V>* previousElement = nullptr;
		Node<K, V>* currentElement = this->head;
		while (currentElement != nullptr) {
			previousElement = currentElement;
			if (currentElement->key >= key) currentElement = currentElement->left;
			else currentElement = currentElement->right;
		}
		return previousElement;
	}

	void AddElement(K key, V value) {
		Node<K, V>* parent = FindElementParent(key);
		auto* newNode = new Node<K, V>(key, value);
		if (parent->key >= key) {
			parent->left = newNode;
			newNode->parent = parent;
		}
		else {
			parent->right = newNode;
			newNode->parent = parent;
		}
	}

	void DeleteNodeWithBothChildren(Node<K, V>* currentNode) {
		Node<K, V>* successor = currentNode->right->GetMinimumKey();
		currentNode->key = successor->key;
		currentNode->value = successor->value;
		Delete(successor->key, successor);
	}

	void DeleteNodeWithRightChild(Node<K, V>* currentNode) {
		currentNode->right->parent = currentNode->parent;
		if (currentNode->parent) {
			if (currentNode == currentNode->parent->left) currentNode->parent->left = currentNode->right;
			else currentNode->parent->right = currentNode->right;
		}
		if (IsHead(currentNode)) {
			this->head = currentNode->right;
			currentNode->right->parent = nullptr;
		}
		delete currentNode;
	}

	void DeleteNodeWithLeftChild(Node<K, V>* currentNode) {
		currentNode->left->parent = currentNode->parent;
		if (currentNode->parent) {
			if (currentNode == currentNode->parent->left) currentNode->parent->left = currentNode->left;
			else currentNode->parent->right = currentNode->left;
		}
		if (IsHead(currentNode)) {
			this->head = currentNode->left;
			currentNode->left->parent = nullptr;
		}
		delete currentNode;
	}

	void DeleteLeafNode(Node<K, V>* currentNode) {
		if (currentNode->parent) {
			if (currentNode == currentNode->parent->left) currentNode->parent->left = nullptr;
			else currentNode->parent->right = nullptr;
		}
		if (IsHead(currentNode)) this->head = nullptr;
		delete currentNode;
	}
};