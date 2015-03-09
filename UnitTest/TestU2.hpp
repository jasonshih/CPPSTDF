#include <cxxtest/TestSuite.h>

#include "DataTypes.hpp"

class TestU2 : public CxxTest::TestSuite 
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
      U2 stdfStr;
      TS_ASSERT(stdfStr.mData == 0);
    }

    void testConstructor2()
    {
      U2 stdfStr = 0;
      TS_ASSERT(stdfStr.mData == 0);
    }

    void testConstructor3()
    {
      U2 stdfStr;
      TS_ASSERT(stdfStr.mData == 0);
      stdfStr = 0xFEDC;
      TS_ASSERT(stdfStr.mData == 0xFEDC);
    }

    void testConstructor4()
    {
      U2 stdfStr = 0xFFFF;
      TS_ASSERT(stdfStr.mData == 0xFFFF);
    }

    void testWriteRead1()
    {
      const char *filename = "TestU2.testWriteRead1.txt";

      U2 stdfStrIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U2 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
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
      const char *filename = "TestU2.testWriteRead2.txt";

      U2 stdfStrIn = 100;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U2 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0x64);
      TS_ASSERT(stdfStrOut.mData == 0x64);
      TS_ASSERT(stdfStrIn.getValue() == 100);
      TS_ASSERT(stdfStrOut.getValue() == 100);
      TS_ASSERT(stdfStrIn.to_string() == "100");
      TS_ASSERT(stdfStrOut.to_string() == "100");
      TS_ASSERT(stdfStrIn.storage() == 2);
      TS_ASSERT(stdfStrOut.storage() == 2);
    }

    void testWriteRead3()
    {
      const char *filename = "TestU2.testWriteRead3.txt";

      U2 stdfStrIn = 65535;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U2 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0xFFFF);
      TS_ASSERT(stdfStrOut.mData == 0xFFFF);
      TS_ASSERT(stdfStrIn.getValue() == 65535);
      TS_ASSERT(stdfStrOut.getValue() == 65535);
      TS_ASSERT(stdfStrIn.to_string() == "65535");
      TS_ASSERT(stdfStrOut.to_string() == "65535");
      TS_ASSERT(stdfStrIn.storage() == 2);
      TS_ASSERT(stdfStrOut.storage() == 2);
    }

    void testWriteRead4()
    {
      const char *filename = "TestU2.testWriteRead4.txt";

      U2 stdfStrIn = 65244;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U2 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0xFEDC);
      TS_ASSERT(stdfStrOut.mData == 0xFEDC);
      TS_ASSERT(stdfStrIn.getValue() == 65244);
      TS_ASSERT(stdfStrOut.getValue() == 65244);
      TS_ASSERT(stdfStrIn.to_string() == "65244");
      TS_ASSERT(stdfStrOut.to_string() == "65244");
      TS_ASSERT(stdfStrIn.storage() == 2);
      TS_ASSERT(stdfStrOut.storage() == 2);
    }


};
