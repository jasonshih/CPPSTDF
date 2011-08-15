#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

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
      B6 stdfStr("0000000100100000001");
      unsigned char ch[SIZE] = {0};
      ch[0] = 128;
      ch[1] = 4;
      ch[2] = 4;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), string("000000010010000000100000000000000000000000000000"));
      stdfStr = "1000000000000001";
      memset(ch, 0, SIZE);
      ch[0] = 1;
      ch[1] = 128;
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, SIZE);
      TS_ASSERT_EQUALS(stdfStr.to_string(), string("100000000000000100000000000000000000000000000000"));
      stdfStr.reset(1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "111111111111111111111111111111111111111111111111");
      stdfStr.reset(0);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "000000000000000000000000000000000000000000000000");
      stdfStr[0] = 1;
      TS_ASSERT_EQUALS(stdfStr.to_string(), "100000000000000000000000000000000000000000000000");
      TS_ASSERT_EQUALS(stdfStr[0], 1);
    }

    void testWriteRead1()
    {
      const char *filename = "TestB6.testWriteRead1.txt";

      B6 stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      B6 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
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
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      B6 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "111111110000000111111110000000000000000000000000");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "111111110000000111111110000000000000000000000000");
    }

    void testWriteRead3()
    {
      const char *filename = "TestB6.testWriteRead3.txt";

      B6 stdfStrIn;
      stdfStrIn[0] = 1;
      stdfStrIn[6] = 1;
      stdfStrIn[26] = 1;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      B6 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, SIZE);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "100000100000000000000000001000000000000000000000");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "100000100000000000000000001000000000000000000000");
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
