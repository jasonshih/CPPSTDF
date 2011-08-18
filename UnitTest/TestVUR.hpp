#include <cxxtest/TestSuite.h>

#include "../src/VUR.hpp"

class TestVUR : public CxxTest::TestSuite 
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
      VUR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 25u);
      vector<string> str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "25");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "2");
      TS_ASSERT_EQUALS(str[4], "V4-2007,Scan:2007.1");
    }

    void testWriteRead1()
    {
      const char *filename = "TestVUR.testWriteRead1.txt";

      VUR stdfRecIn;
      ofstream outfile(filename, ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      VUR stdfRecOut;
      ifstream infile(filename, ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      vector<string> str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "25");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "2");
      TS_ASSERT_EQUALS(str[4], "V4-2007,Scan:2007.1");
    }

};
