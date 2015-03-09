#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestPTR : public CxxTest::TestSuite 
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
      PTR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 38u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "38");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "00000000");
      TS_ASSERT_EQUALS(str[7], "11000000");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "");
      TS_ASSERT_EQUALS(str[10], "");
      TS_ASSERT_EQUALS(str[11], "00001110");
      TS_ASSERT_EQUALS(str[12], "0");
      TS_ASSERT_EQUALS(str[13], "0");
      TS_ASSERT_EQUALS(str[14], "0");
      TS_ASSERT_EQUALS(str[15], "0");
      TS_ASSERT_EQUALS(str[16], "0");
      TS_ASSERT_EQUALS(str[17], "");
      TS_ASSERT_EQUALS(str[18], "");
      TS_ASSERT_EQUALS(str[19], "");
      TS_ASSERT_EQUALS(str[20], "");
      TS_ASSERT_EQUALS(str[21], "0");
      TS_ASSERT_EQUALS(str[22], "0");
    }

    void testConstructor1()
    {
      PTR stdfRec;
      stdfRec.setTestnum(1234567890);
      stdfRec.setHeadnum(255);
      stdfRec.setSitenum(255);
      stdfRec.setTestflg("00011000");
      stdfRec.setParmflg("10001000");
      stdfRec.setResult (0.123456);
      stdfRec.setTesttxt("Cn");
      stdfRec.setAlarmid("Cn");
      stdfRec.setOptflag("00011000");
      stdfRec.setResscal(127);
      stdfRec.setLlmscal(0);
      stdfRec.setHlmscal(-128);
      stdfRec.setLolimit(0.123456);
      stdfRec.setHilimit(0.123456);
      stdfRec.setUnits  ("Cn");
      stdfRec.setCresfmt("Cn");
      stdfRec.setCllmfmt("Cn");
      stdfRec.setChlmfmt("Cn");
      stdfRec.setLospec (0.123456);
      stdfRec.setHispec (0.123456);
      TS_ASSERT_EQUALS(stdfRec.storage(), 50u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "50");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "1234567890");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "255");
      TS_ASSERT_EQUALS(str[6], "00011000");
      TS_ASSERT_EQUALS(str[7], "10001000");
      TS_ASSERT_EQUALS(str[8], "0.123456")
      TS_ASSERT_EQUALS(str[9], "Cn");
      TS_ASSERT_EQUALS(str[10], "Cn");
      TS_ASSERT_EQUALS(str[11], "00011000");
      TS_ASSERT_EQUALS(str[12], "127");
      TS_ASSERT_EQUALS(str[13], "0");
      TS_ASSERT_EQUALS(str[14], "-128");
      TS_ASSERT_EQUALS(str[15], "0.123456");
      TS_ASSERT_EQUALS(str[16], "0.123456");
      TS_ASSERT_EQUALS(str[17], "Cn");
      TS_ASSERT_EQUALS(str[18], "Cn");
      TS_ASSERT_EQUALS(str[19], "Cn");
      TS_ASSERT_EQUALS(str[20], "Cn");
      TS_ASSERT_EQUALS(str[21], "0.123456");
      TS_ASSERT_EQUALS(str[22], "0.123456");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "38");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "00000000");
      TS_ASSERT_EQUALS(str[7], "11000000");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "");
      TS_ASSERT_EQUALS(str[10], "");
      TS_ASSERT_EQUALS(str[11], "00001110");
      TS_ASSERT_EQUALS(str[12], "0");
      TS_ASSERT_EQUALS(str[13], "0");
      TS_ASSERT_EQUALS(str[14], "0");
      TS_ASSERT_EQUALS(str[15], "0");
      TS_ASSERT_EQUALS(str[16], "0");
      TS_ASSERT_EQUALS(str[17], "");
      TS_ASSERT_EQUALS(str[18], "");
      TS_ASSERT_EQUALS(str[19], "");
      TS_ASSERT_EQUALS(str[20], "");
      TS_ASSERT_EQUALS(str[21], "0");
      TS_ASSERT_EQUALS(str[22], "0");
    }

    void testWriteRead1()
    {
      const char *filename = "TestPTR.testWriteRead1.txt";

      PTR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      PTR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "38");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "00000000");
      TS_ASSERT_EQUALS(str[7], "11000000");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "");
      TS_ASSERT_EQUALS(str[10], "");
      TS_ASSERT_EQUALS(str[11], "00001110");
      TS_ASSERT_EQUALS(str[12], "0");
      TS_ASSERT_EQUALS(str[13], "0");
      TS_ASSERT_EQUALS(str[14], "0");
      TS_ASSERT_EQUALS(str[15], "0");
      TS_ASSERT_EQUALS(str[16], "0");
      TS_ASSERT_EQUALS(str[17], "");
      TS_ASSERT_EQUALS(str[18], "");
      TS_ASSERT_EQUALS(str[19], "");
      TS_ASSERT_EQUALS(str[20], "");
      TS_ASSERT_EQUALS(str[21], "0");
      TS_ASSERT_EQUALS(str[22], "0");
    }

    void testWriteRead2()
    {
      const char *filename = "TestPTR.testWriteRead2.txt";

      PTR stdfRecIn;
      stdfRecIn.setTestnum(1234567890);
      stdfRecIn.setHeadnum(255);
      stdfRecIn.setSitenum(255);
      stdfRecIn.setTestflg("00011000");
      stdfRecIn.setParmflg("10001000");
      stdfRecIn.setResult (0.123456);
      stdfRecIn.setTesttxt("Cn");
      stdfRecIn.setAlarmid("Cn");
      stdfRecIn.setOptflag("00011000");
      stdfRecIn.setResscal(127);
      stdfRecIn.setLlmscal(0);
      stdfRecIn.setHlmscal(-128);
      stdfRecIn.setLolimit(0.123456);
      stdfRecIn.setHilimit(0.123456);
      stdfRecIn.setUnits  ("Cn");
      stdfRecIn.setCresfmt("Cn");
      stdfRecIn.setCllmfmt("Cn");
      stdfRecIn.setChlmfmt("Cn");
      stdfRecIn.setLospec (0.123456);
      stdfRecIn.setHispec (0.123456);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 50u)

      PTR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "50");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "1234567890");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "255");
      TS_ASSERT_EQUALS(str[6], "00011000");
      TS_ASSERT_EQUALS(str[7], "10001000");
      TS_ASSERT_EQUALS(str[8], "0.123456")
      TS_ASSERT_EQUALS(str[9], "Cn");
      TS_ASSERT_EQUALS(str[10], "Cn");
      TS_ASSERT_EQUALS(str[11], "00011000");
      TS_ASSERT_EQUALS(str[12], "127");
      TS_ASSERT_EQUALS(str[13], "0");
      TS_ASSERT_EQUALS(str[14], "-128");
      TS_ASSERT_EQUALS(str[15], "0.123456");
      TS_ASSERT_EQUALS(str[16], "0.123456");
      TS_ASSERT_EQUALS(str[17], "Cn");
      TS_ASSERT_EQUALS(str[18], "Cn");
      TS_ASSERT_EQUALS(str[19], "Cn");
      TS_ASSERT_EQUALS(str[20], "Cn");
      TS_ASSERT_EQUALS(str[21], "0.123456");
      TS_ASSERT_EQUALS(str[22], "0.123456");
    }

};
