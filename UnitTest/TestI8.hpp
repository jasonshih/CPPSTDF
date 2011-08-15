#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestI8 : public CxxTest::TestSuite 
{
  public:
    void setUp()
    {
    }
    void tearDown()
    {
    }

    void testConstructor1()
    {
      I8 stdfStr;
      TS_ASSERT(stdfStr.mData == 0);
    }

    void testConstructor2()
    {
      I8 stdfStr = 0;
      TS_ASSERT(stdfStr.mData == 0);
    }


    void testConstructor3()
    {
      I8 stdfStr = -0x8000000000000000;
      //TS_ASSERT(stdfStr.mData == -9223372036854775808);
      TS_ASSERT(stdfStr.mData == (long long)-0x8000000000000000);
      stdfStr = 0xFFFFFFFFFFFFFFFF;
      TS_ASSERT(stdfStr.mData == -1);
      stdfStr = 0x7FFFFFFFFFFFFFFF;
      TS_ASSERT(stdfStr.mData == 9223372036854775807);
    }

    void testWriteRead1()
    {
      const char *filename = "TestI8.testWriteRead1.txt";

      I8 stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I8 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0);
      TS_ASSERT(stdfStrOut.mData == 0);
      TS_ASSERT(stdfStrIn.getValue() == 0);
      TS_ASSERT(stdfStrOut.getValue() == 0);
      TS_ASSERT(stdfStrIn.to_string() == "0");
      TS_ASSERT(stdfStrOut.to_string() == "0");
      TS_ASSERT(stdfStrIn.storage() == 8);
      TS_ASSERT(stdfStrOut.storage() == 8);
    }

    void testWriteRead2()
    {
      const char *filename = "TestI8.testWriteRead2.txt";

      I8 stdfStrIn = -1;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I8 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == (char)0xFFFFFFFFFFFFFFFF);
      TS_ASSERT(stdfStrOut.mData == (char)0xFFFFFFFFFFFFFFFF);
      TS_ASSERT(stdfStrIn.getValue() == -1);
      TS_ASSERT(stdfStrOut.getValue() == -1);
      TS_ASSERT(stdfStrIn.to_string() == "-1");
      TS_ASSERT(stdfStrOut.to_string() == "-1");
      TS_ASSERT(stdfStrIn.storage() == 8);
      TS_ASSERT(stdfStrOut.storage() == 8);
    }

    void testWriteRead3()
    {
      const char *filename = "TestI8.testWriteRead3.txt";

      I8 stdfStrIn = 9223372036854775807;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I8 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0x7FFFFFFFFFFFFFFF);
      TS_ASSERT(stdfStrOut.mData == 0x7FFFFFFFFFFFFFFF);
      TS_ASSERT(stdfStrIn.getValue() == 9223372036854775807);
      TS_ASSERT(stdfStrOut.getValue() == 9223372036854775807);
      TS_ASSERT(stdfStrIn.to_string() == "9223372036854775807");
      TS_ASSERT(stdfStrOut.to_string() == "9223372036854775807");
      TS_ASSERT(stdfStrIn.storage() == 8);
      TS_ASSERT(stdfStrOut.storage() == 8);
    }

    void testWriteRead4()
    {
      const char *filename = "TestI8.testWriteRead4.txt";

      //I8 stdfStrIn = -9223372036854775808;
      I8 stdfStrIn = -0x8000000000000000;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I8 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == (long long)-0x8000000000000000);
      TS_ASSERT(stdfStrOut.mData == (long long)-0x8000000000000000);
      TS_ASSERT(stdfStrIn.getValue() == (long long)-0x8000000000000000);
      TS_ASSERT(stdfStrOut.getValue() == (long long)-0x8000000000000000);
      TS_ASSERT(stdfStrIn.to_string() == "-9223372036854775808");
      TS_ASSERT(stdfStrOut.to_string() == "-9223372036854775808");
      TS_ASSERT(stdfStrIn.storage() == 8);
      TS_ASSERT(stdfStrOut.storage() == 8);
    }


};
