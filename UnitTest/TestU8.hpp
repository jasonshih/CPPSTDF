#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestU8 : public CxxTest::TestSuite 
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
      U8 stdfStr;
      TS_ASSERT(stdfStr.mData == 0);
    }

    void testConstructor2()
    {
      U8 stdfStr = 0;
      TS_ASSERT(stdfStr.mData == 0);
    }

    void testConstructor3()
    {
      U8 stdfStr;
      TS_ASSERT(stdfStr.mData == 0);
      stdfStr = 0xFEDCBA9876543210;
      TS_ASSERT(stdfStr.mData == 0xFEDCBA9876543210);
    }

    void testConstructor4()
    {
      U8 stdfStr = 0xFFFFFFFFFFFFFFFF;
      TS_ASSERT(stdfStr.mData == 0xFFFFFFFFFFFFFFFF);
    }

    void testWriteRead1()
    {
      const char *filename = "TestU8.testWriteRead1.txt";

      U8 stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U8 stdfStrOut;
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
    }

    void testWriteRead2()
    {
      const char *filename = "TestU8.testWriteRead2.txt";

      U8 stdfStrIn = 100000;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U8 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0x186A0);
      TS_ASSERT(stdfStrOut.mData == 0x186A0);
      TS_ASSERT(stdfStrIn.getValue() == 100000);
      TS_ASSERT(stdfStrOut.getValue() == 100000);
      TS_ASSERT(stdfStrIn.to_string() == "100000");
      TS_ASSERT(stdfStrOut.to_string() == "100000");
      TS_ASSERT(stdfStrIn.size() == 8);
      TS_ASSERT(stdfStrOut.size() == 8);
    }

    void testWriteRead3()
    {
      const char *filename = "TestU8.testWriteRead3.txt";

      U8 stdfStrIn = 18446744073709551615ULL;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U8 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0xFFFFFFFFFFFFFFFF);
      TS_ASSERT(stdfStrOut.mData == 0xFFFFFFFFFFFFFFFF);
      TS_ASSERT(stdfStrIn.getValue() == 18446744073709551615ULL);
      TS_ASSERT(stdfStrOut.getValue() == 18446744073709551615ULL);
      TS_ASSERT(stdfStrIn.to_string() == "18446744073709551615");
      TS_ASSERT(stdfStrOut.to_string() == "18446744073709551615");
      TS_ASSERT(stdfStrIn.size() == 8);
      TS_ASSERT(stdfStrOut.size() == 8);
    }

    void testWriteRead4()
    {
      const char *filename = "TestU8.testWriteRead4.txt";

      U8 stdfStrIn = 18364758544493064720ULL;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U8 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0xFEDCBA9876543210);
      TS_ASSERT(stdfStrOut.mData == 0xFEDCBA9876543210);
      TS_ASSERT(stdfStrIn.getValue() == 18364758544493064720ULL);
      TS_ASSERT(stdfStrOut.getValue() == 18364758544493064720ULL);
      TS_ASSERT(stdfStrIn.to_string() == "18364758544493064720");
      TS_ASSERT(stdfStrOut.to_string() == "18364758544493064720");
      TS_ASSERT(stdfStrIn.size() == 8);
      TS_ASSERT(stdfStrOut.size() == 8);
    }


};
