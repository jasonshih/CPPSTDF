#ifndef _DATA_TYPES_H_
#define _DATA_TYPES_H_

#include <new>             // nothrow
#include <string>          // basic_string
#include <vector>          // vector
//#include <utility>         // pair, make_pair
//#include <algorithm>       // for_each, copy, transform, count_if, find_if, min, max
//#include <functional>      // unary_function, mem_fun_ref, not1, modulus, equal_to
//#include <limits>          // numeric_limits<T>::max, numeric_limits<T>::min
#include <iterator>        // advance, ostream_iterator, back_inserter
#include <fstream>         // ifstream, ofstream, basic_ostream, dec, hex, uppercase
#include <sstream>         // basic_stringstream
#include <iomanip>         // setprecision, setw, setfill
#include <cassert>         // assert
#include <boost/bind.hpp>        // bind, ref
#include <boost/shared_ptr.hpp>  // shared_ptr

namespace helper
{
  inline bool isBigEndian()
  {
    union
    {
      uint16_t a;
      uint8_t b;
    } c;
    c.a = 0x0102;
    if(c.b == 1) return true;
    else return false;
  }

  struct isbdigitChar : public std::unary_function<char, bool>
  {
    inline bool operator() (char c) const {return ((c == '0') || (c == '1'));}
  };

  struct isbdigitString : public std::binary_function<const char*, size_t, bool>
  {
    inline bool operator() (const char* s, size_t l) const {return (0u == std::count_if(s, s+l, std::not1(helper::isbdigitChar())));}
  };

  struct isxdigitChar : public std::unary_function<char, bool>
  {
    inline bool operator() (char c) const {return (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'F')) || ((c >= 'a') && (c <= 'f')));}
  };

  struct isxdigitString : public std::binary_function<const char*, size_t, bool>
  {
    inline bool operator() (const char* s, size_t l) const {return (0u == std::count_if(s, s+l, std::not1(helper::isxdigitChar())));}
  };

  inline char c2d(char x)
  {
    assert(helper::isxdigitChar()(x));
    if     ((x >= '0') && (x <= '9')) return (x-'0');
    else if((x >= 'A') && (x <= 'F')) return (x-'A'+10);
    else if((x >= 'a') && (x <= 'f')) return (x-'a'+10);
    else return 0;
  }

  inline std::basic_string<char> trim_last_c(const std::basic_stringstream<char>& ss)
  {
    std::basic_string<char> ret(ss.str());
    if(!ret.empty()) ret.resize(ret.size()-1);
    return ret;
  }

  template <typename T> struct accumulator : public std::unary_function<T, T>
  {
    accumulator() : _v(0) {}
    inline T operator() (const T& v) {_v += v; return _v;}
    inline operator T() {return _v;}
    private: T _v;
  };
}
///////////////////////////////////////////////////////////////////////////////
class DataType
{
  public:
    typedef boost::shared_ptr<DataType> DataTypeSharedPtr;

    struct Cleaner : public std::unary_function<DataTypeSharedPtr, void>
    {
      inline void operator() (const DataTypeSharedPtr& ptr) {ptr->clear();}
    };

    struct Writer : public std::unary_function<DataTypeSharedPtr, void>
    {
      Writer(std::ofstream& outfile) : mFile(outfile) {}
      inline void operator() (const DataTypeSharedPtr& ptr) { ptr->write(mFile);}
      private: std::ofstream& mFile;
    };

    struct Reader : public std::unary_function<DataTypeSharedPtr, void>
    {
      Reader(std::ifstream& infile) : mFile(infile) {}
      inline void operator() (const DataTypeSharedPtr& ptr) { ptr->read(mFile, 0);}
      private: std::ifstream& mFile;
    };

    struct Stringer : public std::unary_function<DataTypeSharedPtr, std::basic_string<char> >
    {
      inline std::basic_string<char> operator() (const DataTypeSharedPtr& ptr) { return ptr->to_string();}
    };

    struct StorageCalculator : public std::unary_function<DataTypeSharedPtr, size_t>
    {
      inline size_t operator() (const DataTypeSharedPtr& ptr) { return _a(ptr->storage());}
      inline operator size_t () {return _a;}
      private: helper::accumulator<size_t> _a;
    };

    virtual ~DataType() {};
    virtual DataTypeSharedPtr clone() const = 0;
    virtual void clear() = 0;
    virtual void write(std::ofstream& outfile) = 0;
    virtual void read(std::ifstream& infile, size_t size = 0) = 0;
    virtual size_t storage() const = 0;
    virtual std::basic_string<char> to_string() const = 0;
    template <typename Derived> inline DataType& operator =(const Derived& value)
    {
      Derived* pThis = dynamic_cast<Derived*>(this);
      assert(NULL != pThis);
      *pThis = value;
      return *this;
    }
};
///////////////////////////////////////////////////////////////////////////////
template <size_t SIZE> class CharArray : public DataType
{
  friend class TestC1;
  friend class TestC5;
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const CharArray<SIZE>& ca) {os << ca.to_string(); return os;}

  public:
    ~CharArray() {}
    CharArray(const std::basic_string<char>& str) {init(); memcpy(mData, str.data(), std::min(SIZE, str.size()));}
    CharArray(const char* str = "") {assert(str != NULL); init(); memcpy(mData, str, std::min(SIZE, strlen(str)));}
    CharArray(char ch) {init(); memcpy(mData, &ch, sizeof(ch));}
    CharArray(const CharArray& rhs) {memcpy(mData, rhs.mData, SIZE);}
    CharArray& operator=(const CharArray& rhs);
    DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new CharArray(*this));}
    CharArray& operator+=(const CharArray& rhs);
    void clear() {init();}
    void write(std::ofstream& outfile) {outfile.write(mData, SIZE);}
    void read(std::ifstream& infile, size_t size = SIZE) {infile.read(mData, SIZE);}
    size_t storage() const {return SIZE;}
    std::basic_string<char> to_string() const;

  private:
    inline void init() {memset(mData, ' ', SIZE);}

  private:
    char            mData[SIZE];
};

template <size_t SIZE> CharArray<SIZE>& CharArray<SIZE>::operator=(const CharArray<SIZE>& rhs)
{
  if(this == &rhs) return *this;
  memcpy(mData, rhs.mData, SIZE);
  return *this;
}

