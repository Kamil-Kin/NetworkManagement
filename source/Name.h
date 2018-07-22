#ifndef NETWORK_MANAGEMENT_NAME_H
#define NETWORK_MANAGEMENT_NAME_H

#include "TLV.h"

class Name :public TLV
{
public:
  Name();
  ~Name();

  vector<byte> ValueToBytes();
  void         SaveToFile();

private:
  static const byte m_NameType = 0x30;  // Sequence type in BER

  BitString m_FN;
  BitString m_SN;
  BitString m_AD;
  Integer   m_AGE;
  Order     m_STRUCT;

};


#endif // !NETWORK_MANAGEMENT_NAME_H
