#include <cxxtest/TestSuite.h>

#include "DataTypes.hpp"

class TestI1 : public CxxTest::TestSuite 
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
      I1 stdfStr;
      TS_ASSERT(stdfStr.mData == 0);
      TS_ASSERT(stdfStr.storage() == 1);
    }

    void testConstructor2()
    {
      I1 stdfStr = 0;
      TS_ASSERT(stdfStr.mData == 0);
      TS_ASSERT(stdfStr.storage() == 1);
    }


    void testConstructor3()
    {
      I1 stdfStr = -0x80;
      TS_ASSERT(stdfStr.mData == -128);
      stdfStr = 0xFF;
      TS_ASSERT(stdfStr.mData == -1);
      stdfStr = 0x7F;
      TS_ASSERT(stdfStr.mData == 127);
      TS_ASSERT(stdfStr.storage() == 1);
    }

    void testWriteRead1()
    {
      const char *filename = "TestI1.testWriteRead1.txt";

      I1 stdfStrIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I1 stdfStrOut;
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
      const char *filename = "TestI1.testWriteRead2.txt";

      I1 stdfStrIn = -1;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I1 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == (char)0xFF);
      TS_ASSERT(stdfStrOut.mData == (char)0xFF);
      TS_ASSERT(stdfStrIn.getValue() == -1);
      TS_ASSERT(stdfStrOut.getValue() == -1);
    }

    void testWriteRead3()
    {
      const char *filename = "TestI1.testWriteRead3.txt";

      I1 stdfStrIn = 127;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I1 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0x7F);
      TS_ASSERT(stdfStrOut.mData == 0x7F);
      TS_ASSERT(stdfStrIn.getValue() == 127);
      TS_ASSERT(stdfStrOut.getValue() == 127);
      TS_ASSERT(stdfStrOut.to_string() == "127");
    }

    void testWriteRead4()
    {
      const char *filename = "TestI1.testWriteRead4.txt";

      I1 stdfStrIn = -128;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      I1 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == -0x80);
      TS_ASSERT(stdfStrOut.mData == -0x80);
      TS_ASSERT(stdfStrIn.getValue() == -128);
      TS_ASSERT(stdfStrOut.getValue() == -128);
      TS_ASSERT(stdfStrOut.to_string() == "-128");
    }


};
