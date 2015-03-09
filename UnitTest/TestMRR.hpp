#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestMRR : public CxxTest::TestSuite 
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
      MRR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 7u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "7");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");//U4
      TS_ASSERT_EQUALS(str[4], " ");//C1
      TS_ASSERT_EQUALS(str[5], "");//CN
      TS_ASSERT_EQUALS(str[6], "");
    }

    void testConstructor1()
    {
      MRR stdfRec;
      stdfRec.setFinisht(1234567890u);
      stdfRec.setDispcod('b');
      stdfRec.setUsrdesc("TestMRR");
      stdfRec.setExcdesc("TestMRR");
      TS_ASSERT_EQUALS(stdfRec.storage(), 21u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "21");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "1234567890");
      TS_ASSERT_EQUALS(str[4], "b");
      TS_ASSERT_EQUALS(str[5], "TestMRR");
      TS_ASSERT_EQUALS(str[6], "TestMRR");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "7");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], " ");
      TS_ASSERT_EQUALS(str[5], "");
      TS_ASSERT_EQUALS(str[6], "");
    }

    void testConstructor2()
    {
      MRR stdfRec;
      stdfRec["DISP_COD"]=C1('M');
      TS_ASSERT_EQUALS(stdfRec.storage(), 7u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "7");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "M");
    }

    void testWriteRead1()
    {
      const char *filename = "TestMRR.testWriteRead1.txt";

      MRR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      MRR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "7");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], " ");
      TS_ASSERT_EQUALS(str[5], "");
      TS_ASSERT_EQUALS(str[6], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestMRR.testWriteRead2.txt";

      MRR stdfRecIn;
      stdfRecIn.setFinisht(255);
      stdfRecIn.setDispcod('a');
      stdfRecIn.setUsrdesc("abcd");
      stdfRecIn.setExcdesc("efgh");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 15u)

      MRR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "15");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[4], "a");
      TS_ASSERT_EQUALS(str[5], "abcd");
      TS_ASSERT_EQUALS(str[6], "efgh");
    }

    void testWriteRead3()
    {
      const char *filename = "TestMRR.testWriteRead3.txt";

      MRR stdfRecIn;
      
      *((U4*)(&(stdfRecIn["FINISH_T"]))) = 0xffffffff;
      stdfRecIn["DISP_COD"] = C1('F');
      *((Cn*)(&(stdfRecIn["USR_DESC"]))) = Cn("sss");
      *((Cn*)(&(stdfRecIn["EXC_DESC"]))) = Cn("fff");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      MRR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "13");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "20");
      TS_ASSERT_EQUALS(str[3], "4294967295");
      TS_ASSERT_EQUALS(str[4], "F");
      TS_ASSERT_EQUALS(str[5], "sss");
      TS_ASSERT_EQUALS(str[6], "fff");

      TS_ASSERT_EQUALS(stdfRecIn["FINISH_T"].to_string(), "4294967295");
      TS_ASSERT_EQUALS(stdfRecIn["DISP_COD"].to_string(), "F");
      TS_ASSERT_EQUALS(stdfRecIn["USR_DESC"].to_string(), "sss");
      TS_ASSERT_EQUALS(stdfRecIn["EXC_DESC"].to_string(), "fff");
      
     // stdfRecOut.find("DISP_COD");
    }

};


