#include "TLV.h"
#include <cmath>

using std::ceil;
using std::log;
using std::pow;

void TLV::encodeLength()
{
  byte NumOctetsLength = m_Value.size();

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

Integer::Integer(int Value) :TLV(m_IntType) 
{
  m_Value = ValueToBytes(Value);
  encodeLength();
  encodeTLV();
}
Integer::~Integer() {}
vector<byte> Integer::ValueToBytes(int Value) 
{
  vector<byte> IntValue;
  const byte NumBytesInValue = sizeof(Value);
  vector<byte> ValueTab;



  for (byte i = 0; i < NumBytesInValue; ++i)
    IntValue.push_back(ValueTab[i]);
  return IntValue;
}

BitString::BitString() :TLV(m_BitStrType) 
{
  m_Value = ValueToBytes();
  encodeLength();
  encodeTLV();
}
BitString::~BitString() {}
vector<byte> BitString::ValueToBytes(/*todo*/) 
{

}

Real::Real(float Value) :TLV(m_RealType) 
{
  m_Value = ValueToBytes(Value);
  encodeLength();
  encodeTLV();
}
Real::~Real() {}
vector<byte> Real::ValueToBytes(float Value) 
{
  vector<byte> RealValue;
  const byte NumBytesInValue = sizeof(Value);
  byte ValueTab[NumBytesInValue];


  for (byte i = 0; i < NumBytesInValue; ++i)
    RealValue.push_back(ValueTab[i]);
  return RealValue;
}

OctetString::OctetString(char Value) :TLV(m_OctetStrType) 
{
  m_Value = ValueToBytes(Value);
  encodeLength();
  encodeTLV();
}
OctetString::~OctetString() {}
vector<byte> OctetString::ValueToBytes(char Value) 
{
  vector<byte> OctetStrValue;
  const byte NumBytesInValue = sizeof(Value);
  byte ValueTab[NumBytesInValue];



  for (byte i = 0; i < NumBytesInValue; ++i)
    OctetStrValue.push_back(ValueTab[i]);
  return OctetStrValue;
}

Elem::Elem(vector<Integer> Value) :TLV(m_ElemType) 
{
  m_Value = ValueToBytes(Value);
  encodeLength();
  encodeTLV();
}
Elem::~Elem() {}
vector<byte> Elem::ValueToBytes(vector<Integer> Value)
{
  vector<byte> ElemValue;
  //todo

  return ElemValue;
}

Struct::Struct() :TLV(m_StructType) 
{
  m_Value = StructToBytes();
  encodeLength();
  encodeTLV();
}
Struct::~Struct() {}

vector<byte> Struct::StructToBytes() 
{
  vector<byte> StructValue;
  //todo
  return StructValue;
}
