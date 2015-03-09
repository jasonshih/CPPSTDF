#include <cxxtest/TestSuite.h>

#include "DataTypes.hpp"

class TestB1 : public CxxTest::TestSuite 
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
      B1 stdfStr;
      unsigned char ch = '\0';
      TS_ASSERT_SAME_DATA(stdfStr.mData, &ch, 1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "00000000");
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
    }

    void testConstructor2()
    {
      B1 stdfStr = "";
      unsigned char ch = '\0';
      TS_ASSERT_SAME_DATA(stdfStr.mData, &ch, 1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "00000000");
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
    }

    void testConstructor3()
    {
      B1 stdfStr("00000001");//left to right: bit7 ... bit0
      unsigned char ch = 1;
      TS_ASSERT_SAME_DATA(stdfStr.mData, &ch, 1);
      TS_ASSERT_EQUALS(stdfStr[0], 1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("00000001"));
      stdfStr = "10000000";
      ch = 128;
      TS_ASSERT_SAME_DATA(stdfStr.mData, &ch, 1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("10000000"));
      TS_ASSERT_EQUALS(stdfStr[7], 1);
      
      stdfStr.reset(1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "11111111");
      stdfStr.reset(0);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "00000000");
      stdfStr[7] = 1;
      TS_ASSERT_EQUALS(stdfStr.to_string(), "10000000");
      TS_ASSERT_EQUALS(stdfStr[7], 1);
      
      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), "00000000");
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
      
      stdfStr.reset(true);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "11111111");
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
    }

    void testCopyConstructor1()
    {
      B1 source("00000001");
      B1 stdfStr(source);
      unsigned char ch = 1;
      TS_ASSERT_SAME_DATA(stdfStr.mData, &ch, 1);
      TS_ASSERT_EQUALS(stdfStr[0], 1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("00000001"));
      stdfStr = "10000000";
      ch = 128;
      TS_ASSERT_SAME_DATA(stdfStr.mData, &ch, 1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("10000000"));
      TS_ASSERT_EQUALS(stdfStr[7], 1);
      TS_ASSERT_EQUALS(source.to_string(), std::basic_string<char>("00000001"));
    }

    void testAssigner1()
    {
      B1 stdfStr("11111111");
      B1 source("00000001");
      stdfStr = source;
      unsigned char ch = 1;
      TS_ASSERT_SAME_DATA(stdfStr.mData, &ch, 1);
      TS_ASSERT_EQUALS(stdfStr[0], 1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("00000001"));
      stdfStr = "10000000";
      ch = 128;
      TS_ASSERT_SAME_DATA(stdfStr.mData, &ch, 1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("10000000"));
      TS_ASSERT_EQUALS(stdfStr[7], 1);
      TS_ASSERT_EQUALS(source.to_string(), std::basic_string<char>("00000001"));
    }

    void testClone1()
    {
      B1 source("00000001");
      DataType::DataTypeSharedPtr stdfStr = source.clone();
      TS_ASSERT_EQUALS((*stdfStr).to_string(), std::basic_string<char>("00000001"));
      source = "10000000";
      TS_ASSERT_EQUALS((*stdfStr).to_string(), std::basic_string<char>("00000001"));
      TS_ASSERT_EQUALS(source.to_string(), std::basic_string<char>("10000000"));
    }

    void testWriteRead1()
    {
      const char *filename = "TestB1.testWriteRead1.txt";

      B1 stdfStrIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      B1 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, 1);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "00000000");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "00000000");
    }

    void testWriteRead2()
    {
      const char *filename = "TestB1.testWriteRead2.txt";

      B1 stdfStrIn("11111111");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      B1 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, 1);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "11111111");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "11111111");
    }

    void testWriteRead3()
    {
      const char *filename = "TestB1.testWriteRead3.txt";

      B1 stdfStrIn;
      stdfStrIn[0] = 1;
      stdfStrIn[6] = 1;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      B1 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, 1);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "01000001");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "01000001");
      TS_ASSERT_EQUALS(stdfStrIn[0], 1);
      TS_ASSERT_EQUALS(stdfStrOut[0], 1);
      TS_ASSERT_EQUALS(stdfStrIn[6], 1);
      TS_ASSERT_EQUALS(stdfStrOut[6], 1);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 1u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 1u);
    }

};
