#include <cxxtest/TestSuite.h>

#include "DataTypes.hpp"

class TestKxN1 : public CxxTest::TestSuite 
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
      KxN1<1> stdfStr;
      unsigned char ch[1] = {0};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, 1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0");
    }

    void testConstructor1()
    {
      KxN1<9> stdfStr;
      unsigned char ch[5] = {0};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, 5);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "000000000");
    }

    void testConstructor2()
    {
      KxN1<9> stdfStr = "";
      unsigned char ch[5] = {0};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, 5);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "000000000");
      TS_ASSERT_EQUALS(stdfStr.max_size(), 9u);
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
    }

    void testConstructor3()
    {
      KxN1<3> stdfStr("ABC");
      unsigned char ch[2] = {0xBA, 0x0C};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, 2);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "ABC");
      TS_ASSERT_EQUALS(stdfStr.max_size(), 3u);
      TS_ASSERT_EQUALS(stdfStr.storage(), 2u);
    }

    void testCopyConstructor1()
    {
      KxN1<3> source("ABC");
      KxN1<3> stdfStr(source);
      source = "CBA";
      TS_ASSERT_EQUALS(stdfStr.to_string(), "ABC");
      TS_ASSERT_EQUALS(stdfStr.storage(), 2u);
      TS_ASSERT_DIFFERS(stdfStr.to_string(), source.to_string());
      TS_ASSERT_EQUALS(source.to_string(), "CBA");
    }

    void testClone1()
    {
      KxN1<3> source("ABC");
      DataType::DataTypeSharedPtr stdfStr = source.clone();
      TS_ASSERT_EQUALS(stdfStr->to_string(), "ABC");
      TS_ASSERT_EQUALS(stdfStr->storage(), 2u);
      TS_ASSERT_EQUALS(stdfStr->to_string(), source.to_string());
      source = "CBA";
      TS_ASSERT_EQUALS(source.to_string(), "CBA");
      TS_ASSERT_DIFFERS(stdfStr->to_string(), source.to_string());
    }

    void testConstructor4()
    {
      KxN1<16> stdfStr = ("0123456789ABCDEF");
      unsigned char ch[8] = {0x10, 0x32, 0x54, 0x76, 0x98, 0xBA, 0xDC, 0xFE};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, 8);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0123456789ABCDEF");
      TS_ASSERT_EQUALS(stdfStr.max_size(), 16u);
      TS_ASSERT_EQUALS(stdfStr.storage(), 8u);
    }

    void testWriteRead1()
    {
      const char *filename = "TestKxN1.testWriteRead1.txt";

      KxN1<22> stdfStrIn = ("");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxN1<22> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, 11);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "0000000000000000000000");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "0000000000000000000000");
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 22u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 22u);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 11u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 11u);
    }

    void testWriteRead2()
    {
      const char *filename = "TestKxN1.testWriteRead2.txt";

      KxN1<22> stdfStrIn = ("0123456789ABCDEFabcdef");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxN1<22> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, 11);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "0123456789ABCDEFABCDEF");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "0123456789ABCDEFABCDEF");
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 22u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 22u);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 11u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 11u);
    }

    void testWriteRead3()
    {
      const char *filename = "TestKxN1.testWriteRead3.txt";

      KxN1<22> stdfStrIn;
      stdfStrIn[1] = 1;
      stdfStrIn[21] = 0xf;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxN1<22> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, 11);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "010000000000000000000F");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "010000000000000000000F");
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 22u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 22u);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 11u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 11u);
      TS_ASSERT_EQUALS(stdfStrIn[1], 1);
      TS_ASSERT_EQUALS(stdfStrOut[1], 1);
      TS_ASSERT_EQUALS(stdfStrIn[21], 0xf);
      TS_ASSERT_EQUALS(stdfStrOut[21], 0xf);

      stdfStrIn.clear();
      stdfStrOut.clear();
      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, 11);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "0000000000000000000000");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "0000000000000000000000");
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 22u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 22u);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 11u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 11u);
    }

};
