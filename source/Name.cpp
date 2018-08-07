#include "Name.h"

using std::ofstream;
using std::ios;

Name::Name() :TLV(m_NameType)
{
  m_FN     = NULL;
  m_SN     = NULL;
  m_AD     = NULL;
  m_AGE    = NULL;
  m_STRUCT = NULL;

  m_Value = ValueToBytes(); //todo
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
  ifstream infile;
  infile.open("InputMessage.txt");
  if (infile.good() == true) 
  {

    infile.close();
  }
  else std::cout << "Nie uzyskano dostepu do pliku" << std::endl;
}

string Name::LoadLineFromFile(ifstream& file, string name)  //todo
{
  string str;
  getline(file, str, '#');  //std::cout << str << std::endl;
  size_t str_begin = str.find_first_of(":");
  str.erase(0, str_begin + 1);  //std::cout << str << std::endl;
  return str;
}

void Name::SaveToFile() 
{
  ofstream outfile;
  outfile.open("BERMessage.txt", ios::out | ios::trunc);

  if (outfile.good() == true) 
  { 
    for (byte i = 0; i < m_Message.size(); ++i)
      outfile << m_Message[i];

    outfile.close(); 
  }
  else std::cout << "Nie uzyskano dostepu do pliku" << std::endl;
}
