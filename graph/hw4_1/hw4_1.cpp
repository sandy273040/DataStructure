#include<iostream>
using namespace std;

class Graph;
class Stack;
class MinHeap;

struct vertexNode{
    int vertexIndex;
    int weight;
    int parent;
    int distance;
    vertexNode* next;
};
struct node{
    //for min heap
    int nodeIndex;
    int parentIndex;
    int weight;
};

class MinHeap{
    public:
        friend class Graph;
        node* heap;
        int heapSize;
    
        MinHeap(bool* exist, int start){//bottom up build heap
            //initialization
            //capacity = 102;
            heapSize = 0;
            for(int i = 0; i < 101; i++){
                if(exist[i])
                    heapSize++;
            }
            heap = new node[heapSize + 1];

            //initialize: index, parent, distance
            int heapIndex = 1;
            for(int i = 0; i < 101; i++){
                if(exist[i]){
                    (heap[heapIndex]).nodeIndex = i;
                    (heap[heapIndex]).parentIndex = start;
                    if(i == start){
                        (heap[heapIndex]).weight = 0;
                    }
                    else{
                        (heap[heapIndex]).weight = INT_MAX;
                    }
                    heapIndex++;
                }
            }

            adjust();
            //zero is not used
            //note that after adjust, heap index doesn't imply vertexNode index
        }

