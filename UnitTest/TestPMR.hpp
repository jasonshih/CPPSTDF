#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestPMR : public CxxTest::TestSuite 
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
      PMR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 9u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "9");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "60");
      TS_ASSERT_EQUALS(str[3], "0");//?
      TS_ASSERT_EQUALS(str[4], "0");//?
      TS_ASSERT_EQUALS(str[5], "");
      TS_ASSERT_EQUALS(str[6], "");
      TS_ASSERT_EQUALS(str[7], "");
      TS_ASSERT_EQUALS(str[8], "1");
      TS_ASSERT_EQUALS(str[9], "1");
    }

    void testConstructor1()
    {
      PMR stdfRec;
      stdfRec.setPmrindx(65535u);
      stdfRec.setChantyp(65535u);
      stdfRec.setChannam("TestPMR");
      stdfRec.setPhynam("TestPMR");
      stdfRec.setLognam("TestPMR");
      stdfRec.setHeadnum(255);
      stdfRec.setSitenum(255u);
      TS_ASSERT_EQUALS(stdfRec.storage(), 30u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "30");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "60");
      TS_ASSERT_EQUALS(str[3], "65535");
      TS_ASSERT_EQUALS(str[4], "65535");
      TS_ASSERT_EQUALS(str[5], "TestPMR");
      TS_ASSERT_EQUALS(str[6], "TestPMR");
      TS_ASSERT_EQUALS(str[7], "TestPMR");
      TS_ASSERT_EQUALS(str[8], "255");
      TS_ASSERT_EQUALS(str[9], "255");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "9");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "60");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "");
      TS_ASSERT_EQUALS(str[6], "");
      TS_ASSERT_EQUALS(str[7], "");
      TS_ASSERT_EQUALS(str[8], "1");
      TS_ASSERT_EQUALS(str[9], "1");
    }

    void testWriteRead1()
    {
      const char *filename = "TestPMR.testWriteRead1.txt";

      PMR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      PMR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "9");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "60");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "");
      TS_ASSERT_EQUALS(str[6], "");
      TS_ASSERT_EQUALS(str[7], "");
      TS_ASSERT_EQUALS(str[8], "1");
      TS_ASSERT_EQUALS(str[9], "1");
    }

    void testWriteRead2()
    {
      const char *filename = "TestPMR.testWriteRead2.txt";

      PMR stdfRecIn;
      stdfRecIn.setPmrindx(65535u);
      stdfRecIn.setChannam("TestPMR");
      stdfRecIn.setSitenum(255u);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 16u)

      PMR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "16");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "60");
      TS_ASSERT_EQUALS(str[3], "65535");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "TestPMR");
      TS_ASSERT_EQUALS(str[6], "");
      TS_ASSERT_EQUALS(str[7], "");
      TS_ASSERT_EQUALS(str[8], "1");
      TS_ASSERT_EQUALS(str[9], "255");
    }

};
