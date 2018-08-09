#ifndef NETWORK_MANAGEMENT_TLV_H
#define NETWORK_MANAGEMENT_TLV_H

#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <cstring>

typedef uint8_t byte;

using std::string;
using std::vector;
using std::size_t;

class TLV 
{
public:
  TLV(byte Type) :m_Type(Type) {}
  ~TLV() {}

  void         encodeLength();
  void         encodeTLV   ();
  vector<byte> GetMessage  () { return m_Message; }

protected:
  const byte   m_Type;
  vector<byte> m_Message;
  vector<byte> m_Length;
  vector<byte> m_Value;
};

class Integer :public TLV
{
public:
  Integer(int Value);
  ~Integer();
  vector<byte> ValueToBytes(int Value);

private:
  static const byte m_IntType = 0x02;  // Integer type in BER
};

class BitString :public TLV 
{
public:
  BitString(string Value);
  ~BitString();
  vector<byte> ValueToBytes(string Value);

private:
  static const byte m_BitStrType = 0x03;  // BitString type in BER
};

class OctetString :public TLV
{
public:
  OctetString(const char* Value);
  OctetString(const char* Value, const byte Type);
  ~OctetString();
  vector<byte> ValueToBytes(const char* Value);

private:
  static const byte m_OctetStrType = 0x04;  // OctetString type in BER
};

class Real :public TLV 
{
public:
  Real(float Value);
  ~Real();
  vector<byte> ValueToBytes(float Value);

private:
  static const byte m_RealType = 0x09;  // Real type in BER
};

class Elem :public TLV
{
public:
  Elem(vector<int> Value);
  ~Elem();
  vector<byte> ValueToBytes(vector<int> Value);

private:
  static const byte m_ElemType = 0x30;  // Sequence type in BER
};

class Order :public TLV 
{
public:
  Order(string Name, string F2, int F3, float F4, string F5, vector<int> F6);
  ~Order();
  vector<byte> OrderToBytes();
  void         AddToOrder(vector<byte> &Order, vector<byte> &Field);
  void         CheckSize(string Name, string f2, int f3, string f5);

private:
  static const byte m_StructType = 0x30;  // Sequence type in BER

  OctetString m_Name;  //todo BitString czy OctetString?
  OctetString m_F2;
  Integer     m_F3;
  Real        m_F4;
  OctetString m_F5;
  Elem        m_F6;

  const size_t m_NameLength = 20;
  const size_t m_F2Length   = 30;
  const int    m_F3ValueMin = 0;
  const int    m_F3ValueMax = 50;
  const size_t m_F5Length   = 60;
};


#endif // !NETWORK_MANAGEMENT_TLV_H
