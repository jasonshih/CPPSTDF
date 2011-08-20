#include <cxxtest/TestSuite.h>

#include "../src/MIR.hpp"

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
      TS_ASSERT_EQUALS(stdfRec.storage(), 49u);
      vector<string> str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "49");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");

      TS_ASSERT_EQUALS(stdfRec["REC_LEN"].to_string(), "49");
      TS_ASSERT_EQUALS(stdfRec["REC_TYP"].to_string(), "1");
      TS_ASSERT_EQUALS(stdfRec["REC_SUB"].to_string(), "10");
      TS_ASSERT_EQUALS(stdfRec["SETUP_T"].to_string(), "0");
      TS_ASSERT_EQUALS(stdfRec["START_T"].to_string(), "0");
      TS_ASSERT_EQUALS(stdfRec["MODE_COD"].to_string(), " ");
      TS_ASSERT_EQUALS(stdfRec["OPER_NAM"].to_string(), "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestMIR.testWriteRead1.txt";

      MIR stdfRecIn;
      ofstream outfile(filename, ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      MIR stdfRecOut;
      ifstream infile(filename, ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      vector<string> str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "49");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");

      TS_ASSERT_EQUALS(stdfRecOut["REC_LEN"].to_string(), "49");
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
      stdfRecIn["SETUP_T"] = U4(9999);
      stdfRecIn["START_T"] = U4(8888);
      stdfRecIn["STAT_NUM"] = U1(1);
      stdfRecIn["MODE_COD"] = C1('F');
      stdfRecIn["BURN_TIM"] = U2(7777);
      stdfRecIn["OPER_NAM"] = Cn("lidanglin");
      ofstream outfile(filename, ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      MIR stdfRecOut;
      ifstream infile(filename, ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      vector<string> str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "49");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "9999");
      TS_ASSERT_EQUALS(str[4], "8888");

      TS_ASSERT_EQUALS(stdfRecIn["REC_LEN"].to_string(), "49");
      TS_ASSERT_EQUALS(stdfRecIn["REC_TYP"].to_string(), "1");
      TS_ASSERT_EQUALS(stdfRecIn["REC_SUB"].to_string(), "10");
      TS_ASSERT_EQUALS(stdfRecIn["SETUP_T"].to_string(), "9999");
      TS_ASSERT_EQUALS(stdfRecIn["START_T"].to_string(), "8888");
      TS_ASSERT_EQUALS(stdfRecIn["MODE_COD"].to_string(), "F");
      TS_ASSERT_EQUALS(stdfRecIn["OPER_NAM"].to_string(), "lidanglin");

      TS_ASSERT_EQUALS(stdfRecOut["REC_LEN"].to_string(), "49");
      TS_ASSERT_EQUALS(stdfRecOut["REC_TYP"].to_string(), "1");
      TS_ASSERT_EQUALS(stdfRecOut["REC_SUB"].to_string(), "10");
      TS_ASSERT_EQUALS(stdfRecOut["SETUP_T"].to_string(), "9999");
      TS_ASSERT_EQUALS(stdfRecOut["START_T"].to_string(), "8888");
      TS_ASSERT_EQUALS(stdfRecOut["MODE_COD"].to_string(), "F");
      TS_ASSERT_EQUALS(stdfRecOut["OPER_NAM"].to_string(), "lidanglin");
    }

};