template <size_t SIZE> std::basic_string<char> CharArray<SIZE>::to_string() const
{
//lidl, ?
#if OLD_STDF_VERSION
  char buffer[SIZE+3] = {'\'', 0, '\'', 0};
  memcpy(&buffer[1], mData, SIZE);
  return buffer;
#else
  char buffer[SIZE+1] = {0};
  memcpy(buffer, mData, SIZE);
  return buffer;
#endif
}
///////////////////////////////////////////////////////////////////////////////
template <typename T> class VarCharArray : public DataType
{
  friend class TestSn;
  friend class TestCn;
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const VarCharArray<T>& va) {os << va.to_string(); return os;}

  public:
    ~VarCharArray() {delete[] mData;}
    VarCharArray(const std::basic_string<char>& str) : mSize(0) {alloc(); fill(str.data(), str.size());}
    VarCharArray(const char* str = "") : mSize(0) {assert(str != NULL); alloc(); fill(str, strlen(str));}
    VarCharArray(char ch) : mSize(0) {alloc(); fill(&ch, 1u);}
    VarCharArray(const VarCharArray& rhs) : mSize(rhs.mSize) {mData = new char[capacity()]; memcpy(mData, rhs.mData, capacity());}
    VarCharArray& operator=(const VarCharArray& rhs);
    DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new VarCharArray(*this));}
    VarCharArray& operator+=(const VarCharArray& rhs) {fill(rhs.mData+sizeof(T), rhs.mSize); return *this;}
    void clear() { mSize = 0; memset(mData, 0, capacity());}
    void write(std::ofstream& outfile) {outfile.write(mData, sizeof(T)+mSize);}
    void read(std::ifstream& infile, size_t size = 0);
    size_t max_size() const {return ((1<<(8*sizeof(T)))-1);}
    size_t storage() const {return sizeof(T)+mSize;}
    std::basic_string<char> to_string() const;

  private:
    inline size_t capacity() const {return sizeof(T)+((1<<(8*sizeof(T)))-1);}
    inline void alloc() {mData = new char[capacity()]; memset(mData, 0, capacity());}
    inline size_t merged_size(size_t size) const
    {
      return (mSize+size > max_size())? max_size()-mSize : size;
    }
    inline void fill(const char* str, size_t len)
    {
      size_t size = merged_size(len);
      memcpy(mData+sizeof(T)+mSize, str, size);   // copy data
      mSize += size;
      memcpy(mData, &mSize, sizeof(T));           // copy length
    }

  private:
    T               mSize;
    char*           mData;
};

template <typename T> VarCharArray<T>& VarCharArray<T>::operator=(const VarCharArray& rhs)
{
  if(this == &rhs) return *this;
  mSize = rhs.mSize;
  memcpy(mData, rhs.mData, capacity());
  return *this;
}

template <typename T> void VarCharArray<T>::read(std::ifstream& infile, size_t size)
{
  infile.read(reinterpret_cast<char*>(&mSize), sizeof(T));

  memcpy(mData, &mSize, sizeof(T));
  if(0 != mSize)
  {
    infile.read(mData+sizeof(T), mSize);
  }
}

template <typename T> std::basic_string<char> VarCharArray<T>::to_string() const
{
  //char buffer[mSize+1]; // ISO C++ forbids variable-size array
  char *buffer = new (std::nothrow)char[mSize+1];
  if(NULL == buffer) return std::basic_string<char>();
  memset(buffer, 0, sizeof(buffer)/sizeof(char));
  memcpy(buffer, mData+sizeof(T), mSize);
  return std::basic_string<char>(buffer);
}
///////////////////////////////////////////////////////////////////////////////
template <size_t SIZE> class Cf : public DataType
{
  friend class TestCf;
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const Cf<SIZE>& cf) {os << cf.to_string(); return os;}

  public:
    ~Cf() {}
    Cf(const std::basic_string<char>& str) : mData(str) {}
    Cf(const char* str = "") {assert(str != NULL); mData = str;}
    Cf(char ch) : mData(1u, ch) {}
    Cf(const Cf& rhs) : mData(rhs.mData) {}
    Cf& operator=(const Cf& rhs) {if(this == &rhs) return *this; mData = rhs.mData; return *this;}
    DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new Cf(*this));}
    Cf& operator+=(const std::basic_string<char>& str) {mData += str; return *this;}
    bool operator==(const Cf& rhs) {return to_string()==rhs.to_string();}
    inline size_t max_size() const {return SIZE;}
    void clear() {mData.clear();}
    void write(std::ofstream& outfile) {std::basic_string<char> data = to_string(); outfile.write(data.data(), data.size());}
    void read(std::ifstream& infile, size_t size = SIZE);
    size_t storage() const {return SIZE;}
    std::basic_string<char> to_string() const;


  private:
    static const char PAD = ' ';

    std::basic_string<char>          mData;
};

template <size_t SIZE> void Cf<SIZE>::read(std::ifstream& infile, size_t size)
{
  if(SIZE==0) mData = "";
  else
  {
    char buffer[SIZE+1];
    memset(buffer, 0, SIZE+1);
    infile.read(buffer, SIZE);
    for(char* p=buffer+SIZE-1; (p != buffer)&&(*p == PAD); --p) {*p = 0;}
    mData = buffer;
  }
}

template <size_t SIZE> std::basic_string<char> Cf<SIZE>::to_string() const
{
  if(SIZE <= mData.size())
  {
    return mData.substr(0, SIZE);
  }
  else
  {
    std::basic_string<char> data = mData;
    data.append(SIZE-mData.size(), PAD);
    return data;
  }
}
///////////////////////////////////////////////////////////////////////////////
template <size_t SIZE> class Uf : public DataType
{
  friend class TestUf;
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const Uf<SIZE>& uf) {os << uf.to_string(); return os;}

  public:
    ~Uf() {}
    Uf(uint64_t value = 0u);
    Uf(const Uf& rhs) {memcpy(mData, rhs.mData, SIZE);}
    Uf& operator=(const Uf& rhs) {if(this == &rhs) return *this; memcpy(mData, rhs.mData, SIZE); return *this;}
    DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new Uf(*this));}
    uint64_t getValue() const;
    operator uint64_t() const {return getValue();}
    void clear() {memset(mData, 0, SIZE);}
    void write(std::ofstream& outfile) {outfile.write(mData, SIZE);}
    void read(std::ifstream& infile, size_t size = SIZE) {infile.read(mData, SIZE);}
    size_t storage() const {return SIZE;}
    std::basic_string<char> to_string() const {std::basic_stringstream<char> ss; ss << getValue(); return ss.str();}

  private:
    char            mData[SIZE];
};

template <size_t SIZE> Uf<SIZE>::Uf(uint64_t value)
{
  memset(mData, 0, SIZE);
  switch(SIZE)
  {
    case 1:  {uint8_t  data = value; memcpy(mData, &data, sizeof(data));}
      break;
    case 2:  {uint16_t data = value; memcpy(mData, &data, sizeof(data));}
      break;
    case 4:  {uint32_t data = value; memcpy(mData, &data, sizeof(data));}
      break;
    case 8:
    default: {uint64_t data = value; memcpy(mData, &data, sizeof(data));}
      break;
  }
}

