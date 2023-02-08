#include<iostream>
using namespace std;

struct node{
    int digit;
    int exp;
    node* next;
    node* left;
};

void print(node* head){
    //stil need to deal with zero beginning situation*****
    node* find = head;
    while(find != nullptr){
        if(find->digit == 45){
            cout << (char)find->digit;
        }
        else{
            cout << find->digit;
        }
        if(find->next != nullptr){
            find = find->next;
        }
        else{
            break;
        }
    }
}

void left_print(node* head){//可以刪
    //for checking overflow of node->digit
    node* find = head;
    while(find != nullptr){
        if(find->next != nullptr){
            find = find->next;
        }
        else{
            break;
        }
    }
    while(find != nullptr){
        if(find->left != nullptr){
            cout << find->digit << endl;
            find = find->left;
        }
        else{
            cout << find->digit << endl;
            break;
        }
    }
}

void print_num(node* head){
    node* find = head; node* accum_zero = nullptr;
    if(find->digit == 45){
        cout << (char)find->digit;
        if(find->next != nullptr){
            find = find->next;
        }
    }
    if(find->digit == 0){
        //first digit
        accum_zero = find;
        if(find->next != nullptr){
            find = find->next;
        }
    }
    
    while(find != nullptr){
        if(find->digit == 0){
            if(find->left != accum_zero)
                cout << find->digit;
            else
                accum_zero = find;
        }
        else
            cout << find->digit;

        if(find->next != nullptr){
            find = find->next;
        }
        else{
            break;
        }
    }
}

node* make_node(int number){
    //produce node
    int exp = 0;
    node* previous = nullptr; node* n;
    if((number == 45) || (number == 43)){
        //negative number or operator
        n = new node;
        n->digit = number; n->next = nullptr; n->left = nullptr;
        return n;
    }
    else{
        //positive number
        n = new node;
        n->digit = number; n->next = nullptr; n->left = nullptr;
        return n;
    }
}

int compare(node* a, node* b, int count1, int count2){
    //compare the two lists and return the bigger list's index
    node* find1 = a; node* find2 = b;
    if(count1 > count2){
        return 1;
    }
    else if(count1 < count2){
        return 2;
    }
    else{
        //same length
        while((find1->next != nullptr) && (find2->next != nullptr)){
            if(find1->digit == 45){
                find1 = find1->next;
            }
            if(find2->digit == 45){
                find2 = find2->next;
            }

            if(find1->digit > find2->digit){
                return 1;
            }
            else if(find1->digit < find2->digit){
                return 2;
            }
            else{
                if(find1->next != nullptr)
                    find1 = find1->next;
                if(find2->next != nullptr)
                    find2 = find2->next;
            }
        }

        if(find1->digit > find2->digit){
            return 1;
        }
        else if(find1->digit < find2->digit){
            return 2;
        }
        else{
            return 0;
        }
    }
}

node* node_overflow(node* head){
    //deal with overflow(not within 0 to 9) within a node
    int carry = 0;
    node* find = head; node* p = nullptr;
    while(find != nullptr){
        if(find->next != nullptr){
            find = find->next;
        }
        else{
            break;
        }
    }//find tail using find

    while((find->left != nullptr) && ((find->left)->digit != 45)){
        if(find->left != nullptr){
            find->digit = find->digit + carry;
            carry = 0;
            if(find->digit > 9){
                //overflow
                carry = 1;
                find->digit = find->digit - 10;
            }
            find = find->left;
        }
    }

    //deal with the last node
    find->digit = find->digit + carry;
    carry = 0;
    if(find->digit > 9){
        //overflow
        carry = 1;
        find->digit = find->digit - 10;
    }

    //check carry out
    if(carry == 1){
        p = new node;
        p->digit = carry;
        p->exp = find->exp + 1;
        if(find->left == nullptr){
            //insert into the head of the list
            p->next = find; p->left = nullptr;
            find->left = p;
            head = p;
        }
        else{
            //insert into the second of the list(behind '-')
            p->next = find; p->left = find->left;
            (find->left)->next = p;
            find->left = p;
        }
    }
    return head;
    
}

