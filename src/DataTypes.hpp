#ifndef _DATA_TYPES_H_
#define _DATA_TYPES_H_

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cassert>

using std::string;
using std::ifstream;
using std::ofstream;

bool isBigEndian()
{
  union
  {
    unsigned short a;
    char b;
  } c;
  c.a = 0x0102;
  if(c.b == 1) return true;
  else return false;
}

///////////////////////////////////////////////////////////////////////////////
class DataType
{
  public:
    virtual ~DataType() {};
    virtual void write(ofstream& outfile) = 0;
    virtual void read(ifstream& infile) = 0;
    virtual size_t size() const = 0;
    virtual string to_string() const = 0;
};
///////////////////////////////////////////////////////////////////////////////
template <size_t SIZE>
class CharArray : public DataType
{
  friend class TestC1;
  friend class TestC5;

  public:
    ~CharArray() {}
    CharArray(const string& str = "") {init(); memcpy(mData, str.data(), std::min(SIZE, str.size()));}
    CharArray(const char* str) {assert(str != NULL); init(); memcpy(mData, str, std::min(SIZE, strlen(str)));}
    CharArray(char ch) {init(); memcpy(mData, &ch, sizeof(ch));}
    CharArray(const CharArray& rhs) {memcpy(mData, rhs.mData, SIZE);}
    CharArray& operator=(const CharArray& rhs);
    void clear() {init();}
    void write(ofstream& outfile) {outfile.write(mData, SIZE);}
    void read(ifstream& infile) {infile.read(mData, SIZE);}
    size_t size() const {return SIZE;}
    string to_string() const;

  private:
    inline void init() {memset(mData, ' ', SIZE);}

  private:
    char            mData[SIZE];
};

template <size_t SIZE>
CharArray<SIZE>& CharArray<SIZE>::operator=(const CharArray<SIZE>& rhs)
{
  if(this == &rhs) return *this;
  memcpy(mData, rhs.mData, SIZE);
  return *this;
}

template <size_t SIZE>
string CharArray<SIZE>::to_string() const
{
  char buffer[SIZE+1] = {0};
  memcpy(buffer, mData, SIZE);
  return buffer;
}


///////////////////////////////////////////////////////////////////////////////
template <typename T>
class VarCharArray : public DataType
{
  friend class TestSn;
  friend class TestCn;

  public:
    ~VarCharArray() {}
    VarCharArray(const string& str = "") {init(); fill(str);}
    VarCharArray(const char* str) {assert(str != NULL); init(); fill(string(str));}
    VarCharArray(const VarCharArray& rhs) : mSize(rhs.mSize) {memcpy(mData, rhs.mData, capacity());}
    VarCharArray& operator=(const VarCharArray& rhs);
    VarCharArray& operator+=(const string& str) {fill(str); return *this;}
    void clear() { init();}
    void write(ofstream& outfile) {outfile.write(mData, sizeof(T)+mSize);}
    void read(ifstream& infile);
    size_t max_size() const {return ((1<<(8*sizeof(T)))-1);}
    size_t size() const {return sizeof(T)+mSize;}
    string to_string() const;

  private:
    inline size_t capacity() const {return sizeof(mData)/sizeof(char);}
    inline void init() {mSize = 0; memset(mData, 0, capacity());}
    inline size_t merged_size(const string& str) const
    {
      return (mSize+str.size() > max_size())? max_size()-mSize : str.size();
    }
    inline void fill(const string& str)
    {
      size_t size = merged_size(str);
      memcpy(mData+sizeof(T)+mSize, str.data(), size);   // copy data
      mSize += size;
      memcpy(mData, &mSize, sizeof(T));                  // copy length
    }

  private:
    T               mSize;
    char            mData[sizeof(T)+((1<<(8*sizeof(T)))-1)];
};

template <typename T>
VarCharArray<T>& VarCharArray<T>::operator=(const VarCharArray& rhs)
{
  if(this == &rhs) return *this;
  mSize = rhs.mSize;
  memcpy(mData, rhs.mData, capacity());
  return *this;
}