template <size_t SIZE> uint64_t Uf<SIZE>::getValue() const
{
  switch(SIZE)
  {
    case 1:  {uint8_t  data = 0u; memcpy(&data, mData, sizeof(data)); return data;}
    case 2:  {uint16_t data = 0u; memcpy(&data, mData, sizeof(data)); return data;}
    case 4:  {uint32_t data = 0u; memcpy(&data, mData, sizeof(data)); return data;}
    case 8:
    default: {uint64_t data = 0u; memcpy(&data, mData, sizeof(data)); return data;}
  }
}
///////////////////////////////////////////////////////////////////////////////
template <typename T> class NumericalType : public DataType
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
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const NumericalType<T>& nt) {os << nt.to_string(); return os;}

  public:
    ~NumericalType() {}
    NumericalType(const T& value = 0) : mData(value) {}
    NumericalType(const NumericalType& rhs) : mData(rhs.mData) {}
    NumericalType& operator=(const NumericalType& rhs);
    DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new NumericalType(*this));}
    NumericalType& operator+=(const T& value) {mData += value; return *this;}
    NumericalType& operator++() {++mData;return *this;}
    NumericalType operator++(int) {NumericalType temp(*this); ++mData; return temp;}
    void clear() {mData = 0;}
    void write(std::ofstream& outfile) {outfile.write(reinterpret_cast<char*>(&mData), sizeof(mData));}
    void read(std::ifstream& infile, size_t size = sizeof(T)) {infile.read(reinterpret_cast<char*>(&mData), sizeof(mData));}
    T getValue() const {return mData;}
    operator T() const {return getValue();}
    T max() const {return std::numeric_limits<T>::max();}
    T min() const {return std::numeric_limits<T>::min();}
    size_t storage() const {return sizeof(T);}
    std::basic_string<char> to_string() const;

  private:
    T               mData;
};

template <typename T> NumericalType<T>& NumericalType<T>::operator=(const NumericalType& rhs)
{
  if(this == &rhs) return *this;
  mData = rhs.mData;
  return *this;
}

template <typename T> std::basic_string<char> NumericalType<T>::to_string() const
{
  std::basic_stringstream<char> ss;
#if OLD_STDF_VERSION
  ss.setf(std::ios::scientific | std::ios::uppercase);
  if(typeid(T) == typeid(float))
    ss<< std::setprecision(12) << std::dec << mData;
  else if(typeid(T) == typeid(double))
    ss<< std::setprecision(21) << std::dec << mData;
  else if(sizeof(T) > 1)
  {
    ss.unsetf(std::ios::scientific | std::ios::uppercase);
    ss << std::dec << mData;
  }
  else
  {
    ss.unsetf(std::ios::scientific | std::ios::uppercase);
    ss << std::dec << static_cast<int>(mData);
  }
#else
  if(sizeof(T) > 1) ss << std::dec << mData;
  else              ss << std::dec << static_cast<int>(mData);
#endif
  return ss.str();
}
///////////////////////////////////////////////////////////////////////////////
template <size_t SIZE> class BitArray : public DataType
{
  friend class BitReference;
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const BitArray<SIZE>& ba) {os << ba.to_string(); return os;}

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
    BitArray(const std::basic_string<char>& str) {assert(helper::isbdigitString()(str.data(), str.size())); fill(str.data(), str.size());}
    BitArray(const char* str = "") {assert(str != NULL); assert(helper::isbdigitString()(str, strlen(str))); fill(str, strlen(str));}
    BitArray(char ch) {assert(helper::isbdigitString()(&ch, 1u)); fill(&ch, 1u);}
    BitArray(const BitArray& rhs) {memcpy(mData, rhs.mData, SIZE);}
    BitArray& operator=(const BitArray& rhs);
    DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new BitArray(*this));}
    bool operator[] (size_t pos) const {assert(pos < 8*SIZE); return ((mData[pos/8] & (1 << (pos%8))) != 0);}
    BitReference operator[] (size_t pos) {assert(pos < 8*SIZE); return BitReference(mData, pos);}
    BitArray& reset(bool x) {for(size_t i = 0; i < SIZE; ++i){if(x) mData[i] = (char)0xFF;else mData[i] = (char)0x00;} return *this;}
    void clear() {reset(false);}
    void write(std::ofstream& outfile) {outfile.write(mData, SIZE);}
    void read(std::ifstream& infile, size_t size = SIZE) {infile.read(mData, SIZE);}
    size_t storage() const {return SIZE;}
    std::basic_string<char> to_string() const;

  private:
    inline void fill(const char* str, size_t len)
    {
      memset(mData, '\0', SIZE);

      for(size_t i = 0; ((i < 8*SIZE) && (i < len)); ++i)
      {
        if('1' == str[len-1-i])      mData[i/8] |=  (1 << (i%8));
        else if('0' == str[len-1-i]) mData[i/8] &= ~(1 << (i%8));
      }
    }

  private:
    char            mData[SIZE];
};

template <size_t SIZE> BitArray<SIZE>& BitArray<SIZE>::operator=(const BitArray<SIZE>& rhs)
{
  if(this == &rhs) return *this;
  memcpy(mData, rhs.mData, SIZE);
  return *this;
}

template <size_t SIZE> std::basic_string<char> BitArray<SIZE>::to_string() const
{
  std::basic_stringstream<char> ss;
  for(size_t i = 0; i < 8*SIZE; ++i)
  {
    ss << (*this)[8*SIZE-1-i];
  }
//lidl, ?
#if OLD_STDF_VERSION
   const char* s =ss.str().c_str();
   int sum = 0x00;
   for(int i = 0; i < 8; ++i) {sum = (sum << 1) + (*s++ & 1);}
   //while(*s == '0' || *s == '1') sum = (sum << 1) + (*s++ & 1);
   //for(int i = 0; i < 8; ++i) {sum <<= 1; if(str[i] == 1) ++sum; }
   std::basic_stringstream<char> sstr;
   sstr.setf(std::ios::uppercase);
   sstr<<"0x"<<std::hex<<sum;
   return sstr.str();
#else
  return ss.str();
#endif
}
///////////////////////////////////////////////////////////////////////////////
template <typename T> class VarBitArray : public DataType
{
  friend class BitReference;
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const VarBitArray<T>& va) {os << va.to_string(); return os;}

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
          return *this;
        }
        operator bool() const {return (pBits[sizeof(T)+(pos/8)] & (1 << (pos%8))) != 0;}

      private:
       BitReference();

      private:
        char*  pBits;
        size_t pos;
    };

    ~VarBitArray() {delete[] mData;}
    VarBitArray(const std::basic_string<char>& str);
    VarBitArray(const char* str = "");
    VarBitArray(char ch);
    VarBitArray(const VarBitArray& rhs) : mSize(rhs.mSize) {mData = new char[capacity()]; memcpy(mData, rhs.mData, capacity());}
    VarBitArray& operator=(const VarBitArray& rhs);
    DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new VarBitArray(*this));}
    VarBitArray& operator+=(const std::basic_string<char>& str) {fill(str.c_str(), str.size()); return *this;}
    bool operator[] (size_t pos) const {assert(pos < mSize); return ((mData[sizeof(T)+(pos/8)] & (1 << (pos%8))) != 0);}
    BitReference operator[] (size_t pos) {assert(pos < mSize); return BitReference(mData, pos);}
    void clear() {mSize = 0; memset(mData, 0, capacity());}
    void write(std::ofstream& outfile) {if( (mSize%8) == 0 ) outfile.write(mData, sizeof(T)+(mSize/8)); else outfile.write(mData, sizeof(T)+(mSize/8)+1);}
    void read(std::ifstream& infile, size_t size = 0);
    inline size_t max_size() const {return ((1<<(8*sizeof(T)))-1);}
    size_t storage() const {return ((mSize%8) == 0)?(sizeof(T)+(mSize/8)):(sizeof(T)+(mSize/8)+1);}
    std::basic_string<char> to_string() const;

  private:
    inline size_t capacity() const {return sizeof(T)+(1<<(8*sizeof(T)-3));}
    inline size_t merged_size(size_t size) const
    {
      return (mSize+size > max_size())? max_size()-mSize : size;
    }
    void   fill(const char* str, size_t len)
    {
      size_t size = merged_size(len);
      for(size_t i = mSize; i < mSize+size; ++i)
      {
        if('1' == str[mSize+size-i-1])      mData[sizeof(T)+(i/8)] |=  (1 << (i%8));
        else if('0' == str[mSize+size-i-1]) mData[sizeof(T)+(i/8)] &= ~(1 << (i%8));
      }
      mSize += size;
      memcpy(mData, &mSize, sizeof(T));                  // copy length
    }

  private:
    T               mSize;
    char*           mData;
};

