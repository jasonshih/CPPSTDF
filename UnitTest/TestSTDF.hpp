#include <cxxtest/TestSuite.h>

#include "STDF.hpp"
#include "STDF.cpp"

class TestSTDF : public CxxTest::TestSuite 
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
      const char *filename = "TestSTDF.testWriteRead0.txt";
      STDF stdfRecOut(filename);
      TS_ASSERT_EQUALS(stdfRecOut.to_string(), "");
      TS_ASSERT_EQUALS(stdfRecOut.storage(), 0u);
    }

    void testConstructor1()
    {
      const char *filename = "TestSTDF.testWriteRead1.txt";
      STDF stdfRecOut(filename);
      FAR far;
      ATR atr;
      MRR mrr;
      stdfRecOut<<far<<atr<<mrr;
      stdfRecOut.close();

      stdfRecOut.read();
      TS_ASSERT_EQUALS(stdfRecOut.to_string(), "FAR,2,0,10,2,4,ATR,5,0,20,0,,MRR,7,1,20,0, ,,,");
      TS_ASSERT_EQUALS(stdfRecOut.storage(), 14u);
    }

    void testConstructor2()
    {
      const char *filename = "TestSTDF.testWriteRead2.txt";
      STDF stdfRecOut(filename);
      FAR far;
      ATR atr;
      MRR mrr;
      stdfRecOut.addRecord(far).addRecord(atr).addRecord(mrr);
      stdfRecOut.close();

      stdfRecOut.read();
      TS_ASSERT_EQUALS(stdfRecOut.to_string(), "FAR,2,0,10,2,4,ATR,5,0,20,0,,MRR,7,1,20,0, ,,,");
      TS_ASSERT_EQUALS(stdfRecOut.storage(), 14u);
    }

    void testWriteRead1()
    {
      const char *filename = "TestSTDF.testWriteRead3.txt";
      STDF stdfRecOut(filename,STDF::WRITE);
      FAR far;
      ATR atr;
      MRR mrr;
      stdfRecOut<<far<<atr;
      stdfRecOut.addRecord(mrr);
      stdfRecOut.close();

      stdfRecOut.read();
      TS_ASSERT_EQUALS(stdfRecOut.to_string(), "FAR,2,0,10,2,4,ATR,5,0,20,0,,MRR,7,1,20,0, ,,,");
      TS_ASSERT_EQUALS(stdfRecOut.storage(), 14u)
    }

    void testWriteRead2()
    {
      const char *filename = "TestSTDF.testWriteRead3.txt";
      STDF stdfRecIn(filename,STDF::READ);
      stdfRecIn.read();
      TS_ASSERT_EQUALS(stdfRecIn.to_string(), "FAR,2,0,10,2,4,ATR,5,0,20,0,,MRR,7,1,20,0, ,,,");
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 14u);
    }

    void testWriteRead3()
    {
      const char *filename = "TestSTDF.testWriteRead3.txt";
      STDF stdfRecOut(filename,STDF::APPEND);
      MRR mrr;
      mrr.setFinisht(65536u);
      mrr.setDispcod('d');
      mrr.setUsrdesc("usrdesc");
      mrr.setExcdesc("excdesc");
      PCR pcr;
      pcr.setHeadnum(222u);
      pcr.setSitenum(222u);
      pcr.setPartcnt(1111111111);
      pcr.setRtstcnt(1234567891);
      HBR hbr;
      hbr.setHeadnum(255);
      hbr.setSitenum(255);
      hbr.setHbinnum(65535);
      hbr.setHbincnt(1111111111u);
      hbr.setHbinpf('c');
      hbr.setHbinnam("TestHBR");
      stdfRecOut<<mrr<<pcr<<hbr;
      stdfRecOut.close();

      STDF stdfRecIn(filename,STDF::READ);
      stdfRecIn.read();
      TS_ASSERT_EQUALS(stdfRecIn.to_string(),"FAR,2,0,10,2,4,ATR,5,0,20,0,,MRR,7,1,20,0, ,,,MRR,21,1,20,65536,d,usrdesc,excdesc,PCR,22,1,30,222,222,1111111111,1234567891,4294967295,4294967295,4294967295,HBR,17,1,40,255,255,65535,1111111111,c,TestHBR,");
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 74u);
    }
    
    void testWriteRead4()
    {
      const char *filename = "TestSTDF.testWriteRead3.txt";
      STDF stdfRecOut(filename,STDF::MODIFY);
      stdfRecOut.read();
      stdfRecOut.changeValue("MRR","EXC_DESC",Cn("first_DESC_CUS"),0);
      stdfRecOut.changeValue("MRR","DISP_COD",C1('X'),0);
      stdfRecOut.write();
      stdfRecOut.clear();
      stdfRecOut.close();

      STDF stdfRecIn(filename,STDF::READ);
      stdfRecIn.read();
      TS_ASSERT_EQUALS(stdfRecIn.to_string(),"FAR,2,0,10,2,4,ATR,5,0,20,0,,MRR,21,1,20,0,X,,first_DESC_CUS,MRR,21,1,20,65536,d,usrdesc,excdesc,PCR,22,1,30,222,222,1111111111,1234567891,4294967295,4294967295,4294967295,HBR,17,1,40,255,255,65535,1111111111,c,TestHBR,");
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 88u);
    }

    void testWriteRead5()
    {
      const char *filename = "TestSTDF.testWriteRead3.txt";
      STDF stdfRecOut(filename,STDF::MODIFY);
      stdfRecOut.read();
      stdfRecOut.changeValue("MRR","EXC_DESC",Cn("second_DESC_CUS"),1);
      stdfRecOut.changeValue("MRR","DISP_COD",C1('X'),1);
      stdfRecOut.write();
      stdfRecOut.clear();
      stdfRecOut.close();

      STDF stdfRecIn(filename,STDF::READ);
      stdfRecIn.read();
      TS_ASSERT_EQUALS(stdfRecIn.to_string(),"FAR,2,0,10,2,4,ATR,5,0,20,0,,MRR,21,1,20,0,X,,first_DESC_CUS,MRR,29,1,20,65536,X,usrdesc,second_DESC_CUS,PCR,22,1,30,222,222,1111111111,1234567891,4294967295,4294967295,4294967295,HBR,17,1,40,255,255,65535,1111111111,c,TestHBR,");
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 96u);
    }

    void testWriteRead6()
    {
      const char *filename = "/home/andrewc/stdf/main_Lot_1234_Wafer_1_Apr_30_02h31m41s_STDF";
      STDF stdfRecIn(filename,STDF::READ);
      stdfRecIn.read();
      //stdfRecIn.print_record();
    }
};