template <typename T>
void VarCharArray<T>::read(ifstream& infile)
{
  infile.read(reinterpret_cast<char*>(&mSize), sizeof(T));

  if(0 != mSize)
  {
    infile.read(mData+sizeof(T), mSize);
  }
}

template <typename T>
string VarCharArray<T>::to_string() const
{
  char buffer[mSize+1];
  memset(buffer, 0, sizeof(buffer)/sizeof(char));
  memcpy(buffer, mData+sizeof(T), mSize);
  return string(buffer);
}


///////////////////////////////////////////////////////////////////////////////
class StdfString
{
  friend class TestCf;

  public:
    ~StdfString() {}
    StdfString(const string& str = "") : mData(str) {}
    StdfString(const char* str) {assert(str != NULL); mData = str;}
    StdfString(const StdfString& rhs) {mData = rhs.mData;}
    StdfString& operator=(const StdfString& rhs);
    StdfString& operator+=(const string& str) {mData += str; return *this;}
    void clear() {mData.clear();}
    void write(ofstream& outfile, size_t size) {outfile.write(mData.data(), std::min(mData.size(), size));}
    void write(ofstream& outfile) {outfile.write(mData.data(), mData.size());}
    void read(ifstream& infile, size_t size);
    size_t size() const {return mData.size();}
    const string& to_string() const {return mData;} 

  private:
    string          mData;
};

StdfString& StdfString::operator=(const StdfString& rhs)
{
  if(this == &rhs) return *this;
  mData = rhs.mData;
  return *this;
}

void StdfString::read(ifstream& infile, size_t size)
{
  assert(size >= 0);

  if(0 != size)
  {
    char buffer[size+1];
    memset(buffer, '\0', size+1);
    infile.read(buffer, size);
    mData = buffer;
  }
  else
  {
    mData = "";
  }
}


///////////////////////////////////////////////////////////////////////////////
class VarUType
{
  friend class TestUf;

  public:
    enum Type
    {
      TYPE_1B = 1u, TYPE_2B = 2u, TYPE_4B = 4u, TYPE_8B = 8u
    };

    ~VarUType() {}
    VarUType(unsigned long long value = 0) : mData(value) {}
    VarUType(const VarUType& rhs) : mData(rhs.mData) {}
    VarUType& operator=(const VarUType& rhs);
    void clear() {mData = 0;}
    void write(ofstream& outfile, Type type) {outfile.write(reinterpret_cast<char*>(&mData), type);}
    void read(ifstream& infile, Type type) {infile.read(reinterpret_cast<char*>(&mData), type);}
    unsigned long long getValue() const {return mData;}
    size_t size(Type type) const {return type;}
    string to_string() const {std::stringstream ss; ss << mData; return ss.str();}

  private:
    unsigned long long mData;
};

VarUType& VarUType::operator=(const VarUType& rhs)
{
  if(this == &rhs) return *this;
  mData = rhs.mData;
  return *this;
}


///////////////////////////////////////////////////////////////////////////////
template <typename T>
class NumericalType : public DataType
{
  friend class TestU1;
  friend class TestU2;
  friend class TestU4;
  friend class TestU8;
  friend class TestI1;
  friend class TestI2;
  friend class TestI4;
  friend class TestI8;
  friend class TestR4;
  friend class TestR8;

  public:
    ~NumericalType() {}
    NumericalType(T value = 0) : mData(value) {}
    NumericalType(const NumericalType& rhs) : mData(rhs.mData) {}
    NumericalType& operator=(const NumericalType& rhs);
    void clear() {mData = 0;}
    void write(ofstream& outfile) {outfile.write(reinterpret_cast<char*>(&mData), sizeof(mData));}
    void read(ifstream& infile) {infile.read(reinterpret_cast<char*>(&mData), sizeof(mData));}
    T getValue() const {return mData;}
    size_t size() const {return sizeof(T);}
    string to_string() const;

