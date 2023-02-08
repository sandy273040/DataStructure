#include<iostream>
#include<vector>
using namespace std;

int main(){
    int day = 0; int temp_price = 0; vector<int> price;
    cout << "總天數: "; cin >> day; cout << endl;
    cout << "每一天的價格: ";
    for(int i = 0; i < day; i++){
        cin >> temp_price;
        price.push_back(temp_price);
    }
    cout << endl;

    int profit = 0;
    for(int i = 0; i < day; i++){
        for(int j = i + 1; j < day; j++){
            if(price[i] - price[j] < 0){//有正收益
                if(-(price[i] - price[j]) > profit){
                    profit = -(price[i] - price[j]);
                }

            }
        }
    }
    cout << "獲利 " << profit << " 元" << endl;
    return 0;
}