        void adjust(){
            int i, j;
            int min = 0; int parent = 0;
            for(i = heapSize / 2; i >= 1; i--){//from the last parent
                min = i;
                parent = i;
                for(j = 2 * i; j <= heapSize; j *= 2){//adjust downwards
                    if(j <= heapSize){//i has left child
                        if(heap[j].weight < heap[min].weight){//left child freq is smaller
                            min = j;
                        }
                    } 
                    if((j + 1) <= heapSize){//i has right child
                        if(heap[j + 1].weight < heap[min].weight){//right child freq is smaller
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
                    if(heap[j].weight < heap[min].weight){//left child freq is smaller
                        min = j;
                    }
                } 
                if((j + 1) <= heapSize){//i has right child
                    if(heap[j + 1].weight < heap[min].weight){//right child freq is smaller
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
            temp->nodeIndex = heap[a].nodeIndex; temp->weight = heap[a].weight; temp->parentIndex = heap[a].parentIndex; 
            heap[a].nodeIndex = heap[b].nodeIndex; heap[a].weight = heap[b].weight; heap[a].parentIndex = heap[b].parentIndex;  
            heap[b].nodeIndex = temp->nodeIndex; heap[b].weight = temp->weight; heap[b].parentIndex = temp->parentIndex; 
        }
        node* popMin(){
            //if empty
            node* res = new node;
            if(heapSize == 0){
                cout << "empty";
                return nullptr;
            }
            else{
                res->nodeIndex = heap[1].nodeIndex;//res stores root data
                res->weight = heap[1].weight;
                res->parentIndex = heap[1].parentIndex;
                //let the last node become the first node to delete root in an array
                heap[1].nodeIndex = heap[heapSize].nodeIndex;
                heap[1].weight = heap[heapSize].weight;
                heap[1].parentIndex = heap[heapSize].parentIndex;
                heapSize--;
            }
            //downward adjust
            adjustRoot();
            return res;
        }
        void updateWeight(int& parent, int& index, int& compareWeight){
            node* find = nullptr;
            for(int i = 1; i <= heapSize; i++){
                find = &(heap[i]);
                if(find->nodeIndex == index){
                    //find the node
                    //relax()
                    if(compareWeight < (find->weight)){
                        find->weight = compareWeight;
                        find->parentIndex = parent;
                    }
                    break;
                }
            }
            //adjust();
            return;

        }
};

class Stack{
    public: 
        //vertexNode* stack;
        int* stack;
        int top;
        //constructor
        Stack(){
            //stack = new vertexNode[101];
            //cout << "construct" << endl;
            stack = new int[101];
            top = -1;
        }
        int getSize(){
            return top + 1;
        }
        void push(int &index){
            top += 1;
            stack[top] = index;
            //cout << "top in push" << top << endl;
        }
        int pop(){
            int result;
            result = stack[top--];
            return result;
        }
};

class Graph{
    public:
        //record whether the vertex exists in this graph, index 0~100 (total 101)
        bool exist[101];
        int count;
        vertexNode** adjacencyList;//adjacent list

        //for strongly connected component
        bool visited[101];
        vertexNode** reverseGraph;
        int counterComponent;

        //for Dijkstra
        vertexNode* sure;

        Graph(){
            count = 0;
            adjacencyList = new vertexNode * [101];
            //sure = new vertexNode[101];
            for(int i = 0; i < 101; i++){
                adjacencyList[i] = nullptr;
                exist[i] = 0;
            }
        }
        void setCount(){
            //calculate the number of existed 
            for(int i = 0; i < 101; i++){
                if(exist[i]){
                    count++;
                }
            }
        }
        
        void addVertex(int  a){
            if((a < 0) || (a > 100)){
                //out if boundary
                cout << "add an invalid vertex" << endl;
                return;
            }
            if(exist[a] == true){
                //vertex already exists
                cout << "vertex " << a << " is already in G." << endl;
                return;
            }
            exist[a] = true; count++;
            //cout << "add vertex " << a << " to graph" << endl;///////
            return;
        }
        void deleteVertex(int a){
            if((a < 0) || (a > 100)){
                //out if boundary
                cout << "delete an invalid vertex" << endl;
                return;
            }
            if(exist[a] == false){
                //vertex doesn't exist
                cout << "vertex " << a << " isn't in G." << endl;
                return;
            }
            exist[a] = false; count--;
            return;
        }
        //Edge operation
        void addEdge(int a, int b, int w){
            if((! exist[a]) || (! exist[b])){
                //a doesn't exist or b doesn't exist
                cout << "add an invalid edge" << endl;
                return;
            }
            //traverse the list of a, if edge(a, b) exists, replace the original weight, otherwise new a node
            vertexNode* ptr = adjacencyList[a];
            while(ptr != nullptr){
                if(ptr->vertexIndex == b){
                    //b exists, replace the weight
                    ptr->weight = w;
                    return;
                }
                else{
                    //not yet find b
                    ptr = ptr->next;
                }
            }
            //b doesn't exist
            vertexNode * newNode = new vertexNode;
            newNode->vertexIndex = b; newNode->weight = w; newNode->next = nullptr;
            //insert back
            vertexNode * findSpace = adjacencyList[a];
            if(findSpace == nullptr){
                //first node
                adjacencyList[a] = newNode;
            }
            else{
                while(findSpace != nullptr){
                    if(findSpace->next == nullptr){
                        //find the last node
                        findSpace->next = newNode;
                        return;
                    }
                    findSpace = findSpace->next;
                }
            }
            return;
        }
        void deleteEdge(int a, int b){
            //delete node index b at list a
            //first, check a and b both in graph
            if((! exist[a]) || (! exist[b])){
                //a doesn't exist or b doesn't exist
                cout << "delete an invalid edge" << endl;
                return;
            }
            //inspect whether b is in a: find b
            vertexNode* ptr = adjacencyList[a];
            vertexNode* findPrev = adjacencyList[a];
            vertexNode* deleteNode = nullptr;
            while(ptr != nullptr){
                //cout << "ptr index: " << ptr->vertexIndex << endl;
                if(ptr->vertexIndex == b){
                    //find b
                    deleteNode = ptr;
                    //but ptr might be the first node
                    if(findPrev == ptr){
                        //first node
                        adjacencyList[a] = ptr->next;
                    }
                    else{
                        while(findPrev->next != ptr){//find previous node of b
                            findPrev = findPrev->next;
                        }
                        findPrev->next = ptr->next;
                    }
                    delete deleteNode;
                    deleteNode = nullptr;
                    return;
                }
                else{
                    ptr = ptr->next;
                }
            }
            //edge not exists
            cout << "fail to delete edge<" << a << "," << b << ">" << endl;
        }
        void initComponent(){
            counterComponent = 0;
            //initial adjacency list
            //vertexNode * p = nullptr;
            for(int i = 0; i < 101; i++){
                visited[i] = 0;
            }
        }

        void buildReverse(){
            //build the reverseGraph of Adjacent list
            //initialization
            reverseGraph = new vertexNode * [101];
            for(int i = 0; i < 101; i++){
                reverseGraph[i] = nullptr;
            }
            //traverse adjacency list and new node
            vertexNode* ptr = nullptr; int a = 0, weig = 0;
            for(int i = 0; i < 101; i++){
                ptr = adjacencyList[i];
                while(ptr != nullptr){
                    //addNode = new vertexNode;
                    //reverseGraph[ptr->vertexIndex];
                    a = ptr->vertexIndex; weig = ptr->weight;
                    addReverseEdge(a, i, weig);
                    ptr = ptr->next;
                }
            }
        }
        void addReverseEdge(int a, int b, int w){
            if((! exist[a]) || (! exist[b])){
                //a doesn't exist or b doesn't exist
                cout << "add an invalid edge" << endl;
                return;
            }
            //traverse the list of a, if edge(a, b) exists, replace the original weight, otherwise new a node
            vertexNode* ptr = reverseGraph[a];
            while(ptr != nullptr){
                if(ptr->vertexIndex == b){
                    //b exists, replace the weight
                    ptr->weight = w;
                    return;
                }
                else{
                    //not yet find b
                    ptr = ptr->next;
                }
            }
            //b doesn't exist
            vertexNode * newNode = new vertexNode;
            newNode->vertexIndex = b; newNode->weight = w; newNode->next = reverseGraph[a];
            //insert front
            reverseGraph[a] = newNode;
            return;
        }

        void connectedComponents(){
            initComponent();
            Stack s;//construct a stack
            //vertexNode * p = nullptr;
            for(int i = 0; i < 101; i++){
                if(((visited[i]) != true) && (exist[i])){
                    //the node exists and not visited yet
                    DFS(i, s);
                }
            }
            initComponent();
            buildReverse();
            int index = 0;
            while(s.getSize() > 0){
                index = s.pop();
                if((!(visited[index])) && exist[index]){
                    reverseDFS(index, s);
                    counterComponent += 1;
                }
            }
            cout << "connectedComponents: " << counterComponent << endl;
        }
        void DFS(int start, Stack &s){
            //cout << "start: " << start.visited << endl;
            visited[start] = true;
            //cout << "visited : " << start << endl;///////
            vertexNode* ptr = adjacencyList[start];
            while(ptr != nullptr){//now p points at start's first neighbor
                if((visited[ptr->vertexIndex]) != true){
                    //neighbor has not visited
                    DFS((ptr->vertexIndex), s);
                }
                ptr = ptr->next;
                
            }
            //p has visited all the neighbor, aka finish, push to stack
            s.push(start);
        }
        void reverseDFS(int start, Stack &s){
            //cout << "start: " << start.visited << endl;
            visited[start] = true;
            vertexNode* ptr = reverseGraph[start];
            while(ptr != nullptr){//now p points at start's first neighbor
                if((visited[ptr->vertexIndex]) != true){
                    //neighbor has not visited
                    reverseDFS((ptr->vertexIndex), s);
                }
                ptr = ptr->next;
                
            }
            //p has visited all the neighbor, aka finish, push to stack
            s.push(start);
        }
        void initDijkstra(int& a){
            sure = new vertexNode[101];
            for(int i = 0; i < 101; i++){
                visited[i] = 0;
                sure[i].distance = INT_MAX;
                sure[i].parent = a;
            }
        }

        void dijkstra(int a, int b){
            if((!(exist[a])) || (!(exist[b]))){
                cout << "an invalid vertex" << endl;
                return;
            }
            vertexNode* ptr = nullptr;
            for(int i = 0; i < 101; i++){
                ptr = adjacencyList[i];
                while(ptr != nullptr){//now p points at start's first neighbor
                    if((exist[ptr->vertexIndex]) == true){
                        if(ptr->weight < 0){
                            cout << "G contains a negative edge." << endl;
                            return;
                        }
                    }
                    ptr = ptr->next;
                    
                }
            }
            initDijkstra(a);
            MinHeap distance(exist, a);//array of distance from source
            //initialization
            int round = 0; vertexNode* p = nullptr; node* nodePtr = nullptr; int minWeight = 0; int selfIndex = 0; int parIndex = a;
            int neighIndex = 0; int currWeight = 0; int totalRound = distance.heapSize;//since we popMin(), heapSize will change
            while(round < totalRound){
                nodePtr = distance.popMin();
                minWeight = nodePtr->weight;
                selfIndex = nodePtr->nodeIndex;
                parIndex = nodePtr->parentIndex;
                sure[selfIndex].distance = minWeight;
                sure[selfIndex].parent = parIndex;

                visited[nodePtr->nodeIndex] = true;//already "sure" that this node is shortest path
                p = adjacencyList[nodePtr->nodeIndex];
                while(p != nullptr){
                    //check negative weight, compare and update the weight of a's neighbor
                    neighIndex = p->vertexIndex;
                    if(visited[neighIndex] != true){//if neighbor hasn't in set sure
                        currWeight = (p->weight) + minWeight;
                        distance.updateWeight(selfIndex, neighIndex, currWeight);
                    }
                    p = p->next;
                }
                distance.adjust();
                round++;
            }
            if(sure[b].distance == INT_MAX){
                cout << "Dijkstra: no solution for" << a << "->" << b << endl;
            }
            else{
                Stack path;
                int end = b;
                while(end != a){
                    path.push(end);
                    end = sure[end].parent;
                }
                path.push(end);

                while(path.getSize() > 1){
                    cout << path.pop() << "->";
                }
                cout << path.pop();
                cout << " total: " << sure[b].distance << endl;
            }
        }
        void initBell(int& a){
            sure = new vertexNode[101];
            for(int i = 0; i < 101; i++){
                visited[i] = 0;
                sure[i].distance = INT_MAX;
                sure[i].parent = a;
            }
            //first round
            vertexNode* p = adjacencyList[a];
            while(p != nullptr){
                sure[p->vertexIndex].distance = p->weight;
                p = p->next;
            }
            sure[a].distance = 0;
        }
        void bellmanFord(int a, int b){
            if((!(exist[a])) || (!(exist[b]))){
                cout << "an invalid vertex" << endl;
                return;
            }
            initBell(a);//initialize sure[i] as dist[i]
            setCount();//get the correct vertex number on count
            int k = 1;
            vertexNode* ptr = nullptr; int u = 0; int v = 0;
            while(k <= (count - 2)){//control round, do |v| - 2 times
                //cout << "round: " << k << endl;
                for(int i = 0; i < 101; i++){
                    if(exist[i]){
                        ptr = adjacencyList[i];//this is source
                        u = i; //i is source, ptr->vertexIndex is destination
                        while(ptr != nullptr){
                            v = ptr->vertexIndex;
                            if((sure[u].distance != INT_MAX) && ((sure[u].distance + ptr->weight ) < sure[v].distance)){
                                //prevent INT_MAX overflow
                                sure[v].distance = sure[u].distance + ptr->weight;
                                sure[v].parent = u;
                            }
                            ptr = ptr->next;
                        }
                    }
                    
                }
                k++;
            }
            /*for(int i = 0; i < 101; i++){
                if(exist[i]){
                    cout << sure[i].distance << " ";
                }
            }*/

            for(int i = 0; i < 101; i++){
                    if(exist[i]){
                        ptr = adjacencyList[i];//this is source
                        u = i;
                        while(ptr != nullptr){
                            v = ptr->vertexIndex;
                            if((sure[u].distance != INT_MAX) && ((sure[u].distance + ptr->weight) < sure[v].distance)){
                                cout << "G contains a cycle of negative length." << endl;
                                return;
                            }
                            ptr = ptr->next;
                        }
                    }
                    
            }
            if(sure[b].distance == INT_MAX){
                cout << "BellmanFord: no solution for" << a << "->" << b << endl;
            }
            else{
                Stack path;
                int end = b;
                while(end != a){
                    path.push(end);
                    end = sure[end].parent;
                }
                path.push(end);

                while(path.getSize() > 1){
                    cout << path.pop() << "->";
                }
                cout << path.pop();
                cout << " total: " << sure[b].distance << endl;
            }


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
int getNum(char* num){
    int data = 0;
    int dig = 0;
    int sign = 1;
    if(num[0] == 45){
        sign = -1;
    }
    while(num[dig] != '\0'){
        //count total digit
        dig += 1;
    }
    if(sign == -1){
        dig -= 1;
    }
    dig-=1; int i = dig;//digit becomes highest exponent
    while(i >= 0){
        //note that if the num is negative, we need to shift a digit to right
        if(num[i + 1] == 45)
            break;
        if(sign == -1){
            //negative num
            data += ((num[i + 1]-48) * tenPow(dig-i));//fetch number from end, and use lower exponent
        }
        else if(sign == 1){
            //positive num
            data += ((num[i]-48) * tenPow(dig-i));//fetch number from end, and use lower exponent
        }
        i--; 
    }
    return data * sign;
}


int main(){
    char file[200] = "";
    Graph g;
    while(cin.getline(file, 200)){
        
        if(file[0] == -1){
            break;
        }
        if((file[0] == 'a') && (file[3] == 'V')){
            int i = 0; char num[200] = "";
            while(file[i] != '\0'){
                num[i-10] = file[i];
                i++;
            }
            int n = getNum(num);
            g.addVertex(n);
            //cout << "n: " << n << endl;
        }
        else if((file[0] == 'a') && (file[3] == 'E')){
            int source = 0; int destination = 0; int capacity = 0;
            int accumIndex = 8;//to indicate each number's beginning index
            
            for(int i = 1; i <= 3; i++){
                char num[200] = "";
                //get source, dest, and capacity
                int fileIndex = accumIndex;
                while((file[fileIndex] != '\t') && (file[fileIndex] != '\0' && (file[fileIndex] != 32))){
                    //extract num(subString) from file array
                    num[fileIndex - accumIndex] = file[fileIndex];
                    fileIndex += 1;
                }
                accumIndex = fileIndex + 1;//since fileIndext points to the position of '\t' or '\0' when breaking loop
                if(i == 1){
                    //source
                    source = getNum(num);
                }
                else if (i == 2){
                    destination = getNum(num);
                }
                else if(i == 3){
                    capacity = getNum(num);
                }
            }
            //cout << "add edge: " << source << " " << destination << " " << capacity << endl;
            g.addEdge(source, destination, capacity);
            
        }
        else if(file[0] == 'D'){
            char num[200] = "";
            int source = 0; int destination = 0;
            int accumIndex = 9;//to indicate each number's beginning index
            
            for(int i = 1; i <= 2; i++){
                char num[200] = "";
                //get source, dest, and capacity
                int fileIndex = accumIndex;
                while((file[fileIndex] != '\t') && (file[fileIndex] != '\0' && (file[fileIndex] != 32))){
                    //extract num(subString) from file array
                    num[fileIndex - accumIndex] = file[fileIndex];
                    fileIndex += 1;
                }
                accumIndex = fileIndex + 1;//since fileIndext points to the position of '\t' or '\0' when breaking loop
                if(i == 1){
                    //source
                    source = getNum(num);
                }
                else if (i == 2){
                    destination = getNum(num);
                }
            }
            //cout << "dijk: " << source << " " << destination <<  endl;
            g.dijkstra(source, destination);
        }
        else if(file[0] == 'c'){
            g.connectedComponents();
        }
        else if(file[0] == 'B'){
            char num[200] = "";
            int source = 0; int destination = 0;
            int accumIndex = 12;//to indicate each number's beginning index
            
            for(int i = 1; i <= 2; i++){
                char num[200] = "";
                //get source, dest, and capacity
                int fileIndex = accumIndex;
                while((file[fileIndex] != '\t') && (file[fileIndex] != '\0' && (file[fileIndex] != 32))){
                    //extract num(subString) from file array
                    num[fileIndex - accumIndex] = file[fileIndex];
                    fileIndex += 1;
                }
                accumIndex = fileIndex + 1;//since fileIndext points to the position of '\t' or '\0' when breaking loop
                if(i == 1){
                    //source
                    source = getNum(num);
                }
                else if (i == 2){
                    destination = getNum(num);
                }
            }
            //cout << "bell: " << source << " " << destination <<  endl;
            g.bellmanFord(source , destination);
        }
        else{
            cout << "Wrong instruction" << endl;
        }
    }

    return 0;
}