  private:
    T               mData;
};

template <typename T>
NumericalType<T>& NumericalType<T>::operator=(const NumericalType& rhs)
{
  if(this == &rhs) return *this;
  mData = rhs.mData;
  return *this;
}

template <typename T>
string NumericalType<T>::to_string() const
{
  std::stringstream ss;
  if(sizeof(T) > 1) ss << std::dec << mData;
  else              ss << std::dec << static_cast<int>(mData);
  return ss.str();
}

///////////////////////////////////////////////////////////////////////////////
template <size_t SIZE>
class BitArray : public DataType
{
  friend class BitReference;

  friend class TestB1;
  friend class TestB6;

  public:
    class BitReference
    {
      public:
        BitReference(char* pb, size_t p) : pBits(pb), pos(p) {}
        BitReference(const BitReference& rhs) : pBits(rhs.pBits), pos(rhs.pos) {}
        BitReference& operator=(const BitReference& rhs)
        {
          if(this == &rhs) return *this;
          pBits = rhs.pBits;
          pos = rhs.pos;
          return *this;
        }
        BitReference& operator=(bool x)
        {
          if(x) pBits[pos/8] |=  (1 << (pos%8));
          else  pBits[pos/8] &= ~(1 << (pos%8));
          return *this;
        }
        operator bool() const {return (pBits[pos/8] & (1 << (pos%8))) != 0;}

      private:
        BitReference();

      private:
        char*  pBits;
        size_t pos;
    };

    ~BitArray() {}
    BitArray(const string& str = "");
    BitArray(const char* str) {assert(str != NULL); *this = BitArray(string(str));}
    BitArray(const BitArray& rhs) {memcpy(mData, rhs.mData, SIZE);}
    BitArray& operator=(const BitArray& rhs);
    bool operator[] (size_t pos) const {assert(pos < 8*SIZE); return ((mData[pos/8] & (1 << (pos%8))) != 0);}
    BitReference operator[] (size_t pos) {assert(pos < 8*SIZE); return BitReference(mData, pos);}
    BitArray& reset(bool x) {for(size_t i = 0; i < SIZE; ++i){if(x) mData[i] = 0xFF;else mData[i] = 0x00;}}
    void clear() {reset(false);}
    void write(ofstream& outfile) {outfile.write(mData, SIZE);}
    void read(ifstream& infile) {infile.read(mData, SIZE);}
    size_t size() const {return SIZE;}
    string to_string() const;

  private:
    char            mData[SIZE];
};

template <size_t SIZE>
BitArray<SIZE>::BitArray(const string& str)
{
  for(size_t i = 0; i < str.size(); i++)
  {
    assert(('1' == str[i]) || ('0' == str[i]));
  }

  memset(mData, '\0', SIZE);

  for(size_t i = 0; ((i < 8*SIZE) && (i < str.size())); i++)
  {
    if('1' == str[i])      mData[i/8] |=  (1 << (i%8));
    else if('0' == str[i]) mData[i/8] &= ~(1 << (i%8));
  }
}

template <size_t SIZE>
BitArray<SIZE>& BitArray<SIZE>::operator=(const BitArray<SIZE>& rhs)
{
  if(this == &rhs) return *this;
  memcpy(mData, rhs.mData, SIZE);
  return *this;
}

template <size_t SIZE>
string BitArray<SIZE>::to_string() const
{
  std::stringstream ss;
  for(size_t i = 0; i < 8*SIZE; i++)
  {
    ss << (*this)[i];
  }
  return ss.str();
}


///////////////////////////////////////////////////////////////////////////////
template <typename T>
class VarBitArray : public DataType
{
  friend class BitReference;

  friend class TestBn;
  friend class TestDn;

