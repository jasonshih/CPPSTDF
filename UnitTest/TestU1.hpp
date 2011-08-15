#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestU1 : public CxxTest::TestSuite 
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
      U1 stdfStr;
      TS_ASSERT(stdfStr.mData == 0);
    }

    void testConstructor2()
    {
      U1 stdfStr = 0;
      TS_ASSERT(stdfStr.mData == 0);
    }

    void testConstructor3()
    {
      U1 stdfStr;
      TS_ASSERT(stdfStr.mData == 0);
      stdfStr = 0xFF;
      TS_ASSERT(stdfStr.mData == 0xFF);
    }

    void testConstructor4()
    {
      U1 stdfStr = 0xFF;
      TS_ASSERT(stdfStr.mData == 0xFF);
    }

    void testWriteRead1()
    {
      const char *filename = "TestU1.testWriteRead1.txt";

      U1 stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U1 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0);
      TS_ASSERT(stdfStrOut.mData == 0);
      TS_ASSERT(stdfStrIn.getValue() == 0);
      TS_ASSERT(stdfStrOut.getValue() == 0);
      TS_ASSERT(stdfStrIn.storage() == 1);
      TS_ASSERT(stdfStrOut.storage() == 1);
    }

    void testWriteRead2()
    {
      const char *filename = "TestU1.testWriteRead2.txt";

      U1 stdfStrIn = 100;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U1 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0x64);
      TS_ASSERT(stdfStrOut.mData == 0x64);
      TS_ASSERT(stdfStrIn.getValue() == 100);
      TS_ASSERT(stdfStrOut.getValue() == 100);
      TS_ASSERT(stdfStrIn.to_string() == "100");
      TS_ASSERT(stdfStrOut.to_string() == "100");
      TS_ASSERT(stdfStrIn.storage() == 1);
      TS_ASSERT(stdfStrOut.storage() == 1);
    }

    void testWriteRead3()
    {
      const char *filename = "TestU1.testWriteRead3.txt";

      U1 stdfStrIn = 255;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U1 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0xFF);
      TS_ASSERT(stdfStrOut.mData == 0xFF);
      TS_ASSERT(stdfStrIn.getValue() == 255);
      TS_ASSERT(stdfStrOut.getValue() == 255);
      TS_ASSERT(stdfStrIn.to_string() == "255");
      TS_ASSERT(stdfStrOut.to_string() == "255");
      TS_ASSERT(stdfStrIn.storage() == 1);
      TS_ASSERT(stdfStrOut.storage() == 1);
    }

    void testWriteRead4()
    {
      const char *filename = "TestU1.testWriteRead4.txt";

      U1 stdfStrIn = 254;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U1 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0xFE);
      TS_ASSERT(stdfStrOut.mData == 0xFE);
      TS_ASSERT(stdfStrIn.getValue() == 254);
      TS_ASSERT(stdfStrOut.getValue() == 254);
      TS_ASSERT(stdfStrIn.to_string() == "254");
      TS_ASSERT(stdfStrOut.to_string() == "254");
      TS_ASSERT(stdfStrIn.storage() == 1);
      TS_ASSERT(stdfStrOut.storage() == 1);
    }


};
