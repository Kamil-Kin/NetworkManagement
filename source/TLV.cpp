#include "TLV.h"
#include <cmath>
#include <cassert>
#include <string>
#include <cstring>

using std::ceil;
using std::log;
using std::pow;
using std::memcpy;

void TLV::encodeLength()
{
  size_t NumBytesLength = m_Value.size();

  if (NumBytesLength <= 127)
    m_Length.push_back(NumBytesLength);
  else 
  {
    const int LongFormFlag = 0x80;  // b1000 0000
    
    int NumBitsInByte = 8;
    double MaxValueInByte = pow(2.0, NumBitsInByte) - 1;
    double LongFormLengthBytes = ceil(log2(NumBytesLength)/NumBitsInByte);
    
    m_Length.push_back(LongFormFlag + LongFormLengthBytes);
    
    while (NumBytesLength > 0)
    {
      int ContentBytes = NumBytesLength & static_cast<int>(MaxValueInByte);
      NumBytesLength /= MaxValueInByte;
      m_Length.push_back(static_cast<byte>(ContentBytes));
    }
  }
}
void TLV::encodeTLV() 
{
  m_Message.push_back(m_Type);
  for (size_t i = 0; i < m_Length.size(); ++i)
    m_Message.push_back(m_Length[i]);
  for (size_t i = 0; i < m_Value.size(); ++i)
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
 
  //for (int i = 0; i < NumBytesInValue; ++i)
  for (int i = NumBytesInValue - 1; i >= 0; --i)
    if (ValueTab[i] != 0)
      IntValue.push_back(ValueTab[i]);

  return IntValue;
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

  //for (byte i = 0; i < NumBytesInValue; ++i)
  for (int i = NumBytesInValue - 1; i >= 0; --i)
    if (ValueTab[i] != 0)
      RealValue.push_back(ValueTab[i]);

  return RealValue;
}

OctetString::OctetString(const char* Value) :TLV(m_OctetStrType) 
{
  m_Value = ValueToBytes(Value);
  encodeLength();
  encodeTLV();
}
OctetString::OctetString(const char* Value, const byte Type) :TLV(Type)
{
  m_Value = ValueToBytes(Value);
  encodeLength();
  encodeTLV();
}
OctetString::~OctetString() {}
vector<byte> OctetString::ValueToBytes(const char* Value) 
{
  vector<byte> OctetStrValue;
  const size_t NumBytesInValue = strlen(Value);
  char* ValueTab = new char[NumBytesInValue];

  memcpy(ValueTab, Value, NumBytesInValue);

  for (size_t i = 0; i < NumBytesInValue; ++i)
    OctetStrValue.push_back(ValueTab[i]);

  return OctetStrValue;
}

Elem::Elem(vector<int> Value) :TLV(m_ElemType) 
{
  m_Value = ValueToBytes(Value);
  encodeLength();
  encodeTLV();
}
Elem::~Elem() {}
vector<byte> Elem::ValueToBytes(vector<int> Value)
{
  vector<byte> ElemValue;
  for (int i = 0; i < Value.size(); ++i) 
  {
    Integer temp = Integer(Value[i]);
    vector<byte> TempValue = temp.GetMessage();
    ElemValue.insert(ElemValue.end(), TempValue.begin(), TempValue.end());
  }
  return ElemValue;
}

Order::Order(string Name, string F2, int F3, float F4, string F5, vector<int> F6) :
            TLV(m_StructType), m_Name(Name.c_str()), m_F2(F2.c_str()), m_F3(F3), m_F4(F4), m_F5(F5.c_str()), m_F6(F6)
{
  CheckSize(Name, F2, F3, F5);
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
}
void Order::CheckSize(string Name, string f2, int f3, string f5) 
{
  assert(Name.size() == m_NameLength);
  assert(f2.size() == m_F2Length);
  assert(f3 <= m_F3ValueMax);
  assert(f3 >= m_F3ValueMin);
  assert(f5.size() == m_F5Length);
}