  public:
    class BitReference
    {
      public:
        BitReference(char* pb, size_t p) : pBits(pb), pos(p) {}
        BitReference(const BitReference& rhs) : pBits(rhs.pBits), pos(rhs.pos) {}
        BitReference& operator=(const BitReference& rhs)
        {
          if(this == &rhs) return *this;
          pBits = rhs.pBits;
          pos = rhs.pos;
          return *this;
        }
        BitReference& operator=(bool x)
        {
          if(x) pBits[sizeof(T)+(pos/8)] |=  (1 << (pos%8));
          else  pBits[sizeof(T)+(pos/8)] &= ~(1 << (pos%8));
/*
          T len = 0;
          memcpy(reinterpret_cast<char*>(&len), pBits, sizeof(T));
          if(pos+1 > len)
          {
            len = pos+1;
            memcpy(pBits, &len, sizeof(T));
          }
*/
          return *this;
        }
        operator bool() const {return (pBits[sizeof(T)+(pos/8)] & (1 << (pos%8))) != 0;}

      private:
       BitReference();

      private:
        char*  pBits;
        size_t pos;
    };

    ~VarBitArray() {}
    VarBitArray(const string& str = "");
    VarBitArray(const char* str) {assert(str != NULL); *this = VarBitArray(string(str));}
    VarBitArray(const VarBitArray& rhs) : mSize(rhs.mSize) {memcpy(mData, rhs.mData, capacity());}
    VarBitArray& operator=(const VarBitArray& rhs);
    VarBitArray& operator+=(const string& str) {fill(str); return *this;}
    bool operator[] (size_t pos) const {assert(pos < mSize); return ((mData[sizeof(T)+(pos/8)] & (1 << (pos%8))) != 0);}
    BitReference operator[] (size_t pos) {assert(pos < mSize); return BitReference(mData, pos);}
    void clear() {mSize = 0; memset(mData, 0, capacity());}
    void write(ofstream& outfile) {if( (mSize%8) == 0 ) outfile.write(mData, sizeof(T)+(mSize/8)); else outfile.write(mData, sizeof(T)+(mSize/8)+1);}
    void read(ifstream& infile);
    inline size_t max_size() const {return ((1<<(8*sizeof(T)))-1);}
    size_t size() const {return ((mSize%8) == 0)?(sizeof(T)+(mSize/8)):(sizeof(T)+(mSize/8)+1);}
    string to_string() const;

  private:
    inline size_t capacity() const {return sizeof(mData)/sizeof(char);}
    inline size_t merged_size(const string& str) const
    {
      return (mSize+str.size() > max_size())? max_size()-mSize : str.size();
    }
    void   fill(const string& str)
    {
      size_t size = merged_size(str);
      for(size_t i = mSize; i < mSize+size; i++)
      {
        if('1' == str[i-mSize])      mData[sizeof(T)+(i/8)] |=  (1 << (i%8));
        else if('0' == str[i-mSize]) mData[sizeof(T)+(i/8)] &= ~(1 << (i%8));
      }
      mSize += size;
      memcpy(mData, &mSize, sizeof(T));                  // copy length
    }

  private:
    T               mSize;
    char            mData[sizeof(T)+(1<<(8*sizeof(T)-3))];
};

template <typename T>
VarBitArray<T>::VarBitArray(const string& str) : mSize(0)
{
  for(size_t i = 0; i < str.size(); i++) assert(('1' == str[i]) || ('0' == str[i]));

  memset(mData, 0, capacity());
  fill(str);
}

template <typename T>
VarBitArray<T>& VarBitArray<T>::operator=(const VarBitArray<T>& rhs)
{
  if(this == &rhs) return *this;
  mSize = rhs.mSize;
  memcpy(mData, rhs.mData, capacity());
  return *this;
}

template <typename T>
void VarBitArray<T>::read(ifstream& infile)
{
  infile.read(reinterpret_cast<char*>(&mSize), sizeof(T));

  memcpy(mData, &mSize, sizeof(T));
  if(0 != mSize)
  {
    if( (mSize%8) == 0 ) infile.read(mData+sizeof(T), (mSize/8));
    else                 infile.read(mData+sizeof(T), (mSize/8)+1);
  }
}

