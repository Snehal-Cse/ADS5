#include <iostream>
#include <cstdint>

using namespace std;

class Node {
public:
    int data;
    Node* xorPointer;

    Node(int data) : data(data), xorPointer(nullptr) {}
};

class XORLinkedList {
private:
    Node* head;
public:
    XORLinkedList() : head(nullptr) {}

    Node* XOR(Node* a, Node* b) {
        return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b));
    }

    void insert(int data) {
        Node* newNode = new Node(data);

        if (head == nullptr) {
            newNode->xorPointer = XOR(nullptr, nullptr);
            head = newNode;
        } else {
            newNode->xorPointer = XOR(nullptr, head);
            head->xorPointer = XOR(newNode, XOR(nullptr, head->xorPointer));
            head = newNode;
        }
    }

    void traverse() {
        Node* current = head;
        Node* prev = nullptr;
        Node* next;

        cout << "XOR Linked List: ";
        while (current != nullptr) {
            cout << current->data << " ";
            next = XOR(prev, current->xorPointer);
            prev = current;
            current = next;
        }
        cout << endl;
    }
};

int main() {
    XORLinkedList list;

    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.insert(40);

    list.traverse();

    return 0;
}
