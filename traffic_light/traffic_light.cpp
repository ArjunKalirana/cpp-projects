#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

void redLight(){
    system("Color 0C");
    for(int i=5;i>0;i--){
        system("cls");
        cout << "🔴 RED light - STOP" << endl;
        cout<< "⌛ " << i<< " seconds remaining..."<<endl;
        Beep(523,1000);
    
    }
}
void greenLight(){
    system("Color 0A");
    for (int i = 4; i >= 1; i--) {
        system("cls");
        cout << "🟢 GREEN light - GO" << endl;
        cout << "⏳ " << i << " seconds remaining..." << endl;
        Beep(784,1000);
    }
}

void yellowLight(){
    for (int i = 3; i >= 1; i--) {
        system("cls");
        cout << "🟡 YELLOW light - WAIT" << endl;
        cout << "⏳ " << i << " seconds remaining..." << endl;
        Beep(659,1000);
    }

}


int main(){
    SetConsoleOutputCP(CP_UTF8);
    int cycles=3;

    for (int i = 1; i <= cycles; i++) {
        
        redLight();
        yellowLight();
        greenLight();
        
    }

    system("cls");
    cout <<" Traffic simulation ended after " << cycles <<" cycles." <<endl;
    
    return 0;
}
