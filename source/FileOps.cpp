#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

void LoadFromFile();
string LoadLine(ifstream& file, string str);
void SaveToFile();

int main()
{
  LoadFromFile();
  system("pause");
  return 0;
}

void LoadFromFile()
{
  ifstream file;
  string fn, sn, ad, age, name, f2, f3, f4, f5, f6;
  file.open("InputData.txt");
  if (file.good())
  {
    string f = LoadLine(file, fn);
    int i_hex = stoi(f, nullptr, 16);
    int i_dec = stoi(f, nullptr, 10);
    cout << i_hex << endl;
    cout << i_dec << endl;
  }
  else cout << "Nie uzyskano dostepu do pliku\n";
}

string LoadLine(ifstream& file, string str) 
{
  getline(file, str, '#');
  //cout << str << endl;
  size_t str_begin = str.find_first_of(":");
  str.erase(0, str_begin + 1);
  //cout << str << endl;
  return str;
}

void SaveToFile()
{
  ofstream file;
  file.open("OutputData.txt", ios::trunc);
  if (file.good())
  {
    file.close();
  }
  else cout << "Nie uzyskano dostepu do pliku\n";
}
