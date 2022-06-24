// Конечный автомат поиска в строке email адресов

#include <iostream>
#include <vector>
#include <string>

using namespace std;
vector<vector<int>> states = {
        {1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 2, 0},
        {2, 0, 3, 0, 0, 0},
        {4, 0, 0, 0, 0, 0},
        {4, 5, 5, 5, 5, 5},
        {1, 1, 0, 0, 0, 0}
};
string email = "";
int state = 0;
void state_machine(char sym) {
    if (isalpha(sym))
        state = states[state][0];
    else if (isdigit(sym))
        state = states[state][1];
    else if (sym == '.')
        state = states[state][2];
    else if (sym == '_' || sym == '-')
        state = states[state][3];
    else if (sym == '@')
        state = states[state][4];
    else
        state = states[state][5];
    if (state == 0)
        email = "";
    else if (state == 5) {
        cout << email << endl;
        email = "";
    }
    else
        email += sym;
}

int main() {
    setlocale(0, "");
    string string = "wwwwwqqqqq_r@mail.ru iiiii fghfgh_s@gmail.com rtyrty rty@rty. rtrtrtrt@gmail.com rty 11678rtyrty@mail.ru cvcvxxcv345_s2@gmail.com";
    cout << "Исходная строка:" << endl;
    cout << string << endl << endl;
    cout << "Emails:" << endl;
    for (int i = 0; i < string.length(); i++)
        state_machine(string[i]);
    if (state == 4)
        cout << email;
    cout << endl;
    return 0;
}
