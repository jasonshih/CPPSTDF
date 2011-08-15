#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestC5 : public CxxTest::TestSuite 
{
  private:
    typedef CharArray<5> C5;
  public:
    void setUp()
    {
    }
    void tearDown()
    {
    }

    void testConstructor1()
    {
      C5 stdfStr;
      TS_ASSERT_SAME_DATA(stdfStr.mData, "     ", 5);
    }

    void testConstructor2()
    {
      C5 stdfStr = "";
      TS_ASSERT_SAME_DATA(stdfStr.mData, "     ", 5);
    }

    void testConstructor3()
    {
      C5 stdfStr;
      TS_ASSERT_SAME_DATA(stdfStr.mData, "     ", 5);
      stdfStr = "A";
      TS_ASSERT_SAME_DATA(stdfStr.mData, "A    ", 5);
    }

    void testConstructor4()
    {
      C5 stdfStr;
      TS_ASSERT_SAME_DATA(stdfStr.mData, "     ", 5);
      stdfStr = 'A';
      TS_ASSERT_SAME_DATA(stdfStr.mData, "A    ", 5);
      TS_ASSERT_SAME_DATA(stdfStr.to_string().data(), "A    ", 5);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "A    ");
      TS_ASSERT_EQUALS(stdfStr.size(), 5u);
    }

    void testWriteRead1()
    {
      const char *filename = "TestC5.testWriteRead1.txt";

      C5 stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      C5 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, 5);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "     ");
      TS_ASSERT_EQUALS(stdfStrIn.size(), 5u);
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "     ");
      TS_ASSERT_EQUALS(stdfStrOut.size(), 5u);
    }

    void testWriteRead2()
    {
      const char *filename = "TestC5.testWriteRead2.txt";

      C5 stdfStrIn("AA");
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      C5 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, 5);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "AA   ");
      TS_ASSERT_EQUALS(stdfStrIn.size(), 5u);
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "AA   ");
      TS_ASSERT_EQUALS(stdfStrOut.size(), 5u);
    }

};
