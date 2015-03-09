#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestTSR : public CxxTest::TestSuite 
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
      TSR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 43u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "43");
      TS_ASSERT_EQUALS(str[1], "10");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], " ");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "4294967295");
      TS_ASSERT_EQUALS(str[8], "4294967295");
      TS_ASSERT_EQUALS(str[9], "4294967295");
      TS_ASSERT_EQUALS(str[10], "");
      TS_ASSERT_EQUALS(str[11], "");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "11111111");
      TS_ASSERT_EQUALS(str[14], "0");
      TS_ASSERT_EQUALS(str[15], "0");
      TS_ASSERT_EQUALS(str[16], "0");
      TS_ASSERT_EQUALS(str[17], "0");
      TS_ASSERT_EQUALS(str[18], "0");
    }

    void testConstructor1()
    {
      TSR stdfRec;
      stdfRec.setHeadnum(255u);
      stdfRec.setTesttyp('S');
      stdfRec.setTestnum(4294967295u);
      stdfRec.setExeccnt(1234567890u);
      stdfRec.setTestnam("TestTSR");
      stdfRec.setOptflag("10001000");
      stdfRec.setTesttim(0.123459);
      TS_ASSERT_EQUALS(stdfRec.storage(), 50u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "50");
      TS_ASSERT_EQUALS(str[1], "10");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[5], "S");
      TS_ASSERT_EQUALS(str[6], "4294967295");
      TS_ASSERT_EQUALS(str[7], "1234567890");
      TS_ASSERT_EQUALS(str[10], "TestTSR");
      TS_ASSERT_EQUALS(str[13], "10001000");
      TS_ASSERT_EQUALS(str[14], "0.123459");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "43");
      TS_ASSERT_EQUALS(str[1], "10");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], " ");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "4294967295");
      TS_ASSERT_EQUALS(str[8], "4294967295");
      TS_ASSERT_EQUALS(str[9], "4294967295");
      TS_ASSERT_EQUALS(str[10], "");
      TS_ASSERT_EQUALS(str[11], "");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "11111111");
      TS_ASSERT_EQUALS(str[14], "0");
      TS_ASSERT_EQUALS(str[15], "0");
      TS_ASSERT_EQUALS(str[16], "0");
      TS_ASSERT_EQUALS(str[17], "0");
      TS_ASSERT_EQUALS(str[18], "0");
    }

    void testWriteRead1()
    {
      const char *filename = "TestTSR.testWriteRead1.txt";

      TSR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      TSR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "43");
      TS_ASSERT_EQUALS(str[1], "10");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], " ");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "4294967295");
      TS_ASSERT_EQUALS(str[8], "4294967295");
      TS_ASSERT_EQUALS(str[9], "4294967295");
      TS_ASSERT_EQUALS(str[10], "");
      TS_ASSERT_EQUALS(str[11], "");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "11111111");
      TS_ASSERT_EQUALS(str[14], "0");
      TS_ASSERT_EQUALS(str[15], "0");
      TS_ASSERT_EQUALS(str[16], "0");
      TS_ASSERT_EQUALS(str[17], "0");
      TS_ASSERT_EQUALS(str[18], "0");
    }

    void testWriteRead2()
    {
      const char *filename = "TestTSR.testWriteRead2.txt";

      TSR stdfRecIn;
      stdfRecIn.setHeadnum(255u);
      stdfRecIn.setTesttyp('S');
      stdfRecIn.setTestnum(4294967295u);
      stdfRecIn.setExeccnt(1234567890u);
      stdfRecIn.setTestnam("TestTSR");
      stdfRecIn.setOptflag("10001000");
      stdfRecIn.setTesttim(0.123459);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 50u)

      TSR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "50");
      TS_ASSERT_EQUALS(str[1], "10");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[5], "S");
      TS_ASSERT_EQUALS(str[6], "4294967295");
      TS_ASSERT_EQUALS(str[7], "1234567890");
      TS_ASSERT_EQUALS(str[10], "TestTSR");
      TS_ASSERT_EQUALS(str[13], "10001000");
      TS_ASSERT_EQUALS(str[14], "0.123459");
    }

};
