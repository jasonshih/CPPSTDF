#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

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
      TS_ASSERT_EQUALS(stdfRec.storage(), 21u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "21");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "1");
      TS_ASSERT_EQUALS(str[4], "V4-2007,Scan:2007.1");
    }

    void testWriteRead1()
    {
      const char *filename = "TestVUR.testWriteRead1.txt";

      VUR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      VUR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "21");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "1");
      TS_ASSERT_EQUALS(str[4], "V4-2007,Scan:2007.1");
    }

};