node* node_underflow(node* head){
    //deal with overflow(not within 0 to 9) within a node: scan left to right
    node* find = head; node* borrow = nullptr;

    if((find->digit == 45) && (find->next != nullptr)){
        find = find->next;
    }

     while(find != nullptr){
        if(find->digit < 0){
            borrow = find->left;
            while(borrow != nullptr){
                if(borrow->digit > 0){
                    borrow->digit = borrow->digit - 1;
                    borrow = borrow->next;
                    while(borrow != find){
                        borrow->digit += 9;
                        borrow = borrow->next;
                    }
                    find->digit += 10;
                    break;
                        
                }
                if(borrow->left != nullptr){
                    borrow = borrow->left;
                }
                else{
                    break;
                }
            }
        }

        if(find->next != nullptr){
            find = find->next;
        }
        else{
            break;
        }
    }
    return head;
}

node* add(node* a, node* b, int negative){
    //if negative == 1, print '-'
    //input two lists to "add/minus" together
    node* a_run = a; node* b_run = b;
    node* output = nullptr; 
    node* p = nullptr; node* previous = nullptr;

    if(a_run->exp == -2){
        a_run = a_run->next;
    }
    if(b_run->exp == -2){
        b_run = b_run->next;
    }

    while((a_run != nullptr) && (b_run != nullptr)){
        //a and b do not run out of list
        if(a_run->exp == b_run->exp){
            //if exp is the same, add to output list
            p = new node;
            p->digit = a_run->digit + b_run->digit;
            p->exp = a_run->exp; p->next = nullptr; p->left = nullptr;

            if(output == nullptr){
                previous = p; output = p;
            }
            else{
                previous->next = p; p->left = previous;
                previous = p;
            }

            // a and b both moves forward
            if(a_run->next != nullptr){
                a_run = a_run->next;
            }
            else{
                a_run = nullptr;
            }
            if(b_run->next != nullptr) {
                b_run = b_run->next;
            }
            else{
                b_run = nullptr;
                break;
            }

        }
        else if(a_run->exp > b_run->exp){
            //a exp larger, a digit to output and go to next
            p = new node;
            p->digit = a_run->digit;
            p->exp = a_run->exp; p->next = nullptr; p->left = nullptr;
            if(output == nullptr){
                previous = p; output = p;
            }
            else{
                previous->next = p; p->left = previous;
                previous = p; 
            }

            if(a_run->next != nullptr){
                a_run = a_run->next;
            }
            else{
                a_run = nullptr;
                break;
            }
            
        }
        else{
            //b exp larger, b digit output and go to next
            p = new node;
            p->digit = b_run->digit;
            p->exp = b_run->exp; p->next = nullptr; p->left = nullptr;
            if(output == nullptr){
                previous = p; output = p;
            }
            else{
                previous->next = p; p->left = previous;
                previous = p;
            }

            if(b_run->next != nullptr){
                b_run = b_run->next;
            }
            else{
                b_run = nullptr;
                break;
            }
        }
    }
    while((a_run != nullptr) && (b_run == nullptr)){
        //only list a remains, copy to output
        p = new node;
        p->digit = a_run->digit;
        p->exp = a_run->exp; p->next = nullptr; p->left = nullptr;
        if(output == nullptr){
            previous = p; output = p;
        }
        else{
            previous->next = p; p->left = previous;
            previous = p;
        }

        if(a_run->next != nullptr){
            a_run = a_run->next;
        }
        else{
            a_run = nullptr;
            break;
        }
    }
    while((b_run != nullptr) && (a_run == nullptr)){
        //only lisit b remains, copy to output
        p = new node;
        p->digit = b_run->digit;
        p->exp = b_run->exp; p->next = nullptr; p->left = nullptr;
        if(output == nullptr){
            previous = p; output = p;
        }
        else{
            previous->next = p; p->left = previous;
            previous = p;
        }

        if(b_run->next != nullptr){
            b_run = b_run->next;
        }
        else{
            b_run = nullptr;
            break;
        }
    }

    if(negative == 1){
        p = new node;
        p->digit = 45;
        p->exp = -2; p->next = output; p->left = nullptr;
        output->left = p; output = p;
    }
    return output;

}

