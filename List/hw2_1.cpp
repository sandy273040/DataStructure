#include<iostream>
using namespace std;

struct node{
    char charac;
    node* left; 
    node* right;
};
struct element{
    char data;
    int num;
    element* next;
};

int count(node* first){
    int counter = 0;
    while(first){
        counter += 1;
        first = first->right;
    }
    return counter;
}
void PrintList(node* head){
    if(!head){
        cout << "Empty List" << endl;
    }
    else{
        node* go = head;
        while(go){
            cout << go->charac << " ";
            go = go->right;
        }
        cout << endl;
    }
}

node* InsertNode(node* head, char data, int pos){
    node* p = nullptr; node* find = nullptr;
    if(!((32 <= data) && (data <= 126) )){
        cout << "Insert wrong data" << endl;
    }
    else{
        if(!head){//list empty
            if(pos == 0){
                //insert first node
                p = new node; p->charac = data;  p->left = nullptr; p->right = nullptr;
                head = p;
                //return head;
            }
            else{
                cout << "Insert wrong position" << endl;
            }
        }
        else{//non empty list
            if(pos == 0){
                //insert into the non-empty list as the first node
                p = new node; p->charac = data;  p->left = nullptr; p->right = head;
                head->left = p; head = p;
                //return head;
            }
            else{
                //not the first node
                //check pos is not out of range
                int length = count(head);
                if((pos >= 0) && (pos <= length)){
                    find = head;
                    for(int i = 0; i < pos; i++){
                        //find pos node when the inserted node is not the last one
                        if(find->right != nullptr)
                            find = find->right;
                    }
                    //find now points to pos node
                    if(find->right == nullptr){
                        // as the last node
                        p = new node; p->charac = data;  p->left = find; p->right = nullptr;
                        find->right = p;

                    }
                    else{
                        p = new node; p->charac = data;  p->left = find->left; p->right = find;
                        (find->left)->right = p; find->left = p;
                    }
                    
                }
                else{
                    cout << "Insert wrong position" << endl;
                }
                

            }

        }
    }
    return head;
}

node* DeleteNode(node* head, int pos){
    node* find = nullptr;
    if(!head){
        //list empty
        cout << "Linked list is empty" << endl;
    }
    else{
        int length = count(head);//count the length of list
        if((0 <= pos) && (pos < length)){
            //pos range ok
            if(length == 1){
                //only one node
                delete head;
                head = nullptr;
            }
            else{
                if(pos == 0){
                    //delete the first node
                    find = head;
                    head = head->right;
                    head->left = find->left;
                    delete find; find = nullptr;
                }
                else{
                    find = head;
                    for(int i = 0; i < pos; i++){
                        if(find->right != nullptr)
                            find = find->right;
                    }
                    (find->left)->right = find->right;
                    if((find->right) != nullptr){
                        (find->right)->left = find->left;
                    }
                    delete find; find = nullptr;
                }
            }
        }
        else{
            //pos out of range
            cout << "Delete wrong position" << endl;
        }
    }
    return head;
}

node* DeleteData(node* head, char data){
    node* find = head; node* next = nullptr; node* counter = head;
    node* progress = head;
    int index = 0;
    if(head == nullptr){
        cout << "Linked list is empty" << endl;
    }
    else{
        if((32<= data) && (data <= 126)){
            while(find != nullptr){
                if(find->charac == data){
                    //data found
                    //restore the progress, delete the node, and resume
                    if(find->left != nullptr){
                        //not the first node
                        progress = find->left;
                        (find->left)->right = find->right;
                        if((find->right) != nullptr){
                            (find->right)->left = find->left;
                        }
                        delete find; find = progress;
                    }
                    else{
                        //the first node
                        find = head;
                        if(head->right != nullptr){
                            //more than one node
                            head = head->right;
                            head->left = find->left;
                            delete find; find = head; progress = head;
                        }
                        else{
                            //only one node
                            head = nullptr;
                        }
                        
                    }
                }
                //next round
                if(find->right != nullptr){
                    find = find->right;
                }
                else{
                    break;
                }
            }
        }
        else{
            cout << "Delete wrong data" << endl;
        }
        
    }
    return head;
}

void NumOfOccur(node* head, char data){
    node* find = head; int counter = 0;
    if(count(head) == 0){
        cout << "Link list is empty" << endl;
    }
    else{
        if((32 <= data) && (data <= 126)){
            while(find != nullptr){
                if(find->charac == data){
                    counter += 1;
                }
                if((find->right) != nullptr){
                    find = find->right;
                }
                else{
                    break;
                }
        
            }
            cout << counter << endl;
        }
        else{
            cout << "Search wrong data" << endl;
        }
        
    }
}

