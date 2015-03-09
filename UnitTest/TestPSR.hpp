#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestPSR : public CxxTest::TestSuite 
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
      PSR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 9u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "9");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "90");
      TS_ASSERT_EQUALS(str[3], "00000000");//default is "00000000" about B1, size = 1
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "");
      TS_ASSERT_EQUALS(str[6], "00000000");
      TS_ASSERT_EQUALS(str[7], "0");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "");
      TS_ASSERT_EQUALS(str[10],"");
      TS_ASSERT_EQUALS(str[11],"");
      TS_ASSERT_EQUALS(str[12],"");
      TS_ASSERT_EQUALS(str[13],"");
      TS_ASSERT_EQUALS(str[14],"");
      TS_ASSERT_EQUALS(str[15],"");
    }

    void testConstructor1()
    {
      PSR stdfRec;
      stdfRec.setContflg("00000000");
      stdfRec.setPsrindx(65535);
      stdfRec.setPsrnam("Cn");
      stdfRec.setOptflg("00001000");//If the bit is set to 1 the corresponding optional field is considered missing
      stdfRec.setTotpcnt(65535);
      stdfRec.setLocpcnt(5);
      stdfRec.setPatbgn(4, 4);
      stdfRec.setPatend(3, 3);
      stdfRec.setPatfile(2,"Cn2");
      stdfRec.setPatlbl(1,"Cn1");
      stdfRec.setFileuid(0,"Cn0");
      stdfRec.setAtpgdsc(1,"Cn1");
      stdfRec.setSrcid(2,"Cn2");
      TS_ASSERT_EQUALS(stdfRec.storage(), 131u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "131");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "90");
      TS_ASSERT_EQUALS(str[3], "00000000");
      TS_ASSERT_EQUALS(str[4], "65535");
      TS_ASSERT_EQUALS(str[5], "Cn");
      TS_ASSERT_EQUALS(str[6], "00001000");
      TS_ASSERT_EQUALS(str[7], "65535");
      TS_ASSERT_EQUALS(str[8], "5");
      TS_ASSERT_EQUALS(str[9], "0,0,0,0,4");
      TS_ASSERT_EQUALS(str[10],"0,0,0,3,0");
      TS_ASSERT_EQUALS(str[11],",,Cn2,,");//default empty,if cnt=5, then ",,,," this formatter for JxCn and JxU8 and so on. 
      TS_ASSERT_EQUALS(str[12],",Cn1,,,");
      TS_ASSERT_EQUALS(str[13],"Cn0,,,,");
      TS_ASSERT_EQUALS(str[14],",Cn1,,,");
      TS_ASSERT_EQUALS(str[15],",,Cn2,,");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "9");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "90");
      TS_ASSERT_EQUALS(str[3], "00000000");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "");
      TS_ASSERT_EQUALS(str[6], "00000000");
      TS_ASSERT_EQUALS(str[7], "0");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "");
      TS_ASSERT_EQUALS(str[10],"");
      TS_ASSERT_EQUALS(str[11],"");
      TS_ASSERT_EQUALS(str[12],"");
      TS_ASSERT_EQUALS(str[13],"");
      TS_ASSERT_EQUALS(str[14],"");
      TS_ASSERT_EQUALS(str[15],"");
    }

    void testWriteRead1()
    {
      const char *filename = "TestPSR.testWriteRead1.txt";

      PSR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      PSR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "9");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "90");
      TS_ASSERT_EQUALS(str[3], "00000000");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "");
      TS_ASSERT_EQUALS(str[6], "00000000");
      TS_ASSERT_EQUALS(str[7], "0");
      TS_ASSERT_EQUALS(str[8], "0");
      TS_ASSERT_EQUALS(str[9], "");
      TS_ASSERT_EQUALS(str[10],"");
      TS_ASSERT_EQUALS(str[11],"");
      TS_ASSERT_EQUALS(str[12],"");
      TS_ASSERT_EQUALS(str[13],"");
      TS_ASSERT_EQUALS(str[14],"");
      TS_ASSERT_EQUALS(str[15],"");
    }

    void testWriteRead2()
    {
      const char *filename = "TestPSR.testWriteRead2.txt";

      PSR stdfRecIn;
      stdfRecIn.setContflg("00000000");
      stdfRecIn.setPsrindx(65535);
      stdfRecIn.setPsrnam("Cn");
      stdfRecIn.setOptflg("00001000");
      stdfRecIn.setTotpcnt(65535);
      stdfRecIn.setLocpcnt(5);
      stdfRecIn.setPatbgn(4, 4);
      stdfRecIn.setPatend(3, 3);
      stdfRecIn.setPatfile(2,"Cn2");
      stdfRecIn.setPatlbl(1,"Cn1");
      stdfRecIn.setFileuid(0,"Cn0");
      stdfRecIn.setAtpgdsc(1,"Cn1");
      stdfRecIn.setSrcid(2,"Cn2");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 123u)

      PSR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "123");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "90");
      TS_ASSERT_EQUALS(str[3], "00000000");
      TS_ASSERT_EQUALS(str[4], "65535");
      TS_ASSERT_EQUALS(str[5], "Cn");
      TS_ASSERT_EQUALS(str[6], "00001000");
      TS_ASSERT_EQUALS(str[7], "65535");
      TS_ASSERT_EQUALS(str[8], "5");
      TS_ASSERT_EQUALS(str[9], "0,0,0,0,4");
      TS_ASSERT_EQUALS(str[10],"0,0,0,3,0");
      TS_ASSERT_EQUALS(str[11],",,Cn2,,");
      TS_ASSERT_EQUALS(str[12],",Cn1,,,");
      TS_ASSERT_EQUALS(str[13],"Cn0,,,,");
      TS_ASSERT_EQUALS(str[14],",Cn1,,,");
    }

};
