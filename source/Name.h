#ifndef NETWORK_MANAGEMENT_NAME_H
#define NETWORK_MANAGEMENT_NAME_H

#include "TLV.h"

class Name 
{
private:
  const byte m_Type = 0x30;
  BitString m_FN;
  BitString m_SN;
  BitString m_AD;
  Integer   m_AGE;
  Sequence  m_order;

public:
  Name() {}
  ~Name() {}

};

#endif // !NETWORK_MANAGEMENT_NAME_H