template <typename T> VarBitArray<T>::VarBitArray(const std::basic_string<char>& str) : mSize(0)
{
  assert(helper::isbdigitString()(str.data(), str.size()));

  mData = new char[capacity()];
  memset(mData, 0, capacity());
  fill(str.data(), str.size());
}

template <typename T> VarBitArray<T>::VarBitArray(const char* str) : mSize(0)
{
  assert(str != NULL);
  assert(helper::isbdigitString()(str, strlen(str)));

  mData = new char[capacity()];
  memset(mData, 0, capacity());
  fill(str, strlen(str));
}

template <typename T> VarBitArray<T>::VarBitArray(char ch) : mSize(0)
{
  assert(helper::isbdigitChar()(ch));

  mData = new char[capacity()];
  memset(mData, 0, capacity());
  fill(&ch, 1u);
}

template <typename T> VarBitArray<T>& VarBitArray<T>::operator=(const VarBitArray<T>& rhs)
{
  if(this == &rhs) return *this;
  mSize = rhs.mSize;
  memcpy(mData, rhs.mData, capacity());
  return *this;
}

template <typename T> void VarBitArray<T>::read(std::ifstream& infile, size_t size)
{
  infile.read(reinterpret_cast<char*>(&mSize), sizeof(T));

//lidl, ?
#if OLD_STDF_VERSION
  //note: can't read more than once, because the mSize is no-const
  if(1 == sizeof(T) && 0 != mSize && mSize <= 32){mSize = (mSize*8) - 1;}
#endif
  memcpy(mData, &mSize, sizeof(T));
  if(0 != mSize)
  {
    if( (mSize%8) == 0 ) infile.read(mData+sizeof(T), (mSize/8));
    else                 infile.read(mData+sizeof(T), (mSize/8)+1);
  }
}

template <typename T> std::basic_string<char> VarBitArray<T>::to_string() const
{
  std::basic_stringstream<char> ss;
//lidl, ?
#if OLD_STDF_VERSION
  for(size_t i = 0; i < mSize; ++i)
  {
    if(0 != i && 0 == i%8) ss << " ";
    ss << (*this)[i];
  }

  //fill "0" for 8bit
  int len = mSize ? (8 - mSize%8) : 0;
  for(int i = 0; i < len; ++i) ss << "0";

  std::string line = ss.str();
  std::string bitline;
  std::string::size_type begIdx, endIdx;
  const std::string delims(" ");
  begIdx = line.find_first_not_of(delims);

  //adjust characters in reverse order
  while(begIdx != std::string::npos)
  {
    endIdx = line.find_first_of(delims, begIdx);

    if(endIdx == std::string::npos)
    {
      endIdx = line.length();
    }
    for(int i = endIdx - 1; i >= static_cast<int>(begIdx); --i)
    {
       bitline += line[i];
    }
    bitline += " ";

    begIdx = line.find_first_not_of(delims, endIdx);
  }
  ss.str(bitline);
#else
  for(size_t i = 0; i < mSize; ++i)
  {
    ss << (*this)[mSize-i-1];
  }
#endif
  return ss.str();
}
///////////////////////////////////////////////////////////////////////////////
template <size_t SIZE> class KxN1 : public DataType
{
  friend class TestKxN1;
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const KxN1<SIZE>& kn) {os << kn.to_string(); return os;}

  public:
    class Reference
    {
      public:
        Reference (char* pt, size_t p) : pType(reinterpret_cast<uint8_t*>(pt)), pos(p) {}
        Reference(const Reference& rhs) : pType(rhs.pType), pos(rhs.pos) {}
        Reference& operator=(const Reference& rhs)
        {
          if(this == &rhs) return *this;
          pType = rhs.pType;
          pos = rhs.pos;
          return *this;
        }
        Reference& operator=(uint8_t x)
        {
          if(0==(pos%2)) pType[pos/2] |= (x);       // low  4 bits
          else           pType[pos/2] |= (x << 4);  // high 4 bits
          return *this;
        }
        operator uint8_t() const {return (((pType[pos/2] >> ((0==(pos%2))?0:4))) & 0xF);}

      private:
        Reference();

      private:
        uint8_t*        pType;
        size_t          pos;
    };

    ~KxN1() {delete[] mData;}
    KxN1(const std::basic_string<char>& str) {assert(helper::isxdigitString()(str.data(), str.size())); mData = new char[capacity()]; memset(mData, 0, capacity()); fill(str.data(), str.size());}
    KxN1(const char* str = "") {assert(str != NULL); assert(helper::isxdigitString()(str, strlen(str))); mData = new char[capacity()]; memset(mData, 0, capacity()); fill(str, strlen(str));}
    KxN1(char ch) {assert(helper::isxdigitString()(&ch, 1u)); mData = new char[capacity()]; memset(mData, 0, capacity()); fill(&ch, 1u);}
    KxN1(const KxN1& rhs) {mData = new char[capacity()]; memcpy(mData, rhs.mData, capacity());}
    KxN1& operator=(const KxN1& rhs) {if(this == &rhs) return *this; memcpy(mData, rhs.mData, capacity()); return *this;}
    DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new KxN1(*this));}
    uint8_t operator[] (size_t pos) const {assert(pos < SIZE); return (((mData[pos/2] >> ((0==(pos%2))?0:4))) & 0xF);}
    Reference operator[] (size_t pos) {assert(pos < SIZE); return Reference(mData, pos);}
    void clear() {memset(mData, 0, capacity());}
    void write(std::ofstream& outfile) {outfile.write(mData, capacity());}
    void read(std::ifstream& infile, size_t size = (SIZE%2)?(SIZE/2+1):(SIZE/2)) {infile.read(mData, (SIZE%2)?(SIZE/2+1):(SIZE/2));}
    inline size_t max_size() const {return SIZE;}
    size_t storage() const {return capacity();}
    std::basic_string<char> to_string() const;

  private:
    inline size_t capacity() const {return (SIZE%2)?(SIZE/2+1):(SIZE/2);}
    inline void fill(const char* str, size_t len)
    {
      for(size_t i = 0; (i < SIZE) && (i < len); ++i)
      {
        if(0==(i%2)) mData[i/2] |= (helper::c2d(str[i]));       // low  4 bits
        else         mData[i/2] |= (helper::c2d(str[i]) << 4);  // high 4 bits
      }
    }

  private:
    char*           mData;
};

