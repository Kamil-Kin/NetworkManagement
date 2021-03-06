#ifndef NETWORK_MANAGEMENT_NAME_H
#define NETWORK_MANAGEMENT_NAME_H

#include "TLV.h"
#include <fstream>

using std::ifstream;

class Name :public TLV
{
public:
  Name();
  ~Name();

  vector<byte> ValueToBytes();
  void         AddToName(vector<byte> &Name, vector<byte> &Field);
  void         LoadValuesFromFile();
  string       LoadLine(ifstream& file);
  vector<int>  LoadElem(ifstream& file);
  void         SaveToFile();
  void         DisplayValues();
private:
  static const byte m_NameType = 0x30;  // Sequence type in BER

  OctetString* m_FN;
  OctetString* m_SN;
  OctetString* m_AD;
  Integer*     m_AGE;
  Order*       m_STRUCT;
};


#endif // !NETWORK_MANAGEMENT_NAME_H
