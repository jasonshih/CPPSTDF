#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestSBR : public CxxTest::TestSuite 
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
      SBR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 10u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "10");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "50");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], " ");
      TS_ASSERT_EQUALS(str[8], "");
    }

    void testConstructor1()
    {
      SBR stdfRec;
      stdfRec.setHeadnum(111u);
      stdfRec.setSitenum(255u);
      stdfRec.setSbinnum(255u);
      stdfRec.setSbincnt(255u);
      stdfRec.setSbinpf('P');
      stdfRec.setSbinnam("TestSBR");
      TS_ASSERT_EQUALS(stdfRec.storage(), 17u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "17");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "50");
      TS_ASSERT_EQUALS(str[3], "111");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "255");
      TS_ASSERT_EQUALS(str[6], "255");
      TS_ASSERT_EQUALS(str[7], "P");
      TS_ASSERT_EQUALS(str[8], "TestSBR");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "10");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "50");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], " ");
      TS_ASSERT_EQUALS(str[8], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestSBR.testWriteRead1.txt";

      SBR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      SBR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "10");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "50");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], " ");
      TS_ASSERT_EQUALS(str[8], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestSBR.testWriteRead2.txt";

      SBR stdfRecIn;
      stdfRecIn.setSbinpf('P');
      stdfRecIn.setSbinnam("TestSBR");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 17u)

      SBR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "17");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "50");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "P");
      TS_ASSERT_EQUALS(str[8], "TestSBR");
    }

};
