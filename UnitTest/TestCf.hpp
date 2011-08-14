#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestCf : public CxxTest::TestSuite 
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
      Cf stdfStr;
      TS_ASSERT(stdfStr.mData == "");
      TS_ASSERT_EQUALS(stdfStr.size(), 0);
    }

    void testConstructor2()
    {
      Cf stdfStr = "";
      TS_ASSERT(stdfStr.mData == "");
      TS_ASSERT_EQUALS(stdfStr.size(), 0);
      stdfStr += "";
      TS_ASSERT(stdfStr.mData == "");
      TS_ASSERT_EQUALS(stdfStr.size(), 0);
    }

    void testConstructor3()
    {
      Cf stdfStr = "AA";
      TS_ASSERT(stdfStr.mData == "AA");
      TS_ASSERT_EQUALS(stdfStr.to_string(), "AA");
      TS_ASSERT_EQUALS(stdfStr.size(), 2);
      stdfStr += "BB";
      TS_ASSERT(stdfStr.mData == "AABB");
      TS_ASSERT_EQUALS(stdfStr.to_string(), "AABB");
      TS_ASSERT_EQUALS(stdfStr.size(), 4);
      stdfStr = "CC";
      TS_ASSERT(stdfStr.mData == "CC");
      TS_ASSERT_EQUALS(stdfStr.to_string(), "CC");
      TS_ASSERT_EQUALS(stdfStr.size(), 2);
    }

    void testWriteRead1()
    {
      const char *filename = "TestCf.testWriteRead1.txt";

     int size = 0;

      Cf stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      size = stdfStrIn.to_string().size();
      stdfStrIn.write(outfile);
      outfile.close();

      Cf stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "");
      TS_ASSERT_EQUALS(stdfStrIn.size(), 0);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 0);
    }

    void testWriteRead2()
    {
      const char *filename = "TestCf.testWriteRead2.txt";

     int size = 0;

      Cf stdfStrIn = "123456789";
      ofstream outfile(filename, ofstream::binary);
      size = stdfStrIn.to_string().size();
      stdfStrIn.write(outfile);
      outfile.close();

      Cf stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "123456789");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "123456789");
      TS_ASSERT_EQUALS(stdfStrIn.size(), 9);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 9);
    }

    void testWriteRead3()
    {
      const char *filename = "TestCf.testWriteRead3.txt";

     int size = 0;

      Cf stdfStrIn = "123456789";
      ofstream outfile(filename, ofstream::binary);
      size = stdfStrIn.to_string().size();
      stdfStrIn.write(outfile, size+1);
      outfile.close();

      Cf stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "123456789");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "123456789");
      TS_ASSERT_EQUALS(stdfStrIn.size(), 9);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 9);
    }

};
