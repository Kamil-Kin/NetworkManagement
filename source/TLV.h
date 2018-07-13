#ifndef NETWORK_MANAGEMENT_TLV_H
#define NETWORK_MANAGEMENT_TLV_H

#include <vector>
#include <cstdint>

typedef uint8_t byte;

using std::vector;

class TLV 
{
protected:
  const byte m_Type;

public:
  TLV(byte Type) :m_Type(Type) {}
  ~TLV() {}
};

class Integer :public TLV
{
private:
  const byte m_Type = 0x02;
public:
  Integer() :TLV(m_Type) {} 
  ~Integer() {}
};

class BitString :public TLV 
{
private:
  const byte m_Type = 0x03;
public:
  BitString() :TLV(m_Type) {}
  ~BitString() {}
};

class OctetString :public TLV 
{
private:
  const byte m_Type = 0x04;
public:
  OctetString() :TLV(m_Type) {}
  ~OctetString() {}
};

class Real :public TLV 
{
private:
  const byte m_Type = 0x09;
public:
  Real() :TLV(m_Type) {}
  ~Real() {}
};

class Sequence :public TLV 
{
private:
  const byte   m_Type = 0x30;
  BitString    m_Name;
  const size_t m_NameLength = 20;
  BitString    m_F2;
  const size_t m_F2Length = 30;
  Integer      m_F3;
  const size_t m_F3LengthMin = 0;
  const size_t m_F3LengthMax = 50;
  Real         m_F4;
  OctetString  m_F5;
  const size_t m_F5Length = 60;
  BitString    m_F6;

public:
  Sequence() :TLV(m_Type) {}
  ~Sequence() {}
};


#endif // !NETWORK_MANAGEMENT_TLV_H
