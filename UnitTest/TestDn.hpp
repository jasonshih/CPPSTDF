#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

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
      TS_ASSERT_EQUALS(stdfStr.size(), 2u);
    }

    void testConstructor2()
    {
      Dn stdfStr = "";
      char ch[SIZE] = {0};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
      TS_ASSERT_EQUALS(stdfStr.size(), 2u);
    }

    void testConstructor3()
    {
      Dn stdfStr("0000000100100000001");
      unsigned char ch[SIZE] = {0};
      ch[0] = 19;
      ch[2] = 128;
      ch[3] = 4;
      ch[4] = 4;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), string("0000000100100000001"));
      TS_ASSERT_EQUALS(stdfStr.size(), 5u);
      stdfStr = "1000000000000001";
      memset(ch, 0, SIZE);
      ch[0] = 16;
      ch[2] = 1;
      ch[3] = 128;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), string("1000000000000001"));
      TS_ASSERT_EQUALS(stdfStr.size(), 4u);
      stdfStr.clear();
      memset(ch, 0, SIZE);
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
      TS_ASSERT_EQUALS(stdfStr.size(), 2u);
      stdfStr.clear();
      memset(ch, 0, SIZE);
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
      stdfStr = "00000000000000000000";
      ch[0] = 20;
      stdfStr[18] = 1;
      ch[4] = 4;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "00000000000000000010");
      TS_ASSERT_EQUALS(stdfStr[18], 1);
      stdfStr[9] = 1;
      ch[3] = 2;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "00000000010000000010");
      TS_ASSERT_EQUALS(stdfStr[9], 1);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535u);
    }

    void testWriteRead1()
    {
      const char *filename = "TestDn.testWriteRead1.txt";

      Dn stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Dn stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "");
      TS_ASSERT_EQUALS(stdfStrIn.size(), 2u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 2u);
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 65535u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 65535u);
    }

    void testWriteRead2()
    {
      const char *filename = "TestDn.testWriteRead2.txt";

      Dn stdfStrIn("11111111000000011111111");
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Dn stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "11111111000000011111111");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "11111111000000011111111");
      TS_ASSERT_EQUALS(stdfStrIn.size(), 5u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 5u);
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 65535u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 65535u);
    }

    void testWriteRead3()
    {
      const char *filename = "TestDn.testWriteRead3.txt";

      string str;
      str.assign(27, '0');
      Dn stdfStrIn = str;
      stdfStrIn[0] = 1;
      stdfStrIn[6] = 1;
      stdfStrIn[26] = 1;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Dn stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "100000100000000000000000001");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "100000100000000000000000001");
      TS_ASSERT_EQUALS(stdfStrIn[0], 1);
      TS_ASSERT_EQUALS(stdfStrOut[0], 1);
      TS_ASSERT_EQUALS(stdfStrIn[6], 1);
      TS_ASSERT_EQUALS(stdfStrOut[6], 1);
      TS_ASSERT_EQUALS(stdfStrIn[26], 1);
      TS_ASSERT_EQUALS(stdfStrOut[26], 1);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 6u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 6u);
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 65535u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 65535u);
    }

    void testWriteRead4()
    {
      const char *filename = "TestDn.testWriteRead4.txt";

      string str;
      str.assign(65536, '1');
      Dn stdfStrIn(str);
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Dn stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      str.erase(65535,1);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), str);
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), str);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 8194u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 8194u);
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 65535u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 65535u);
    }
};
