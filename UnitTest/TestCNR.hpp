#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestCNR : public CxxTest::TestSuite 
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
      CNR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 8u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "8");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "92");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "");
    }

    void testConstructor1()
    {
      CNR stdfRec;
      stdfRec.setChnnum(255);
      stdfRec.setBitpos(1234567890);
      stdfRec.setCellnam("name");
      TS_ASSERT_EQUALS(stdfRec.storage(), 12u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "12");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "92");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[4], "1234567890");
      TS_ASSERT_EQUALS(str[5], "name");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "8");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "92");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestCNR.testWriteRead1.txt";

      CNR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      CNR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "8");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "92");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestCNR.testWriteRead2.txt";

      CNR stdfRecIn;
      stdfRecIn.setChnnum(255);
      stdfRecIn.setBitpos(1234567890);
      stdfRecIn.setCellnam("name");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 12u)

      CNR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "12");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "92");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[4], "1234567890");
      TS_ASSERT_EQUALS(str[5], "name");
    }

};
