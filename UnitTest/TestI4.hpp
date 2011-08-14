#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestI4 : public CxxTest::TestSuite 
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
      I4 stdfStr;
      TS_ASSERT(stdfStr.mData == 0);
    }

    void testConstructor2()
    {
      I4 stdfStr = 0;
      TS_ASSERT(stdfStr.mData == 0);
    }


    void testConstructor3()
    {
      I4 stdfStr = -0x80000000;
      TS_ASSERT(stdfStr.mData == -2147483648);
      stdfStr = 0xFFFFFFFF;
      TS_ASSERT(stdfStr.mData == -1);
      stdfStr = 0x7FFFFFFF;
      TS_ASSERT(stdfStr.mData == 2147483647);
    }

    void testWriteRead1()
    {
      const char *filename = "TestI4.testWriteRead1.txt";

      I4 stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I4 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0);
      TS_ASSERT(stdfStrOut.mData == 0);
      TS_ASSERT(stdfStrIn.getValue() == 0);
      TS_ASSERT(stdfStrOut.getValue() == 0);
    }

    void testWriteRead2()
    {
      const char *filename = "TestI4.testWriteRead2.txt";

      I4 stdfStrIn = -1;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I4 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == (char)0xFFFFFFFF);
      TS_ASSERT(stdfStrOut.mData == (char)0xFFFFFFFF);
      TS_ASSERT(stdfStrIn.getValue() == -1);
      TS_ASSERT(stdfStrOut.getValue() == -1);
    }

    void testWriteRead3()
    {
      const char *filename = "TestI4.testWriteRead3.txt";

      I4 stdfStrIn = 2147483647;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I4 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0x7FFFFFFF);
      TS_ASSERT(stdfStrOut.mData == 0x7FFFFFFF);
      TS_ASSERT(stdfStrIn.getValue() == 2147483647);
      TS_ASSERT(stdfStrOut.getValue() == 2147483647);
      TS_ASSERT(stdfStrOut.to_string() == "2147483647");
    }

    void testWriteRead4()
    {
      const char *filename = "TestI4.testWriteRead4.txt";

      I4 stdfStrIn = -2147483648;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I4 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == -0x80000000);
      TS_ASSERT(stdfStrOut.mData == -0x80000000);
      TS_ASSERT(stdfStrIn.getValue() == -2147483648);
      TS_ASSERT(stdfStrOut.getValue() == -2147483648);
      TS_ASSERT(stdfStrOut.to_string() == "-2147483648");
    }


};
