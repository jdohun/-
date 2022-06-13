// huffman.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
#include <iostream>

using namespace std;

typedef struct nodetype nodetype;

struct nodetype {
    char symbol;
    int freq;
    unsigned int codeWord;
    unsigned int codeLength;
    nodetype* left;
    nodetype* right;
};

typedef struct {
    int number;
    int size;
    nodetype** node;
} PQ;

void swap(nodetype* &a, nodetype* &b)
{
    nodetype* temp = a;
    a = b;
    b = temp;
}

PQ* createPQ(int size)
{
    PQ* pq = new PQ;
    pq->node = new nodetype * [size];
    pq->size = size;
    pq->number = 0;

    return pq;
}

void heapify(PQ* pq, int index)
{
    int left = (index + 1) * 2 - 1;
    int right = (index + 1) * 2;
    int min = index;
    nodetype** node = pq->node;
    if (left >= pq->number)
        return;
    if (node[left]->freq < node[index]->freq)
        min = left;
    if (right < pq->number && node[right]->freq < node[min]->freq)
        min = right;
    if (min != index) {
        swap(node[min], node[index]);
        heapify(pq, min);
    }
}

void insertPQ(PQ* pq, nodetype *node)
{
    if (pq->number < pq->size) {
            int index = pq->number++;
            nodetype** nodes = pq->node;
            nodes[index] = node;
            while (index > 0) {
                int parent = ((index + 1) / 2) - 1;
                if (nodes[parent]->freq > nodes[index]->freq) {
                    swap(nodes[parent], nodes[index]);
                    index = parent;
                } else
                    break;
            }
    }
}

nodetype *removePQ(PQ* pq)
{
    if (pq->number == 0) {
        return NULL;
    }
    nodetype * node = pq->node[0];
    pq->node[0] = pq->node[pq->number - 1];
    pq->number--;
    heapify(pq, 0);
    return node;
}

nodetype* allocNode(int symbol, int freq)
{
    nodetype* node = new nodetype;
    node->symbol = symbol;
    node->freq = freq;
    node->codeWord = 0;
    node->codeLength = 0;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void showPQ(PQ* pq)
{
    for (int i = 0; i < pq->number; i++) {
        cout << pq->node[i]->symbol << ' ' << pq->node[i]->freq << endl;
    }
    cout << endl;
}

nodetype *huffman(PQ* pq)
{
    nodetype* r;
    int n = pq->number;
    for (int i = 0; i < n-1; i++) {
        nodetype* p = removePQ(pq);
        nodetype* q = removePQ(pq);
        r = allocNode(0, p->freq + q->freq);
        r->left = p;
        r->right = q;
        insertPQ(pq, r);
    }
    r = removePQ(pq);
    return r;
}

void showCode(unsigned int codeWord, int codeLength)
{
    unsigned int msb = 1 << (codeLength - 1);
    for (int i = 0; i < codeLength; i++, msb >>= 1) {
        if (msb & codeWord)
            cout << '1';
        else
            cout << '0';
    }
}

void showTree(nodetype* node)
{
    if (node == NULL)
        return;
    if (node->symbol != 0) {
        cout << (char)node->symbol << ':' << node->freq << ':';
        showCode(node->codeWord, node->codeLength);
        cout << endl;
    } else
        cout << node->freq << endl;
    showTree(node->left);
    showTree(node->right);
}


void codeTree(nodetype* node, unsigned int codeWord, int codeLength)
{
    if (node == NULL)
        return;
    if (node->symbol != 0) {
        node->codeWord = codeWord;
        node->codeLength = codeLength;
    }
    else {
        codeTree(node->left, (codeWord << 1), codeLength + 1);
        codeTree(node->right, (codeWord << 1) | 1, codeLength + 1);
    }
}


int main()
{
    std::cout << "Hello World!\n";
    PQ* pq;
    pq = createPQ(16);
    nodetype* node;
    char alpha[6] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[6] = { 16, 5, 12, 17, 10, 25 };


    for (int i = 0; i < 6; i++) {
        node = allocNode(alpha[i], freq[i]);
        insertPQ(pq, node);
        showPQ(pq);
    }

    //showPQ(pq);

    node = huffman(pq);
    codeTree(node, 0, 0);
    showTree(node);
}
