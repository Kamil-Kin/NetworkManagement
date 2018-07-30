#include "Name.h"
#include <fstream>
#include <iostream>

using std::ifstream;
using std::ofstream;
using std::ios;


Name::Name() :TLV(m_NameType)
{
  m_FN     = NULL;
  m_SN     = NULL;
  m_AD     = NULL;
  m_AGE    = NULL;
  m_STRUCT = NULL;
}
Name::~Name() {}

vector<byte> Name::ValueToBytes() 
{
  vector<byte> NameValue;


  return NameValue;
}

void Name::LoadValuesFromFile() 
{
  ifstream file;
  file.open("InputData.txt");
  if (file.good() == true) 
  {


    file.close();
  }
  else std::cout << "Nie uzyskano dostepu do pliku" << std::endl;
}

void Name::SaveToFile() 
{
  ofstream file;
  file.open("BERMessage.txt", ios::out | ios::trunc);

  if (file.good() == true) 
  { 


    file.close(); 
  }
  else std::cout << "Nie uzyskano dostepu do pliku" << std::endl;
}