template <typename T>
string VarBitArray<T>::to_string() const
{
  std::stringstream ss;
  for(size_t i = 0; i < mSize; i++)
  {
    ss << (*this)[i];
  }
  return ss.str();
}


///////////////////////////////////////////////////////////////////////////////
template <size_t SIZE>
class JxN1 : public DataType
{
  friend class TestJxN1;

  public:
    class Reference
    {
      public:
        Reference (char* pt, size_t p)
          : pType(reinterpret_cast<unsigned char*>(pt)), pos(p) {}
        Reference(const Reference& rhs) : pType(rhs.pType), pos(rhs.pos) {}
        Reference& operator=(const Reference& rhs)
        {
          if(this == &rhs) return *this;
          pType = rhs.pType;
          pos = rhs.pos;
          return *this;
        }
        Reference operator=(unsigned char x)
        {
          if(0==(pos%2)) pType[pos/2] |= (x);       // low  4 bits
          else           pType[pos/2] |= (x << 4);  // high 4 bits
        }
        operator unsigned char() const {return (((pType[pos/2] >> ((0==(pos%2))?0:4))) & 0xF);}

      private:
        Reference();

      private:
        unsigned char*  pType;
        size_t          pos;
    };

    ~JxN1() {}
    JxN1(const string& str = "");
    JxN1(const char* str) {assert(str != NULL); *this = JxN1(string(str));}
    JxN1(const JxN1& rhs) {memcpy(mData, rhs.mData, capacity());}
    JxN1& operator=(const JxN1& rhs);
    unsigned char operator[] (size_t pos) const {assert(pos < SIZE); return (((mData[pos/2] >> ((0==(pos%2))?0:4))) & 0xF);}
    Reference operator[] (size_t pos) {assert(pos < SIZE); return Reference(mData, pos);}
    void clear() {memset(mData, 0, capacity());}
    void write(ofstream& outfile) {outfile.write(mData, capacity());}
    void read(ifstream& infile) {infile.read(mData, (SIZE%2)?(SIZE/2+1):(SIZE/2));}
    inline size_t max_size() const {return SIZE;}
    size_t size() const {return capacity();}
    string to_string() const;

  private:
    inline size_t capacity() const {return sizeof(mData)/sizeof(char);}
    inline void fill(const string& str)
    {
      for(size_t i = 0; (i < SIZE) && (i < str.size()); i++)
      {
        if(0==(i%2)) mData[i/2] |= (c2d(str[i]));       // low  4 bits
        else         mData[i/2] |= (c2d(str[i]) << 4);  // high 4 bits
      }
    }
    inline char c2d(char x)
    {
      if     ((x >= '0') && (x <= '9')) return (x-'0');
      else if((x >= 'A') && (x <= 'F')) return (x-'A'+10);
      else if((x >= 'a') && (x <= 'f')) return (x-'a'+10);
    }

  private:
    char            mData[(SIZE%2)?(SIZE/2+1):(SIZE/2)];
};

template <size_t SIZE>
JxN1<SIZE>::JxN1(const string& str)
{
  for(size_t i = 0; i < str.size(); i++)
  {
    assert( ((str[i] >= '0') && (str[i] <= '9')) ||
        ((str[i] >= 'A') && (str[i] <= 'F')) ||
        ((str[i] >= 'a') && (str[i] <= 'f'))
        );
  }

  memset(mData, 0, capacity());
  fill(str);
}

template <size_t SIZE>
JxN1<SIZE>& JxN1<SIZE>::operator=(const JxN1<SIZE>& rhs)
{
  if(this == &rhs) return *this;
  memcpy(mData, rhs.mData, capacity());
  return *this;
}

template <size_t SIZE>
string JxN1<SIZE>::to_string() const
{
  std::stringstream ss;
  for(size_t i = 0; i < SIZE; i++)
  {
    ss << std::uppercase << std::hex << static_cast<int>((*this)[i]);
  }
  return ss.str();
}


