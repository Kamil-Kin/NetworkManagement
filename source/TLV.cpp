#include "TLV.h"
#include <cmath>
#include <cstring>

using std::ceil;
using std::log;
using std::pow;
using std::memcpy;

void TLV::encodeLength()
{
  byte NumBytesLength = m_Value.size();

  if (NumBytesLength <= 127)
    m_Length.push_back(NumBytesLength);
  else 
  {
    const int LongFormFlag = 0x80;  // 1000 0000
    
    byte NumBitsInByte = 8;
    byte LongFormLengthBytes = ceil(log2(NumBytesLength)/NumBitsInByte);
    
    m_Length.push_back(LongFormFlag + LongFormLengthBytes);
    
    double ValuesInByte = pow(2.0, NumBitsInByte);
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
  char ValueTab[NumBytesInValue];

  memcpy(ValueTab, &Value, NumBytesInValue);

  for (byte i = 0; i < NumBytesInValue; ++i)
    IntValue.push_back(ValueTab[i]);
  return IntValue;
}

BitString::BitString(vector<byte> Value) :TLV(m_BitStrType)
{
  m_Value = ValueToBytes(Value);
  encodeLength();
  encodeTLV();
}
BitString::~BitString() {}
vector<byte> BitString::ValueToBytes(vector<byte> Value) 
{
  vector<byte> BitStrValue;

  const byte NumBitsInByte = 8;
  byte NumBytesInValue = ceil(Value.size() / NumBitsInByte);
  
  for (byte i = 0; i < NumBytesInValue; i--) 
  {
    byte tmpVal = 0;
    for (byte j = NumBitsInByte - 1; j >= 0; j--)
    {
      int ValueOfBit = Value[i * NumBitsInByte + (NumBitsInByte - j - 1)] and 0xFF;
      tmpVal += ValueOfBit * pow(2.0, j);
    }
    BitStrValue.push_back(tmpVal);
  }

  return BitStrValue;
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
  char ValueTab[NumBytesInValue];
  
  memcpy(ValueTab, &Value, NumBytesInValue);

  for (byte i = 0; i < NumBytesInValue; ++i)
    RealValue.push_back(ValueTab[i]);
  return RealValue;
}

OctetString::OctetString(char* Value) :TLV(m_OctetStrType) 
{
  m_Value = ValueToBytes(Value);
  encodeLength();
  encodeTLV();
}
OctetString::~OctetString() {}
vector<byte> OctetString::ValueToBytes(char* Value) 
{
  vector<byte> OctetStrValue;
  const byte NumBytesInValue = strlen(Value);
  char* ValueTab = new char[NumBytesInValue];

  memcpy(ValueTab, Value, NumBytesInValue);

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
  for (int i = 0; i < Value.size(); ++i) 
  {
    Real temp = Real(i);
    vector<byte> TempValue = temp.GetMessage();
    ElemValue.insert(ElemValue.end(), TempValue.begin(), TempValue.end());
  }
  return ElemValue;
}

Order::Order(BitString Name, BitString F2,Integer F3, Real F4, OctetString F5, Elem F6) :
            TLV(m_StructType), m_Name(Name), m_F2(F2), m_F3(F3), m_F4(F4), m_F5(F5), m_F6(F6)
{
  m_Value = OrderToBytes();
  encodeLength();
  encodeTLV();
}
Order::~Order() {}

vector<byte> Order::OrderToBytes() 
{
  vector<byte> OrderValue;
  vector<byte> FieldValue;

  FieldValue = m_Name.GetMessage(); AddToOrder(OrderValue, FieldValue);
  FieldValue = m_F2.GetMessage();   AddToOrder(OrderValue, FieldValue);
  FieldValue = m_F3.GetMessage();   AddToOrder(OrderValue, FieldValue);
  FieldValue = m_F4.GetMessage();   AddToOrder(OrderValue, FieldValue);
  FieldValue = m_F5.GetMessage();   AddToOrder(OrderValue, FieldValue);
  FieldValue = m_F6.GetMessage();   AddToOrder(OrderValue, FieldValue);

  return OrderValue;
}
void Order::AddToOrder(vector<byte> &OrderValue, vector<byte> &FieldValue)
{
   OrderValue.insert(OrderValue.end(), FieldValue.begin(), FieldValue.end());
   //return NameValue; http://cpp.sh/2knz
}
