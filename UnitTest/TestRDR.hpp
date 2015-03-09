#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestRDR : public CxxTest::TestSuite 
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
      RDR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 2u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "2");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "70");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
    }

    void testConstructor1()
    {
      RDR stdfRec;
      stdfRec.setNumbins(5);
      stdfRec.setRtstbin(0, 0);
      stdfRec.setRtstbin(1, 1);
      stdfRec.setRtstbin(2, 2);
      stdfRec.setRtstbin(3, 3);
      stdfRec.setRtstbin(4, 4);
      TS_ASSERT_EQUALS(stdfRec.storage(), 12u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "12");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "70");
      TS_ASSERT_EQUALS(str[3], "5");
      TS_ASSERT_EQUALS(str[4], "0,1,2,3,4");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "2");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "70");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestRDR.testWriteRead1.txt";

      RDR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      RDR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "2");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "70");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestRDR.testWriteRead2.txt";

      RDR stdfRecIn;
      stdfRecIn.setNumbins(5);
      stdfRecIn.setRtstbin(0, 0);
      stdfRecIn.setRtstbin(1, 1);
      stdfRecIn.setRtstbin(2, 2);
      stdfRecIn.setRtstbin(3, 3);
      stdfRecIn.setRtstbin(4, 4);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 12u)

      RDR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "12");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "70");
      TS_ASSERT_EQUALS(str[3], "5");
      TS_ASSERT_EQUALS(str[4], "0,1,2,3,4");
    }

};
