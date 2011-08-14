#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestKxSn : public CxxTest::TestSuite 
{
  public:
    void setUp()
    {
    }
    void tearDown()
    {
    }

    void testConstructor0()
    {
      const int size = 0;
      KxTYPE<Sn, size> stdfStr;
      Sn data[size];
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor1()
    {
      const int size = 10;
      KxTYPE<Sn, size> stdfStr;
      Sn data[size];
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), 2*size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), ",,,,,,,,,");
    }

    void testConstructor2()
    {
      const int size = 30;
      KxTYPE<Sn, size> stdfStr;
      Sn data[size];
      for(size_t i = 0; i < size; i++)
      {
        stdfStr[i] = data[i] = "ABCD";
      }
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), 6*size);
      Sn data8 = stdfStr[8];
      TS_ASSERT_EQUALS(data8.to_string(), data[8].to_string());
      Sn data9 = stdfStr[9];
      TS_ASSERT_EQUALS(data9.to_string(), data[9].to_string());
      string str;
      for(size_t i = 0; i < size-1; i++) str.append("ABCD,"); str.append("ABCD");
      TS_ASSERT_EQUALS(stdfStr.to_string(), str);
      stdfStr.clear();
      str.clear(); str.assign(size-1, ',');
      TS_ASSERT_EQUALS(stdfStr.to_string(), str);
    }

    void testConstructor3()
    {
      const int size = 94;
      KxTYPE<Sn, size> stdfStr;
      Sn data[size];
      for(size_t i = 0; i < size; i++)
      {
        stdfStr[i] = data[i] = "ABCD";
      }
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), 6*size);
      Sn data88 = stdfStr[88];
      TS_ASSERT_EQUALS(data88.to_string(), data[88].to_string());
      Sn data93 = stdfStr[93];
      TS_ASSERT_EQUALS(data93.to_string(), data[93].to_string());
      string str;
      for(size_t i = 0; i < size-1; i++) str.append("ABCD,"); str.append("ABCD");
      TS_ASSERT_EQUALS(stdfStr.to_string(), str);
      stdfStr.clear();
      str.clear(); str.assign(size-1, ',');
      TS_ASSERT_EQUALS(stdfStr.to_string(), str);
    }

    void testConstructor4()
    {
      const int size = 394;
      KxTYPE<Sn, size> stdfStr;
      Sn data[size];
      for(size_t i = 0; i < size; i++)
      {
        stdfStr[i] = data[i] = "ABCD";
      }
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), 6*size);
      Sn data88 = stdfStr[88];
      TS_ASSERT_EQUALS(data88.to_string(), data[88].to_string());
      Sn data93 = stdfStr[93];
      TS_ASSERT_EQUALS(data93.to_string(), data[93].to_string());
      string str;
      for(size_t i = 0; i < size-1; i++) str.append("ABCD,"); str.append("ABCD");
      TS_ASSERT_EQUALS(stdfStr.to_string(), str);
      stdfStr.clear();
      str.clear(); str.assign(size-1, ',');
      TS_ASSERT_EQUALS(stdfStr.to_string(), str);
    }

    void testWriteRead1()
    {
      const char *filename = "TestKxSn.testWriteRead1.txt";

      const int size = 1;
      Sn data[size];

      KxTYPE<Sn, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<Sn, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 1);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 1);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 2);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 2);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead2()
    {
      const char *filename = "TestKxSn.testWriteRead2.txt";

      const int size = 10;
      Sn data[size];

      KxTYPE<Sn, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<Sn, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 10);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 10);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 20);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 20);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead3()
    {
      const char *filename = "TestKxSn.testWriteRead3.txt";

      const int size = 20;
      Sn data[size];

      KxTYPE<Sn, size> stdfStrIn;
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = "ABCDEF";
      }
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<Sn, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 20);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 20);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 160);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 160);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string());
      string str;
      for(size_t i = 0; i < size-1; i++) str.append("ABCDEF,"); str.append("ABCDEF");
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), str);
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), str);
    }

};
