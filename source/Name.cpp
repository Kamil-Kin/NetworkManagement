#include "Name.h"
#include <fstream>
#include <iostream>

using std::fstream;
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

void Name::SaveToFile() 
{
  fstream file;
  file.open("BERMessage.txt", ios::out | ios::trunc);

  if (file.good() == true) 
  { 


    file.close(); 
  }
  else std::cout << "Nie uzyskano dostepu do pliku" << std::endl;
}