template <size_t SIZE> std::basic_string<char> KxN1<SIZE>::to_string() const
{
  std::basic_stringstream<char> ss;
  for(size_t i = 0; i < SIZE; ++i)
  {
    ss << std::uppercase << std::hex << static_cast<int>((*this)[i]);
  }
  return ss.str();
}
///////////////////////////////////////////////////////////////////////////////
class JxN1 : public DataType
{
  friend class TestJxN1;
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const JxN1& jn) {os << jn.to_string(); return os;}

  public:
    class Reference
    {
      public:
        Reference (std::vector<char>* pt, size_t p) : pType(pt), pos(p) {}
        Reference(const Reference& rhs) : pType(rhs.pType), pos(rhs.pos) {}
        Reference& operator=(const Reference& rhs)
        {
          if(this == &rhs) return *this;
          pType = rhs.pType;
          pos = rhs.pos;
          return *this;
        }
        Reference& operator=(uint8_t x)
        {
          if(0==(pos%2)) (*pType)[pos/2] |= (x);       // low  4 bits
          else           (*pType)[pos/2] |= (x << 4);  // high 4 bits
          return *this;
        }
        operator uint8_t() const {return ((((*pType)[pos/2] >> ((0==(pos%2))?0:4))) & 0xF);}

      private:
        Reference();

      private:
        std::vector<char>*   pType;
        size_t               pos;
    };

    ~JxN1() {}
    JxN1(const std::basic_string<char>& str) :mSize(0) {assert(helper::isxdigitString()(str.data(), str.size())); init(str.size()); fill(str.data(), str.size());}
    JxN1(const char* str = "") :mSize(0) {assert(str != NULL); assert(helper::isxdigitString()(str, strlen(str))); init(strlen(str)); fill(str, strlen(str));}
    JxN1(size_t n, char ch) :mSize(0) {assert(helper::isxdigitString()(&ch, 1u)); init(n); fill(n, ch);}
    JxN1(size_t size) :mSize(size) {init(size);}
    JxN1(const JxN1& rhs) :mSize(rhs.mSize), mData(rhs.mData) {}
    JxN1& operator=(const JxN1& rhs) {if(this == &rhs) return *this; mSize = rhs.mSize; std::vector<char>(rhs.mData).swap(mData); return *this;}
    DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new JxN1(*this));}
    uint8_t operator[] (size_t pos) const {assert(pos < mSize); return (((mData[pos/2] >> ((0==(pos%2))?0:4))) & 0xF);}
    Reference operator[] (size_t pos) {assert(pos < mSize); return Reference(&mData, pos);}
    JxN1& add(const std::basic_string<char>& str) {assert(helper::isxdigitString()(str.data(), str.size())); init(mSize+str.size()); fill(str.data(), str.size()); return *this;}
    JxN1& add(const char* str) {assert(str != NULL); assert(helper::isxdigitString()(str, strlen(str))); init(mSize+strlen(str)); fill(str, strlen(str)); return *this;}
    inline size_t size() const {return mSize;}
    void clear() {mSize = 0; std::vector<char>().swap(mData);}
    void write(std::ofstream& outfile) {for(size_t i = 0; i < mData.size(); ++i) outfile.write(&(mData[i]), sizeof(char));}
    void read(std::ifstream& infile, size_t size) {mSize = size; init(size); for(size_t i = 0; i < mData.size(); ++i) infile.read(&(mData[i]), sizeof(char));}
    size_t storage() const {return mData.size();}
    std::basic_string<char> to_string() const
    {
      std::basic_stringstream<char> ss;
      for(size_t i = 0; i < mSize; ++i)
      {
#if OLD_STDF_VERSION
        ss << "0x" << std::uppercase << std::hex << static_cast<int>((*this)[i]) << ", ";
#else
        ss << std::uppercase << std::hex << static_cast<int>((*this)[i]);
#endif
      }
      return ss.str();
    }

  private:
    inline void init(size_t size) {mData.resize((size%2)?(size/2+1):(size/2), 0);}
    inline void fill(const char* str, size_t len)
    {
      for(size_t i = mSize; i < mSize+len; ++i)
      {
        if(0==(i%2)) mData[i/2] |= (helper::c2d(str[i-mSize]));       // low  4 bits
        else         mData[i/2] |= (helper::c2d(str[i-mSize]) << 4);  // high 4 bits
      }
      mSize += len;
    }
    inline void fill(size_t n, char ch)
    {
      for(size_t i = mSize; i < mSize+n; ++i)
      {
        if(0==(i%2)) mData[i/2] |= (helper::c2d(ch));       // low  4 bits
        else         mData[i/2] |= (helper::c2d(ch) << 4);  // high 4 bits
      }
      mSize += n;
    }

  private:
    size_t               mSize;
    std::vector<char>    mData;
};
///////////////////////////////////////////////////////////////////////////////
template <typename T, size_t SIZE> class KxTYPE : public DataType
{
  friend class TestKxTYPE;
  friend class TestKxU1;
  friend class TestKxU2;
  friend class TestKxU4;
  friend class TestKxU8;
  friend class TestKxUf;
  friend class TestKxR4;
  friend class TestKxCn;
  friend class TestKxSn;
  friend class TestKxCf;
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const KxTYPE<T, SIZE>& kt) {os << kt.to_string(); return os;}

  public:
    ~KxTYPE() {delete[] mData;}
    KxTYPE() :mData(new T[SIZE]) {}
    KxTYPE(const KxTYPE& rhs) :mData(new T[SIZE]) {std::copy(rhs.mData, rhs.mData+SIZE, mData);}
    KxTYPE& operator=(const KxTYPE& rhs) {if(this != &rhs) std::copy(rhs.mData, rhs.mData+SIZE, mData); return *this;}
    DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new KxTYPE(*this));}
    const T& operator[] (size_t pos) const {assert(pos < SIZE); return mData[pos];}
    T& operator[] (size_t pos) {assert(pos < SIZE); return mData[pos];}
    inline size_t max_size() const {return SIZE;}
    //void clear() {for(size_t i = 0; i < SIZE; ++i) mData[i].clear();}
    void clear() {std::for_each(mData, mData+SIZE, boost::bind(&T::clear, _1));}
    //void write(std::ofstream& outfile) {for(size_t i = 0; i < SIZE; ++i) mData[i].write(outfile);}
    void write(std::ofstream& outfile) {std::for_each(mData, mData+SIZE, boost::bind(&T::write, _1, boost::ref(outfile)));}
    void read(std::ifstream& infile, size_t size = SIZE) {for(size_t i = 0; i < SIZE; ++i) mData[i].read(infile);}
    //size_t storage() const {size_t ret = 0; for(size_t i = 0; i < SIZE; ++i) ret += mData[i].storage(); return ret;}
    size_t storage() const {helper::accumulator<size_t> a; std::for_each(mData, mData+SIZE, boost::bind(boost::ref(a), boost::bind(&T::storage, _1))); return a;}
    std::basic_string<char> to_string() const;

  private:
    T*                mData;
};

