#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestR4 : public CxxTest::TestSuite 
{
  private:
    bool isEqual(float a, float b, float relError)
    {
      if(fabs(a) < fabs(b)) return ((fabs((a-b))/a) < relError)? true:false;
      else                  return ((fabs((a-b))/b) < relError)? true:false;
    }
    bool isEqual(float a, float b) {return isEqual(a, b, FLT_EPSILON);}

  public:
    void setUp()
    {
    }
    void tearDown()
    {
    }

    void testConstructor1()
    {
      R4 stdfStr;
      TS_ASSERT_EQUALS(stdfStr.mData, 0.0);
    }

    void testConstructor2()
    {
      R4 stdfStr = -0;
      TS_ASSERT_EQUALS(stdfStr.mData, 0.0);
    }


    void testConstructor3()
    {
      R4 stdfStr = 0.1234567;
      TS_ASSERT_EQUALS(stdfStr.mData, (float)0.1234567);
      stdfStr = -0.1234567;
      TS_ASSERT_EQUALS(stdfStr.mData, (float)-0.1234567);
      stdfStr = 9999999999;
      TS_ASSERT_EQUALS(stdfStr.mData, (float)9999999999);
    }

    void testWriteRead1()
    {
      const char *filename = "TestR4.testWriteRead1.txt";

      R4 stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      R4 stdfStrOut;
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
      const char *filename = "TestR4.testWriteRead2.txt";

      R4 stdfStrIn = -0.0;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      R4 stdfStrOut;
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
      const char *filename = "TestR4.testWriteRead3.txt";

      R4 stdfStrIn = 214748364700000000ULL;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      R4 stdfStrOut;
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
      const char *filename = "TestR4.testWriteRead4.txt";

      R4 stdfStrIn = -214748364700000000;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      R4 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.mData, stdfStrOut.mData);
      TS_ASSERT_EQUALS(stdfStrIn.mData, -214748364700000000);
      TS_ASSERT_EQUALS(stdfStrOut.mData, -214748364700000000);
      TS_ASSERT_EQUALS(stdfStrIn.getValue(), -214748364700000000);
      TS_ASSERT_EQUALS(stdfStrOut.getValue(), -214748364700000000);
    }

    void testWriteRead5()
    {
      const char *filename = "TestR5.testWriteRead4.txt";

      R4 stdfStrIn = -0.123456789;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      R4 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.mData, stdfStrOut.mData);
      TS_ASSERT_EQUALS(stdfStrIn.mData, (float)-0.123456789);
      TS_ASSERT_EQUALS(stdfStrOut.mData, (float)-0.123456789);
      TS_ASSERT_EQUALS(stdfStrIn.getValue(), (float)-0.123456789);
      TS_ASSERT_EQUALS(stdfStrOut.getValue(), (float)-0.123456789);
    }


};
