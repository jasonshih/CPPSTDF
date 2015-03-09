#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

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
      TS_ASSERT_EQUALS(stdfRec.storage(), 5u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "5");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
    }

    void testConstructor1()
    {
      ATR stdfRec;
      stdfRec.setModtim(1111111111u);
      stdfRec.setCmdline("TestATR");
      TS_ASSERT_EQUALS(stdfRec.storage(), 12u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "12");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "1111111111");
      TS_ASSERT_EQUALS(str[4], "TestATR");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "5");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestATR.testWriteRead1.txt";

      ATR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      ATR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "5");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestATR.testWriteRead2.txt";

      ATR stdfRecIn;
      stdfRecIn.setModtim(1111111111u);
      stdfRecIn.setCmdline("TestATR");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 12u)

      ATR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "12");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "1111111111");
      TS_ASSERT_EQUALS(str[4], "TestATR");
    }

};
