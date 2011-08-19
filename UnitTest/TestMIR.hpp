#include <cxxtest/TestSuite.h>

#include "../src/MIR.hpp"

class TestMIR : public CxxTest::TestSuite 
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
      MIR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 49u);
      vector<string> str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "49");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
    }

    void testWriteRead1()
    {
      const char *filename = "TestMIR.testWriteRead1.txt";

      MIR stdfRecIn;
      ofstream outfile(filename, ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      MIR stdfRecOut;
      ifstream infile(filename, ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      vector<string> str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "49");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
    }

};
