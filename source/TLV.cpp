#include "TLV.h"

void TLV::encodeLength()
{
  byte NumBytesLen = m_Length.size();
  if (NumBytesLen <= 127)
    m_Length.push_back(NumBytesLen);
  else 
  {
    const int long_form_flag = 0x80;  // 1000 0000
    //
    //todo
    //
    m_Length.push_back(long_form_flag);
  }
}

void TLV::encodeTLV() 
{
  m_Message.push_back(m_Type);
  for (int i = 0; i < m_Length.size(); i++)
    m_Message.push_back(m_Length[i]);
  for (int i = 0; i < m_Value.size(); i++)
    m_Message.push_back(m_Value[i]);
}
