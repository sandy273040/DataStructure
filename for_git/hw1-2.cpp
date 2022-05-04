#include<iostream>
#include<vector>
using namespace std;

int main(){
    //char a[100] = {};
    string s; vector<char> stack; int error = 0;
    cout << "輸入字串";
    cin >> s;
    
    for(int i = 0; i < sizeof(s); i++){
        if(s[i] == '('){
            stack.push_back(s[i]);
        }
        else if(s[i] == ')'){
            if(stack.size() != 0){
                stack.pop_back();
            }
            else{
                error += 1;
            }
        }
    }

    while (stack.size() != 0){
        error += 1;
        stack.pop_back();
    }
    
    cout << "輸出" << endl;
    cout << error;
    

    return 0;
}