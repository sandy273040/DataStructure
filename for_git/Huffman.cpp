#include<iostream>
using namespace std;

struct node{
    char c;
    int freq;
    bool leaf;
    node* left, *right;
};
struct codeNode{
    char cha;//node's c
    char* code;//size == height
    int len;
};

class MinHeap{
    private:
        node* heap;
        node* hoffRoot;//hoffman tree's root
        int heapSize;
        int leafNum;
        int capacity;
        codeNode* codeTable;//
        int codeTop;
        char* table;
        int tableTop;
        char* indexTable;
        int rear;
    public:
        MinHeap(int* a){//bottom up build heap
            //initialization
            capacity = 27;
            heapSize = 0;
            heap = new node[capacity];
            //push back to heap
            for(int i = 1; i < capacity; i++){//1-26(total 27)
                if(a[i] > 0){
                    heapSize++;
                    (heap[heapSize]).c = i + 96;
                    (heap[heapSize]).freq = a[i];
                    (heap[heapSize]).leaf = 1;
                    (heap[heapSize]).left = nullptr; (heap[heapSize]).right = nullptr;
                }
            }
            adjust();
            //zero is not used
            leafNum = heapSize;

            cout << "Symbol: ";
            for(int i = 1; i <= heapSize; i++){
                cout << (heap[i]).c << " ";
            }
            cout << endl;
            cout << "Frequency: ";
            for(int i = 1; i <= heapSize; i++){
                cout << (heap[i]).freq << " ";
            }
            cout << endl;
        }
        int getLeaf(){
            return leafNum;
        }
        void adjust(){
            int i, j;
            int min = 0; int parent = 0;
            for(i = heapSize / 2; i >= 1; i--){//from the last parent
                min = i;
                parent = i;
                for(j = 2 * i; j <= heapSize; j *= 2){//adjust downwards
                    if(j <= heapSize){//i has left child
                        if(heap[j].freq < heap[min].freq){//left child freq is smaller
                            min = j;
                        }
                    } 
                    if((j + 1) <= heapSize){//i has right child
                        if(heap[j + 1].freq < heap[min].freq){//right child freq is smaller
                            min = j + 1;
                        }
                    }
                    if(min != i){//min is not parent(children smaller)
                        swap(parent, min);//child go up
                        parent = min;//parent index goes down
                    }
                    
                }
            }
        }
        void adjustRoot(){
            int i = 1, j;
            int min = i, parent = i;
            for(j = 2 * i; j <= heapSize; j *= 2){//adjust downwards
                if(j <= heapSize){//i has left child
                    if(heap[j].freq < heap[min].freq){//left child freq is smaller
                        min = j;
                    }
                } 
                if((j + 1) <= heapSize){//i has right child
                    if(heap[j + 1].freq < heap[min].freq){//right child freq is smaller
                        min = j + 1;
                    }
                }
                if(min != i){//min is not parent(children smaller)
                    swap(parent, min);//child go up
                    parent = min;//parent index goes down
                }
                else{
                    break;
                }
            }
        }
        void swap(int a, int b){
            node* temp = new node;//temp records a
            temp->c = heap[a].c; temp->freq = heap[a].freq; temp->leaf =  heap[a].leaf; temp->left = heap[a].left; temp->right = heap[a].right;
            heap[a].c = heap[b].c; heap[a].freq = heap[b].freq; heap[a].leaf = heap[b].leaf; heap[a].left = heap[b].left; heap[a].right = heap[b].right; 
            heap[b].c = temp->c; heap[b].freq = temp->freq; heap[b].leaf = temp->leaf; heap[b].left = temp->left; heap[b].right = temp->right;
        }
        void pushHeap(node* n){//not yet used
            //if full
            if((heapSize + 1) == capacity){
                return;
            }    
            else{
                heapSize++;
                heap[heapSize].c = (*n).c;
                heap[heapSize].freq = (*n).freq;
                heap[heapSize].leaf = 0;//insert non leaf(circle)
                heap[heapSize].left = (*n).left;
                heap[heapSize].right = (*n).right;
            }        
            adjust();
            return;
        }
        node* popMin(){
            //if empty
            node* res = new node;
            if(heapSize == 0){
                cout << "empty";
                return nullptr;
            }
            else{
                res->c = heap[1].c;//res stores root data
                res->freq = heap[1].freq;
                res->leaf = heap[1].leaf;
                res->left = heap[1].left; 
                res->right = heap[1].right;
                //let the last node become the first node to delete root in an array
                heap[1].c = heap[heapSize].c;
                heap[1].freq = heap[heapSize].freq;
                heap[1].leaf = heap[heapSize].leaf;
                heap[1].left = heap[heapSize].left;
                heap[1].right = heap[heapSize].right;
                heapSize--;
            }
            //downward adjust
            adjustRoot();
            return res;
        }
        void buildHuff(){
            //build huffman tree using delete twice and push once
            node* leftChild = nullptr, *rightChild = nullptr, *newNode = nullptr;
            while(heapSize > 1){
                leftChild = popMin();
                rightChild = popMin();
                if((leftChild != nullptr) && (rightChild != nullptr)){//we have both child
                    newNode = new node;
                    newNode->c = '\0';
                    newNode->freq = (leftChild->freq) + (rightChild->freq);
                    newNode->leaf = 0; newNode->left = leftChild; newNode->right = rightChild;
                    pushHeap(newNode);
                }
                else{
                    cout << "already ends error" << endl;
                    return;
                }
            }
            //only one node left
            hoffRoot = newNode;
        }
        node* getRoot(){
            return hoffRoot;
        }
        void preorderHuff(node* start){
            if(start != nullptr){
                cout << start->freq << " ";
                preorderHuff(start->left);
                preorderHuff(start->right);
            }
        }
        void inorderHuff(node* start){
            if(start != nullptr){
                inorderHuff(start->left);
                cout << start->freq << " ";
                inorderHuff(start->right);
            }
            return;
        }
        int printHeight(node* start){
            if(start != nullptr){
                int nl = printHeight(start->left);
                int nr = printHeight(start->right);
                if(nl >= nr)
                    return nl + 1;
                else
                    return nr + 1;
            }
            return 0;
        }
        void initCodeTable(){
            codeTop = 0; //0 or -1?
            codeTable = new codeNode[leafNum];
            table = new char[printHeight(getRoot())];//initialization
            tableTop = 0;
        }
        void printTable(){
            int j = 0; int top = 0;
            cout << "Huffman Code:" << endl;
            while(top < leafNum){
                cout << codeTable[top].cha << ": ";
                cout << codeTable[top].code;
                top++;
                cout << endl;
            } 
        }
        void makeTable(node* start){
            //using postorder to make coding table
            if(start->left != nullptr){
                table[tableTop++] = '0';
                makeTable(start->left);
                tableTop--;//go back
            }
            if(start->right != nullptr){
                table[tableTop++] = '1';
                makeTable(start->right);
                tableTop--;//go back
            }
            if(start->leaf){
                //it is a leaf: put the character and code inside
                (codeTable)[codeTop].cha = start->c;
                codeTable[codeTop].code = new char[printHeight(getRoot())]; int length = 0;
                int i = 0; //num = printHeight(getRoot()); temp = new char[num];//char array
                //cout << "\nthis code: "<< table << endl;;
                while(table[i] != '\0'){
                    (codeTable[codeTop].code)[i] = table[i];//code is a char array
                    //cout <<((codeTable)[codeTop].code)[i];
                    i++; length++;
                }
                codeTable[codeTop].len = length;
                table[i - 1] = '\0';//since table[i] == '\0', we need to set last element(aka i - 1) to null

                codeTop++;
            }
        }
        void codeSearch(char* str1, int slen){
            for(int i = 0; i < slen; i++){//scan the string
                for(int j = 0; j < leafNum; j++){//scan the codeTable
                    for(int k = 0; k < codeTable[j].len; k++){//code match in coding table
                        if(str1[i + k] != (codeTable[j].code[k])){//code mismatch
                            break;
                        }
                        if(k == (codeTable[j].len - 1)){//the code has been scanned, matches
                            rear += 1;
                            indexTable[rear] = codeTable[j].cha;
                            i += codeTable[j].len;
                            j = -1;//from the beginning entry of codeTable
                        }
                    }
                }
            }
        }
        void codeMatching(char* code, int userLen){
            //initialization
            indexTable = new char[sizeof(code) - 1];
            rear = -1;
            codeSearch(code, userLen);

            cout << "Decoded Result:" << endl;
            for(int i = 0; i <= rear; i++){
                cout << indexTable[i];
            }
            cout << endl;
        }
};



int main(){
    char input[200]; char userCode[200]; 
    cin.getline(input, 200);
    cin.getline(userCode, 200);


    char* charPtr = &(input[0]); int countInput[27] = {};
    node* temp;

    //count the frequency of each alphabet
    while(*(charPtr) != '\0'){
        countInput[(*(charPtr))-96]++;
        charPtr++;
    } 

    //construct a heap of nodes
    MinHeap h(countInput);

    h.buildHuff();

    cout << "Preorder: ";
    h.preorderHuff(h.getRoot());
    cout << endl;

    cout << "Inorder: ";
    h.inorderHuff(h.getRoot());
    cout << endl;

    cout << "Level: " << h.printHeight(h.getRoot()) << endl;
    
    h.initCodeTable();
    h.makeTable(h.getRoot());
    //now codeTable[leafNum] stores code for each hoffman leaf
    h.printTable();

    int usrlen = sizeof(userCode) - 1;
    h.codeMatching(userCode, usrlen);

    return 0;
}