template <typename T, size_t SIZE> std::basic_string<char> KxTYPE<T, SIZE>::to_string() const
{
  std::basic_stringstream<char> ss;
  std::ostream_iterator<std::basic_string<char> > o(ss, ",");
  std::transform(mData, mData+SIZE, o, std::mem_fun_ref(&T::to_string));
  return helper::trim_last_c(ss);
}
///////////////////////////////////////////////////////////////////////////////
template <typename T> class JxTYPE : public DataType
{
  friend class TestJxTYPE;
  friend class TestJxU1;
  friend class TestJxU2;
  friend class TestJxU4;
  friend class TestJxU8;
  friend class TestJxUf;
  friend class TestJxR4;
  friend class TestJxCn;
  friend class TestJxSn;
  friend class TestJxCf;
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const JxTYPE<T>& jt) {os << jt.to_string(); return os;}

  public:
    ~JxTYPE() {}
    JxTYPE(size_t size = 0) :mData(size) {}
    JxTYPE(const JxTYPE& rhs) {std::vector<T>(rhs.mData).swap(mData);}
    JxTYPE& operator=(const JxTYPE& rhs) {if(this != &rhs) std::vector<T>(rhs.mData).swap(mData); return *this;}
    DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new JxTYPE(*this));}
    const T& operator[] (size_t pos) const {assert(pos < mData.size()); return mData[pos];}
    T& operator[] (size_t pos) {assert(pos < mData.size()); return mData[pos];}
    JxTYPE& add(const T& t) {mData.push_back(t); return *this;}
    inline size_t size() const {return mData.size();}
    void clear() {std::vector<T>().swap(mData);}
    //void write(std::ofstream& outfile) {for(size_t i = 0; i < mData.size(); ++i) mData[i].write(outfile);}
    void write(std::ofstream& outfile) {std::for_each(mData.begin(), mData.end(), boost::bind(&T::write, _1, boost::ref(outfile)));}
    void read(std::ifstream& infile, size_t size) {mData.clear(); for(size_t i = 0; i < size; ++i) {mData.push_back(T()); mData[i].read(infile);}}
    //size_t storage() const {size_t ret = 0; for(size_t i = 0; i < mData.size(); ++i) ret += mData[i].storage(); return ret;}
    size_t storage() const {helper::accumulator<size_t> a; std::for_each(mData.begin(), mData.end(), boost::bind(boost::ref(a), boost::bind(&T::storage, _1))); return a;}
    std::basic_string<char> to_string() const;

  private:
    std::vector<T>       mData;
};

