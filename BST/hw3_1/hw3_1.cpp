#include<iostream>
using namespace std;
class BinarySearchTree;
class QueueNode;
class node{
    friend class BinarySearchTree;
    friend class QueueNode;
    private:
        int data;
        int id;
        node* left;
        node* right;
        node* parent;

    public:
        node(int num, node* lchild = nullptr, node* rchild = nullptr, node* giveParent = nullptr){
            data = num;
            left = lchild;
            right = rchild;
            parent = giveParent;
        }
        int getData(){
            return data;
        }
        int getID(){
            return id;
        }
        void setID(int &num){
            id = num;
        }
        node* getLeft(){//careful to out of boundary
            return left;
        }
        node* getRight(){
            return right;
        }
        node* getParent(){
            return parent;
        }
        void setData(int &d){
            data = d;
        }
        void setLeft(node* lchild){//add & to solve the call by value problem
            left = lchild;
        }
        void setRight(node* rchild){
            right = rchild;
        }
        void setParent(node* myParent){
            parent = myParent;
        }
};
class QueueNode{
     public:
        int data;
        QueueNode* next;
        QueueNode(int d, QueueNode* ptr){
            data = d;
            next = ptr;
        }
};

class BinarySearchTree{
    private:
        node* root;
        int count;//total number of node of the tree
    public:
        BinarySearchTree(node &treeNode){
            treeNode.id = 1;
            root = &treeNode;
            count = 0;
        }
        node* getRoot(){
            return root;
        }
        int getCount(){
            return count;
        }
        int search(const int k){
            updateID();

            int res = 0;
            if(!((k>=0) && (k<=100))){
                cout << "Search Wrong data" << endl;
                return 0;
            }
            res = searchHelper((*root).getRight(), k);
            if(res == 0){
                return 0;
            }
            else{
                cout << res << endl;
                return res;
            }
        }
        int searchHelper(node* start, const int k){
            if(start != nullptr){
                if((*start).getData() == k){
                    //cout << "1";
                    return (*start).getID();
                }
                else if((*start).getData() < k){
                    return searchHelper((*start).getRight(), k);
                }
                else{
                    return searchHelper((*start).getLeft(), k);
                }
            }
            cout << "This data is not in BST" << endl;
            return 0;
        }
        node* insertHelper(node* start, const int k){
            node* finalPtr = nullptr;
            node* tempPtr = nullptr;
            
            if(start != nullptr){
                if((*start).getData() < k){
                    //node finalNode(k, 0, 0, 0);//to store the new node from recusrion
                    finalPtr = insertHelper((*start).getRight(), k);
                    if(finalPtr != nullptr){
                        (*start).setRight(finalPtr);//insert right
                        (*finalPtr).setParent(start);
                    }
                    else{
                        return nullptr;
                    }
                    return start;
                }
                else if((*start).getData() > k){
                    //node finalNode(k, 0, 0, 0);//to store the new node from recusrion
                    finalPtr = insertHelper((*start).getLeft(), k);
                    if(finalPtr != nullptr){
                        (*start).setLeft((finalPtr));//insert left
                        (*finalPtr).setParent(start);
                    }
                    else{
                        return nullptr;
                    }
                    return start;
                }
                else{
                    //data already exists
                    cout << "This data is in BST" << endl;
                    return nullptr;
                }
            }
            tempPtr = new node(k, 0, 0, 0);//consruct a new node
            return tempPtr;
        }
        node* insertTree(int num){
            if(!((num>=0) && (num<=100))){//boundary check
                cout << "Insert Wrong data" << endl;
                return root;
            }
            if(((*root).getLeft() == nullptr) && (*root).getRight() == nullptr){//empty tree
                node* firstNode = new node(num, 0, 0, 0);
                (*root).setRight(firstNode);
                (*firstNode).setParent(root);
                //return root;
            }
            else{
                //insert a new node into correct position
                node* nodePtr = nullptr;
                nodePtr = insertHelper((*root).getRight(), num);
                if(nodePtr == nullptr){
                    return root;
                }
                else{
                    (*root).setRight(nodePtr);
                }
                //insert new bst to the right of head node
                //return root;
            }
            count++;
            return root;
        }
        void printLevel(){
            QueueNode* front = nullptr, *rear = nullptr;//constrcut queue
            node* start = nullptr, *find = nullptr; QueueNode* temp = nullptr, *t = nullptr;
            int countid = 0;
            if((*root).getRight() == nullptr){
                //empty tree
                cout << endl;
                return;
            }
            else{
                //start with root node
                start = (*root).getRight();
                temp = new QueueNode((*start).getData(), 0);
                //Enqueue the first queue node
                front = rear = temp;

                while(front != nullptr){//if queue is not empty
                    //add start's children
                    if((*start).getLeft() != nullptr){
                        //start has its left child
                        temp = new QueueNode((*(*start).getLeft()).getData(), 0);
                        rear->next = temp;
                        rear = temp;
                    }
                    if((*start).getRight() != nullptr){
                        //start has its right child
                        temp = new QueueNode((*(*start).getRight()).getData(), 0);
                        rear->next = temp;
                        rear = temp;
                    }
                    cout << (*start).getData() << " ";
                    (*start).setID(++countid);
                    //dequeue and set new start
                    t = front; 
                    if(front->next != nullptr){
                        front = front->next;
                    }
                    else{
                        front = rear = nullptr;
                    }
                    delete t; t = nullptr;
                    //set new start
                    find = (*root).getRight();
                    if(front != nullptr){
                        while((*find).getData() != front->data){
                            if(front->data < (*find).getData()){
                                find = (*find).getLeft();
                            }
                            else if(front->data > (*find).getData()){
                                find = (*find).getRight();
                            }
                        }
                        start = find;
                    }
                    
                }
            }
            cout << endl;
            return;
        }
        void updateID(){
            QueueNode* front = nullptr, *rear = nullptr;//constrcut queue
            node* start = nullptr, *find = nullptr; QueueNode* temp = nullptr, *t = nullptr;
            int countid = 0; int passed = 0;
            if((*root).getRight() == nullptr){
                return;
            }
            else{
                //start with root node
                start = (*root).getRight();
                temp = new QueueNode((*start).getData(), 0);
                //Enqueue the first queue node
                front = rear = temp;
                passed += 1;

                while(front != nullptr){//if queue is not empty
                    //add start's children
                    if((*start).getLeft() != nullptr){
                        //start has its left child
                        temp = new QueueNode((*(*start).getLeft()).getData(), 0);
                        rear->next = temp;
                        rear = temp;
                    }
                    else{
                        temp = new QueueNode(-2, 0);
                        rear->next = temp;
                        rear = temp;
                    }
                    if((*start).getRight() != nullptr){
                        //start has its right child
                        temp = new QueueNode((*(*start).getRight()).getData(), 0);
                        rear->next = temp;
                        rear = temp;
                    }
                    else{
                        temp = new QueueNode(-2, 0);
                        rear->next = temp;
                        rear = temp;
                    }
                    //print data and set id
                    (*start).setID(++countid);
                    t = front; 
                    if(front->next != nullptr){
                        front = front->next;
                    }
                    else{
                        front = rear = nullptr;
                    }
                    delete t; t = nullptr;

                    if(passed == count){
                        return;//has visited all the node
                    }
                    while(front->data == -2){//advance steps
                        countid++;
                        if(front->next != nullptr){
                            //add null child: left and right
                            temp = new QueueNode(-2, 0);
                            rear->next = temp;
                            rear = temp;
                            temp = new QueueNode(-2, 0);
                            rear->next = temp;
                            rear = temp;
                            //advance
                            t = front;
                            front = front->next; delete t; t = nullptr;
                        }
                        else{
                            t = front;
                            front = rear = nullptr; delete t; t = nullptr;
                            break;
                        }
                    }
                    //set new start
                    find = (*root).getRight();
                    if(front != nullptr){
                        while((*find).getData() != front->data){
                            if(front->data < (*find).getData()){
                                find = (*find).getLeft();
                            }
                            else if(front->data > (*find).getData()){
                                find = (*find).getRight();
                            }
                        }
                        start = find;
                        passed += 1;
                    }
                }
            }
            return;
        }
        