void MaxNumOfOccur(node* head){
    node* find = head; 
    element* head_count = new element; head_count->data = ' '; head_count->num = -1; head_count->next = nullptr;
    element* element_find = head_count;
    element* previous = head_count;
    element* counter = head_count; int max = 0; int flag = 0;

    if(head == nullptr){
        cout << "Linked list is empty" << endl;
    }
    else{
        while(find != nullptr){
            element_find = head_count;
            while(element_find != nullptr){
                if(find->charac == element_find->data){
                    //data already exists
                    element_find->num += 1;
                    break;
                }
                else{
                    if(element_find->next != nullptr){
                        element_find = element_find->next;
                    }
                    else{
                        //the end of element list  
                        //data not found in element list, insert at the beginning
                        element* p = new element;
                        p->data = find->charac; p->num = 1; p->next = head_count->next;
                        head_count->next = p;
                        break;
                    }
                    
                }
                
            }
            if(find->right != nullptr){
                find = find->right;
            }
            else{
                break;
            }
        }
        while(counter != nullptr){
            //find out max num among element list
            if(counter->num > max){
                max = counter->num;
            }
            if(counter->next != nullptr){
                counter = counter->next;
            }
            else{
                break;
            }
        }
        element_find = head_count->next;
        while(element_find != nullptr){
            //print the node data with max count
            if(element_find->num == max){
                cout << element_find->data << " ";
            }
            if(element_find->next != nullptr){
                element_find = element_find->next;
            }
            else{
                break;
            }
        }
        cout << endl;
    }
}

void SearchWord(node* head, char* word){
    if(head == nullptr){
        cout << "Linked list is empty" << endl;
    }
    else{
        int org_size = 0;
        int size = 0; char* char_size = &word[0]; node* find = head;
        org_size = count(head); int i = 0;
        while(*char_size != '\0'){
            //size of word
            size += 1;
            char_size ++;
        }
        while(find != nullptr){
            //running loop based on linked list
            if(find->charac == word[i]){
                i += 1;
                if(i >= size){
                    cout << "found" << endl;
                    return;
                }
            }
            if(find->right != nullptr){
                find = find->right;
            }
            else{
                cout << "Not found" << endl;
                return;
            }
        }

    }
}

int main(){
    char file[200];
    char func[20];
    char rep_word = '0'; int rep_pos = 0; char rep_arr[20];
    node* result = nullptr;
    while(cin.getline(file, 200)){
        if(file[0] == -1)
            break;

        int i = 0;

        if(file[0] == 'I'){
            while(file[i] != ' '){
                func[i] = file[i];
                i++;
            }
            i++;
            while(file[i] != ' '){
                rep_word = file[i];
                i++;
            }
            i++;
            while(file[i] != '\0'){
                rep_pos = file[i] - 48;
                i++;
            }
            result = InsertNode(result, rep_word, rep_pos);
        }
        else if(file[0] == 'D'){
            if(file[6] == 'N'){
                while(file[i] != ' '){
                    func[i] = file[i];
                    i++;
                }
                i++;
                while(file[i] != '\0'){
                    rep_pos = file[i] - 48;
                    i++;
                }
                result = DeleteNode(result, rep_pos);

            }
            else if(file[6] == 'D'){
                while(file[i] != ' '){
                    func[i] = file[i];
                    i++;
                }
                i++;
                while(file[i] != '\0'){
                    rep_word = file[i];
                    i++;
                }
                result = DeleteData(result, rep_word);
                
            }

        }
        else if(file[0] == 'P'){
            while(file[i] != '\0'){
                func[i] = file[i];
                i++;
            }
            PrintList(result);
        }
        else if(file[0] == 'N'){
            while(file[i] != ' '){
                func[i] = file[i];
                i++;
            }
            i++;
            while(file[i] != '\0'){
                rep_word = file[i];
                i++;
            }
            NumOfOccur(result, rep_word);
            
        }
        else if(file[0] == 'M'){
            while(file[i] != '\0'){
                func[i] = file[i];
                i++;
            }
            MaxNumOfOccur(result);
            
        }
        else if(file[0] == 'S'){
            while(file[i] != ' '){
                func[i] = file[i];
                i++;
            }
            i++;
            int j = 0;
            while(file[i] != '\0'){
                rep_arr[j] = file[i];
                i++; j++;
            }
            SearchWord(result, rep_arr);
            
        }
    }

    return 0;
    
}