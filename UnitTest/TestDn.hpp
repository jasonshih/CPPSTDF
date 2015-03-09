#include <cxxtest/TestSuite.h>

#include "DataTypes.hpp"

class TestDn : public CxxTest::TestSuite 
{
  const static unsigned int SIZE = 8194;
  public:
    void setUp()
    {
    }
    void tearDown()
    {
    }

    void testConstructor1()
    {
      Dn stdfStr;
      char ch[SIZE] = {0};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
      TS_ASSERT_EQUALS(stdfStr.storage(), 2u);
    }

    void testConstructor2()
    {
      Dn stdfStr = "";
      char ch[SIZE] = {0};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
      TS_ASSERT_EQUALS(stdfStr.storage(), 2u);
    }

    void testConstructor3()
    {
      Dn stdfStr("0000000100100000001");
      unsigned char ch[SIZE] = {0};
      ch[0] = 19;
      ch[2] = 1;
      ch[3] = 9;
      ch[4] = 0;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("0000000100100000001"));
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      stdfStr = "1000000000000001";
      memset(ch, 0, SIZE);
      ch[0] = 16;
      ch[2] = 1;
      ch[3] = 128;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("1000000000000001"));
      TS_ASSERT_EQUALS(stdfStr.storage(), 4u);
      stdfStr.clear();
      memset(ch, 0, SIZE);
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
      TS_ASSERT_EQUALS(stdfStr.storage(), 2u);
      stdfStr.clear();
      memset(ch, 0, SIZE);
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
      stdfStr = "00000000000000000000";
      ch[0] = 20;
      stdfStr[1] = 1;
      ch[2] = 2;
      ch[4] = 0;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "00000000000000000010");
      TS_ASSERT_EQUALS(stdfStr[1], 1);
      stdfStr[10] = 1;
      ch[3] = 4;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "00000000010000000010");
      TS_ASSERT_EQUALS(stdfStr[10], 1);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535u);
    }

    void testCopyConstructor1()
    {
      Dn source = "0000000100100000001";
      Dn stdfStr = source;
      TS_ASSERT_EQUALS(stdfStr.to_string(), source.to_string());
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535u);
      source = "00000000100100000001";
      TS_ASSERT_DIFFERS(stdfStr.to_string(), source.to_string());
    }

    void testAssigner1()
    {
      Dn source = "0000000100100000001";
      Dn stdfStr = "1111111"; stdfStr = source;
      TS_ASSERT_EQUALS(stdfStr.to_string(), source.to_string());
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535u);
      source = "10000000100100000001";
      TS_ASSERT_DIFFERS(stdfStr.to_string(), source.to_string());
    }

    void testClone1()
    {
      Dn source = "0000000100100000001";
      DataType::DataTypeSharedPtr stdfStr = source.clone();
      TS_ASSERT_EQUALS(stdfStr->to_string(), source.to_string());
      TS_ASSERT_EQUALS(stdfStr->storage(), 5u);
      source =    "1000000100100000001";
      TS_ASSERT_DIFFERS(stdfStr->to_string(), source.to_string());
    }

    void testWriteRead1()
    {
      const char *filename = "TestDn.testWriteRead1.txt";

      Dn stdfStrIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Dn stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "");
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 2u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 2u);
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 65535u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 65535u);
    }

    void testWriteRead2()
    {
      const char *filename = "TestDn.testWriteRead2.txt";

      Dn stdfStrIn("11111111000000011111111");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Dn stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "11111111000000011111111");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "11111111000000011111111");
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 5u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 5u);
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 65535u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 65535u);
    }

    void testWriteRead3()
    {
      const char *filename = "TestDn.testWriteRead3.txt";

      std::basic_string<char> str;
      str.assign(27, '0');
      Dn stdfStrIn = str;
      stdfStrIn[0] = 1;
      stdfStrIn[6] = 1;
      stdfStrIn[26] = 1;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Dn stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(),  "100000000000000000001000001");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "100000000000000000001000001");
      TS_ASSERT_EQUALS(stdfStrIn[0], 1);
      TS_ASSERT_EQUALS(stdfStrOut[0], 1);
      TS_ASSERT_EQUALS(stdfStrIn[6], 1);
      TS_ASSERT_EQUALS(stdfStrOut[6], 1);
      TS_ASSERT_EQUALS(stdfStrIn[26], 1);
      TS_ASSERT_EQUALS(stdfStrOut[26], 1);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 6u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 6u);
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 65535u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 65535u);
    }

    void testWriteRead4()
    {
      const char *filename = "TestDn.testWriteRead4.txt";

      std::basic_string<char> str;
      str.assign(65536, '1');
      Dn stdfStrIn(str);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Dn stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      str.erase(65535,1);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), str);
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), str);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 8194u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 8194u);
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 65535u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 65535u);
    }
};