///////////////////////////////////////////////////////////////////////////////
template <typename T, size_t SIZE>
class KxTYPE
{
  friend class TestKxTYPE;
  friend class TestKxU1;
  friend class TestKxU2;
  friend class TestKxU4;
  friend class TestKxU8;
  friend class TestKxUf;
  friend class TestKxCf;
  friend class TestKxR4;
  friend class TestKxCn;
  friend class TestKxSn;

  public:
    class Reference
    {
      public:
        Reference (T* pt, size_t p) : pType(pt), pos(p) {}
        Reference(const Reference& rhs) : pType(rhs.pType), pos(rhs.pos) {}
        Reference& operator=(const Reference& rhs)
        {
          if(this == &rhs) return *this;
          pType = rhs.pType;
          pos = rhs.pos;
          return *this;
        }
        Reference operator=(const T& x)
        {
          pType[pos] = x; 
        }
        operator T() const {return pType[pos];}

      private:
        Reference();

      private:
        T*     pType;
        size_t pos;
    };

    ~KxTYPE() {}
    KxTYPE() {}
    T operator[] (size_t pos) const {assert(pos < SIZE); return mData[pos];}
    Reference operator[] (size_t pos) {assert(pos < SIZE); return Reference(mData, pos);}
    void clear() {for(size_t i = 0; i < SIZE; i++) mData[i].clear();}
    void write(ofstream& outfile) {for(size_t i = 0; i < SIZE; i++) mData[i].write(outfile);}
    void write(ofstream& outfile, VarUType::Type type) {for(size_t i = 0; i < SIZE; i++) mData[i].write(outfile, type);}
    void write(ofstream& outfile, size_t size) {for(size_t i = 0; i < SIZE; i++) mData[i].write(outfile, size);}
    void read(ifstream& infile) {for(size_t i = 0; i < SIZE; i++) mData[i].read(infile);}
    void read(ifstream& infile, VarUType::Type type) {for(size_t i = 0; i < SIZE; i++) mData[i].read(infile, type);}
    void read(ifstream& infile, size_t size) {for(size_t i = 0; i < SIZE; i++) mData[i].read(infile, size);}
    inline size_t max_size() const {return SIZE;}
    size_t size() const {size_t ret = 0; for(size_t i = 0; i < SIZE; i++) ret += mData[i].size(); return ret;}
    size_t size(VarUType::Type type) const {size_t ret = 0; for(size_t i = 0; i < SIZE; i++) ret += mData[i].size(type); return ret;}
    string to_string() const;

  private:
    KxTYPE(const KxTYPE& rhs);
    KxTYPE& operator=(const KxTYPE& rhs);

  private:
    T                 mData[SIZE];
};

template <typename T, size_t SIZE>
string KxTYPE<T, SIZE>::to_string() const
{
  std::stringstream ss;
  for(size_t i = 0; i < SIZE; i++)
  {
    ss << mData[i].to_string() << ",";
  }
  string ret = ss.str();
  if(!ret.empty()) ret = ret.substr(0, ret.size()-1);
  return ret;
}
///////////////////////////////////////////////////////////////////////////////
typedef CharArray<1>                          C1;
typedef VarCharArray<unsigned char>           Cn;
typedef VarCharArray<unsigned short>          Sn;
typedef StdfString                            Cf;
typedef VarUType                              Uf;
typedef NumericalType<unsigned char>          U1;
typedef NumericalType<unsigned short>         U2;
typedef NumericalType<unsigned int>           U4;
typedef NumericalType<unsigned long long>     U8;
typedef NumericalType<char>                   I1;
typedef NumericalType<short>                  I2;
typedef NumericalType<int>                    I4;
typedef NumericalType<long long>              I8;
typedef NumericalType<float>                  R4;
typedef NumericalType<double>                 R8;
typedef BitArray<1>                           B1;
typedef VarBitArray<unsigned char>            Bn;
typedef VarBitArray<unsigned short>           Dn;
typedef JxN1<1>                               N1;
///////////////////////////////////////////////////////////////////////////////
template <size_t SIZE>
class VarTypeArray
{
  friend class TestVn;