        node* deleteHelper(node* start, const int k){
            //cout << "in delete helper" <<  "data: " << (*start).getData() << "k: " << k << endl;
            node* par = nullptr, *temp = nullptr, *find = nullptr;
            int modData = 0;
            //{
                if((*start).getData() == k){//we find the node we want
                    //step2: delete
                    while(start != nullptr){
                        if(((*start).getLeft() == nullptr) && ((*start).getRight() == nullptr)){//no child
                            //find parent
                            temp = start;
                            par = (*start).getParent();
                            //cout << "data: " << (*start).getData() << endl;
                            if((*par).getLeft() == start){
                                //start is left child
                                (*par).setLeft(nullptr);
                            }
                            else if((*par).getRight() == start){
                                //start is right child
                                (*par).setRight(nullptr);
                            }
                            delete temp; temp = nullptr;
                            return root;
                        }
                        else if(((*start).getLeft() == nullptr)){//start only have right child
                            temp = start;
                            par = (*start).getParent();
                            if((*par).getLeft() == start){
                                //start is left child
                                (*par).setLeft((*start).getRight());
                                (*(*start).getRight()).setParent((par));
                            }
                            else if((*par).getRight() == start){
                                //start is right child
                                (*par).setRight((*start).getRight());
                                (*(*start).getRight()).setParent(par);
                            }
                            delete temp; temp = nullptr;
                            return root;

                        }
                        else if(((*start).getRight() == nullptr)){//only have left child
                            temp = start;
                            par = (*start).getParent();
                            if((*par).getLeft() == start){
                                //start is left child
                                (*par).setLeft((*start).getLeft());
                                (*(*start).getLeft()).setParent(par);
                            }
                            else if((*par).getRight() == start){
                                //start is right child
                                (*par).setRight((*start).getLeft());
                                (*(*start).getLeft()).setParent(par);
                            }
                            delete temp; temp = nullptr;
                            return root;
                        }
                        else{//have both left and right child
                            //find
                            find = (*start).getRight();
                            while((*find).getLeft() != nullptr){
                                //find the min node in right-sub tree
                                if((*find).getLeft() != nullptr){
                                    find = (*find).getLeft();
                                }
                                else{
                                    break;
                                }
                            }
                            //cout << "node data1: " << (*start).getData() << endl;
                            modData = (*find).getData();
                            (*start).setData(modData);
                            //cout << "node data2: " << (*(*start).getParent()).getData() << endl; 
                            start = find;
                            //cout << "node data3: " << (*(*start).getParent()).getData() << endl; 
                        }
                    }

                }
                else if ((*start).getData() > k){//to left
                    //cout << "call: " << (*start).getLeft() << k << endl;
                    //cout << (*start).getData() << endl;
                    if((*start).getLeft() == nullptr){
                        cout << "This data is not in BST" << endl;
                        return nullptr;
                    }
                    else{
                        return deleteHelper((*start).getLeft(), k);
                    }
                    
                }
                else if ((*start).getData() < k){// to right
                    //cout << (*start).getData() << endl;
                    if((*start).getRight() == nullptr){
                        cout << "This data is not in BST" << endl;
                        return nullptr;
                    }
                    else{
                        return deleteHelper((*start).getRight(), k);
                    }
                    
                }
                return root;
            //}
            
        }
        node* deleteTree(const int num){
            node* ptr = nullptr;
            if(!((num>=0) && (num<=100))){//boundary check
                cout << "Delete Wrong data" << endl;
                return root;
            }
            //if(root == nullptr)
            if(count == 0){
                cout << "Delete Wrong data" << endl;
                return root;
            }
            else{
                //call helper to do the recursion
                ptr = deleteHelper((*root).getRight(), num);
            }
            if(ptr == nullptr){
                return root;
            }
            else{
                count--;
                return root;
            }
        }
        int printHeight(node* start){
            if(start != nullptr){
                int nl = printHeight((*start).getLeft());
                int nr = printHeight((*start).getRight());
                if(nl >= nr)
                    return nl + 1;
                else
                    return nr + 1;
            }
            return 0;
        }
        
    
};
int tenPow(int x){
    int r = x; int res = 1;
    while(r > 0){
        res *= 10;
        r--;
    }
    return res;
}

