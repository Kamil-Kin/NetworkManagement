#include "TLV.h"
#include <cmath>

using std::ceil;
using std::log;
using std::pow;

void TLV::encodeLength()
{
  byte NumOctetsLength = m_Length.size();

  if (NumOctetsLength <= 127)
    m_Length.push_back(NumOctetsLength);
  else 
  {
    const int LongFormFlag = 0x80;  // 1000 0000
    
    byte NumBitsInOctet = 8;
    byte LongFormLengthBytes = ceil(log2(NumOctetsLength)/NumBitsInOctet);
    
    m_Length.push_back(LongFormFlag + LongFormLengthBytes);
    
    double ValuesInOctet = pow(2.0, NumBitsInOctet);
    while (NumOctetsLength > 0)
    {
      byte ContentOctets = NumOctetsLength and ValuesInOctet;
      NumOctetsLength /= ValuesInOctet;
      m_Length.push_back(ContentOctets);
    }
  }
}

void TLV::encodeTLV() 
{
  m_Message.push_back(m_Type);
  for (int i = 0; i < m_Length.size(); ++i)
    m_Message.push_back(m_Length[i]);
  for (int i = 0; i < m_Value.size(); ++i)
    m_Message.push_back(m_Value[i]);
}

Integer::Integer() :TLV(m_IntType) 
{
  encodeLength();
  encodeTLV();
}
vector<byte> Integer::ValueToBytes(int Value) 
{
  vector<byte> IntValue;
  byte NumBytesInValue = sizeof(Value);



  for (byte i = 0; i < NumBytesInValue; ++i)
    IntValue.push_back(/*todo*/);
}

BitString::BitString() :TLV(m_BitStrType) 
{
  encodeLength();
  encodeTLV();
}
vector<byte> BitString::ValueToBytes(/*todo*/) 
{

}

Real::Real() :TLV(m_RealType) 
{
  encodeLength();
  encodeTLV();
}
vector<byte> Real::ValueToBytes(float Value) 
{
  vector<byte> RealValue;

  byte NumBytesInValue = sizeof(Value);



  for (byte i = 0; i < NumBytesInValue; ++i)
    RealValue.push_back(/*todo*/);
}

OctetString::OctetString() :TLV(m_OctetStrType) 
{
  encodeLength();
  encodeTLV();
}
vector<byte> OctetString::ValueToBytes(char Value) 
{
  vector<byte> OctetStrValue;
  byte NumBytesInValue = sizeof(Value);



  for (byte i = 0; i < NumBytesInValue; ++i)
    OctetStrValue.push_back(/*todo*/);
}

