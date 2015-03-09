#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestPLR : public CxxTest::TestSuite 
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
      PLR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 2u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "2");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "63");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
      TS_ASSERT_EQUALS(str[5], "");
      TS_ASSERT_EQUALS(str[6], "");
      TS_ASSERT_EQUALS(str[7], "");
      TS_ASSERT_EQUALS(str[8], "");
      TS_ASSERT_EQUALS(str[9], "");
      TS_ASSERT_EQUALS(str[10],"");
    }

    void testConstructor1()
    {
      PLR stdfRec;
      stdfRec.setGrpcnt(5);
      stdfRec.setGrpindx(1,1);
      stdfRec.setGrpmode(2,2);
      stdfRec.setGrpradx(3,3);
      stdfRec.setPgmchar(0,"pgmchar");
      stdfRec.setRtnchar(1,"rtnchar");
      stdfRec.setPgmchal(2,"pgmchal");
      stdfRec.setRtnchal(3,"rtnchal");
      TS_ASSERT_EQUALS(stdfRec.storage(), 75u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "75");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "63");
      TS_ASSERT_EQUALS(str[3], "5");
      TS_ASSERT_EQUALS(str[4], "0,1,0,0,0");
      TS_ASSERT_EQUALS(str[5], "0,0,2,0,0");
      TS_ASSERT_EQUALS(str[6], "0,0,0,3,0");
      TS_ASSERT_EQUALS(str[7], "pgmchar,,,,");//size = 7+1,1,1,1,1
      TS_ASSERT_EQUALS(str[8], ",rtnchar,,,");
      TS_ASSERT_EQUALS(str[9], ",,pgmchal,,");
      TS_ASSERT_EQUALS(str[10],",,,rtnchal,");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "2");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "63");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
      TS_ASSERT_EQUALS(str[5], "");
      TS_ASSERT_EQUALS(str[6], "");
      TS_ASSERT_EQUALS(str[7], "");
      TS_ASSERT_EQUALS(str[8], "");
      TS_ASSERT_EQUALS(str[9], "");
      TS_ASSERT_EQUALS(str[10],"");
    }

    void testWriteRead1()
    {
      const char *filename = "TestPLR.testWriteRead1.txt";

      PLR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      PLR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "2");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "63");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
      TS_ASSERT_EQUALS(str[5], "");
      TS_ASSERT_EQUALS(str[6], "");
      TS_ASSERT_EQUALS(str[7], "");
      TS_ASSERT_EQUALS(str[8], "");
      TS_ASSERT_EQUALS(str[9], "");
      TS_ASSERT_EQUALS(str[10],"");
    }

    void testWriteRead2()
    {
      const char *filename = "TestPLR.testWriteRead2.txt";

      PLR stdfRecIn;
      stdfRecIn.setGrpcnt(5);
      stdfRecIn.setGrpindx(1,1);
      stdfRecIn.setGrpmode(2,2);
      stdfRecIn.setGrpradx(3,3);
      stdfRecIn.setPgmchar(0,"pgmchar");
      stdfRecIn.setRtnchar(1,"rtnchar");
      stdfRecIn.setPgmchal(2,"pgmchal");
      stdfRecIn.setRtnchal(3,"rtnchal");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 75u)

      PLR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "75");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "63");
      TS_ASSERT_EQUALS(str[3], "5");
      TS_ASSERT_EQUALS(str[4], "0,1,0,0,0");
      TS_ASSERT_EQUALS(str[5], "0,0,2,0,0");
      TS_ASSERT_EQUALS(str[6], "0,0,0,3,0");
      TS_ASSERT_EQUALS(str[7], "pgmchar,,,,");
      TS_ASSERT_EQUALS(str[8], ",rtnchar,,,");
      TS_ASSERT_EQUALS(str[9], ",,pgmchal,,");
      TS_ASSERT_EQUALS(str[10],",,,rtnchal,");
    }

};
