#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestI2 : public CxxTest::TestSuite 
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
      I2 stdfStr;
      TS_ASSERT(stdfStr.mData == 0);
    }

    void testConstructor2()
    {
      I2 stdfStr = 0;
      TS_ASSERT(stdfStr.mData == 0);
    }


    void testConstructor3()
    {
      I2 stdfStr = -0x8000;
      TS_ASSERT(stdfStr.mData == -32768);
      stdfStr = 0xFFFF;
      TS_ASSERT(stdfStr.mData == -1);
      stdfStr = 0x7FFF;
      TS_ASSERT(stdfStr.mData == 32767);
    }

    void testWriteRead1()
    {
      const char *filename = "TestI2.testWriteRead1.txt";

      I2 stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I2 stdfStrOut;
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
      const char *filename = "TestI2.testWriteRead2.txt";

      I2 stdfStrIn = -1;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I2 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == (char)0xFFFF);
      TS_ASSERT(stdfStrOut.mData == (char)0xFFFF);
      TS_ASSERT(stdfStrIn.getValue() == -1);
      TS_ASSERT(stdfStrOut.getValue() == -1);
    }

    void testWriteRead3()
    {
      const char *filename = "TestI2.testWriteRead3.txt";

      I2 stdfStrIn = 32767;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I2 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0x7FFF);
      TS_ASSERT(stdfStrOut.mData == 0x7FFF);
      TS_ASSERT(stdfStrIn.getValue() == 32767);
      TS_ASSERT(stdfStrOut.getValue() == 32767);
      TS_ASSERT(stdfStrOut.to_string() == "32767");
    }

    void testWriteRead4()
    {
      const char *filename = "TestI2.testWriteRead4.txt";

      I2 stdfStrIn = -32768;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I2 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == -0x8000);
      TS_ASSERT(stdfStrOut.mData == -0x8000);
      TS_ASSERT(stdfStrIn.getValue() == -32768);
      TS_ASSERT(stdfStrOut.getValue() == -32768);
      TS_ASSERT(stdfStrOut.to_string() == "-32768");
    }


};
