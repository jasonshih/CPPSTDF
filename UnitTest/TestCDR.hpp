#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestCDR : public CxxTest::TestSuite 
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
      CDR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 17u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "17");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "94");
      TS_ASSERT_EQUALS(str[3], "00000000");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "0");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "0");
      TS_ASSERT_EQUALS(str[10], "");
      TS_ASSERT_EQUALS(str[11], "0");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "255");
      TS_ASSERT_EQUALS(str[14], "0");
      TS_ASSERT_EQUALS(str[15], "");
    }

    void testConstructor1()
    {
      CDR stdfRec;
      stdfRec.setContflg("00011000");
      stdfRec.setCdrindx(255);
      stdfRec.setChnnam("abcd");
      stdfRec.setChnlen(1234567890);
      stdfRec.setSinpin(65535);
      stdfRec.setSoutpin(65535);
      stdfRec.setMstrcnt(5);
      stdfRec.setMclks(0, 0);
      stdfRec.setMclks(1, 1);
      stdfRec.setMclks(2, 2);
      stdfRec.setMclks(3, 3);
      stdfRec.setMclks(4, 4);
      stdfRec.setSlavcnt(5);
      stdfRec.setSclks(0, 0);
      stdfRec.setSclks(1, 1);
      stdfRec.setSclks(2, 2);
      stdfRec.setSclks(3, 3);
      stdfRec.setSclks(4, 4);
      stdfRec.setInvval(0);
      stdfRec.setLstcnt(5);
      stdfRec.setCelllst(0, "a");
      stdfRec.setCelllst(1, "b");
      stdfRec.setCelllst(2, "c");
      stdfRec.setCelllst(3, "d");
      stdfRec.setCelllst(4, "e");
      TS_ASSERT_EQUALS(stdfRec.storage(), 56u);//41+sizeof(kxSn)=56
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "56");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "94");
      TS_ASSERT_EQUALS(str[3], "00011000");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "abcd");
      TS_ASSERT_EQUALS(str[6], "1234567890");
      TS_ASSERT_EQUALS(str[7], "65535");
      TS_ASSERT_EQUALS(str[8], "65535");
      TS_ASSERT_EQUALS(str[9], "5");
      TS_ASSERT_EQUALS(str[10], "0,1,2,3,4");
      TS_ASSERT_EQUALS(str[11], "5");
      TS_ASSERT_EQUALS(str[12], "0,1,2,3,4");
      TS_ASSERT_EQUALS(str[13], "0");
      TS_ASSERT_EQUALS(str[14], "5");
      TS_ASSERT_EQUALS(str[15], "a,b,c,d,e");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "17");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "94");
      TS_ASSERT_EQUALS(str[3], "00000000");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "0");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "0");
      TS_ASSERT_EQUALS(str[10], "");
      TS_ASSERT_EQUALS(str[11], "0");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "255");
      TS_ASSERT_EQUALS(str[14], "0");
      TS_ASSERT_EQUALS(str[15], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestCDR.testWriteRead1.txt";

      CDR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      CDR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "17");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "94");
      TS_ASSERT_EQUALS(str[3], "00000000");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "0");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "0");
      TS_ASSERT_EQUALS(str[10], "");
      TS_ASSERT_EQUALS(str[11], "0");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "255");
      TS_ASSERT_EQUALS(str[14], "0");
      TS_ASSERT_EQUALS(str[15], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestCDR.testWriteRead2.txt";

      CDR stdfRecIn;
      stdfRecIn.setContflg("00011000");
      stdfRecIn.setCdrindx(255);
      stdfRecIn.setChnnam("abcd");
      stdfRecIn.setChnlen(1234567890);
      stdfRecIn.setSinpin(65535);
      stdfRecIn.setSoutpin(65535);
      stdfRecIn.setMstrcnt(5);
      stdfRecIn.setMclks(0, 0);
      stdfRecIn.setMclks(1, 1);
      stdfRecIn.setMclks(2, 2);
      stdfRecIn.setMclks(3, 3);
      stdfRecIn.setMclks(4, 4);
      stdfRecIn.setSlavcnt(5);
      stdfRecIn.setSclks(0, 0);
      stdfRecIn.setSclks(1, 1);
      stdfRecIn.setSclks(2, 2);
      stdfRecIn.setSclks(3, 3);
      stdfRecIn.setSclks(4, 4);
      stdfRecIn.setInvval(0);
      stdfRecIn.setLstcnt(5);
      stdfRecIn.setCelllst(0, "a");
      stdfRecIn.setCelllst(1, "b");
      stdfRecIn.setCelllst(2, "c");
      stdfRecIn.setCelllst(3, "d");
      stdfRecIn.setCelllst(4, "e");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 56u)

      CDR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "56");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "94");
      TS_ASSERT_EQUALS(str[3], "00011000");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "abcd");
      TS_ASSERT_EQUALS(str[6], "1234567890");
      TS_ASSERT_EQUALS(str[7], "65535");
      TS_ASSERT_EQUALS(str[8], "65535");
      TS_ASSERT_EQUALS(str[9], "5");
      TS_ASSERT_EQUALS(str[10], "0,1,2,3,4");
      TS_ASSERT_EQUALS(str[11], "5");
      TS_ASSERT_EQUALS(str[12], "0,1,2,3,4");
      TS_ASSERT_EQUALS(str[13], "0");
      TS_ASSERT_EQUALS(str[14], "5");
      TS_ASSERT_EQUALS(str[15], "a,b,c,d,e");
    }

};
