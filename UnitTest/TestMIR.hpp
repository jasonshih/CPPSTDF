#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestMIR : public CxxTest::TestSuite 
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
      MIR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 45u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "45");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");

      TS_ASSERT_EQUALS(stdfRec["REC_LEN"].to_string(), "45");
      TS_ASSERT_EQUALS(stdfRec["REC_TYP"].to_string(), "1");
      TS_ASSERT_EQUALS(stdfRec["REC_SUB"].to_string(), "10");
      TS_ASSERT_EQUALS(stdfRec["SETUP_T"].to_string(), "0");
      TS_ASSERT_EQUALS(stdfRec["START_T"].to_string(), "0");
      TS_ASSERT_EQUALS(stdfRec["MODE_COD"].to_string(), " ");
      TS_ASSERT_EQUALS(stdfRec["OPER_NAM"].to_string(), "");
      TS_ASSERT_EQUALS(stdfRec["BURN_TIM"].to_string(), "65535");
      
      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);

      TS_ASSERT_EQUALS(stdfRec["SETUP_T"].to_string(), "0");
    }

    void testWriteRead1()
    {
      const char *filename = "TestMIR.testWriteRead1.txt";

      MIR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      MIR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "45");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[9], "65535");

      TS_ASSERT_EQUALS(stdfRecOut["REC_LEN"].to_string(), "45");
      TS_ASSERT_EQUALS(stdfRecOut["REC_TYP"].to_string(), "1");
      TS_ASSERT_EQUALS(stdfRecOut["REC_SUB"].to_string(), "10");
      TS_ASSERT_EQUALS(stdfRecOut["SETUP_T"].to_string(), "0");
      TS_ASSERT_EQUALS(stdfRecOut["START_T"].to_string(), "0");
      TS_ASSERT_EQUALS(stdfRecOut["MODE_COD"].to_string(), " ");
      TS_ASSERT_EQUALS(stdfRecOut["OPER_NAM"].to_string(), "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestMIR.testWriteRead2.txt";

      MIR stdfRecIn;

      stdfRecIn["SETUP_T"] = U4(4294967295u);
      stdfRecIn["START_T"] = U4(8888u);
      stdfRecIn["STAT_NUM"] = U1(255u);
      stdfRecIn["MODE_COD"] = C1('M');
      stdfRecIn["PROT_COD"] = C1('P');
      stdfRecIn["LOT_ID"] = Cn("LOT_ID");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      MIR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "51");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "4294967295");
      TS_ASSERT_EQUALS(str[4], "8888");

      TS_ASSERT_EQUALS(stdfRecIn["REC_LEN"].to_string(), "51");
      TS_ASSERT_EQUALS(stdfRecIn["REC_TYP"].to_string(), "1");
      TS_ASSERT_EQUALS(stdfRecIn["REC_SUB"].to_string(), "10");
      TS_ASSERT_EQUALS(stdfRecIn["SETUP_T"].to_string(), "4294967295");
      TS_ASSERT_EQUALS(stdfRecIn["START_T"].to_string(), "8888");
      TS_ASSERT_EQUALS(stdfRecIn["STAT_NUM"].to_string(), "255");
      TS_ASSERT_EQUALS(stdfRecIn["MODE_COD"].to_string(), "M");
      TS_ASSERT_EQUALS(stdfRecIn["PROT_COD"].to_string(), "P");
      TS_ASSERT_EQUALS(stdfRecIn["LOT_ID"].to_string(), "LOT_ID");
    }

    void testWriteRead3()
    {
      const char *filename = "TestMIR.testWriteRead3.txt";

      MIR stdfRecIn;

      stdfRecIn.set("SETUP_T", U4(1234567890u));
      stdfRecIn.set("START_T", U4(1234u));
      stdfRecIn.set("STAT_NUM", U1(123u));
      stdfRecIn.set("MODE_COD", C1('m'));
      stdfRecIn.set("PROT_COD", C1('p'));
      stdfRecIn.set("LOT_ID", Cn("LOT_ID_1"));
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      MIR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "53");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "1234567890");
      TS_ASSERT_EQUALS(str[4], "1234");

      TS_ASSERT_EQUALS(stdfRecIn["REC_LEN"].to_string(), "53");
      TS_ASSERT_EQUALS(stdfRecIn["REC_TYP"].to_string(), "1");
      TS_ASSERT_EQUALS(stdfRecIn["REC_SUB"].to_string(), "10");
      TS_ASSERT_EQUALS(stdfRecIn["SETUP_T"].to_string(), "1234567890");
      TS_ASSERT_EQUALS(stdfRecIn["START_T"].to_string(), "1234");
      TS_ASSERT_EQUALS(stdfRecIn["STAT_NUM"].to_string(), "123");
      TS_ASSERT_EQUALS(stdfRecIn["MODE_COD"].to_string(), "m");
      TS_ASSERT_EQUALS(stdfRecIn["PROT_COD"].to_string(), "p");
      TS_ASSERT_EQUALS(stdfRecIn["LOT_ID"].to_string(), "LOT_ID_1");
    }
};
