#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestR8 : public CxxTest::TestSuite 
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
      R8 stdfStr;
      TS_ASSERT_EQUALS(stdfStr.mData, 0.0);
    }

    void testConstructor2()
    {
      R8 stdfStr = -0;
      TS_ASSERT_EQUALS(stdfStr.mData, 0.0);
    }


    void testConstructor3()
    {
      R8 stdfStr = 0.1234567890123456789;
      TS_ASSERT_EQUALS(stdfStr.mData, (double)0.1234567890123456789);
      stdfStr = -0.1234567890123456789;
      TS_ASSERT_EQUALS(stdfStr.mData, (double)-0.1234567890123456789);
      stdfStr = 9999999999999999;
      TS_ASSERT_EQUALS(stdfStr.mData, (double)9999999999999999);
    }

    void testWriteRead1()
    {
      const char *filename = "TestR8.testWriteRead1.txt";

      R8 stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      R8 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.mData, stdfStrOut.mData);
      TS_ASSERT_EQUALS(stdfStrIn.mData, 0);
      TS_ASSERT_EQUALS(stdfStrOut.mData, 0);
      TS_ASSERT_EQUALS(stdfStrIn.getValue(), 0);
      TS_ASSERT_EQUALS(stdfStrOut.getValue(), 0);
    }

    void testWriteRead2()
    {
      const char *filename = "TestR8.testWriteRead2.txt";

      R8 stdfStrIn = -0.0;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      R8 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.mData, stdfStrOut.mData);
      TS_ASSERT_EQUALS(stdfStrIn.mData, 0);
      TS_ASSERT_EQUALS(stdfStrOut.mData, 0);
      TS_ASSERT_EQUALS(stdfStrIn.getValue(), 0);
      TS_ASSERT_EQUALS(stdfStrOut.getValue(), 0);
    }

    void testWriteRead3()
    {
      const char *filename = "TestR8.testWriteRead3.txt";

      R8 stdfStrIn = 214748364700000000ULL;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      R8 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.mData, stdfStrOut.mData);
      TS_ASSERT_EQUALS(stdfStrIn.mData, 214748364700000000ULL);
      TS_ASSERT_EQUALS(stdfStrOut.mData, 214748364700000000ULL);
      TS_ASSERT_EQUALS(stdfStrIn.getValue(), 214748364700000000ULL);
      TS_ASSERT_EQUALS(stdfStrOut.getValue(), 214748364700000000ULL);
    }

    void testWriteRead4()
    {
      const char *filename = "TestR8.testWriteRead4.txt";

      R8 stdfStrIn = -2147483647000000009;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      R8 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.mData, stdfStrOut.mData);
      TS_ASSERT_EQUALS(stdfStrIn.mData, -2147483647000000009);
      TS_ASSERT_EQUALS(stdfStrOut.mData, -2147483647000000009);
      TS_ASSERT_EQUALS(stdfStrIn.getValue(), -2147483647000000009);
      TS_ASSERT_EQUALS(stdfStrOut.getValue(), -2147483647000000009);
    }

    void testWriteRead5()
    {
      const char *filename = "TestR5.testWriteRead4.txt";

      R8 stdfStrIn = -0.1234567890123456789;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      R8 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.mData, stdfStrOut.mData);
      TS_ASSERT_EQUALS(stdfStrIn.mData, (double)-0.1234567890123456789);
      TS_ASSERT_EQUALS(stdfStrOut.mData, (double)-0.1234567890123456789);
      TS_ASSERT_EQUALS(stdfStrIn.getValue(), (double)-0.1234567890123456789);
      TS_ASSERT_EQUALS(stdfStrOut.getValue(), (double)-0.1234567890123456789);
    }


};
