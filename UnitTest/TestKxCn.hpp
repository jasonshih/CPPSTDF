#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestKxCn : public CxxTest::TestSuite 
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
      KxTYPE<Cn, size> stdfStr;
      Cn data[size];
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor1()
    {
      const int size = 10;
      KxTYPE<Cn, size> stdfStr;
      Cn data[size];
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), ",,,,,,,,,");
    }

    void testConstructor2()
    {
      const int size = 100;
      KxTYPE<Cn, size> stdfStr;
      Cn data[size];
      for(size_t i = 0; i < size; i++)
      {
        stdfStr[i] = data[i] = "ABCD";
      }
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), 5*size);
      Cn data88 = stdfStr[88];
      TS_ASSERT_EQUALS(data88.to_string(), data[88].to_string());
      Cn data99 = stdfStr[99];
      TS_ASSERT_EQUALS(data99.to_string(), data[99].to_string());
      string str;
      for(size_t i = 0; i < size-1; i++) str.append("ABCD,"); str.append("ABCD");
      TS_ASSERT_EQUALS(stdfStr.to_string(), str);
      stdfStr.clear();
      str.clear(); str.assign(size-1, ',');
      TS_ASSERT_EQUALS(stdfStr.to_string(), str);
    }

    void testWriteRead1()
    {
      const char *filename = "TestKxCn.testWriteRead1.txt";

      const int size = 1;
      Cn data[size];

      KxTYPE<Cn, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<Cn, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 1);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 1);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 1);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 1);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead2()
    {
      const char *filename = "TestKxCn.testWriteRead2.txt";

      const int size = 10;
      Cn data[size];

      KxTYPE<Cn, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<Cn, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 10);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 10);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 10);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 10);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead3()
    {
      const char *filename = "TestKxCn.testWriteRead3.txt";

      const int size = 20;
      Cn data[size];

      KxTYPE<Cn, size> stdfStrIn;
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = "ABCDEF";
      }
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<Cn, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 20);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 20);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 140);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 140);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string());
      string str;
      for(size_t i = 0; i < size-1; i++) str.append("ABCDEF,"); str.append("ABCDEF");
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), str);
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), str);
    }

};
