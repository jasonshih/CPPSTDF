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
      JxN1 stdfStr;
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
      TS_ASSERT_EQUALS(stdfStr.size(), 0u);
      TS_ASSERT_EQUALS(stdfStr.storage(), 0u);
    }

    void testConstructor1()
    {
      JxN1 stdfStr("00000");
      for(size_t i = 0; i < 5; i++)
      {
        TS_ASSERT_EQUALS(stdfStr[i], 0);
      }
      TS_ASSERT_EQUALS(stdfStr.to_string(), "00000");
      TS_ASSERT_EQUALS(stdfStr.size(), 5u);
      TS_ASSERT_EQUALS(stdfStr.storage(), 3u);
    }

    void testConstructor2()
    {
      JxN1 stdfStr = "00000";
      for(size_t i = 0; i < 5; i++)
      {
        TS_ASSERT_EQUALS(stdfStr[i], 0);
      }
      TS_ASSERT_EQUALS(stdfStr.to_string(), "00000");
      TS_ASSERT_EQUALS(stdfStr.size(), 5u);
      TS_ASSERT_EQUALS(stdfStr.storage(), 3u);
    }

    void testConstructor3()
    {
      JxN1 stdfStr("ABC");
      TS_ASSERT_EQUALS(stdfStr[0], 0xA);
      TS_ASSERT_EQUALS(stdfStr[1], 0xB);
      TS_ASSERT_EQUALS(stdfStr[2], 0xC);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "ABC");
      TS_ASSERT_EQUALS(stdfStr.size(), 3u);
      TS_ASSERT_EQUALS(stdfStr.storage(), 2u);
    }

    void testConstructor4()
    {
      JxN1 stdfStr = ("0123456789ABCDEF");
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0123456789ABCDEF");
      TS_ASSERT_EQUALS(stdfStr.size(), 16u);
      TS_ASSERT_EQUALS(stdfStr.storage(), 8u);
    }

    void testWriteRead1()
    {
      const char *filename = "TestJxN1.testWriteRead1.txt";

      JxN1 stdfStrIn = ("");
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxN1 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, 0);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "");
      TS_ASSERT_EQUALS(stdfStrIn.size(), 0u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 0u);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 0u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 0u);
    }

    void testWriteRead2()
    {
      const char *filename = "TestJxN1.testWriteRead2.txt";

      JxN1 stdfStrIn = ("0123456789ABCDEFabcdef");
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxN1 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, 22);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "0123456789ABCDEFABCDEF");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "0123456789ABCDEFABCDEF");
      TS_ASSERT_EQUALS(stdfStrIn.size(), 22u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 22u);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 11u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 11u);
    }

    void testWriteRead3()
    {
      const char *filename = "TestJxN1.testWriteRead3.txt";

      JxN1 stdfStrIn(22);
      stdfStrIn[1] = 1;
      stdfStrIn[21] = 0xf;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxN1 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, 22);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "010000000000000000000F");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "010000000000000000000F");
      TS_ASSERT_EQUALS(stdfStrIn.size(), 22u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 22u);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 11u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 11u);
      TS_ASSERT_EQUALS(stdfStrIn[1], 1);
      TS_ASSERT_EQUALS(stdfStrOut[1], 1);
      TS_ASSERT_EQUALS(stdfStrIn[21], 0xf);
      TS_ASSERT_EQUALS(stdfStrOut[21], 0xf);

      stdfStrIn.clear();
      stdfStrOut.clear();
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "");
      TS_ASSERT_EQUALS(stdfStrIn.size(), 0u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 0u);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 0u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 0u);
    }

};
