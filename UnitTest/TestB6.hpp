#include <cxxtest/TestSuite.h>

#include "DataTypes.hpp"

class TestB6 : public CxxTest::TestSuite 
{
  static const unsigned int SIZE = 6;
  typedef BitArray<SIZE> B6;

  public:
    void setUp()
    {
    }
    void tearDown()
    {
    }

    void testConstructor1()
    {
      B6 stdfStr;
      unsigned char ch[SIZE] = {0};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "000000000000000000000000000000000000000000000000");
      TS_ASSERT_EQUALS(stdfStr.storage(), SIZE);
    }

    void testConstructor2()
    {
      B6 stdfStr = "";
      unsigned char ch[SIZE] = {0};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "000000000000000000000000000000000000000000000000");
      TS_ASSERT_EQUALS(stdfStr.storage(), SIZE);
    }

    void testConstructor3()
    {
      B6 stdfStr("0100000100100000001");
      unsigned char ch[SIZE] = {0};
      ch[0] = 1;
      ch[1] = 9;
      ch[2] = 2;
      
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("000000000000000000000000000000100000100100000001"));
      stdfStr = "1000000000000001";
      memset(ch, 0, SIZE);
      ch[0] = 1;
      ch[1] = 128;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("000000000000000000000000000000001000000000000001"));
      stdfStr.reset(1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "111111111111111111111111111111111111111111111111");
      stdfStr.reset(0);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "000000000000000000000000000000000000000000000000");
      stdfStr[0] = 1;
      TS_ASSERT_EQUALS(stdfStr.to_string(), "000000000000000000000000000000000000000000000001");
      TS_ASSERT_EQUALS(stdfStr[0], 1);
      TS_ASSERT_EQUALS(stdfStr[1], 0);
      TS_ASSERT_EQUALS(stdfStr[2], 0);
      TS_ASSERT_EQUALS(stdfStr[3], 0);
      TS_ASSERT_EQUALS(stdfStr[4], 0);
      TS_ASSERT_EQUALS(stdfStr[5], 0);
      TS_ASSERT_EQUALS(stdfStr[6], 0);
      TS_ASSERT_EQUALS(stdfStr[7], 0);
      TS_ASSERT_EQUALS(stdfStr[47], 0);
      stdfStr.reset(0);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "000000000000000000000000000000000000000000000000");
      stdfStr[47] = 1;
      TS_ASSERT_EQUALS(stdfStr.to_string(), "100000000000000000000000000000000000000000000000");
      TS_ASSERT_EQUALS(stdfStr[0], 0);
      TS_ASSERT_EQUALS(stdfStr[1], 0);
      TS_ASSERT_EQUALS(stdfStr[2], 0);
      TS_ASSERT_EQUALS(stdfStr[3], 0);
      TS_ASSERT_EQUALS(stdfStr[4], 0);
      TS_ASSERT_EQUALS(stdfStr[5], 0);
      TS_ASSERT_EQUALS(stdfStr[6], 0);
      TS_ASSERT_EQUALS(stdfStr[7], 0);
      TS_ASSERT_EQUALS(stdfStr[47], 1);
    }

    void testCopyConstructor1()
    {
      B6 source("00000001");
      B6 stdfStr(source);
      unsigned char ch = 1;
      TS_ASSERT_SAME_DATA(stdfStr.mData, &ch, 1);
      TS_ASSERT_EQUALS(stdfStr[0], 1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("000000000000000000000000000000000000000000000001"));
      stdfStr = "10000000";
      ch = 128;
      TS_ASSERT_SAME_DATA(stdfStr.mData, &ch, 1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("000000000000000000000000000000000000000010000000"));
      TS_ASSERT_EQUALS(stdfStr[7], 1);
      TS_ASSERT_EQUALS(source.to_string(), std::basic_string<char>("000000000000000000000000000000000000000000000001"));
    }

    void testAssigner1()
    {
      B6 stdfStr("11111111");
      B6 source("00000001");
      stdfStr = source;
      unsigned char ch = 1;
      TS_ASSERT_SAME_DATA(stdfStr.mData, &ch, 1);
      TS_ASSERT_EQUALS(stdfStr[0], 1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("000000000000000000000000000000000000000000000001"));
      stdfStr = "10000000";
      ch = 128;
      TS_ASSERT_SAME_DATA(stdfStr.mData, &ch, 1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("000000000000000000000000000000000000000010000000"));
      TS_ASSERT_EQUALS(stdfStr[7], 1);
      TS_ASSERT_EQUALS(source.to_string(), std::basic_string<char>("000000000000000000000000000000000000000000000001"));
    }

    void testClone1()
    {
      B6 source("00000001");
      DataType::DataTypeSharedPtr stdfStr = source.clone();
      TS_ASSERT_EQUALS((*stdfStr).to_string(), std::basic_string<char>("000000000000000000000000000000000000000000000001"));
      source = "10000000";
      TS_ASSERT_EQUALS((*stdfStr).to_string(), std::basic_string<char>("000000000000000000000000000000000000000000000001"));
      TS_ASSERT_EQUALS(source.to_string(), std::basic_string<char>("000000000000000000000000000000000000000010000000"));
    }

    void testWriteRead1()
    {
      const char *filename = "TestB6.testWriteRead1.txt";

      B6 stdfStrIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      B6 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "000000000000000000000000000000000000000000000000");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "000000000000000000000000000000000000000000000000");
    }

    void testWriteRead2()
    {
      const char *filename = "TestB6.testWriteRead2.txt";

      B6 stdfStrIn("11111111000000011111111");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      B6 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "000000000000000000000000011111111000000011111111");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "000000000000000000000000011111111000000011111111");
    }

    void testWriteRead3()
    {
      const char *filename = "TestB6.testWriteRead3.txt";

      B6 stdfStrIn;
      stdfStrIn[0] = 1;
      stdfStrIn[6] = 1;
      stdfStrIn[26] = 1;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      B6 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "000000000000000000000100000000000000000001000001");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "000000000000000000000100000000000000000001000001");
      TS_ASSERT_EQUALS(stdfStrIn[0], 1);
      TS_ASSERT_EQUALS(stdfStrOut[0], 1);
      TS_ASSERT_EQUALS(stdfStrIn[6], 1);
      TS_ASSERT_EQUALS(stdfStrOut[6], 1);
      TS_ASSERT_EQUALS(stdfStrIn[26], 1);
      TS_ASSERT_EQUALS(stdfStrOut[26], 1);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), SIZE);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), SIZE);
    }

};
