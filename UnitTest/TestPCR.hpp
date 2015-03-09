#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestPCR : public CxxTest::TestSuite 
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
      PCR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 22u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "22");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "4294967295");
      TS_ASSERT_EQUALS(str[7], "4294967295");
      TS_ASSERT_EQUALS(str[8], "4294967295");
      TS_ASSERT_EQUALS(str[9], "4294967295");
    }

    void testConstructor1()
    {
      PCR stdfRec;
      stdfRec.setHeadnum(222u);
      stdfRec.setSitenum(222u);
      stdfRec.setPartcnt(1111111111);
      stdfRec.setRtstcnt(1234567891);
      stdfRec.setAbrtcnt(1234567891);
      stdfRec.setGoodcnt(1234567891);
      stdfRec.setFunccnt(1234567891);
      TS_ASSERT_EQUALS(stdfRec.storage(), 22u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "22");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "222");
      TS_ASSERT_EQUALS(str[4], "222");
      TS_ASSERT_EQUALS(str[5], "1111111111");
      TS_ASSERT_EQUALS(str[6], "1234567891");
      TS_ASSERT_EQUALS(str[7], "1234567891");
      TS_ASSERT_EQUALS(str[8], "1234567891");
      TS_ASSERT_EQUALS(str[9], "1234567891");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "22");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "4294967295");
      TS_ASSERT_EQUALS(str[7], "4294967295");
      TS_ASSERT_EQUALS(str[8], "4294967295");
      TS_ASSERT_EQUALS(str[8], "4294967295");
    }

    void testWriteRead1()
    {
      const char *filename = "TestPCR.testWriteRead1.txt";

      PCR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      PCR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "22");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[6], "4294967295");
    }

    void testWriteRead2()
    {
      const char *filename = "TestPCR.testWriteRead2.txt";

      PCR stdfRecIn;
      stdfRecIn.setHeadnum(222u);
      stdfRecIn.setSitenum(222u);
      stdfRecIn.setRtstcnt(1234567891);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 22u)

      PCR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "22");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "222");
      TS_ASSERT_EQUALS(str[6], "1234567891");
    }

};
