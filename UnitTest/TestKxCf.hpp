#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestKxCf : public CxxTest::TestSuite 
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
      KxTYPE<Cf, size> stdfStr;
      Cf data[size];
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor1()
    {
      const int size = 10;
      KxTYPE<Cf, size> stdfStr;
      Cf data[size];
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), 0);
      TS_ASSERT_EQUALS(stdfStr.to_string(), ",,,,,,,,,");
    }

    void testConstructor2()
    {
      const int size = 30;
      KxTYPE<Cf, size> stdfStr;
      Cf data[size];
      for(size_t i = 0; i < size; i++)
      {
        stdfStr[i] = data[i] = "ABCD";
      }
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), 4*size);
      Cf data8 = stdfStr[8];
      TS_ASSERT_EQUALS(data8.to_string(), data[8].to_string());
      Cf data9 = stdfStr[9];
      TS_ASSERT_EQUALS(data9.to_string(), data[9].to_string());
      TS_ASSERT_EQUALS(stdfStr.to_string(), "ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD");
      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,");
    }

    void testConstructor3()
    {
      const int size = 94;
      KxTYPE<Cf, size> stdfStr;
      Cf data[size];
      for(size_t i = 0; i < size; i++)
      {
        stdfStr[i] = data[i] = "ABCD";
      }
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), 4*size);
      Cf data88 = stdfStr[88];
      TS_ASSERT_EQUALS(data88.to_string(), data[88].to_string());
      Cf data93 = stdfStr[93];
      TS_ASSERT_EQUALS(data93.to_string(), data[93].to_string());
      TS_ASSERT_EQUALS(stdfStr.to_string(), "ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD,ABCD");
      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,");
    }

    void testWriteRead1()
    {
      const char *filename = "TestKxCf.testWriteRead1.txt";

      const int size = 1;
      Cf data[size];

      KxTYPE<Cf, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<Cf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, 0);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 1);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 1);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 0);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 0);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead2()
    {
      const char *filename = "TestKxCf.testWriteRead2.txt";

      const int size = 10;
      Cf data[size];

      KxTYPE<Cf, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<Cf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, 0);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 10);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 10);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 0);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 0);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead3()
    {
      const char *filename = "TestKxCf.testWriteRead3.txt";

      const int size = 20;
      Cf data[size];

      KxTYPE<Cf, size> stdfStrIn;
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = "ABCDEF";
      }
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<Cf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, 6);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 20);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 20);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 120);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 120);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF,ABCDEF");
    }

};