template <typename T> std::basic_string<char> JxTYPE<T>::to_string() const
{
  std::basic_stringstream<char> ss;
  std::ostream_iterator<std::basic_string<char> > o(ss, ",");
  std::transform(mData.begin(), mData.end(), o, std::mem_fun_ref(&T::to_string));
  return helper::trim_last_c(ss);
}
///////////////////////////////////////////////////////////////////////////////
class MxCf : public DataType
{
  friend class TestMxCf;
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const MxCf& mf) {os << mf.to_string(); return os;}

  public:
    ~MxCf() {}
    MxCf(size_t size = 0) :mStringSize(0), mData(size) {}
    MxCf(const MxCf& rhs) :mStringSize(rhs.mStringSize) {std::vector<std::basic_string<char> >(rhs.mData).swap(mData);}
    MxCf& operator=(const MxCf& rhs) {if(this != &rhs) {mStringSize = rhs.mStringSize; std::vector<std::basic_string<char> >(rhs.mData).swap(mData);} return *this;}
    DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new MxCf(*this));}
    const std::basic_string<char>& operator[] (size_t pos) const {assert(pos < mData.size()); return mData[pos];}
    std::basic_string<char>& operator[] (size_t pos) {assert(pos < mData.size()); return mData[pos];}
    MxCf& add(const std::basic_string<char>& t) {mData.push_back(t); return *this;}
    inline size_t size() const {return mData.size();}
    inline size_t string_size() const {size_t max = 0; for(size_t i = 0; i < mData.size(); ++i) max = std::max(max, mData[i].size()); return max;}
    void string_size(size_t size) {mStringSize = size; resize();}
    void clear() {std::vector<std::basic_string<char> >().swap(mData);}
    //void write(std::ofstream& outfile) {for(size_t i = 0; i < mData.size(); ++i) outfile.write(mData[i].data(), mData[i].size());}
    void write(std::ofstream& outfile)
    {
      std::for_each(mData.begin(), mData.end(),
          boost::bind(&std::ofstream::write, boost::ref(outfile), boost::bind(&std::basic_string<char>::data, _1), boost::bind(&std::basic_string<char>::size, _1)));
    }
    void read(std::ifstream& infile, size_t size)
    {
      clear();
      for(size_t i = 0; i < size; ++i)
      {
        mData.push_back(read(infile));
      }
    }
    size_t storage() const {return (size() * string_size());}
    std::basic_string<char> to_string() const
    {
      std::basic_stringstream<char> ss;
      std::ostream_iterator<std::basic_string<char> > o(ss, ",");
      std::copy(mData.begin(), mData.end(), o);
      return helper::trim_last_c(ss);
    }

  private:
    //void resize() {for(size_t i = 0; i < mData.size(); ++i) mData[i].resize(mStringSize, PAD);}
    void resize() {std::for_each(mData.begin(), mData.end(), boost::bind(&std::basic_string<char>::resize, _1, mStringSize, PAD));}
    inline std::basic_string<char> read(std::ifstream& infile)
    {
      if(0 == mStringSize) return "";
      //char buffer[mStringSize+1]; // ISO C++ forbids variable-size array
      char *buffer  = new (std::nothrow)char[mStringSize+1];
      if(NULL == buffer) return "";
      memset(buffer, 0, mStringSize+1);
      infile.read(buffer, mStringSize);
      return buffer;
    }

  private:
    static const char PAD = ' ';

    size_t                                         mStringSize;
    std::vector<std::basic_string<char> >          mData;
};
///////////////////////////////////////////////////////////////////////////////
class MxUf : public DataType
{
  friend class TestMxUf;
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const MxUf& uf) {os << uf.to_string(); return os;}

  public:
    ~MxUf() {}
    MxUf(size_t size = 0) :mByteSize(1u), mData(size) {}
    // MxUf(const MxUf& rhs); // bit copy by compiler is faster
    MxUf& operator=(const MxUf& rhs) {if(this != &rhs) {mByteSize = rhs.mByteSize; std::vector<uint64_t>(rhs.mData).swap(mData);} return *this;}
    DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new MxUf(*this));}
    uint64_t operator[] (size_t pos) const {assert(pos < mData.size()); return mData[pos];}
    uint64_t& operator[] (size_t pos) {assert(pos < mData.size()); return mData[pos];}
    MxUf& add(uint64_t t) {mData.push_back(t); return *this;}
    inline size_t size() const {return mData.size();}
    inline uint8_t byte_size() const {uint64_t max = 0; for(size_t i = 0; i < mData.size(); ++i) max = std::max(max, mData[i]); return byteSize(max);}
    void byte_size(uint8_t size) {assert((1u == size) || (2u == size) || (4u == size) || (8u == size)); mByteSize = size; byteResize();}
    void clear() {std::vector<uint64_t>().swap(mData);}
    void write(std::ofstream& outfile)
    {
      switch(mByteSize)
      {
        case 1u: {uint8_t  d; for(size_t i = 0; i < mData.size(); ++i) {d = mData[i]; outfile.write(reinterpret_cast<char*>(&d), 1u);}}
                 break;
        case 2u: {uint16_t d; for(size_t i = 0; i < mData.size(); ++i) {d = mData[i]; outfile.write(reinterpret_cast<char*>(&d), 2u);}}
                 break;
        case 4u: {uint32_t d; for(size_t i = 0; i < mData.size(); ++i) {d = mData[i]; outfile.write(reinterpret_cast<char*>(&d), 4u);}}
                 break;
        case 8u:
        default: {uint64_t d; for(size_t i = 0; i < mData.size(); ++i) {d = mData[i]; outfile.write(reinterpret_cast<char*>(&d), 8u);}}
                 break;
      }
    }
    void read(std::ifstream& infile, size_t size)
    {
      clear();
      switch(mByteSize)
      {
        case 1u: {uint8_t  d; for(size_t i = 0; i < size; ++i) {infile.read(reinterpret_cast<char*>(&d), 1u); mData.push_back(d);}}
                 break;
        case 2u: {uint16_t d; for(size_t i = 0; i < size; ++i) {infile.read(reinterpret_cast<char*>(&d), 2u); mData.push_back(d);}}
                 break;
        case 4u: {uint32_t d; for(size_t i = 0; i < size; ++i) {infile.read(reinterpret_cast<char*>(&d), 4u); mData.push_back(d);}}
                 break;
        case 8u:
        default: {uint64_t d; for(size_t i = 0; i < size; ++i) {infile.read(reinterpret_cast<char*>(&d), 8u); mData.push_back(d);}}
                 break;
      }
    }
    size_t storage() const {return (size() * byte_size());}
    std::basic_string<char> to_string() const
    {
      std::basic_stringstream<char> ss;
      std::ostream_iterator<uint64_t> o(ss, ",");
      std::copy(mData.begin(), mData.end(), o);
      return helper::trim_last_c(ss);
    }

  private:
    void byteResize()
    {
      const uint64_t y = (1llu << (8*mByteSize));
      //if(8u != mByteSize) for(size_t i = 0; i < mData.size(); ++i) mData[i] %= y;
      if(8u != mByteSize) std::transform(mData.begin(), mData.end(), mData.begin(), boost::bind(std::modulus<uint64_t>(), _1, y));
    }
    uint8_t byteSize(uint64_t val) const
    {
      if(     val < ((uint8_t ) -1)) return 1u;
      else if(val < ((uint16_t) -1)) return 2u;
      else if(val < ((uint32_t) -1)) return 4u;
      else                           return 8u;
    }

  private:
    uint8_t                          mByteSize;
    std::vector<uint64_t>            mData;
};
///////////////////////////////////////////////////////////////////////////////
typedef CharArray<1>                          C1;
typedef VarCharArray<uint8_t>                 Cn;
typedef VarCharArray<uint16_t>                Sn;
typedef NumericalType<uint8_t>                U1;
typedef NumericalType<uint16_t>               U2;
typedef NumericalType<uint32_t>               U4;
typedef NumericalType<uint64_t>               U8;
typedef NumericalType<char>                   I1;
typedef NumericalType<int16_t>                I2;
typedef NumericalType<int32_t>                I4;
typedef NumericalType<int64_t>                I8;
typedef NumericalType<float>                  R4;
typedef NumericalType<double>                 R8;
typedef BitArray<1>                           B1;
typedef VarBitArray<uint8_t>                  Bn;
typedef VarBitArray<uint16_t>                 Dn;
typedef KxN1<1>                               N1;
///////////////////////////////////////////////////////////////////////////////
template <size_t SIZE> class VarTypeArray : public DataType
{
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const VarTypeArray<SIZE>& va) {os << va.to_string(); return os;}
  friend class TestVn;

  public:
    ~VarTypeArray() {}
    VarTypeArray() :mTypeSize(0) {}
    VarTypeArray(const VarTypeArray& rhs) :mTypeSize(rhs.mTypeSize)
    {
      std::vector<DataTypeSharedPtr> tmp; tmp.reserve(rhs.mData.size());
      std::transform(rhs.mData.begin(), rhs.mData.end(), std::back_inserter(tmp), boost::bind(&DataType::clone, _1));
      tmp.swap(mData);
    }
    VarTypeArray& operator=(const VarTypeArray& rhs) {if(this == &rhs) return *this; mTypeSize = rhs.mTypeSize; std::vector<DataTypeSharedPtr> tmp(rhs.mData); tmp.swap(mData); return *this;}
    DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new VarTypeArray(*this));}

    VarTypeArray& addU1(const U1& u1) {                     add(createTypeU1()); add(U1SharedPtr(new U1(u1))); return *this;}
    VarTypeArray& addU2(const U2& u2) {add(createTypeB0()); add(createTypeU2()); add(U2SharedPtr(new U2(u2))); return *this;}
    VarTypeArray& addU4(const U4& u4) {add(createTypeB0()); add(createTypeU4()); add(U4SharedPtr(new U4(u4))); return *this;}
    VarTypeArray& addI1(const I1& i1) {                     add(createTypeI1()); add(I1SharedPtr(new I1(i1))); return *this;}
    VarTypeArray& addI2(const I2& i2) {add(createTypeB0()); add(createTypeI2()); add(I2SharedPtr(new I2(i2))); return *this;}
    VarTypeArray& addI4(const I4& i4) {add(createTypeB0()); add(createTypeI4()); add(I4SharedPtr(new I4(i4))); return *this;}
    VarTypeArray& addR4(const R4& r4) {add(createTypeB0()); add(createTypeR4()); add(R4SharedPtr(new R4(r4))); return *this;}
    VarTypeArray& addR8(const R8& r8) {add(createTypeB0()); add(createTypeR8()); add(R8SharedPtr(new R8(r8))); return *this;}
    VarTypeArray& addCn(const Cn& cn) {                     add(createTypeCn()); add(CnSharedPtr(new Cn(cn))); return *this;}
    VarTypeArray& addBn(const Bn& bn) {                     add(createTypeBn()); add(BnSharedPtr(new Bn(bn))); return *this;}
    VarTypeArray& addDn(const Dn& dn) {                     add(createTypeDn()); add(DnSharedPtr(new Dn(dn))); return *this;}
    VarTypeArray& addN1(const N1& n1) {                     add(createTypeN1()); add(N1SharedPtr(new N1(n1))); return *this;}
    void clear() {std::vector<DataTypeSharedPtr>().swap(mData);}
    void write(std::ofstream& outfile) {std::for_each(mData.begin(), mData.end(), boost::bind(&DataType::write, _1, boost::ref(outfile)));}
    void read(std::ifstream& infile, size_t size);
    size_t size() const {return (mData.size() - mTypeSize);}
    inline size_t max_size() const {return SIZE;}
    //size_t storage() const {size_t ret = 0; for(size_t i = 0; i < mData.size(); ++i) ret += mData[i]->storage(); return ret;}
    size_t storage() const {helper::accumulator<size_t> a; std::for_each(mData.begin(), mData.end(), boost::bind(boost::ref(a), boost::bind(&DataType::storage, _1))); return a;}
    std::basic_string<char> to_string() const;

  private:
    typedef boost::shared_ptr<U1> U1SharedPtr;
    typedef boost::shared_ptr<U2> U2SharedPtr;
    typedef boost::shared_ptr<U4> U4SharedPtr;
    typedef boost::shared_ptr<I1> I1SharedPtr;
    typedef boost::shared_ptr<I2> I2SharedPtr;
    typedef boost::shared_ptr<I4> I4SharedPtr;
    typedef boost::shared_ptr<R4> R4SharedPtr;
    typedef boost::shared_ptr<R8> R8SharedPtr;
    typedef boost::shared_ptr<Cn> CnSharedPtr;
    typedef boost::shared_ptr<Bn> BnSharedPtr;
    typedef boost::shared_ptr<Dn> DnSharedPtr;
    typedef boost::shared_ptr<N1> N1SharedPtr;

    class VnType : public DataType
    {
      friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const VnType& vt) {os << vt.to_string(); return os;}
      public:
        enum Type {VN_B0=0, VN_U1=1, VN_U2=2, VN_U4=3, VN_I1=4, VN_I2=5, VN_I4=6, VN_R4=7, VN_R8=8, VN_CN=10, VN_BN=11, VN_DN=12, VN_N1=13};
        ~VnType() {}
        VnType(Type type) : mType(type) {}
        VnType(const VnType& rhs) : mType(rhs.mType) {}
        VnType& operator=(const VnType& rhs) {if(this != &rhs) mType = rhs.mType; return *this;}
        DataTypeSharedPtr clone() const {return  DataTypeSharedPtr(new VnType(*this));}
        void clear() {mType = 0;}
        void write(std::ofstream& outfile) {outfile.write(&mType, storage());}
        void read(std::ifstream& infile, size_t size = 0) {}
        size_t storage() const {return sizeof(mType);}
        std::basic_string<char> to_string() const
        {
          const std::basic_string<char> NAME[14] = {"B0", "U1", "U2", "U4", "I1", "I2", "I4", "R4", "R8", "", "Cn", "Bn", "Dn", "N1"};
          return NAME[static_cast<int>(mType)];
        }
      private:
        char                 mType;
    };

    inline void add(const DataTypeSharedPtr& data) {mData.push_back(data);}
    inline DataTypeSharedPtr createTypeB0() {++mTypeSize; return DataTypeSharedPtr(new VnType(VnType::VN_B0));}
    inline DataTypeSharedPtr createTypeU1() {++mTypeSize; return DataTypeSharedPtr(new VnType(VnType::VN_U1));}
    inline DataTypeSharedPtr createTypeU2() {++mTypeSize; return DataTypeSharedPtr(new VnType(VnType::VN_U2));}
    inline DataTypeSharedPtr createTypeU4() {++mTypeSize; return DataTypeSharedPtr(new VnType(VnType::VN_U4));}
    inline DataTypeSharedPtr createTypeI1() {++mTypeSize; return DataTypeSharedPtr(new VnType(VnType::VN_I1));}
    inline DataTypeSharedPtr createTypeI2() {++mTypeSize; return DataTypeSharedPtr(new VnType(VnType::VN_I2));}
    inline DataTypeSharedPtr createTypeI4() {++mTypeSize; return DataTypeSharedPtr(new VnType(VnType::VN_I4));}
    inline DataTypeSharedPtr createTypeR4() {++mTypeSize; return DataTypeSharedPtr(new VnType(VnType::VN_R4));}
    inline DataTypeSharedPtr createTypeR8() {++mTypeSize; return DataTypeSharedPtr(new VnType(VnType::VN_R8));}
    inline DataTypeSharedPtr createTypeCn() {++mTypeSize; return DataTypeSharedPtr(new VnType(VnType::VN_CN));}
    inline DataTypeSharedPtr createTypeBn() {++mTypeSize; return DataTypeSharedPtr(new VnType(VnType::VN_BN));}
    inline DataTypeSharedPtr createTypeDn() {++mTypeSize; return DataTypeSharedPtr(new VnType(VnType::VN_DN));}
    inline DataTypeSharedPtr createTypeN1() {++mTypeSize; return DataTypeSharedPtr(new VnType(VnType::VN_N1));}

  private:
    size_t                            mTypeSize;
    std::vector<DataTypeSharedPtr>    mData;
};