  public:
    ~VarTypeArray() {for(size_t i = 0; i < mData.size(); i++) delete mData[i];}
    VarTypeArray() {}
    VarTypeArray& addU1(const U1& u1) {             addTypeU1(); U1* data = new U1(u1); mData.push_back(data); return *this;}
    VarTypeArray& addU2(const U2& u2) {addTypeB0(); addTypeU2(); U2* data = new U2(u2); mData.push_back(data); return *this;}
    VarTypeArray& addU4(const U4& u4) {addTypeB0(); addTypeU4(); U4* data = new U4(u4); mData.push_back(data); return *this;}
    VarTypeArray& addI1(const I1& i1) {             addTypeI1(); I1* data = new I1(i1); mData.push_back(data); return *this;}
    VarTypeArray& addI2(const I2& i2) {addTypeB0(); addTypeI2(); I2* data = new I2(i2); mData.push_back(data); return *this;}
    VarTypeArray& addI4(const I4& i4) {addTypeB0(); addTypeI4(); I4* data = new I4(i4); mData.push_back(data); return *this;}
    VarTypeArray& addR4(const R4& r4) {addTypeB0(); addTypeR4(); R4* data = new R4(r4); mData.push_back(data); return *this;}
    VarTypeArray& addR8(const R8& r8) {addTypeB0(); addTypeR8(); R8* data = new R8(r8); mData.push_back(data); return *this;}
    VarTypeArray& addCn(const Cn& cn) {             addTypeCn(); Cn* data = new Cn(cn); mData.push_back(data); return *this;}
    VarTypeArray& addBn(const Bn& bn) {             addTypeBn(); Bn* data = new Bn(bn); mData.push_back(data); return *this;}
    VarTypeArray& addDn(const Dn& dn) {             addTypeDn(); Dn* data = new Dn(dn); mData.push_back(data); return *this;}
    VarTypeArray& addN1(const N1& n1) {             addTypeN1(); N1* data = new N1(n1); mData.push_back(data); return *this;}
    void clear() {for(size_t i = 0; i < mData.size(); i++) delete mData[i]; mData.clear();}
    void write(ofstream& outfile) {for(size_t i = 0; i < mData.size(); i++) mData[i]->write(outfile);}
    void read(ifstream& infile, size_t size);
    inline size_t max_size() const {return SIZE;}
    size_t size() const {size_t ret = 0; for(size_t i = 0; i < mData.size(); i++) ret += mData[i]->size(); return ret;}
    string to_string() const;

  private:
    class VnType : public DataType
    {
      public:
        enum Type {VN_B0=0, VN_U1=1, VN_U2=2, VN_U4=3, VN_I1=4, VN_I2=5, VN_I4=6, VN_R4=7, VN_R8=8, VN_CN=10, VN_BN=11, VN_DN=12, VN_N1=13};
        ~VnType() {}
        VnType(Type type) : mData(type) {}
        VnType(const VnType& rhs) : mData(rhs.mData) {}
        VnType& operator =(const VnType& rhs) {if(this == &rhs) return *this; mData = rhs.mData; return *this;}
        void write(ofstream& outfile) {outfile.write(&mData, size());}
        void read(ifstream& infile) {}
        size_t size() const {return sizeof(mData);}
        string to_string() const
        {
          const string NAME[14] = {"B0", "U1", "U2", "U4", "I1", "I2", "I4", "R4", "R8", "", "Cn", "Bn", "Dn", "N1"};
          return NAME[mData];
        }
      private:
        char                 mData;
    };

    VarTypeArray(const VarTypeArray& rhs);
    VarTypeArray& operator =(const VarTypeArray& rhs);

