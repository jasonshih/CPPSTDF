#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestWIR : public CxxTest::TestSuite 
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
      WIR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 7u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "7");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "");
    }

    void testConstructor1()
    {
      WIR stdfRec;
      stdfRec.setHeadnum(111u);
      stdfRec.setSitegrp(222u);
      stdfRec.setStart(1111111111u);
      stdfRec.setWaferid("WIR");
      TS_ASSERT_EQUALS(stdfRec.storage(), 10u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "10");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "111");
      TS_ASSERT_EQUALS(str[4], "222");
      TS_ASSERT_EQUALS(str[5], "1111111111");
      TS_ASSERT_EQUALS(str[6], "WIR");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "7");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestWIR.testWriteRead1.txt";

      WIR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      WIR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "7");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestWIR.testWriteRead2.txt";

      WIR stdfRecIn;
      stdfRecIn.setHeadnum(111u);
      stdfRecIn.setSitegrp(222u);
      stdfRecIn.setStart(1111111111u);
      stdfRecIn.setWaferid("waferid");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 14u)

      WIR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
    
      TS_ASSERT_EQUALS(str[0], "14");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "111");
      TS_ASSERT_EQUALS(str[4], "222");
      TS_ASSERT_EQUALS(str[5], "1111111111");
      TS_ASSERT_EQUALS(str[6], "waferid");
    }

};
