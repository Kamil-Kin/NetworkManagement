#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
using namespace std;

void LoadFromFile();
string LoadLine(ifstream& file);
vector<int> LoadElem(ifstream& file);
void SaveToFile();

int main()
{
  LoadFromFile();
  SaveToFile();
  system("pause");
  return 0;
}

void LoadFromFile()
{
  ifstream file;
  file.open("InputData.txt");
  if (file.good())
  {
    string fn      = LoadLine(file);
    string sn      = LoadLine(file);
    string ad      = LoadLine(file);
    int age        = stoi(LoadLine(file));
    string name    = LoadLine(file);
    string f2      = LoadLine(file);
    int f3         = stoi(LoadLine(file));
    float f4       = stof(LoadLine(file));
    string f5      = LoadLine(file);
    vector<int> f6 = LoadElem(file);
    //cout << fn << "\n" << sn << "\n" << ad << "\n" << age << "\n" << name << "\n"
    //  << f2 << "\n" << f3 << "\n" << f4 << "\n" << f5 << "\n";
    //for (int i = 0; i < f6.size(); ++i) 
    //{
    //  cout << f6.at(i) << " ";
    //}
    //cout << endl;
  }
  else cout << "Nie uzyskano dostepu do pliku\n";
}

string LoadLine(ifstream& file)
{
  string str;
  getline(file, str, '#');  //cout << str << endl;
  size_t str_begin = str.find_first_of(":");
  str.erase(0, str_begin + 1);  //cout << str << endl;
  return str;
}
vector<int> LoadElem(ifstream& file)
{
  string str;
  string substring;
  vector<int> val;
  getline(file, str, '#');  //cout << str << endl;
  size_t str_begin = str.find_first_of(":");
  str.erase(0, str_begin + 1);  //cout << str << endl;
  do 
  {
    cout << str << endl;
    size_t space = str.find_first_of(" ");
    substring.clear();
    substring = str.substr(0, space);
    val.push_back(stoi(substring));
    str.erase(0, space + 1);
  } 
  while (!str.empty());
  for (size_t i = 0; i < val.size(); ++i)
    cout << val[i] << " ";
  return val; //http://cpp.sh/3cueh
}

 void SaveToFile()
{
  ofstream file;
  file.open("OutputData.txt", ios::trunc);
  if (file.good())
  {
    file << "blabalba";
    file.close();
  }
  else cout << "Nie uzyskano dostepu do pliku\n";
}
