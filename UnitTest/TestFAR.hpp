#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestFAR : public CxxTest::TestSuite 
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
      FAR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 2u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "2");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "2");
      TS_ASSERT_EQUALS(str[4], "4");
    }

    void testConstructor1()
    {
      FAR stdfRec;
      stdfRec.setStdfver(3);
      TS_ASSERT_EQUALS(stdfRec.storage(), 2u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "2");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "2");
      TS_ASSERT_EQUALS(str[4], "3");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "2");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "2");
      TS_ASSERT_EQUALS(str[4], "4");
    }

    void testWriteRead1()
    {
      const char *filename = "TestFAR.testWriteRead1.txt";

      FAR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      FAR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "2");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "2");
      TS_ASSERT_EQUALS(str[4], "4");
    }

    void testWriteRead2()
    {
      const char *filename = "TestFAR.testWriteRead2.txt";

      FAR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 2u)

      FAR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "2");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "2");
      TS_ASSERT_EQUALS(str[4], "4");
    }

};
