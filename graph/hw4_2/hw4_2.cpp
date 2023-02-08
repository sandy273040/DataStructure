#include<iostream>
using namespace std;

class Queue;
class Graph;
struct flow_cap{
    int flow;
    int capacity;
};

class Queue{
    public:
        bool* visited;
        int* distance;
        int* predecessor;
        int* q;
        int front, rear;
        int qSize; int elementNum;
        Queue(int n){
            //initialization
            front = rear = -1;
            visited = new bool[n];
            distance = new int[n];
            predecessor = new int[n];
            q = new int[n];
            for(int i = 0; i < n; i++){
                visited[i] = distance[i] = q[i] = 0;
                predecessor[i] = -1;
            }
            qSize = n; elementNum = 0;
        }
        void addQueue(int n){
            if(n != qSize){
                //not full
                q[++rear] = n;
            }
            elementNum++;
        }
        int removeQueue(){
            if(front != rear){
                //not empty
                elementNum--;
                return q[++front];
            }
            else{
                cout << "remove queue error" << endl;
                return -1;
            }
        }
};

class Graph{
    public:
        //adgacency matrix
        flow_cap ** adj_matrix;
        int matrix_size;
        int max_flow;
        int** residual_net;
        int* path, * distance;
        Graph(int n){
            matrix_size = n;
            max_flow = 0;
            //create and initialize an adjacency matrix
            adj_matrix = new flow_cap * [n];
            for(int i = 0; i < n; i++){
                adj_matrix[i] = new flow_cap[n];
                for(int j = 0; j < n; j++){
                    adj_matrix[i][j].flow = 0;
                    adj_matrix[i][j].capacity = 0;
                }

            }
        }
        void addEdge(int index1, int index2, int capacity){
            if((index1 < 0) || (index1 >= matrix_size) || (index2 < 0) || (index2 >= matrix_size) || (capacity < 0)){
                //index out of bound
                cout << "add wrong edge" << endl;
                return;
            }
            //add edge
            adj_matrix[index1][index2].capacity = capacity;
            return;
        }
        bool BFS(int start, int end){
            Queue queue = Queue(matrix_size);//create a queue
            //visit start
            queue.visited[start] = 1;
            queue.addQueue(start);
            //while queue is not empty
            while(queue.elementNum > 0){
                int curr = queue.removeQueue();
                //find unvisited neighbor, update and enqueue
                for(int i = 0; i < matrix_size; i++){
                    if(residual_net[curr][i] != 0){//be careful
                        if(queue.visited[i] != true){
                            queue.visited[i] = true;
                            queue.predecessor[i] = curr;
                            queue.distance[i] = queue.distance[curr] + 1;
                            queue.addQueue(i);
                        }
                    }
                    
                }
            }
            //cout << "parent: ";
            for(int i = 0; i < queue.qSize; i++){
                path[i] = queue.predecessor[i];
                distance[i] = queue.distance[i];
            }
            return (queue.visited[end]);//if return true: means there is a path from start to end
        }
        void init_residual(){
            residual_net = new int*[matrix_size];
            for(int i = 0; i < matrix_size; i++){
                residual_net[i] = new int[matrix_size];
                path = new int[matrix_size];
                distance = new int[matrix_size];
                for(int j = 0; j < matrix_size; j++){
                    residual_net[i][j] = adj_matrix[i][j].capacity;
                }
            }
        }
        int minCapacity(int start, int end){
            //using predecessor to find path, but how to find multiple path?
            //init_residual();//initialize residual network
            int pathFlow = 100;//if capacity < 100
            //checking one the path, while(path[next] != -1)
            int next = end;
            while(next != -1){
                if(path[next] != -1){
                    if(residual_net[path[next]][next] < pathFlow){
                        pathFlow = residual_net[path[next]][next] ;
                    }
                }
                next = path[next];
            }
            return pathFlow;
        }
        void update_residual(int start, int end){
            int pathFlow = minCapacity(start, end);
            //on residual network: find min flow on the path and update(same direction: capacity - flow; opposite direction: original flow+ new flow)
            //update residual network and adj matrix's flow
            int next = end;
            while(next != -1){
                //note that (next, path[next]) is opposite direction
                if(path[next] != -1){
                    residual_net[next][path[next]] += pathFlow;
                    residual_net[path[next]][next] -= pathFlow;
                    //update flow in adj matrix
                    adj_matrix[path[next]][next].flow += pathFlow;
                }
                next = path[next];
            }
            max_flow += pathFlow;
        }
        void flowNetwork(int start, int end){
            //first, initialize residual graph using adjacency matrix's capacity
            init_residual();
            //later on, using residual network to run bfs
            while(BFS(start, end)){
                //using residual graph to do BFS
                update_residual(start, end);
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
    int n = 0;
    char file[200] = ""; //to reverse the power
    cin.getline(file, 200);
    n = getNum(file);
    Graph graph = Graph(n);

    while(cin.getline(file, 200)){
        if(file[0] == -1)
            break;
        int source = 0; int destination = 0; int capacity = 0;
        
        int accumIndex = 0;//to indicate each number's beginning index
        for(int i = 1; i <= 3; i++){
            //get source, dest, and capacity
            char numChar[200] = "";
            int fileIndex = accumIndex;
            while((file[fileIndex] != '\t') && (file[fileIndex] != '\0' && (file[fileIndex] != 32))){
                //extract num(subString) from file array
                numChar[fileIndex - accumIndex] = file[fileIndex];
                fileIndex += 1;
            }
            accumIndex = fileIndex + 1;//since fileIndext points to the position of '\t' or '\0' when breaking loop
            if(i == 1){
                //source
                source = getNum(numChar);
            }
            else if (i == 2){
                destination = getNum(numChar);
            }
            else if(i == 3){
                capacity = getNum(numChar);
            }
        }
        graph.addEdge(source, destination, capacity);
    }
    
    graph.flowNetwork(0, n-1);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(graph.adj_matrix[i][j].capacity != 0){
                cout << "<" << i << "," << j << ">" << "\t" << graph.adj_matrix[i][j].flow << "\t" << graph.adj_matrix[i][j].capacity << endl;
            }
        }
    }
    cout << "total: " << graph.max_flow << endl;

    return 0;
}

