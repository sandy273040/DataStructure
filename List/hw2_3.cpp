#include<iostream>
#include<string>
using namespace std;

struct node{
    int car_number;
    //node* left; 
    node* right;
};
int check = 0;

void print(node* head){//deletable
    node* find = head;
    while(find){
        cout << find->car_number << " ";
        find = find->right;
    }
    cout << endl;
}

int count(node* head){
    int counter = 0;
    node* find = head;
    while(find){
        counter += 1;
        find = find->right;
    }
    return counter;
}

int ten_exp(int n){
    int i = 0; int res = 1;
    if(n == 0)
        return 1;
    else{
        while(i < n){
            res *= 10;
            i++;
        }
        return res;
    }
}

node* insert_front(node* head, int this_car){
    node* find = head; node* p = nullptr;
    if(head == nullptr){
        //empty list
        p = new node; p->car_number = this_car; p->right = nullptr;
        head = p;
    }
    else{
        p = new node; p->car_number = this_car; p->right = head;
        head = p;
    }
    return head;
}

node* re_enter(node* head, int num){
    //find the car num, delete and re-enter
    node* find = head; node* target = nullptr; int step = -2;
    while(find != nullptr){
        if(find ->car_number == num){
            step += 1;
            break;
        }
        else{
            if(find ->right != nullptr){
                step += 1;
                find = find ->right;
            }
            else{
                cout << "This car is not in the garage." << endl;
                check = 1;
                return head;
            }
        }
    }
    target = find; find = head; int i = 0;
    //run step times of loop to find the previous node
    if(step < 0) find = target;
    while(i < step){
        find = find->right;
        i++;
    }//find now points to the node in front of target
    //step == -1 means target is the first node; step == 0 means target is the second node

    //logical deletion
    if(find == target){
        //target is the first node
        if(target->right == nullptr){
            //target is the only node
            head = nullptr;
        }
        else{
            head = target->right;
        }
        
    }
    else{
        //target is not the first node
        find->right = target->right;
    }

    head = insert_front(head, target->car_number);
    return head;

}

node* buy_new(node* head, int new_car){
    //delete the last one, and insert the new car to the front
    node* target = head; node* find = head; node* previous = head;

    //delete the last node
    while(find->right != nullptr){
        find = find->right;
    }//last node
    while(previous->right != find){
        previous = previous->right;
    }//the node before find
    previous->right = nullptr;

    //insert the new node
    head = insert_front(head, new_car);
    return head;
}

int main(){
    string str = " "; int str_size = 0; int num = 0; node* main_list = nullptr; int drive_car = 0;
    getline(cin, str); str_size = str.length() - 1;
    int i = 0;
    while(str[i] != '\0'){
        num = num + ((str[i]-48) * ten_exp(str_size));
        str_size -= 1;
        i++;
    }
    cout << "The size of garage is " << num << endl;

    
    int car_no = 0;
    
    while(getline(cin, str)){
        if(str[0] == -1){
            break;
        }
        
        if(str[0] == 'b'){
            //situation: buy
            if(count(main_list) == num){
                //delete front, and insert buy, int drive = 0, insert new node
                main_list = buy_new(main_list, car_no);
                print(main_list);
                car_no += 1;
            }
            else{
                //not full
                main_list = insert_front(main_list, car_no);
                print(main_list);
                car_no += 1;

            }
        }
        else if(str[0] == 'd'){
            //situation: drive

            //find the car
            str_size = str.length() - 6 - 1;
            i = 6; drive_car = 0;
            while(str[i] != '\0'){
                drive_car = drive_car + ((str[i]-48) * ten_exp(str_size));
                str_size -= 1;
                i++;
            }
            main_list = re_enter(main_list, drive_car);
            if(check != 1)
                print(main_list);
            check = 0;
        }
    }
    return 0;
}