    inline void addTypeB0() {VnType* pad = new VnType(VnType::VN_B0); mData.push_back(pad);}
    inline void addTypeU1() {VnType* pad = new VnType(VnType::VN_U1); mData.push_back(pad);}
    inline void addTypeU2() {VnType* pad = new VnType(VnType::VN_U2); mData.push_back(pad);}
    inline void addTypeU4() {VnType* pad = new VnType(VnType::VN_U4); mData.push_back(pad);}
    inline void addTypeI1() {VnType* pad = new VnType(VnType::VN_I1); mData.push_back(pad);}
    inline void addTypeI2() {VnType* pad = new VnType(VnType::VN_I2); mData.push_back(pad);}
    inline void addTypeI4() {VnType* pad = new VnType(VnType::VN_I4); mData.push_back(pad);}
    inline void addTypeR4() {VnType* pad = new VnType(VnType::VN_R4); mData.push_back(pad);}
    inline void addTypeR8() {VnType* pad = new VnType(VnType::VN_R8); mData.push_back(pad);}
    inline void addTypeCn() {VnType* pad = new VnType(VnType::VN_CN); mData.push_back(pad);}
    inline void addTypeBn() {VnType* pad = new VnType(VnType::VN_BN); mData.push_back(pad);}
    inline void addTypeDn() {VnType* pad = new VnType(VnType::VN_DN); mData.push_back(pad);}
    inline void addTypeN1() {VnType* pad = new VnType(VnType::VN_N1); mData.push_back(pad);}

  private:
    std::vector<DataType*>    mData;
};

template <size_t SIZE>
void VarTypeArray<SIZE>::read(ifstream& infile, size_t size)
{
  while(this->size() < size)
  {
    char type = 0;
    infile.read(&type, sizeof(type));
    switch(type)
    {
      case VnType::VN_B0: {addTypeB0();}
        break;
      case VnType::VN_U1: {addTypeU1(); U1* data = new U1(); data->read(infile); mData.push_back(data);}
        break;
      case VnType::VN_U2: {addTypeU2(); U2* data = new U2(); data->read(infile); mData.push_back(data);}
        break;
      case VnType::VN_U4: {addTypeU4(); U4* data = new U4(); data->read(infile); mData.push_back(data);}
        break;
      case VnType::VN_I1: {addTypeI1(); I1* data = new I1(); data->read(infile); mData.push_back(data);}
        break;
      case VnType::VN_I2: {addTypeI2(); I2* data = new I2(); data->read(infile); mData.push_back(data);}
        break;
      case VnType::VN_I4: {addTypeI4(); I4* data = new I4(); data->read(infile); mData.push_back(data);}
        break;
      case VnType::VN_R4: {addTypeR4(); R4* data = new R4(); data->read(infile); mData.push_back(data);}
        break;
      case VnType::VN_R8: {addTypeR8(); R8* data = new R8(); data->read(infile); mData.push_back(data);}
        break;
      case VnType::VN_CN: {addTypeCn(); Cn* data = new Cn(); data->read(infile); mData.push_back(data);}
        break;
      case VnType::VN_BN: {addTypeBn(); Bn* data = new Bn(); data->read(infile); mData.push_back(data);}
        break;
      case VnType::VN_DN: {addTypeDn(); Dn* data = new Dn(); data->read(infile); mData.push_back(data);}
        break;
      case VnType::VN_N1: {addTypeN1(); N1* data = new N1(); data->read(infile); mData.push_back(data);}
        break;
    }
  }
}

template <size_t SIZE>
string VarTypeArray<SIZE>::to_string() const
{
  std::stringstream ss;
  for(size_t i = 0; i < mData.size(); i++)
  {
    ss << mData[i]->to_string() << ",";
  }
  string ret = ss.str();
  if(!ret.empty()) ret = ret.substr(0, ret.size()-1);
  return ret;
}


///////////////////////////////////////////////////////////////////////////////
typedef VarTypeArray<255>                     Vn;
///////////////////////////////////////////////////////////////////////////////


#endif