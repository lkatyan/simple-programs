// Программа считывает текст из файла, удаляет все повторяющиеся пробелы и 
// записывает в тот же файл измененный текст

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
void del_sps(string& str)
{
    for (string::iterator it = str.begin(); it != str.end(); it++)
    {
        string::iterator begin = it;
        if (*it == '.') it++;
        else {
            while (it != str.end() && ::isspace(*it))it++;
            if (it - begin > 1)
                it = str.erase(begin + 1, it) - 1;
        }
    }
    for (string::reverse_iterator it = str.rbegin(); it != str.rend(); it++)
    {
        if (*it == '.') {
                it++;
                    while (it != str.rend() && ::isspace(*it)) { it = decltype(it)(str.erase(std::next(it).base())) - 1; it++; }
                    it--;
        }
    }
}

void Solve()
{
	vector<string> str;
    ifstream f;
	string s;
    f.open("D:\\pp.txt");
    while (!f.eof())
    {
		getline(f, s);
		str.emplace_back(s);
    }
    f.clear();
	f.close();
	
	ofstream f2;
	f2.open("D:\\pp.txt");
    for (auto it = str.begin(); it != str.end(); ++it)
    {
        del_sps(*it);
        f2 << *it << endl;
    }
    f2.close();
}
int main()
{
	setlocale(0, "");
	Solve();
    cout << "Mission completed" << endl;
	return 0;
}