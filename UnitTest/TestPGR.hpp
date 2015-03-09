#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestPGR : public CxxTest::TestSuite 
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
      PGR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 5u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "5");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "62");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "");
    }

    void testConstructor1()
    {
      PGR stdfRec;
      stdfRec.setGrpindx(255);
      stdfRec.setGrpnam("Cn");
      stdfRec.setIndxcnt(10);
      stdfRec.setPmrindx(1,1);
      stdfRec.setPmrindx(9,9);
      TS_ASSERT_EQUALS(stdfRec.storage(), 27u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "27");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "62");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[4], "Cn");
      TS_ASSERT_EQUALS(str[5], "10");
      TS_ASSERT_EQUALS(str[6], "0,1,0,0,0,0,0,0,0,9");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "5");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "62");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestPGR.testWriteRead1.txt";

      PGR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      PGR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "5");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "62");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestPGR.testWriteRead2.txt";

      PGR stdfRecIn;
      stdfRecIn.setGrpindx(255);
      stdfRecIn.setGrpnam("Cn");
      stdfRecIn.setIndxcnt(10);
      stdfRecIn.setPmrindx(1,1);
      stdfRecIn.setPmrindx(9,9);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 27u)

      PGR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "27");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "62");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[4], "Cn");
      TS_ASSERT_EQUALS(str[5], "10");
      TS_ASSERT_EQUALS(str[6], "0,1,0,0,0,0,0,0,0,9");
    }

};
