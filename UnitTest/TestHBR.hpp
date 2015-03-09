#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestHBR : public CxxTest::TestSuite 
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
      HBR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 10u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "10");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "40");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], " ");
      TS_ASSERT_EQUALS(str[8], "");
    }

    void testConstructor1()
    {
      HBR stdfRec;
      stdfRec.setHeadnum(255);
      stdfRec.setSitenum(255);
      stdfRec.setHbinnum(65535);
      stdfRec.setHbincnt(1111111111u);
      stdfRec.setHbinpf('c');
      stdfRec.setHbinnam("TestHBR");
      TS_ASSERT_EQUALS(stdfRec.storage(), 17u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "17");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "40");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "65535");
      TS_ASSERT_EQUALS(str[6], "1111111111");
      TS_ASSERT_EQUALS(str[7], "c");
      TS_ASSERT_EQUALS(str[8], "TestHBR");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "10");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "40");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], " ");
      TS_ASSERT_EQUALS(str[8], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestHBR.testWriteRead1.txt";

      HBR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      HBR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "10");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "40");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], " ");
      TS_ASSERT_EQUALS(str[8], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestHBR.testWriteRead2.txt";

      HBR stdfRecIn;
      stdfRecIn.setHeadnum(255);
      stdfRecIn.setSitenum(255);
      stdfRecIn.setHbinnum(65535);
      stdfRecIn.setHbincnt(1111111111u);
      stdfRecIn.setHbinpf('c');
      stdfRecIn.setHbinnam("TestHBR");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 17u)

      HBR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "17");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "40");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "65535");
      TS_ASSERT_EQUALS(str[6], "1111111111");
      TS_ASSERT_EQUALS(str[7], "c");
      TS_ASSERT_EQUALS(str[8], "TestHBR");
    }

};
