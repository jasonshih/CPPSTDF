#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestWRR : public CxxTest::TestSuite 
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
      WRR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 32u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "32");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "4294967295");
      TS_ASSERT_EQUALS(str[8], "4294967295");
      TS_ASSERT_EQUALS(str[9], "4294967295");
      TS_ASSERT_EQUALS(str[10], "4294967295");
      TS_ASSERT_EQUALS(str[11], "");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "");
      TS_ASSERT_EQUALS(str[14], "");
      TS_ASSERT_EQUALS(str[15], "");
      TS_ASSERT_EQUALS(str[16], "");
    }

    void testConstructor1()
    {
      WRR stdfRec;
      stdfRec.setHeadnum(255u);
      stdfRec.setSitegrp(0u);
      stdfRec.setFinisht(1234567890u);
      stdfRec.setPartcnt(1234567890u);
      stdfRec.setRtstcnt(1234567890u);
      stdfRec.setAbrtcnt(1234567890u);
      stdfRec.setGoodcnt(1234567890u);
      stdfRec.setFunccnt(1234567890u);
      stdfRec.setWaferid("TestWRR");
      stdfRec.setFabwfid("TestWRR");
      stdfRec.setFrameid("TestWRR");
      stdfRec.setMaskid("TestWRR");
      stdfRec.setUsrdesc("TestWRR");
      stdfRec.setExcdesc("TestWRR");
      TS_ASSERT_EQUALS(stdfRec.storage(), 74u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "74");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "1234567890");
      TS_ASSERT_EQUALS(str[6], "1234567890");
      TS_ASSERT_EQUALS(str[7], "1234567890");
      TS_ASSERT_EQUALS(str[8], "1234567890");
      TS_ASSERT_EQUALS(str[9], "1234567890");
      TS_ASSERT_EQUALS(str[10], "1234567890");
      TS_ASSERT_EQUALS(str[11], "TestWRR");
      TS_ASSERT_EQUALS(str[12], "TestWRR");
      TS_ASSERT_EQUALS(str[13], "TestWRR");
      TS_ASSERT_EQUALS(str[14], "TestWRR");
      TS_ASSERT_EQUALS(str[15], "TestWRR");
      TS_ASSERT_EQUALS(str[16], "TestWRR");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "32");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "4294967295");
      TS_ASSERT_EQUALS(str[8], "4294967295");
      TS_ASSERT_EQUALS(str[9], "4294967295");
      TS_ASSERT_EQUALS(str[10], "4294967295");
      TS_ASSERT_EQUALS(str[11], "");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "");
      TS_ASSERT_EQUALS(str[14], "");
      TS_ASSERT_EQUALS(str[15], "");
      TS_ASSERT_EQUALS(str[16], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestWRR.testWriteRead1.txt";

      WRR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      WRR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "32");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], "4294967295");
      TS_ASSERT_EQUALS(str[8], "4294967295");
      TS_ASSERT_EQUALS(str[9], "4294967295");
      TS_ASSERT_EQUALS(str[10], "4294967295");
      TS_ASSERT_EQUALS(str[11], "");
      TS_ASSERT_EQUALS(str[12], "");
      TS_ASSERT_EQUALS(str[13], "");
      TS_ASSERT_EQUALS(str[14], "");
      TS_ASSERT_EQUALS(str[15], "");
      TS_ASSERT_EQUALS(str[16], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestWRR.testWriteRead2.txt";

      WRR stdfRecIn;
      stdfRecIn.setHeadnum(255u);
      stdfRecIn.setSitegrp(0u);
      stdfRecIn.setFinisht(1234567890u);
      stdfRecIn.setPartcnt(1234567890u);
      stdfRecIn.setRtstcnt(1234567890u);
      stdfRecIn.setAbrtcnt(1234567890u);
      stdfRecIn.setGoodcnt(1234567890u);
      stdfRecIn.setFunccnt(1234567890u);
      stdfRecIn.setWaferid("TestWRR");
      stdfRecIn.setFabwfid("TestWRR");
      stdfRecIn.setFrameid("TestWRR");
      stdfRecIn.setMaskid("TestWRR");
      stdfRecIn.setUsrdesc("TestWRR");
      stdfRecIn.setExcdesc("TestWRR");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 74u)

      WRR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "74");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "1234567890");
      TS_ASSERT_EQUALS(str[6], "1234567890");
      TS_ASSERT_EQUALS(str[7], "1234567890");
      TS_ASSERT_EQUALS(str[8], "1234567890");
      TS_ASSERT_EQUALS(str[9], "1234567890");
      TS_ASSERT_EQUALS(str[10], "1234567890");
      TS_ASSERT_EQUALS(str[11], "TestWRR");
      TS_ASSERT_EQUALS(str[12], "TestWRR");
      TS_ASSERT_EQUALS(str[13], "TestWRR");
      TS_ASSERT_EQUALS(str[14], "TestWRR");
      TS_ASSERT_EQUALS(str[15], "TestWRR");
      TS_ASSERT_EQUALS(str[16], "TestWRR");
    }

};
