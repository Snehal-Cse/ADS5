#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

const int MAX_LEVEL = 6;

class Node {
public:
    int key;
    Node** forward;
    Node(int, int);
    ~Node();
};

Node::Node(int key, int level) {
    this->key = key;
    forward = new Node*[level+1];
    memset(forward, 0, sizeof(Node*)*(level+1));
}

Node::~Node() {
    delete[] forward;
}

class SkipList {
    int level;
    Node* header;
public:
    SkipList();
    ~SkipList();
    int randomLevel();
    Node* createNode(int, int);
    void insertElement(int);
    void deleteElement(int);
    void searchElement(int);
    void displayList();
};

SkipList::SkipList() {
    level = 0;
    header = new Node(INT_MIN, MAX_LEVEL);
}

SkipList::~SkipList() {
    delete header;
}

int SkipList::randomLevel() {
    int lvl = 0;
    while (rand() < RAND_MAX / 2 && lvl < MAX_LEVEL) {
        lvl++;
    }
    return lvl;
}

Node* SkipList::createNode(int key, int level) {
    Node* newNode = new Node(key, level);
    return newNode;
}

void SkipList::insertElement(int key) {
    Node* current = header;
    Node* update[MAX_LEVEL+1];
    memset(update, 0, sizeof(Node*)*(MAX_LEVEL+1));

    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current == NULL || current->key != key) {
        int rlevel = randomLevel();

        if (rlevel > level) {
            for (int i = level+1; i < rlevel+1; i++) {
                update[i] = header;
            }
            level = rlevel;
        }

        Node* newNode = createNode(key, rlevel);

        for (int i = 0; i <= rlevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

void SkipList::deleteElement(int key) {
    Node* current = header;
    Node* update[MAX_LEVEL+1];
    memset(update, 0, sizeof(Node*)*(MAX_LEVEL+1));

    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current != NULL && current->key == key) {
        for (int i = 0; i <= level; i++) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }

        delete current;

        while (level > 0 && header->forward[level] == NULL) {
            level--;
        }
    }
}

void SkipList::searchElement(int key) {
    Node* current = header;

    for (int i = level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];

    if (current != NULL && current->key == key) {
        cout << "Element " << key << " is in the list." << endl;
    } else {
        cout << "Element " << key << " is not in the list." << endl;
    }
}

void SkipList::displayList() {
    cout << "Skip List" << endl;
    for (int i = 0; i <= level; i++) {
        Node* node = header->forward[i];
        cout << "Level " << i << ": ";
        while (node != NULL) {
            cout << node->key << " ";
            node = node->forward[i];
        }
        cout << endl;
    }
}

int main() {
    SkipList skipList;
    int choice, element;
    while (1) {
        cout << "1. Insert Element" << endl;
        cout << "2. Delete Element" << endl;
        cout << "3. Search Element" << endl;
        cout << "4. Display List" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter element to insert: ";
                cin >> element;
                skipList.insertElement(element);
                break;
            case 2:
                cout << "Enter element to delete: ";
                cin >> element;
                skipList.deleteElement(element);
                break;
            case 3:
                cout << "Enter element to search: ";
                cin >> element;
                skipList.searchElement(element);
                break;
            case 4:
                skipList.displayList();
                break;
            case 5:
                exit(0);
            default:
                cout << "Invalid choice" << endl;
        }
    }
    return 0;
}
