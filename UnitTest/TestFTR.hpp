#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestFTR : public CxxTest::TestSuite 
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
      FTR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 50u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "50");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "00000000");
      TS_ASSERT_EQUALS(str[7], "00000000");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "0");
      TS_ASSERT_EQUALS(str[10], "0");
      TS_ASSERT_EQUALS(str[11], "0");
      TS_ASSERT_EQUALS(str[12], "0");
      TS_ASSERT_EQUALS(str[13], "0");
      TS_ASSERT_EQUALS(str[14], "0");
      TS_ASSERT_EQUALS(str[15], "0");
      TS_ASSERT_EQUALS(str[16], "0");
      TS_ASSERT_EQUALS(str[17], "");
      TS_ASSERT_EQUALS(str[18], "");
      TS_ASSERT_EQUALS(str[19], "");
      TS_ASSERT_EQUALS(str[20], "");
      TS_ASSERT_EQUALS(str[21], "");
      TS_ASSERT_EQUALS(str[22], "");
      TS_ASSERT_EQUALS(str[23], "");
      TS_ASSERT_EQUALS(str[24], "");
      TS_ASSERT_EQUALS(str[25], "");
      TS_ASSERT_EQUALS(str[26], "");
      TS_ASSERT_EQUALS(str[27], "");
      TS_ASSERT_EQUALS(str[28], "");
      TS_ASSERT_EQUALS(str[29], "255");
      TS_ASSERT_EQUALS(str[30], "");
    }

    void testConstructor1()
    {
      FTR stdfRec;
      stdfRec.setTestnum(1234567890);
      stdfRec.setHeadnum(255);
      stdfRec.setSitenum(255);
      stdfRec.setTestflg("00011000");
      stdfRec.setOptflag("10101010");
      stdfRec.setCyclcnt(1234567890);
      stdfRec.setRelvadr(1234567890);
      stdfRec.setReptcnt(1234567890);
      stdfRec.setNumfail(1234567890);
      stdfRec.setXfailad(1234567890);
      stdfRec.setYfailad(1234567890);
      stdfRec.setVectoff(32767);
      stdfRec.setRtnicnt(5);
      stdfRec.setPgmicnt(5);
      stdfRec.setRtnindx(0, 0);
      stdfRec.setRtnindx(1, 1);
      stdfRec.setRtnindx(2, 888);
      stdfRec.setRtnindx(3, 65534);
      stdfRec.setRtnindx(4, 65535);
      stdfRec.setRtnstat(0, 0);
      stdfRec.setRtnstat(1, 0);
      stdfRec.setRtnstat(2, 1);
      stdfRec.setRtnstat(3, 0);
      stdfRec.setRtnstat(4, 0);
      stdfRec.setPgmindx(0, 0);
      stdfRec.setPgmindx(1, 1);
      stdfRec.setPgmindx(2, 999);
      stdfRec.setPgmindx(3, 65534);
      stdfRec.setPgmindx(4, 65535);
      stdfRec.setPgmstat(0, 0);
      stdfRec.setPgmstat(1, 1);
      stdfRec.setPgmstat(2, 1);
      stdfRec.setPgmstat(3, 1);
      stdfRec.setPgmstat(4, 0);
      stdfRec.setFailpin("00100");
      stdfRec.setVectnam("Cn");
      stdfRec.setTimeset("Cn");
      stdfRec.setOpcode("Cn");
      stdfRec.setTesttxt("Cn");
      stdfRec.setAlarmid("Cn");
      stdfRec.setProgtxt("Cn");
      stdfRec.setRslttxt("Cn");
      stdfRec.setPatgnum(255);
      stdfRec.setSpinmap("00100");
      TS_ASSERT_EQUALS(stdfRec.storage(), 92u);

      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "92");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "1234567890");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "255");
      TS_ASSERT_EQUALS(str[6], "00011000");
      TS_ASSERT_EQUALS(str[7], "10101010");
      TS_ASSERT_EQUALS(str[8], "1234567890");
      TS_ASSERT_EQUALS(str[9], "1234567890");
      TS_ASSERT_EQUALS(str[10], "1234567890");
      TS_ASSERT_EQUALS(str[11], "1234567890");
      TS_ASSERT_EQUALS(str[12], "1234567890");
      TS_ASSERT_EQUALS(str[13], "1234567890");
      TS_ASSERT_EQUALS(str[14], "32767");
      TS_ASSERT_EQUALS(str[15], "5");
      TS_ASSERT_EQUALS(str[16], "5");
      TS_ASSERT_EQUALS(str[17], "0,1,888,65534,65535");
      TS_ASSERT_EQUALS(str[18], "00100");
      TS_ASSERT_EQUALS(str[19], "0,1,999,65534,65535");
      TS_ASSERT_EQUALS(str[20], "01110");
      TS_ASSERT_EQUALS(str[21], "00100");
      TS_ASSERT_EQUALS(str[22], "Cn");
      TS_ASSERT_EQUALS(str[23], "Cn");
      TS_ASSERT_EQUALS(str[24], "Cn");
      TS_ASSERT_EQUALS(str[25], "Cn");
      TS_ASSERT_EQUALS(str[26], "Cn");
      TS_ASSERT_EQUALS(str[27], "Cn");
      TS_ASSERT_EQUALS(str[28], "Cn");
      TS_ASSERT_EQUALS(str[29], "255");
      TS_ASSERT_EQUALS(str[30], "00100");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "50");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "00000000");
      TS_ASSERT_EQUALS(str[7], "00000000");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "0");
      TS_ASSERT_EQUALS(str[10], "0");
      TS_ASSERT_EQUALS(str[11], "0");
      TS_ASSERT_EQUALS(str[12], "0");
      TS_ASSERT_EQUALS(str[13], "0");
      TS_ASSERT_EQUALS(str[14], "0");
      TS_ASSERT_EQUALS(str[15], "0");
      TS_ASSERT_EQUALS(str[16], "0");
      TS_ASSERT_EQUALS(str[17], "");
      TS_ASSERT_EQUALS(str[18], "");
      TS_ASSERT_EQUALS(str[19], "");
      TS_ASSERT_EQUALS(str[20], "");
      TS_ASSERT_EQUALS(str[21], "");
      TS_ASSERT_EQUALS(str[22], "");
      TS_ASSERT_EQUALS(str[23], "");
      TS_ASSERT_EQUALS(str[24], "");
      TS_ASSERT_EQUALS(str[25], "");
      TS_ASSERT_EQUALS(str[26], "");
      TS_ASSERT_EQUALS(str[27], "");
      TS_ASSERT_EQUALS(str[28], "");
      TS_ASSERT_EQUALS(str[29], "255");
      TS_ASSERT_EQUALS(str[30], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestFTR.testWriteRead1.txt";

      FTR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      FTR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "50");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "00000000");
      TS_ASSERT_EQUALS(str[7], "00000000");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "0");
      TS_ASSERT_EQUALS(str[10], "0");
      TS_ASSERT_EQUALS(str[11], "0");
      TS_ASSERT_EQUALS(str[12], "0");
      TS_ASSERT_EQUALS(str[13], "0");
      TS_ASSERT_EQUALS(str[14], "0");
      TS_ASSERT_EQUALS(str[15], "0");
      TS_ASSERT_EQUALS(str[16], "0");
      TS_ASSERT_EQUALS(str[17], "");
      TS_ASSERT_EQUALS(str[18], "");
      TS_ASSERT_EQUALS(str[19], "");
      TS_ASSERT_EQUALS(str[20], "");
      TS_ASSERT_EQUALS(str[21], "");
      TS_ASSERT_EQUALS(str[22], "");
      TS_ASSERT_EQUALS(str[23], "");
      TS_ASSERT_EQUALS(str[24], "");
      TS_ASSERT_EQUALS(str[25], "");
      TS_ASSERT_EQUALS(str[26], "");
      TS_ASSERT_EQUALS(str[27], "");
      TS_ASSERT_EQUALS(str[28], "");
      TS_ASSERT_EQUALS(str[29], "255");
      TS_ASSERT_EQUALS(str[30], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestFTR.testWriteRead2.txt";

      FTR stdfRecIn;
      stdfRecIn.setTestnum(1234567890);
      stdfRecIn.setHeadnum(255);
      stdfRecIn.setSitenum(255);
      stdfRecIn.setTestflg("00011000");
      stdfRecIn.setOptflag("10101010");
      stdfRecIn.setCyclcnt(1234567890);
      stdfRecIn.setRelvadr(1234567890);
      stdfRecIn.setReptcnt(1234567890);
      stdfRecIn.setNumfail(1234567890);
      stdfRecIn.setXfailad(1234567890);
      stdfRecIn.setYfailad(1234567890);
      stdfRecIn.setVectoff(32767);
      stdfRecIn.setRtnicnt(5);
      stdfRecIn.setPgmicnt(5);
      stdfRecIn.setRtnindx(0, 0);
      stdfRecIn.setRtnindx(1, 1);
      stdfRecIn.setRtnindx(2, 2);
      stdfRecIn.setRtnindx(3, 3);
      stdfRecIn.setRtnindx(4, 65535);
      stdfRecIn.setRtnstat(0, 0);
      stdfRecIn.setRtnstat(1, 0);
      stdfRecIn.setRtnstat(2, 1);
      stdfRecIn.setRtnstat(3, 0);
      stdfRecIn.setRtnstat(4, 0);
      stdfRecIn.setPgmindx(0, 0);
      stdfRecIn.setPgmindx(1, 1);
      stdfRecIn.setPgmindx(2, 2);
      stdfRecIn.setPgmindx(3, 3);
      stdfRecIn.setPgmindx(4, 65535);
      stdfRecIn.setPgmstat(0, 0);
      stdfRecIn.setPgmstat(1, 1);
      stdfRecIn.setPgmstat(2, 1);
      stdfRecIn.setPgmstat(3, 1);
      stdfRecIn.setPgmstat(4, 0);
      stdfRecIn.setFailpin("00100");
      stdfRecIn.setVectnam("Cn");
      stdfRecIn.setTimeset("Cn");
      stdfRecIn.setOpcode("Cn");
      stdfRecIn.setTesttxt("Cn");
      stdfRecIn.setAlarmid("Cn");
      stdfRecIn.setProgtxt("Cn");
      stdfRecIn.setRslttxt("Cn");
      stdfRecIn.setPatgnum(255);
      stdfRecIn.setSpinmap("00100");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 92u)

      FTR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "92");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "1234567890");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "255");
      TS_ASSERT_EQUALS(str[6], "00011000");
      TS_ASSERT_EQUALS(str[7], "10101010");
      TS_ASSERT_EQUALS(str[8], "1234567890");
      TS_ASSERT_EQUALS(str[9], "1234567890");
      TS_ASSERT_EQUALS(str[10], "1234567890");
      TS_ASSERT_EQUALS(str[11], "1234567890");
      TS_ASSERT_EQUALS(str[12], "1234567890");
      TS_ASSERT_EQUALS(str[13], "1234567890");
      TS_ASSERT_EQUALS(str[14], "32767");
      TS_ASSERT_EQUALS(str[15], "5");
      TS_ASSERT_EQUALS(str[16], "5");
      TS_ASSERT_EQUALS(str[17], "0,1,2,3,65535");
      TS_ASSERT_EQUALS(str[18], "00100");
      TS_ASSERT_EQUALS(str[19], "0,1,2,3,65535");
      TS_ASSERT_EQUALS(str[20], "01110");
      TS_ASSERT_EQUALS(str[21], "00100");
      TS_ASSERT_EQUALS(str[22], "Cn");
      TS_ASSERT_EQUALS(str[23], "Cn");
      TS_ASSERT_EQUALS(str[24], "Cn");
      TS_ASSERT_EQUALS(str[25], "Cn");
      TS_ASSERT_EQUALS(str[26], "Cn");
      TS_ASSERT_EQUALS(str[27], "Cn");
      TS_ASSERT_EQUALS(str[28], "Cn");
      TS_ASSERT_EQUALS(str[29], "255");
      TS_ASSERT_EQUALS(str[30], "00100");
    }

};
