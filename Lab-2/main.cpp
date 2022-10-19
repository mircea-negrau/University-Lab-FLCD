#include <string>

template<typename K, typename V>
class Node {
public:
    K Key;
    V Value;
    Node<K, V> *Parent;
    Node<K, V> *Left;
    Node<K, V> *Right;

    Node(K key, V value) {
        this->Key = key;
        this->Value = value;
    }
};

template<typename K, typename V>
class SymbolTable {
public:
    Node<K, V> *Head;

    void Add(K key, V value) {
        if (this->IsEmptyHead()) {
            this->SetHead(key, value);
        } else {
            this->SetElement(key, value);
        }
    }

    Node<K, V> Find(K key) {
        Node<K, V> currentNode = this->Head;
        while (currentNode != nullptr) {
            if (currentNode.Key == key) return currentNode;
            if (currentNode.Key >= key) {
                currentNode = currentNode.Left;
            } else {
                currentNode = currentNode.Right;
            }
        }
        throw std::exception();
    }

    bool Delete(K key) {
        Node<K, V> *node;
        try {
            node = this->Find(key);
        } catch (std::exception &exception) {
            return false;
        }

        if (node->Left == nullptr && node->Right == nullptr) {
            if (node->Parent->Left == node) node->Parent->Left = nullptr;
            else node->Parent->Right = nullptr;
        } else if (node->Left != nullptr && node->Right == nullptr) {
            node->Left->Parent = node->Parent;
            if (node->Parent->Left == node) node->Parent->Left = node->Left;
            else node->Parent->Right = node->Left;
        } else if (node->Left == nullptr && node->Right != nullptr) {
            node->Right->Parent = node->Parent;
            if (node->Parent->Left == node) node->Parent->Left = node->Right;
            else node->Parent->Right = node->Right;
        } else {
            // ToDo: case for node with both children
        }

        free(node);
    }

private:
    bool IsEmptyHead() {
        return this->Head == nullptr;
    }

    void SetHead(K key, V value) {
        this->Head = new Node<K, V>(key, value);
    }

    void SetElement(K key, V value) {
        Node<K, V> *currentElement = this->head;
        while (true) {
            if (currentElement->Key >= key) {
                if (currentElement->Left == nullptr) {
                    auto *newNode = new Node<K, V>(key, value);
                    newNode->Parent = currentElement;
                    currentElement->Left = newNode;
                    break;
                } else {
                    currentElement = currentElement->Left;
                }
            } else {
                if (currentElement->Right == nullptr) {
                    auto *newNode = new Node<K, V>(key, value);
                    newNode->Parent = currentElement;
                    currentElement->Right = newNode;
                    break;
                } else {
                    currentElement = currentElement->Right;
                }
            }
        }
    }
};