template <size_t SIZE> void VarTypeArray<SIZE>::read(std::ifstream& infile, size_t size)
{
  while(this->storage() < size)
  {
    char type = 0;
    infile.read(&type, sizeof(type));
    switch(type)
    {
      case VnType::VN_B0: {add(createTypeB0());}
        break;
      case VnType::VN_U1: {add(createTypeU1()); U1SharedPtr data(new U1()); data->read(infile); add(data);}
        break;
      case VnType::VN_U2: {add(createTypeU2()); U2SharedPtr data(new U2()); data->read(infile); add(data);}
        break;
      case VnType::VN_U4: {add(createTypeU4()); U4SharedPtr data(new U4()); data->read(infile); add(data);}
        break;
      case VnType::VN_I1: {add(createTypeI1()); I1SharedPtr data(new I1()); data->read(infile); add(data);}
        break;
      case VnType::VN_I2: {add(createTypeI2()); I2SharedPtr data(new I2()); data->read(infile); add(data);}
        break;
      case VnType::VN_I4: {add(createTypeI4()); I4SharedPtr data(new I4()); data->read(infile); add(data);}
        break;
      case VnType::VN_R4: {add(createTypeR4()); R4SharedPtr data(new R4()); data->read(infile); add(data);}
        break;
      case VnType::VN_R8: {add(createTypeR8()); R8SharedPtr data(new R8()); data->read(infile); add(data);}
        break;
      case VnType::VN_CN: {add(createTypeCn()); CnSharedPtr data(new Cn()); data->read(infile); add(data);}
        break;
#if OLD_STDF_VERSION
      case VnType::VN_BN: {add(createTypeBn()); CnSharedPtr data(new Cn()); data->read(infile); add(data);}
        break;
#else
      case VnType::VN_BN: {add(createTypeBn()); BnSharedPtr data(new Bn()); data->read(infile); add(data);}
        break;
#endif
      case VnType::VN_DN: {add(createTypeDn()); DnSharedPtr data(new Dn()); data->read(infile); add(data);}
        break;
      case VnType::VN_N1: {add(createTypeN1()); N1SharedPtr data(new N1()); data->read(infile); add(data);}
        break;
    }
  }
}

template <size_t SIZE> std::basic_string<char> VarTypeArray<SIZE>::to_string() const
{
  std::basic_stringstream<char> ss;
  std::ostream_iterator<std::basic_string<char> > o(ss, ",");
  std::transform(mData.begin(), mData.end(), o, boost::bind(&DataType::to_string, _1));
  return helper::trim_last_c(ss);
}


///////////////////////////////////////////////////////////////////////////////
typedef VarTypeArray<USHRT_MAX>               Vn;
///////////////////////////////////////////////////////////////////////////////


#endif
