#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestSDR : public CxxTest::TestSuite 
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
      SDR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 19u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "19");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "80");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "");
      TS_ASSERT_EQUALS(str[7], "");
      TS_ASSERT_EQUALS(str[8], "");
      TS_ASSERT_EQUALS(str[9], "");
      TS_ASSERT_EQUALS(str[10],"");
      TS_ASSERT_EQUALS(str[11],"");
      TS_ASSERT_EQUALS(str[12],"");
      TS_ASSERT_EQUALS(str[13],"");
      TS_ASSERT_EQUALS(str[14],"");
      TS_ASSERT_EQUALS(str[15],"");
      TS_ASSERT_EQUALS(str[16],"");
      TS_ASSERT_EQUALS(str[17],"");
      TS_ASSERT_EQUALS(str[18],"");
      TS_ASSERT_EQUALS(str[19],"");
      TS_ASSERT_EQUALS(str[20],"");
      TS_ASSERT_EQUALS(str[21],"");
      TS_ASSERT_EQUALS(str[22],"");
    }

    void testConstructor1()
    {
      SDR stdfRec;
      stdfRec.setHeadnum(255);
      stdfRec.setSitegrp(255);
      stdfRec.setSitecnt(5);
      stdfRec.setSitenum(0, 0);
      stdfRec.setSitenum(1, 1);
      stdfRec.setSitenum(2, 2);
      stdfRec.setSitenum(3, 3);
      stdfRec.setSitenum(4, 4);
      stdfRec.setHandtyp("Handtyp");
      stdfRec.setHandid ("Handid");
      stdfRec.setCardtyp("Cardtyp");
      stdfRec.setCardid ("Cardid");
      stdfRec.setLoadtyp("Loadtyp");
      stdfRec.setLoadid ("Loadid");
      stdfRec.setDibtyp ("Dibtyp");
      stdfRec.setDibid ("Dibid");
      stdfRec.setCabltyp ("Cabltyp");
      stdfRec.setCablid ("Cablid");
      stdfRec.setConttyp ("Conttyp");
      stdfRec.setContid ("Contid");
      stdfRec.setLasrtyp ("Lasrtyp");
      stdfRec.setLasrid ("Lasrid");
      stdfRec.setExtrtyp ("Extrtyp");
      stdfRec.setExtrid ("Extrid");
      TS_ASSERT_EQUALS(stdfRec.storage(), 126u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "126");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "80");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "5");
      TS_ASSERT_EQUALS(str[6], "0,1,2,3,4");
      TS_ASSERT_EQUALS(str[7], "Handtyp");
      TS_ASSERT_EQUALS(str[8], "Handid");
      TS_ASSERT_EQUALS(str[9], "Cardtyp");
      TS_ASSERT_EQUALS(str[10],"Cardid");
      TS_ASSERT_EQUALS(str[11],"Loadtyp");
      TS_ASSERT_EQUALS(str[12],"Loadid");
      TS_ASSERT_EQUALS(str[13],"Dibtyp");
      TS_ASSERT_EQUALS(str[14],"Dibid");
      TS_ASSERT_EQUALS(str[15],"Cabltyp");
      TS_ASSERT_EQUALS(str[16],"Cablid");
      TS_ASSERT_EQUALS(str[17],"Conttyp");
      TS_ASSERT_EQUALS(str[18],"Contid");
      TS_ASSERT_EQUALS(str[19],"Lasrtyp");
      TS_ASSERT_EQUALS(str[20],"Lasrid");
      TS_ASSERT_EQUALS(str[21],"Extrtyp");
      TS_ASSERT_EQUALS(str[22],"Extrid");
 
      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "19");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "80");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "");//default is empty: kxU1,size = 0
      TS_ASSERT_EQUALS(str[7], "");
      TS_ASSERT_EQUALS(str[8], "");
      TS_ASSERT_EQUALS(str[9], "");
      TS_ASSERT_EQUALS(str[10],"");
      TS_ASSERT_EQUALS(str[11],"");
      TS_ASSERT_EQUALS(str[12],"");
      TS_ASSERT_EQUALS(str[13],"");
      TS_ASSERT_EQUALS(str[14],"");
      TS_ASSERT_EQUALS(str[15],"");
      TS_ASSERT_EQUALS(str[16],"");
      TS_ASSERT_EQUALS(str[17],"");
      TS_ASSERT_EQUALS(str[18],"");
      TS_ASSERT_EQUALS(str[19],"");
      TS_ASSERT_EQUALS(str[20],"");
      TS_ASSERT_EQUALS(str[21],"");
      TS_ASSERT_EQUALS(str[22],"");
    }

    void testWriteRead1()
    {
      const char *filename = "TestSDR.testWriteRead1.txt";

      SDR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      SDR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "19");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "80");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "0");
      TS_ASSERT_EQUALS(str[5], "0");
      TS_ASSERT_EQUALS(str[6], "");
      TS_ASSERT_EQUALS(str[7], "");
      TS_ASSERT_EQUALS(str[8], "");
      TS_ASSERT_EQUALS(str[9], "");
      TS_ASSERT_EQUALS(str[10],"");
      TS_ASSERT_EQUALS(str[11],"");
      TS_ASSERT_EQUALS(str[12],"");
      TS_ASSERT_EQUALS(str[13],"");
      TS_ASSERT_EQUALS(str[14],"");
      TS_ASSERT_EQUALS(str[15],"");
      TS_ASSERT_EQUALS(str[16],"");
      TS_ASSERT_EQUALS(str[17],"");
      TS_ASSERT_EQUALS(str[18],"");
      TS_ASSERT_EQUALS(str[19],"");
      TS_ASSERT_EQUALS(str[20],"");
      TS_ASSERT_EQUALS(str[21],"");
      TS_ASSERT_EQUALS(str[22],"");
    }

    void testWriteRead2()
    {
      const char *filename = "TestSDR.testWriteRead2.txt";

      SDR stdfRecIn;
      stdfRecIn.setHeadnum(255);
      stdfRecIn.setSitegrp(255);
      stdfRecIn.setSitecnt(5);
      stdfRecIn.setSitenum(0, 0);
      stdfRecIn.setSitenum(1, 1);
      stdfRecIn.setSitenum(2, 2);
      stdfRecIn.setSitenum(3, 3);
      stdfRecIn.setSitenum(4, 4);
      stdfRecIn.setHandtyp("Handtyp");
      stdfRecIn.setHandid("Handid");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 37u)

      SDR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "37");
      TS_ASSERT_EQUALS(str[1], "1");
      TS_ASSERT_EQUALS(str[2], "80");
      TS_ASSERT_EQUALS(str[3], "255");
      TS_ASSERT_EQUALS(str[4], "255");
      TS_ASSERT_EQUALS(str[5], "5");
      TS_ASSERT_EQUALS(str[6], "0,1,2,3,4");
      TS_ASSERT_EQUALS(str[7], "Handtyp");
      TS_ASSERT_EQUALS(str[8], "Handid");
      TS_ASSERT_EQUALS(str[9], "");
      TS_ASSERT_EQUALS(str[10],"");
      TS_ASSERT_EQUALS(str[11],"");
      TS_ASSERT_EQUALS(str[12],"");
      TS_ASSERT_EQUALS(str[13],"");
      TS_ASSERT_EQUALS(str[14],"");
      TS_ASSERT_EQUALS(str[15],"");
      TS_ASSERT_EQUALS(str[16],"");
      TS_ASSERT_EQUALS(str[17],"");
      TS_ASSERT_EQUALS(str[18],"");
      TS_ASSERT_EQUALS(str[19],"");
      TS_ASSERT_EQUALS(str[20],"");
      TS_ASSERT_EQUALS(str[21],"");
      TS_ASSERT_EQUALS(str[22],"");
  }

};
