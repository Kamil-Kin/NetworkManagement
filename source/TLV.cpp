#include "TLV.h"
#include <cmath>

using std::ceil;
using std::log;
using std::pow;

void TLV::encodeLength()
{
  byte NumBytesLength = m_Length.size();
  if (NumBytesLength <= 127)
    m_Length.push_back(NumBytesLength);
  else 
  {
    const int LongFormFlag = 0x80;  // 1000 0000
    byte MaxBytes = ceil(log(NumBytesLength));
    int NumBitsInByte = 8;
    double ValuesInByte = pow(2.0, NumBitsInByte);
    int LongFormLengthBytes = MaxBytes / NumBitsInByte;
    m_Length.push_back(LongFormFlag + LongFormLengthBytes);
    
    while (NumBytesLength > 0)
    {
      byte ContentBytes = NumBytesLength and ValuesInByte;
      NumBytesLength /= ValuesInByte;
      m_Length.push_back(ContentBytes);
    }
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
