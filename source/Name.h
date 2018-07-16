#ifndef NETWORK_MANAGEMENT_NAME_H
#define NETWORK_MANAGEMENT_NAME_H

#include "TLV.h"

class Name :public TLV
{
private:
  const byte m_NameType = 0x30;
  BitString m_FN;
  BitString m_SN;
  BitString m_AD;
  Integer   m_AGE;
  Sequence  m_order;

public:
  Name() :TLV(m_NameType) {}
  ~Name() {}

};

#endif // !NETWORK_MANAGEMENT_NAME_H
