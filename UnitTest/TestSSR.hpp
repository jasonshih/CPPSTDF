#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestSSR : public CxxTest::TestSuite 
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
      SSR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 3u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "3");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "93");
      TS_ASSERT_EQUALS(str[3], "");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "");
    }

    void testConstructor1()
    {
      SSR stdfRec;
      stdfRec.setSsrnam("abcd");
      stdfRec.setChncnt(5);
      stdfRec.setChnlist(0, 0);
      stdfRec.setChnlist(1, 1);
      stdfRec.setChnlist(2, 2);
      stdfRec.setChnlist(3, 3);
      stdfRec.setChnlist(4, 4);
      TS_ASSERT_EQUALS(stdfRec.storage(), 17u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "17");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "93");
      TS_ASSERT_EQUALS(str[3], "abcd");
      TS_ASSERT_EQUALS(str[4], "5");
      TS_ASSERT_EQUALS(str[5], "0,1,2,3,4");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "3");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "93");
      TS_ASSERT_EQUALS(str[3], "");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestSSR.testWriteRead1.txt";

      SSR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      SSR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "3");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "93");
      TS_ASSERT_EQUALS(str[3], "");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestSSR.testWriteRead2.txt";

      SSR stdfRecIn;
      stdfRecIn.setSsrnam("abcd");
      stdfRecIn.setChncnt(5);
      stdfRecIn.setChnlist(0, 0);
      stdfRecIn.setChnlist(1, 1);
      stdfRecIn.setChnlist(2, 2);
      stdfRecIn.setChnlist(3, 3);
      stdfRecIn.setChnlist(4, 4);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 17u)

      SSR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "17");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "93");
      TS_ASSERT_EQUALS(str[3], "abcd");
      TS_ASSERT_EQUALS(str[4], "5");
      TS_ASSERT_EQUALS(str[5], "0,1,2,3,4");
    }

};
