#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestMPR : public CxxTest::TestSuite 
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
      MPR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 47u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "47");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "15");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "00000000");
      TS_ASSERT_EQUALS(str[7], "00000000");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "0");
      TS_ASSERT_EQUALS(str[10], "");
      TS_ASSERT_EQUALS(str[11], "");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "");
      TS_ASSERT_EQUALS(str[14], "00000000");
      TS_ASSERT_EQUALS(str[15], "0");
      TS_ASSERT_EQUALS(str[16], "0");
      TS_ASSERT_EQUALS(str[17], "0");
      TS_ASSERT_EQUALS(str[18], "0");
      TS_ASSERT_EQUALS(str[19], "0");
      TS_ASSERT_EQUALS(str[20], "0");
      TS_ASSERT_EQUALS(str[21], "0");
      TS_ASSERT_EQUALS(str[22], "");
      TS_ASSERT_EQUALS(str[23], "");
      TS_ASSERT_EQUALS(str[24], "");
      TS_ASSERT_EQUALS(str[25], "");
      TS_ASSERT_EQUALS(str[26], "");
      TS_ASSERT_EQUALS(str[27], "");
      TS_ASSERT_EQUALS(str[28], "0");
      TS_ASSERT_EQUALS(str[29], "0");
    }

    void testConstructor1()
    {
      MPR stdfRec;
      stdfRec.setTestnum(1234567890);
      stdfRec.setHeadnum(255);
      stdfRec.setSitenum(255);
      stdfRec.setTestflg("11101110");
      stdfRec.setParmflg("00011000");
      stdfRec.setRtnicnt(5);
      stdfRec.setRsltcnt(5);
      stdfRec.setRtnstat(0,0xa);
      stdfRec.setRtnstat(1,0xb);
      stdfRec.setRtnstat(2,0xc);
      stdfRec.setRtnstat(3,0xd);
      stdfRec.setRtnstat(4,0xe);
      stdfRec.setRtnrslt(0,1);
      stdfRec.setRtnrslt(1,2);
      stdfRec.setRtnrslt(2,3);
      stdfRec.setRtnrslt(3,4);
      stdfRec.setRtnrslt(4,5);
      stdfRec.setTesttxt("stdfRecsetTesttxt");
      stdfRec.setAlarmid("stdfRecsetAlarmid");
      stdfRec.setOptflag("11111111");
      stdfRec.setResscal(-128);
      stdfRec.setLlmscal(0);
      stdfRec.setHlmscal(127);
      stdfRec.setLolimit(123456);
      stdfRec.setHilimit(0);
      stdfRec.setStartin(0.123456);
      stdfRec.setIncrin(123.456);
      stdfRec.setRtnindx(0, 1);
      stdfRec.setRtnindx(1, 2);
      stdfRec.setRtnindx(2, 3);
      stdfRec.setRtnindx(3, 4);
      stdfRec.setRtnindx(4, 5);
      stdfRec.setUnits("stdfRecsetUnits");
      stdfRec.setUnitsin("stdfRecsetUnitsin");
      stdfRec.setCresfmt("stdfRecsetCresfmt");
      stdfRec.setCllmfmt("stdfRecsetCllmfmt");
      stdfRec.setChlmfmt("stdfRecsetChlmfmt");
      stdfRec.setLospec(123456);
      stdfRec.setHispec(123457);
      TS_ASSERT_EQUALS(stdfRec.storage(), 197u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "197");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "15");
      TS_ASSERT_EQUALS(str[3], "1234567890");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "255");
      TS_ASSERT_EQUALS(str[6], "11101110");
      TS_ASSERT_EQUALS(str[7], "00011000");
      TS_ASSERT_EQUALS(str[8], "5");
      TS_ASSERT_EQUALS(str[9], "5");
      TS_ASSERT_EQUALS(str[10], "ABCDE");
      TS_ASSERT_EQUALS(str[11], "1,2,3,4,5");
      TS_ASSERT_EQUALS(str[12], "stdfRecsetTesttxt");
      TS_ASSERT_EQUALS(str[13], "stdfRecsetAlarmid");
      TS_ASSERT_EQUALS(str[14], "11111111");
      TS_ASSERT_EQUALS(str[15], "-128");
      TS_ASSERT_EQUALS(str[16], "0");
      TS_ASSERT_EQUALS(str[17], "127");
      TS_ASSERT_EQUALS(str[18], "123456");
      TS_ASSERT_EQUALS(str[19], "0");
      TS_ASSERT_EQUALS(str[20], "0.123456");
      TS_ASSERT_EQUALS(str[21], "123.456");
      TS_ASSERT_EQUALS(str[22], "1,2,3,4,5");
      TS_ASSERT_EQUALS(str[23], "stdfRecsetUnits");
      TS_ASSERT_EQUALS(str[24], "stdfRecsetUnitsin");
      TS_ASSERT_EQUALS(str[25], "stdfRecsetCresfmt");
      TS_ASSERT_EQUALS(str[26], "stdfRecsetCllmfmt");
      TS_ASSERT_EQUALS(str[27], "stdfRecsetChlmfmt");
      TS_ASSERT_EQUALS(str[28], "123456");
      TS_ASSERT_EQUALS(str[29], "123457");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "47");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "15");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "00000000");
      TS_ASSERT_EQUALS(str[7], "00000000");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "0");
      TS_ASSERT_EQUALS(str[10], "");
      TS_ASSERT_EQUALS(str[11], "");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "");
      TS_ASSERT_EQUALS(str[14], "00000000");
      TS_ASSERT_EQUALS(str[15], "0");
      TS_ASSERT_EQUALS(str[16], "0");
      TS_ASSERT_EQUALS(str[17], "0");
      TS_ASSERT_EQUALS(str[18], "0");
      TS_ASSERT_EQUALS(str[19], "0");
      TS_ASSERT_EQUALS(str[20], "0");
      TS_ASSERT_EQUALS(str[21], "0");
      TS_ASSERT_EQUALS(str[22], "");
      TS_ASSERT_EQUALS(str[23], "");
      TS_ASSERT_EQUALS(str[24], "");
      TS_ASSERT_EQUALS(str[25], "");
      TS_ASSERT_EQUALS(str[26], "");
      TS_ASSERT_EQUALS(str[27], "");
      TS_ASSERT_EQUALS(str[28], "0");
      TS_ASSERT_EQUALS(str[29], "0");
    }

    void testWriteRead1()
    {
      const char *filename = "TestMPR.testWriteRead1.txt";

      MPR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      MPR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "47");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "15");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "00000000");
      TS_ASSERT_EQUALS(str[7], "00000000");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "0");
      TS_ASSERT_EQUALS(str[10], "");
      TS_ASSERT_EQUALS(str[11], "");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "");
      TS_ASSERT_EQUALS(str[14], "00000000");
      TS_ASSERT_EQUALS(str[15], "0");
      TS_ASSERT_EQUALS(str[16], "0");
      TS_ASSERT_EQUALS(str[17], "0");
      TS_ASSERT_EQUALS(str[18], "0");
      TS_ASSERT_EQUALS(str[19], "0");
      TS_ASSERT_EQUALS(str[20], "0");
      TS_ASSERT_EQUALS(str[21], "0");
      TS_ASSERT_EQUALS(str[22], "");
      TS_ASSERT_EQUALS(str[23], "");
      TS_ASSERT_EQUALS(str[24], "");
      TS_ASSERT_EQUALS(str[25], "");
      TS_ASSERT_EQUALS(str[26], "");
      TS_ASSERT_EQUALS(str[27], "");
      TS_ASSERT_EQUALS(str[28], "0");
      TS_ASSERT_EQUALS(str[29], "0");
      }

    void testWriteRead2()
    {
      const char *filename = "TestMPR.testWriteRead2.txt";

      MPR stdfRecIn;
      stdfRecIn.setTestnum(123456);
      stdfRecIn.setHeadnum(255);
      stdfRecIn.setSitenum(255);
      stdfRecIn.setTestflg("11101110");
      stdfRecIn.setParmflg("00011000");
      stdfRecIn.setRtnicnt(5);
      stdfRecIn.setRsltcnt(5);
      stdfRecIn.setRtnstat(0,0xa);
      stdfRecIn.setRtnstat(1,0xb);
      stdfRecIn.setRtnstat(2,0xc);
      stdfRecIn.setRtnstat(3,0xd);
      stdfRecIn.setRtnstat(4,0xe);
      stdfRecIn.setRtnrslt(0,1);
      stdfRecIn.setRtnrslt(1,2);
      stdfRecIn.setRtnrslt(2,3);
      stdfRecIn.setRtnrslt(3,4);
      stdfRecIn.setRtnrslt(4,5);
      stdfRecIn.setTesttxt("stdfRecsetTesttxt");
      stdfRecIn.setAlarmid("stdfRecsetAlarmid");
      stdfRecIn.setOptflag("11111111");
      stdfRecIn.setResscal(-128);
      stdfRecIn.setLlmscal(0);
      stdfRecIn.setHlmscal(127);
      stdfRecIn.setLolimit(123456);
      stdfRecIn.setHilimit(0);
      stdfRecIn.setStartin(0.123456);
      stdfRecIn.setIncrin(123.456);
      stdfRecIn.setRtnindx(0, 1);
      stdfRecIn.setRtnindx(1, 2);
      stdfRecIn.setRtnindx(2, 3);
      stdfRecIn.setRtnindx(3, 4);
      stdfRecIn.setRtnindx(4, 5);
      stdfRecIn.setUnits("stdfRecsetUnits");
      stdfRecIn.setUnitsin("stdfRecsetUnitsin");
      stdfRecIn.setCresfmt("stdfRecsetCresfmt");
      stdfRecIn.setCllmfmt("stdfRecsetCllmfmt");
      stdfRecIn.setChlmfmt("stdfRecsetChlmfmt");
      stdfRecIn.setLospec(123456);
      stdfRecIn.setHispec(123456);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 197u)

      MPR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "197");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "15");
      TS_ASSERT_EQUALS(str[3], "123456");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "255");
      TS_ASSERT_EQUALS(str[6], "11101110");
      TS_ASSERT_EQUALS(str[7], "00011000");
      TS_ASSERT_EQUALS(str[8], "5");
      TS_ASSERT_EQUALS(str[9], "5");
      TS_ASSERT_EQUALS(str[10], "ABCDE");
      TS_ASSERT_EQUALS(str[11], "1,2,3,4,5");
      TS_ASSERT_EQUALS(str[12], "stdfRecsetTesttxt");
      TS_ASSERT_EQUALS(str[13], "stdfRecsetAlarmid");
      TS_ASSERT_EQUALS(str[14], "11111111");
      TS_ASSERT_EQUALS(str[15], "-128");
      TS_ASSERT_EQUALS(str[16], "0");
      TS_ASSERT_EQUALS(str[17], "127");
      TS_ASSERT_EQUALS(str[18], "123456");
      TS_ASSERT_EQUALS(str[19], "0");
      TS_ASSERT_EQUALS(str[20], "0.123456");
      TS_ASSERT_EQUALS(str[21], "123.456");
      TS_ASSERT_EQUALS(str[22], "1,2,3,4,5");
      TS_ASSERT_EQUALS(str[23], "stdfRecsetUnits");
      TS_ASSERT_EQUALS(str[24], "stdfRecsetUnitsin");
      TS_ASSERT_EQUALS(str[25], "stdfRecsetCresfmt");
      TS_ASSERT_EQUALS(str[26], "stdfRecsetCllmfmt");
      TS_ASSERT_EQUALS(str[27], "stdfRecsetChlmfmt");
      TS_ASSERT_EQUALS(str[28], "123456");
      TS_ASSERT_EQUALS(str[29], "123456");
    }

};
