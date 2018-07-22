#include "Name.h"
#include <fstream>
#include <iostream>

using std::fstream;
using std::ios;


Name::Name() :TLV(m_NameType) {/*todo*/ }
Name::~Name() {}

vector<byte> Name::ValueToBytes() 
{
  vector<byte> NameValue;

  /*todo*/

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