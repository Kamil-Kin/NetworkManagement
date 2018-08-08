#include "Name.h"

using std::ofstream;
using std::ios;
using std::hex;
using std::stoi;
using std::stof;

Name::Name() :TLV(m_NameType), m_FN(NULL), m_SN(NULL), m_AD(NULL), m_AGE(NULL), m_STRUCT(NULL)
{
  LoadValuesFromFile();  
  
  m_Value = ValueToBytes();
  encodeLength();
  encodeTLV();
}
Name::~Name() {}

vector<byte> Name::ValueToBytes() 
{
  vector<byte> NameValue;
  vector<byte> FieldValue;

  FieldValue = m_FN->GetMessage();     AddToName(NameValue, FieldValue);
  FieldValue = m_SN->GetMessage();     AddToName(NameValue, FieldValue);
  FieldValue = m_AD->GetMessage();     AddToName(NameValue, FieldValue);
  FieldValue = m_AGE->GetMessage();    AddToName(NameValue, FieldValue);
  FieldValue = m_STRUCT->GetMessage(); AddToName(NameValue, FieldValue);

  return NameValue;
}

void Name::AddToName(vector<byte> &NameValue, vector<byte> &FieldValue) 
{
  NameValue.insert(NameValue.end(), FieldValue.begin(), FieldValue.end());
}

void Name::LoadValuesFromFile() 
{
  string fn, sn, ad, name, f2, f5;
  int age, f3;
  float f4;
  vector<int> f6;

  ifstream infile;
  infile.open("InputMessage.txt");
  if (infile.good() == true) 
  {
    fn   = LoadLine(infile);
    sn   = LoadLine(infile);
    ad   = LoadLine(infile);
    age  = stoi(LoadLine(infile));
    name = LoadLine(infile);
    f2   = LoadLine(infile);
    f3   = stoi(LoadLine(infile));
    f4   = stof(LoadLine(infile));
    f5   = LoadLine(infile);
    f6   = LoadElem(infile);

    infile.close();
  }
  else std::cout << "Nie uzyskano dostepu do pliku" << std::endl;

  m_FN     = new OctetString(fn.c_str(), 0x68);
  m_SN     = new OctetString(sn.c_str(), 0x69);
  m_AD     = new OctetString(ad.c_str(), 0x6a);
  m_AGE    = new Integer(age);
  m_STRUCT = new Order(name, f2, f3, f4, f5, f6);
}

string Name::LoadLine(ifstream& file)
{
  string str;
  getline(file, str, '#');  //cout << str << endl;
  size_t str_begin = str.find_first_of(":");
  str.erase(0, str_begin + 1);  //cout << str << endl;
  return str;
}

vector<int> Name::LoadElem(ifstream& file)
{
  string str;
  string substring;
  vector<int> val;
  getline(file, str, '#');  //std::cout << str << std::endl;
  size_t str_begin = str.find_first_of(":");
  str.erase(0, str_begin + 1);  //std::cout << str << std::endl;
  do
  {
    //std::cout << str << std::endl;
    size_t space = str.find_first_of(" ");
    substring.clear();
    substring = str.substr(0, space); //std::cout << substring << std::endl;
    val.push_back(stoi(substring));
    str.erase(0, space + 1);  //std::cout << str << std::endl;
  } while (!str.empty());
  //for (size_t i = 0; i < val.size(); ++i) std::cout << val[i] << ":"; //http://cpp.sh/3cueh
  return val; 
}

void Name::SaveToFile() 
{
  ofstream outfile;
  outfile.open("BERMessage.txt");

  if (outfile.good() == true) 
  {
    outfile.flush();
    for (size_t i = 0; i < m_Message.size(); ++i)
      outfile << hex << static_cast<int>(m_Message[i]) << " ";
    for (size_t i = 0; i < m_Message.size(); ++i)
      std::cout << hex << static_cast<int>(m_Message[i]) << " ";
    outfile.close(); 
  }
  else std::cout << "Nie uzyskano dostepu do pliku" << std::endl;
}