int main(){//be careful connstructor syntax
    node headNode(-1, 0, 0, 0);//headnode
    BinarySearchTree tree(headNode);//construct a binary search tree
    //node* treePtr = tree.getRoot();

    int data = 0;
    char file[200]; char num[5]; int dig = 0; int i = 0;//to reverse the power
    //cout << "begin" << "data: " << data << endl;
    while(cin.getline(file, 200)){
        if(file[0] == -1)
            break;
        //cout << "file 0: " << file[0] << endl;
        if(file[0] == 'I'){//deal with number
            while(file[7 + dig] != '\0'){
                num[dig] = file[7+dig];//power of ten
                dig += 1;
            }
            dig-=1; i = dig;
            while(i >= 0){
                data += ((num[i]-48) * tenPow(dig-i));
                i--;
            }
            tree.insertTree(data);
            data = 0; dig = 0; i = 0;
        }
        else if(file[0] == 'D'){
            while(file[7 + dig] != '\0'){
                num[dig] = file[7+dig];//power of ten
                dig += 1;
            }
            dig-=1; i = dig;
            while(i >= 0){
                data += ((num[i]-48) * tenPow(dig-i));
                i--;
            }
            tree.deleteTree(data);
            data = 0; dig = 0; i = 0;
        }
        else if(file[0] == 'H'){
            cout << tree.printHeight((*(tree.getRoot())).getRight()) << endl;
        }
        else if(file[0] == 'P'){
            tree.printLevel();
        }
        else if(file[0] == 'S'){
            while(file[7 + dig] != '\0'){
                num[dig] = file[7+dig];//power of ten
                dig += 1;
            }
            dig-=1; i = dig;
            while(i >= 0){
                data += ((num[i]-48) * tenPow(dig-i));
                i--;
            }
            tree.search(data);
            data = 0; dig = 0; i = 0;
        }
        else if(file[0] == 'N'){
            cout << tree.getCount() << endl;
        }
        else{
            cout << "Wrong Instruction" << endl;
        }
    }

    return 0;
}