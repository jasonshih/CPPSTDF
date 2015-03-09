#include <cxxtest/TestSuite.h>

#include "DataTypes.hpp"

class TestBn : public CxxTest::TestSuite 
{
  const static unsigned int SIZE = 33;
  public:
    void setUp()
    {
    }
    void tearDown()
    {
    }

    void testConstructor1()
    {
      Bn stdfStr;
      char ch[SIZE] = {0};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
    }

    void testConstructor2()
    {
      Bn stdfStr = "";
      char ch[SIZE] = {0};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
    }

    void testConstructor3()
    {
      Bn stdfStr("0000000100100000001");
      unsigned char ch[SIZE] = {0};
      ch[0] = 19;
      ch[1] = 0x1;
      ch[2] = 0x9;
      ch[3] = 0x0;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("0000000100100000001"));
      TS_ASSERT_EQUALS(stdfStr.storage(), 4u);
      stdfStr = "1000000000000001";
      memset(ch, 0, SIZE);
      ch[0] = 16;
      ch[1] = 0x1;
      ch[2] = 0x80;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("1000000000000001"));
      stdfStr.clear();
      memset(ch, 0, SIZE);
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
      stdfStr = "00000000000000000000";
      ch[0] = 20;
      stdfStr[1] = 1;
      ch[1] = 0x2;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "00000000000000000010");
      TS_ASSERT_EQUALS(stdfStr[1], 1);
      stdfStr[10] = 1;
      ch[2] = 0x4;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "00000000010000000010");
      TS_ASSERT_EQUALS(stdfStr[10], 1);
    }

    void testCopyConstructor1()
    {
      Bn source = "0000000100100000001";
      Bn stdfStr = source;
      TS_ASSERT_EQUALS(stdfStr.to_string(), source.to_string());
      TS_ASSERT_EQUALS(stdfStr.storage(), 4u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
      source = "1000000100100000001";
      TS_ASSERT_DIFFERS(stdfStr.to_string(), source.to_string());
    }

    void testAssigner1()
    {
      Bn source = "0000000100100000001";
      Bn stdfStr = "1111111"; stdfStr = source;
      TS_ASSERT_EQUALS(stdfStr.to_string(), source.to_string());
      TS_ASSERT_EQUALS(stdfStr.storage(), 4u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
      source = "1000000100100000001";
      TS_ASSERT_DIFFERS(stdfStr.to_string(), source.to_string());
    }

    void testAssigner2()
    {
      Bn stdfStr = "0001";
      stdfStr += "1000";
      char ch[SIZE] = {0};
      ch[0]=8;
      ch[1]=0x81;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("10000001"));
      TS_ASSERT_EQUALS(stdfStr.to_string(), "10000001");
      TS_ASSERT_EQUALS(stdfStr.storage(), 2u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
    }

    void testAssigner3()
    {
      Bn stdfStr = "0001";
      stdfStr += "10000";
      char ch[SIZE] = {0};
      ch[0]=9;
      ch[1]=0x01;
      ch[2]=0x01;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("100000001"));
      TS_ASSERT_EQUALS(stdfStr.to_string(), "100000001");
      TS_ASSERT_EQUALS(stdfStr.storage(), 3u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);

      stdfStr.clear();
      memset(ch, '\0', SIZE);
      stdfStr += "100";
      ch[0]=3;
      ch[1]=0x04;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>("100"));
      TS_ASSERT_EQUALS(stdfStr.to_string(), "100");
      TS_ASSERT_EQUALS(stdfStr.storage(), 2u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
 
      stdfStr.clear();
      memset(ch, '\0', SIZE);
      stdfStr += "";
      ch[0]=0;
      ch[1]=0x0;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), std::basic_string<char>(""));
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
    }


    void testClone1()
    {
      Bn source = "0000000100100000001";
      DataType::DataTypeSharedPtr stdfStr = source.clone();
      TS_ASSERT_EQUALS(stdfStr->to_string(), source.to_string());
      TS_ASSERT_EQUALS(stdfStr->storage(), 4u);
      source = "1000000100100000001";
      TS_ASSERT_DIFFERS(stdfStr->to_string(), source.to_string());
    }

    void testWriteRead1()
    {
      const char *filename = "TestBn.testWriteRead1.txt";

      Bn stdfStrIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Bn stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestBn.testWriteRead2.txt";

      Bn stdfStrIn("11111111000000011111111");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Bn stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "11111111000000011111111");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "11111111000000011111111");
    }

    void testWriteRead3()
    {
      const char *filename = "TestBn.testWriteRead3.txt";

      std::basic_string<char> str;
      str.assign(27, '0');
      Bn stdfStrIn = str;
      stdfStrIn[0] = 1;
      stdfStrIn[6] = 1;
      stdfStrIn[26] = 1;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Bn stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "100000000000000000001000001");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(),"100000000000000000001000001");
      TS_ASSERT_EQUALS(stdfStrIn[0], 1);
      TS_ASSERT_EQUALS(stdfStrOut[0], 1);
      TS_ASSERT_EQUALS(stdfStrIn[6], 1);
      TS_ASSERT_EQUALS(stdfStrOut[6], 1);
      TS_ASSERT_EQUALS(stdfStrIn[26], 1);
      TS_ASSERT_EQUALS(stdfStrOut[26], 1);
    }

    void testWriteRead4()
    {
      const char *filename = "TestBn.testWriteRead4.txt";

      std::basic_string<char> str;
      str.assign(256, '1');
      Bn stdfStrIn(str);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Bn stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      str.erase(255,1);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), str);
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), str);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 33u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 33u);
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 255u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 255u);
    }
};
