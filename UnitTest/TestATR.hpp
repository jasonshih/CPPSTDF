#include <cxxtest/TestSuite.h>

#include "../src/ATR.hpp"

class TestATR : public CxxTest::TestSuite 
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
      ATR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 9u);
      vector<string> str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "9");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
    }

    void testConstructor1()
    {
      ATR stdfRec;
      stdfRec.setModtime(1111111111u);
      stdfRec.setCmdline("TestATR");
      TS_ASSERT_EQUALS(stdfRec.storage(), 16u);
      vector<string> str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "16");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "1111111111");
      TS_ASSERT_EQUALS(str[4], "TestATR");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "9");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestATR.testWriteRead1.txt";

      ATR stdfRecIn;
      ofstream outfile(filename, ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      ATR stdfRecOut;
      ifstream infile(filename, ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      vector<string> str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "9");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestATR.testWriteRead2.txt";

      ATR stdfRecIn;
      stdfRecIn.setModtime(1111111111u);
      stdfRecIn.setCmdline("TestATR");
      ofstream outfile(filename, ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 16u)

      ATR stdfRecOut;
      ifstream infile(filename, ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      vector<string> str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "16");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "1111111111");
      TS_ASSERT_EQUALS(str[4], "TestATR");
    }

};
