#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestNMR : public CxxTest::TestSuite 
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
      NMR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 7u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "7");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "91");
      TS_ASSERT_EQUALS(str[3], "00000000");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "");
      TS_ASSERT_EQUALS(str[8], "");
    }

    void testConstructor1()
    {
      NMR stdfRec;
      stdfRec.setContflg("00011000");
      stdfRec.setNmrindx(255);
      stdfRec.setTotmcnt(255);
      stdfRec.setLocmcnt(5);
      stdfRec.setPmrindx(0, 0);
      stdfRec.setPmrindx(1, 1);
      stdfRec.setPmrindx(2, 2);
      stdfRec.setPmrindx(3, 3);
      stdfRec.setPmrindx(4, 4);
      stdfRec.setAtpgnam(0, "a");
      stdfRec.setAtpgnam(1, "b");
      stdfRec.setAtpgnam(2, "c");
      stdfRec.setAtpgnam(3, "d");
      stdfRec.setAtpgnam(4, "e");
      TS_ASSERT_EQUALS(stdfRec.storage(), 27u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "27");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "91");
      TS_ASSERT_EQUALS(str[3], "00011000");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "255");
      TS_ASSERT_EQUALS(str[6], "5");
      TS_ASSERT_EQUALS(str[7], "0,1,2,3,4");
      TS_ASSERT_EQUALS(str[8], "a,b,c,d,e");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "7");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "91");
      TS_ASSERT_EQUALS(str[3], "00000000");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "");
      TS_ASSERT_EQUALS(str[8], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestNMR.testWriteRead1.txt";

      NMR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      NMR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "7");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "91");
      TS_ASSERT_EQUALS(str[3], "00000000");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "");
      TS_ASSERT_EQUALS(str[8], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestNMR.testWriteRead2.txt";

      NMR stdfRecIn;
      stdfRecIn.setContflg("00011000");
      stdfRecIn.setNmrindx(255);
      stdfRecIn.setTotmcnt(255);
      stdfRecIn.setLocmcnt(5);
      stdfRecIn.setPmrindx(0, 0);
      stdfRecIn.setPmrindx(1, 1);
      stdfRecIn.setPmrindx(2, 2);
      stdfRecIn.setPmrindx(3, 3);
      stdfRecIn.setPmrindx(4, 4);
      stdfRecIn.setAtpgnam(0, "a");
      stdfRecIn.setAtpgnam(1, "b");
      stdfRecIn.setAtpgnam(2, "c");
      stdfRecIn.setAtpgnam(3, "d");
      stdfRecIn.setAtpgnam(4, "e");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 27u)

      NMR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "27");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "91");
      TS_ASSERT_EQUALS(str[3], "00011000");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "255");
      TS_ASSERT_EQUALS(str[6], "5");
      TS_ASSERT_EQUALS(str[7], "0,1,2,3,4");
      TS_ASSERT_EQUALS(str[8], "a,b,c,d,e");
    }

};
