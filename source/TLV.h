#ifndef NETWORK_MANAGEMENT_TLV_H
#define NETWORK_MANAGEMENT_TLV_H

#include <vector>
#include <cstdint>

typedef uint8_t byte;

using std::vector;
using std::size_t;

class TLV 
{
public:
  TLV(byte Type) :m_Type(Type) {}
  ~TLV() {}

  void encodeLength();
  void encodeTLV();

protected:
  const byte m_Type;

private:
  vector<byte> m_Message;
  vector<byte> m_Length;
  vector<byte> m_Value;

};

class Integer :public TLV
{
private:
  static const byte m_IntType = 0x02; // Integer type in BER
public:
  Integer() :TLV(m_IntType) {} 
  ~Integer() {}
  vector<byte> ValueToBytes(int Value);
};

class BitString :public TLV 
{
private:
  static const byte m_BitStrType = 0x03;  // BitString type in BER
public:
  BitString() :TLV(m_BitStrType) {}
  ~BitString() {}
  vector<byte> ValueToBytes(/*todo*/);
};

class OctetString :public TLV
{
private:
  static const byte m_OctetStrType = 0x04; // OctetString type in BER
public:
  OctetString() :TLV(m_OctetStrType) {}
  ~OctetString() {}
  vector<byte> ValueToBytes(char Value);
};

class Real :public TLV 
{
private:
  static const byte m_RealType = 0x09; // Real type in BER
public:
  Real() :TLV(m_RealType) {}
  ~Real() {}
  vector<byte> ValueToBytes(float Value);
};

class Struct :public TLV 
{
private:
  static const byte m_StructType = 0x30; // Sequence type in BER

  BitString    m_Name;
  const size_t m_NameLength = 20;
  BitString    m_F2;
  const size_t m_F2Length = 30;
  Integer      m_F3;
  const int    m_F3LengthMin = 0;
  const int    m_F3LengthMax = 50;
  Real         m_F4;
  OctetString  m_F5;
  const size_t m_F5Length = 60;
  //   m_F6;??

public:
  Struct() :TLV(m_StructType) {}
  ~Struct() {}
};


#endif // !NETWORK_MANAGEMENT_TLV_H
