#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

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
      TS_ASSERT_EQUALS(stdfStr.size(), 1u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
    }

    void testConstructor2()
    {
      Bn stdfStr = "";
      char ch[SIZE] = {0};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
      TS_ASSERT_EQUALS(stdfStr.size(), 1u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
    }

    void testConstructor3()
    {
      Bn stdfStr("0000000100100000001");
      unsigned char ch[SIZE] = {0};
      ch[0] = 19;
      ch[1] = 128;
      ch[2] = 4;
      ch[3] = 4;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), string("0000000100100000001"));
      TS_ASSERT_EQUALS(stdfStr.size(), 4u);
      stdfStr = "1000000000000001";
      memset(ch, 0, SIZE);
      ch[0] = 16;
      ch[1] = 1;
      ch[2] = 128;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), string("1000000000000001"));
      stdfStr.clear();
      memset(ch, 0, SIZE);
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
      stdfStr = "00000000000000000000";
      ch[0] = 20;
      stdfStr[18] = 1;
      ch[3] = 4;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "00000000000000000010");
      TS_ASSERT_EQUALS(stdfStr[18], 1);
      stdfStr[9] = 1;
      ch[2] = 2;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "00000000010000000010");
      TS_ASSERT_EQUALS(stdfStr[9], 1);
    }

    void testWriteRead1()
    {
      const char *filename = "TestBn.testWriteRead1.txt";

      Bn stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Bn stdfStrOut;
      ifstream infile(filename, ifstream::binary);
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
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Bn stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "11111111000000011111111");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "11111111000000011111111");
    }

    void testWriteRead3()
    {
      const char *filename = "TestBn.testWriteRead3.txt";

      string str;
      str.assign(27, '0');
      Bn stdfStrIn = str;
      stdfStrIn[0] = 1;
      stdfStrIn[6] = 1;
      stdfStrIn[26] = 1;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Bn stdfStrOut;
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
    }

    void testWriteRead4()
    {
      const char *filename = "TestBn.testWriteRead4.txt";

      string str;
      str.assign(256, '1');
      Bn stdfStrIn(str);
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Bn stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      str.erase(255,1);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), str);
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), str);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 33u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 33u);
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 255u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 255u);
    }
};