node* list_minus(node* a, node* b, int negative){
    //if negative == 1, print '-'
    //input two lists to "add/minus" together
    node* a_run = a; node* b_run = b;
    node* output = nullptr; 
    node* p = nullptr; node* previous = nullptr;

    if(a_run->exp == -2){
        a_run = a_run->next;
    }
    if(b_run->exp == -2){
        b_run = b_run->next;
    }

    while((a_run != nullptr) && (b_run != nullptr)){
        //a and b do not run out of list
        if(a_run->exp == b_run->exp){
            //if exp is the same, add to output list
            p = new node;
            p->digit = a_run->digit - b_run->digit;
            p->exp = a_run->exp; p->next = nullptr; p->left = nullptr;

            if(output == nullptr){
                previous = p; output = p;
            }
            else{
                previous->next = p; p->left = previous;
                previous = p;
            }

            // a and b both moves forward
            if(a_run->next != nullptr){
                a_run = a_run->next;
            }
            else{
                a_run = nullptr;
            }
            if(b_run->next != nullptr) {
                b_run = b_run->next;
            }
            else{
                b_run = nullptr;
                break;
            }

        }
        else if(a_run->exp > b_run->exp){
            //a exp larger, a digit to output and go to next
            p = new node;
            p->digit = a_run->digit;
            p->exp = a_run->exp; p->next = nullptr; p->left = nullptr;
            if(output == nullptr){
                previous = p; output = p;
            }
            else{
                previous->next = p; p->left = previous;
                previous = p; 
            }

            if(a_run->next != nullptr){
                a_run = a_run->next;
            }
            else{
                a_run = nullptr;
                break;
            }
            
        }
        else{
            //b exp larger, b digit output and go to next
            p = new node;
            p->digit = b_run->digit;
            p->exp = b_run->exp; p->next = nullptr; p->left = nullptr;
            if(output == nullptr){
                previous = p; output = p;
            }
            else{
                previous->next = p; p->left = previous;
                previous = p;
            }

            if(b_run->next != nullptr){
                b_run = b_run->next;
            }
            else{
                b_run = nullptr;
                break;
            }
        }
    }
    while((a_run != nullptr) && (b_run == nullptr)){
        //only list a remains, copy to output
        p = new node;
        p->digit = a_run->digit;
        p->exp = a_run->exp; p->next = nullptr; p->left = nullptr;
        if(output == nullptr){
            previous = p; output = p;
        }
        else{
            previous->next = p; p->left = previous;
            previous = p;
        }

        if(a_run->next != nullptr){
            a_run = a_run->next;
        }
        else{
            a_run = nullptr;
            break;
        }
    }
    while((b_run != nullptr) && (a_run == nullptr)){
        //only lisit b remains, copy to output
        p = new node;
        p->digit = b_run->digit;
        p->exp = b_run->exp; p->next = nullptr; p->left = nullptr;
        if(output == nullptr){
            previous = p; output = p;
        }
        else{
            previous->next = p; p->left = previous;
            previous = p;
        }

        if(b_run->next != nullptr){
            b_run = b_run->next;
        }
        else{
            b_run = nullptr;
            break;
        }
    }

    if(negative == 1){
        p = new node;
        p->digit = 45;
        p->exp = -2; p->next = output; p->left = nullptr;
        output->left = p; output = p;
    }
    return output;
}

