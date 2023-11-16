#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_KEY_LENGTH 64

// Definição da estrutura do nó da árvore Patricia
struct PatriciaNode {
    bool isLeaf;                // Indica se este nó é uma folha
    char* key;                  // Chave (somente folhas)
    struct PatriciaNode* left;  // Filho com bit 0
    struct PatriciaNode* right; // Filho com bit 1
};

// Função para criar um novo nó folha
struct PatriciaNode* createLeafNode(char* key) {
    struct PatriciaNode* node = (struct PatriciaNode*)malloc(sizeof(struct PatriciaNode));
    node->isLeaf = true;
    node->key = strdup(key);
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Função para criar um novo nó interno
struct PatriciaNode* createInnerNode(int bit, struct PatriciaNode* left, struct PatriciaNode* right) {
    struct PatriciaNode* node = (struct PatriciaNode*)malloc(sizeof(struct PatriciaNode));
    node->isLeaf = false;
    node->key = NULL;
    node->left = left;
    node->right = right;
    return node;
}

// Função para inserir uma chave na árvore Patricia
struct PatriciaNode* insert(struct PatriciaNode* root, char* key) {
    if (root == NULL) {
        return createLeafNode(key);
    }

    if (root->isLeaf) {
        // Encontrou um nó folha, precisamos dividir
        int i = 0;
        while (key[i] == root->key[i]) {
            i++;
        }

        if (key[i] == '\0') {
            // A chave já existe na árvore
            return root;
        } else {
            // Divide o nó folha
            return createInnerNode(key[i] - '0', createLeafNode(key), root);
        }
    } else {
        // Nó interno, decide para qual filho continuar
        int bit = (key[0] - '0');
        if (bit == 0) {
            root->left = insert(root->left, key);
        } else {
            root->right = insert(root->right, key);
        }
        return root;
    }
}

// Função para encontrar o nó predecessor de um nó interno
struct PatriciaNode* findPredecessor(struct PatriciaNode* node) {
    if (node->isLeaf) {
        return NULL;
    }

    struct PatriciaNode* current = node->left;
    while (!current->isLeaf) {
        current = current->right;
    }
    return current;
}

// Função para remover uma chave da árvore Patricia
struct PatriciaNode* removeKey(struct PatriciaNode* root, char* key) {
    if (root == NULL) {
        return NULL;
    }

    if (root->isLeaf) {
        if (strcmp(root->key, key) == 0) {
            // A chave foi encontrada na folha, remover a folha
            free(root->key);
            free(root);
            return NULL;
        } else {
            // A chave não foi encontrada, retorna o nó sem modificação
            return root;
        }
    } else {
        // Nó interno, decide para qual filho continuar
        int bit = (key[0] - '0');
        if (bit == 0) {
            root->left = removeKey(root->left, key);
        } else {
            root->right = removeKey(root->right, key);
        }

        // Se um dos filhos foi removido, pode ser necessário ajustar a árvore
        if (root->left == NULL) {
            return root->right;
        } else if (root->right == NULL) {
            return root->left;
        } else {
            // Ambos os filhos estão presentes, encontre o predecessor e substitua a chave
            struct PatriciaNode* predecessor = findPredecessor(root);
            free(root->key);
            root->key = strdup(predecessor->key);
            root->left = removeKey(root->left, predecessor->key);
            return root;
        }
    }
}

// Função para buscar uma chave na árvore Patricia
bool search(struct PatriciaNode* root, char* key) {
    if (root == NULL) {
        return false;
    }

    if (root->isLeaf) {
        return (strcmp(root->key, key) == 0);
    } else {
        int bit = (key[0] - '0');
        if (bit == 0) {
            return search(root->left, key);
        } else {
            return search(root->right, key);
        }
    }
}

// Função para liberar a memória da árvore Patricia
void freePatricia(struct PatriciaNode* root) {
    if (root == NULL) {
        return;
    }

    if (root->isLeaf) {
        free(root->key);
    } else {
        freePatricia(root->left);
        freePatricia(root->right);
    }

    free(root);
}

int main() {
    struct PatriciaNode* root = NULL;

    root = insert(root, "apple");
    root = insert(root, "app");
    root = insert(root, "bat");

    // Buscando chaves
    if (search(root, "apple")) {
        printf("Found: apple\n");
    } else {
        printf("Not Found: apple\n");
    }

    if (search(root, "app")) {
        printf("Found: app\n");
    } else {
        printf("Not Found: app\n");
    }

    if (search(root, "bat")) {
        printf("Found: bat\n");
    } else {
        printf("Not Found: bat\n");
    }

    if (search(root, "banana")) {
        printf("Found: banana\n");
    } else {
        printf("Not Found: banana\n");
    }

    // Removendo uma chave
    root = removeKey(root, "app");

    // Buscando a chave removida
    if (search(root, "app")) {
        printf("Found: app\n");
    } else {
        printf("Not Found: app\n");
    }

    // Liberando memória
    freePatricia(root);

    return 0;
}
