#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestJxN1 : public CxxTest::TestSuite 
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
      JxN1<1> stdfStr;
      unsigned char ch[1] = {0};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, 1);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0");
    }

    void testConstructor1()
    {
      JxN1<9> stdfStr;
      unsigned char ch[5] = {0};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, 5);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "000000000");
    }

    void testConstructor2()
    {
      JxN1<9> stdfStr = "";
      unsigned char ch[5] = {0};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, 5);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "000000000");
      TS_ASSERT_EQUALS(stdfStr.max_size(), 9u);
      TS_ASSERT_EQUALS(stdfStr.size(), 5u);
    }

    void testConstructor3()
    {
      JxN1<3> stdfStr("ABC");
      unsigned char ch[2] = {0xBA, 0x0C};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, 2);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "ABC");
      TS_ASSERT_EQUALS(stdfStr.max_size(), 3u);
      TS_ASSERT_EQUALS(stdfStr.size(), 2u);
    }

    void testConstructor4()
    {
      JxN1<16> stdfStr = ("0123456789ABCDEF");
      unsigned char ch[8] = {0x10, 0x32, 0x54, 0x76, 0x98, 0xBA, 0xDC, 0xFE};
      TS_ASSERT_SAME_DATA(stdfStr.mData, ch, 8);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0123456789ABCDEF");
      TS_ASSERT_EQUALS(stdfStr.max_size(), 16u);
      TS_ASSERT_EQUALS(stdfStr.size(), 8u);
    }

    void testWriteRead1()
    {
      const char *filename = "TestJxN1.testWriteRead1.txt";

      JxN1<22> stdfStrIn = ("");
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxN1<22> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, 11);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "0000000000000000000000");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "0000000000000000000000");
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 22u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 22u);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 11u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 11u);
    }

    void testWriteRead2()
    {
      const char *filename = "TestJxN1.testWriteRead2.txt";

      JxN1<22> stdfStrIn = ("0123456789ABCDEFabcdef");
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxN1<22> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, 11);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "0123456789ABCDEFABCDEF");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "0123456789ABCDEFABCDEF");
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 22u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 22u);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 11u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 11u);
    }

    void testWriteRead3()
    {
      const char *filename = "TestJxN1.testWriteRead3.txt";

      JxN1<22> stdfStrIn;
      stdfStrIn[1] = 1;
      stdfStrIn[21] = 0xf;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxN1<22> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, 11);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "010000000000000000000F");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "010000000000000000000F");
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 22u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 22u);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 11u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 11u);
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
      TS_ASSERT_EQUALS(stdfStrIn.size(), 11u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 11u);
    }

};
