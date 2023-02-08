#include<iostream>
using namespace std;

struct node{
    int num;
    int coin;
    int time;
    node* next;

};

void insert_node(node* head, int num, int time, int coin){
    if(head == nullptr){
        node* next_node = new node;
        next_node->num = num;
        next_node->time = time;
        next_node->coin = coin;
        head = next_node;
    }
    else{
        node* next_node = new node;
        next_node->num = num;
        next_node->time = time;
        next_node->coin = coin;
        
        node* find = head;
        if((head->next) == nullptr){
            if(next_node -> time < head->time){
                next_node->next = head;
                head = next_node;
            }
         
            else if((next_node -> time) == head->time){
                if((next_node->num) < head->num){
                    next_node->next = head;
                    head = next_node;
                }
                else{
                    next_node->next = head->next;
                    head->next = next_node;
                }
                
            }
            else{
                next_node->next = head->next;
                head->next = next_node;
            }

        }


        else{
            while(((find->next) != nullptr) && ((next_node->time) > (find->next)->time)){
              find = find->next;
            }
            if((next_node->time) == (find->time)){
                if((next_node->num) < (find->num)){
                    node* find2 = head;
                    while((find2->next) != find){
                        find2 = find2 -> next;
                    }
                    next_node->next = find;
                    find2->next = next_node;
                }
                else{
                    next_node->next = find->next;
                    find->next = next_node;
                }
            }
            else{
                next_node->next = find->next;
                find->next = next_node;
            }
        }
    }
}

int main(){
    int time = 0;//起始時間
    int arrTime[5] = {};
    int eachCoin[5] = {};

    cout << "輸入五人到達時間\n";
    for(int i = 0; i < 5; i++){
        cin >> arrTime[i];
    }
    cout << "輸入五人持有硬幣\n";
    for(int i = 0; i < 5; i++){
        cin >> eachCoin[i];
    }
    node* n0 = new node; n0->num = 0; n0->time = arrTime[0]; n0->coin = eachCoin[0];
    node* n1 = new node; n1->num = 1; n1->time = arrTime[1]; n1->coin = eachCoin[1];
    node* n2 = new node; n2->num = 2; n2->time = arrTime[2]; n2->coin = eachCoin[2];
    node* n3 = new node; n3->num = 3; n3->time = arrTime[3]; n3->coin = eachCoin[3];
    node* n4 = new node; n4->num = 4; n4->time = arrTime[4]; n4->coin = eachCoin[4];
    n4->next = nullptr; n3->next = n4; n2->next = n3; n1->next = n2; n0->next = n1; node* head = n0;
    node* operation = nullptr; int none = 0;

    while((head != nullptr) || (operation != nullptr)){
        if(none == 0){
            if(operation != nullptr){
                delete operation;
                operation = nullptr;
            }
            operation = head;
            head = head->next;
        }
        none = 0;

        if(operation->time <= time){
            if((operation->coin) >= 2){
                printf("time: %-10d", time);
                printf("%s %d \n", "player: ", operation->num);
                time += 1;
                operation->coin -= 1;
                printf("time: %-10d", time);
                printf("%s %d \n", "player: ", operation->num);
                time += 1;
                operation->coin = operation->coin - 1;
                operation->time = time;
                if((operation -> coin) != 0){
                    insert_node(head, operation->num, operation->time, operation->coin);
                }
            
            }
            else if((operation->coin) == 1){
                printf("time: %-10d", time);
                printf("%s %d \n", "player: ", operation->num);
                time += 1;
                operation->coin = operation->coin - 1;
                operation->time = time;
            }
        }
        else{
            printf("time: %-10d", time);
            printf("%s %s \n", "player: ", "none");
            time += 1;
            none = 1;
        }
    }
    return 0;
}