#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestPRR : public CxxTest::TestSuite 
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
      PRR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 20u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "20");
      TS_ASSERT_EQUALS(str[1], "5");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "00001000");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "0");
      TS_ASSERT_EQUALS(str[8], "65535");
      TS_ASSERT_EQUALS(str[9], "-32768");
      TS_ASSERT_EQUALS(str[10], "-32768");
      TS_ASSERT_EQUALS(str[11], "0");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "");
      TS_ASSERT_EQUALS(str[14], "");
    }

    void testConstructor1()
    {
      PRR stdfRec;
      stdfRec.setHeadnum(255);
      stdfRec.setSitenum(255);
      stdfRec.setPartflg("00011000");
      stdfRec.setNumtest(65535);
      stdfRec.setHardbin(65535);
      stdfRec.setSoftbin(0);
      stdfRec.setXcoord(32767);
      stdfRec.setYcoord(0);
      stdfRec.setTestt(1234567890);
      stdfRec.setPartid("partid");
      stdfRec.setParttxt("parttxt");
      stdfRec.setPartfix("000100010001");
      TS_ASSERT_EQUALS(stdfRec.storage(), 35u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "35");
      TS_ASSERT_EQUALS(str[1], "5");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "00011000");
      TS_ASSERT_EQUALS(str[6], "65535");
      TS_ASSERT_EQUALS(str[7], "65535");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "32767");
      TS_ASSERT_EQUALS(str[10], "0");
      TS_ASSERT_EQUALS(str[11], "1234567890");
      TS_ASSERT_EQUALS(str[12], "partid");
      TS_ASSERT_EQUALS(str[13], "parttxt");
      TS_ASSERT_EQUALS(str[14], "000100010001");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "20");
      TS_ASSERT_EQUALS(str[1], "5");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "00001000");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "0");
      TS_ASSERT_EQUALS(str[8], "65535");
      TS_ASSERT_EQUALS(str[9], "-32768");
      TS_ASSERT_EQUALS(str[10], "-32768");
      TS_ASSERT_EQUALS(str[11], "0");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "");
      TS_ASSERT_EQUALS(str[14], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestPRR.testWriteRead1.txt";

      PRR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      PRR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "20");
      TS_ASSERT_EQUALS(str[1], "5");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "00001000");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "0");
      TS_ASSERT_EQUALS(str[8], "65535");
      TS_ASSERT_EQUALS(str[9], "-32768");
      TS_ASSERT_EQUALS(str[10], "-32768");
      TS_ASSERT_EQUALS(str[11], "0");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "");
      TS_ASSERT_EQUALS(str[14], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestPRR.testWriteRead2.txt";

      PRR stdfRecIn;
      stdfRecIn.setHeadnum(255);
      stdfRecIn.setSitenum(255);
      stdfRecIn.setPartflg("00011000");
      stdfRecIn.setNumtest(65535);
      stdfRecIn.setHardbin(65535);
      stdfRecIn.setSoftbin(0);
      stdfRecIn.setXcoord(32767);
      stdfRecIn.setYcoord(0);
      stdfRecIn.setTestt(1234567890);
      stdfRecIn.setPartid("partid");
      stdfRecIn.setParttxt("parttxt");
      stdfRecIn.setPartfix("000100010001");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 35u)

      PRR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "35");
      TS_ASSERT_EQUALS(str[1], "5");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "00011000");
      TS_ASSERT_EQUALS(str[6], "65535");
      TS_ASSERT_EQUALS(str[7], "65535");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "32767");
      TS_ASSERT_EQUALS(str[10], "0");
      TS_ASSERT_EQUALS(str[11], "1234567890");
      TS_ASSERT_EQUALS(str[12], "partid");
      TS_ASSERT_EQUALS(str[13], "parttxt");
      TS_ASSERT_EQUALS(str[14], "000100010001");
    }

};