int main(){
    //三行input，一個數字一個數字接收成linked list until \n
    node* previous = nullptr;//point to the preceding node
    node* head1 = nullptr; node* head2 = nullptr;
    node* set_exp = nullptr; node* pr;
    int a = 1;
    int b = 5;
    node* p = make_node(b);
    int input; int num; int operate_sig; int count1 = -1; int count2 = -1;//minus \n
    int exp1 = 0; int exp2 = 0;


    do{
        input = (cin.get());
        if(input != 43 && input != 45)
            num = input - 48;
        else
            num = input;

        if((input != -1) && (input != 10)){
            p  = make_node(num);
            if(previous != nullptr){
                p->left = previous;
                previous->next = p;
            }
            else{
                head1 = p;
            }
            previous = p;
        }
        if((input != 43) && (input != 45))
            count1 += 1;
    }while(input != 10);

    //one while loop to set exp
    //list one
    set_exp = head1; exp1 = count1 - 1; //count1 -= 1;
    while(set_exp != nullptr){
        if((set_exp->digit != 43) && (set_exp->digit != 45)){
            set_exp->exp = exp1;
            exp1 -=1;
        }
        else{
            if(set_exp->digit == 43) {
                 set_exp->exp = -1;
            }
            else if(set_exp->digit == 45){
                set_exp->exp = -2;
            }
        }
        if((set_exp->next != nullptr) && (exp1 != 0)){
            set_exp = set_exp->next;
        }
        else{
            break;
        }
    }

    input = cin.get();

    while(input != 10){
        operate_sig = input;
        input = cin.get();
    }

    previous = nullptr;
    while(input != -1){
        input = (cin.get());
        if(input != 43 && input != 45)
            num = input - 48;
        else
            num = input;

        if((input != -1) && (input != 10)){
            p  = make_node(num);
            if(previous != nullptr){
                p->left = previous;
                previous->next = p;
            }
            else{
                //empty list
                head2 = p;
            }
            previous = p;
        }
        if((input != 43) && (input != 45))
            count2 += 1;
    }
    
    //one while loop to set exp
    //list two
    set_exp = head2; exp2 = count2 - 1; //count2 -= 1;
    while(set_exp != nullptr){
        if((set_exp->digit != 43) && (set_exp->digit != 45)){
            set_exp->exp = exp2;
            exp2 -=1;
        }
        else{
            if(set_exp->digit == 43) {
                 set_exp->exp = -1;
            }
            else if(set_exp->digit == 45){
                set_exp->exp = -2;
            }
        }
        if((set_exp->next != nullptr) && (exp2 != 0)){
            set_exp = set_exp->next;
        }
        else{
            break;
        }
    }

    if(operate_sig == 43){
        if((head1->exp == -2) && (head2->exp == -2)){
            pr = add(head1, head2, 1);
            pr = node_overflow(pr);
            print_num(pr);
        }
        else if((head1->exp != -2) && (head2->exp != -2)){
            pr = add(head1, head2, 0);
            pr = node_overflow(pr);
            print_num(pr);
        }
        
        //minus
        else if((head1->exp != -2) && (head2->exp == -2)){
            if(compare(head1, head2, count1, count2) == 1){
                pr = list_minus(head1, head2, 0);
                pr = node_underflow(pr);
                print_num(pr);
            }
            else if(compare(head1, head2, count1, count2) == 2){
                pr = list_minus(head2, head1, 1);
                pr = node_underflow(pr);
                print_num(pr);
            }
            else if(compare(head1, head2, count1, count2) == 0)
                cout << 0;
        }
        else if((head1->exp == -2) && (head2->exp != -2)){
            if(compare(head1, head2, count1, count2) == 2){
                pr = list_minus(head2, head1, 0);
                pr = node_underflow(pr);
                print_num(pr);
            }  
            else if(compare(head1, head2, count1, count2) == 1){
                pr = list_minus(head1, head2, 1);
                pr = node_underflow(pr);
                print_num(pr);
            }
            else if(compare(head1, head2, count1, count2) == 0)
                cout << 0;
        }

    }
    else if(operate_sig ==45){
        if((head1->exp == -2) && (head2->exp != -2)){
            //first num is neg
            pr = add(head1, head2, 1);
            pr = node_overflow(pr);
            print_num(pr);
            
        }
        else if((head1->exp != -2) && (head2->exp == -2)){
            pr = add(head1, head2, 0);
            pr = node_overflow(pr);
            print_num(pr);
        }

        //minus
        else if((head1->exp == -2) && (head2->exp == -2)){
            if(compare(head1, head2, count1, count2) == 2){
                pr = list_minus(head2, head1, 0);
                pr = node_underflow(pr);
                print_num(pr);
            }
            else if(compare(head1, head2, count1, count2) == 1){
                pr = list_minus(head1, head2, 1);
                pr = node_underflow(pr);
                print_num(pr);
            }
            else if(compare(head1, head2, count1, count2) == 0)
                cout << 0;
        }
        else if((head1->exp != -2) && (head2->exp != -2)){
            if(compare(head1, head2, count1, count2) == 1){
                pr = list_minus(head1, head2, 0);
                pr = node_underflow(pr);
                print_num(pr);
            }
            else if(compare(head1, head2, count1, count2) == 2){
                pr = list_minus(head2, head1, 1);
                pr = node_underflow(pr);
                print_num(pr);
            }
            else if(compare(head1, head2, count1, count2) == 0)
                cout << 0;
        }


    }
    return 0;
}