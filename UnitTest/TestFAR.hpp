#include <cxxtest/TestSuite.h>

#include "../src/FAR.hpp"

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
      TS_ASSERT_EQUALS(stdfRec.storage(), 6u);
      vector<string> str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "6");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "2");
      TS_ASSERT_EQUALS(str[4], "4");
    }

    void testConstructor1()
    {
      FAR stdfRec;
      stdfRec.setVersion(3);
      TS_ASSERT_EQUALS(stdfRec.storage(), 6u);
      vector<string> str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "6");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "2");
      TS_ASSERT_EQUALS(str[4], "3");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "6");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "2");
      TS_ASSERT_EQUALS(str[4], "4");
    }

    void testWriteRead1()
    {
      const char *filename = "TestFAR.testWriteRead1.txt";

      FAR stdfRecIn;
      ofstream outfile(filename, ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      FAR stdfRecOut;
      ifstream infile(filename, ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      vector<string> str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "6");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "2");
      TS_ASSERT_EQUALS(str[4], "4");
    }

    void testWriteRead2()
    {
      const char *filename = "TestFAR.testWriteRead2.txt";

      FAR stdfRecIn;
      ofstream outfile(filename, ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 6u)

      FAR stdfRecOut;
      ifstream infile(filename, ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      vector<string> str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "6");
      TS_ASSERT_EQUALS(str[1], "0");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "2");
      TS_ASSERT_EQUALS(str[4], "4");
    }

};
