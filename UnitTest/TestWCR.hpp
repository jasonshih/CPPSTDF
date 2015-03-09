#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestWCR : public CxxTest::TestSuite 
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
      WCR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 20u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "20");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "0");//R4
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "0");//U1
      TS_ASSERT_EQUALS(str[7], " ");//C1
      TS_ASSERT_EQUALS(str[8], "-32768");//I2
      TS_ASSERT_EQUALS(str[9], "-32768");
      TS_ASSERT_EQUALS(str[10], " ");//C1
      TS_ASSERT_EQUALS(str[11], " ");
    }

    void testConstructor1()
    {
      WCR stdfRec;
      stdfRec.setWafrsiz(0.123459);
      stdfRec.setWfunits(255u);
      stdfRec.setWfflat('w');
      stdfRec.setCenterx(32767u);
      stdfRec.setPosx('c');
      TS_ASSERT_EQUALS(stdfRec.storage(), 20u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "20");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "0.123459");
      TS_ASSERT_EQUALS(str[6], "255");
      TS_ASSERT_EQUALS(str[7], "w");
      TS_ASSERT_EQUALS(str[8], "32767");
      TS_ASSERT_EQUALS(str[10], "c");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "20");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], " ");
      TS_ASSERT_EQUALS(str[8], "-32768");
      TS_ASSERT_EQUALS(str[10], " ");
    }

    void testWriteRead1()
    {
      const char *filename = "TestWCR.testWriteRead1.txt";

      WCR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      WCR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "20");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[6], "0");
      TS_ASSERT_EQUALS(str[7], " ");
      TS_ASSERT_EQUALS(str[8], "-32768");
      TS_ASSERT_EQUALS(str[10], " ");
    }

    void testWriteRead2()
    {
      const char *filename = "TestWCR.testWriteRead2.txt";

      WCR stdfRecIn;
      stdfRecIn.setWafrsiz(0.123459);
      stdfRecIn.setWfunits(255u);
      stdfRecIn.setWfflat('w');
      stdfRecIn.setCenterx(32767u);
      stdfRecIn.setPosx('c');
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 20u)

      WCR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "20");
      TS_ASSERT_EQUALS(str[1], "2");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "0.123459");
      TS_ASSERT_EQUALS(str[6], "255");
      TS_ASSERT_EQUALS(str[7], "w");
      TS_ASSERT_EQUALS(str[8], "32767");
      TS_ASSERT_EQUALS(str[10], "c");
    }

};
