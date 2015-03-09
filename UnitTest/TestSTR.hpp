#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestSTR : public CxxTest::TestSuite 
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
      STR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 88u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "88");
      TS_ASSERT_EQUALS(str[1], "15"); 
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "00000000"); //CONT_FLG
      TS_ASSERT_EQUALS(str[4], "0");        //TEST_NUM
      TS_ASSERT_EQUALS(str[5], "0");        //HEAD_NUM
      TS_ASSERT_EQUALS(str[6], "0");        //SITE_NUM
      TS_ASSERT_EQUALS(str[7], "0");        //PSR_REF
      TS_ASSERT_EQUALS(str[8], "00000000"); //TEST_FLG
      TS_ASSERT_EQUALS(str[9], "");         //LOG_TYP
      TS_ASSERT_EQUALS(str[10], "");        //TEST_TXT
      TS_ASSERT_EQUALS(str[11], "");        //ALARM_ID
      TS_ASSERT_EQUALS(str[12], "");        //PROG_TXT
      TS_ASSERT_EQUALS(str[13], "");        //RSLT_TXT
      TS_ASSERT_EQUALS(str[14], "0");       //Z_VAL
      TS_ASSERT_EQUALS(str[15], "00000101");//FMU_FLG
      TS_ASSERT_EQUALS(str[16], "");        //CYC_CNT
      TS_ASSERT_EQUALS(str[17], "");        //TOTF_CNT
      TS_ASSERT_EQUALS(str[18], "0");       //TOTL_CNT
      TS_ASSERT_EQUALS(str[19], "0");       //CYC_BASE
      TS_ASSERT_EQUALS(str[20], "0");       //BIT_BASE
      TS_ASSERT_EQUALS(str[21], "0");       //COND_CNT
      TS_ASSERT_EQUALS(str[22], "0");       //LIM_CNT
      TS_ASSERT_EQUALS(str[23], "0");       //CYC_SIZE
      TS_ASSERT_EQUALS(str[24], "0");       //PMR_SIZE
      TS_ASSERT_EQUALS(str[25], "0");       //CHN_SIZE
      TS_ASSERT_EQUALS(str[26], "0");       //PAT_SIZE
      TS_ASSERT_EQUALS(str[27], "0");       //BIT_SIZE
      TS_ASSERT_EQUALS(str[28], "0");       //U1_SIZE
      TS_ASSERT_EQUALS(str[29], "0");       //U2_SIZE
      TS_ASSERT_EQUALS(str[30], "0");       //U3_SIZE
      TS_ASSERT_EQUALS(str[31], "0");       //UTX_SIZE
      TS_ASSERT_EQUALS(str[32], "0");       //CAP_BGN
      TS_ASSERT_EQUALS(str[33], "0");       //LIM_INDX
      TS_ASSERT_EQUALS(str[34], "0");       //LIM_SPEC
      TS_ASSERT_EQUALS(str[35], "");        //COND_LST
      TS_ASSERT_EQUALS(str[36], "");        //CYCO_CNT
      TS_ASSERT_EQUALS(str[37], "");        //CYC_OFST
      TS_ASSERT_EQUALS(str[38], "0");       //PMR_CNT
      TS_ASSERT_EQUALS(str[39], "");        //PMR_INDX
      TS_ASSERT_EQUALS(str[40], "0");       //CHN_CNT
      TS_ASSERT_EQUALS(str[41], "");        //CHN_NUM
      TS_ASSERT_EQUALS(str[42], "0");       //EXP_CNT
      TS_ASSERT_EQUALS(str[43], "");        //EXP_DATA
      TS_ASSERT_EQUALS(str[44], "0");       //CAP_CNT
      TS_ASSERT_EQUALS(str[45], "");        //CAP_DATA
      TS_ASSERT_EQUALS(str[46], "0");       //NEW_CNT
      TS_ASSERT_EQUALS(str[47], "");        //NEW_DATA
      TS_ASSERT_EQUALS(str[48], "0");       //PAT_CNT
      TS_ASSERT_EQUALS(str[49], "");        //PAT_NUM
      TS_ASSERT_EQUALS(str[50], "0");       //BPOS_CNT
      TS_ASSERT_EQUALS(str[51], "");        //BIT_POS
      TS_ASSERT_EQUALS(str[52], "0");       //USR1_CNT
      TS_ASSERT_EQUALS(str[53], "");        //USR1
      TS_ASSERT_EQUALS(str[54], "0");       //USR2_CNT
      TS_ASSERT_EQUALS(str[55], "");        //USR2
      TS_ASSERT_EQUALS(str[56], "0");       //USR3_CNT
      TS_ASSERT_EQUALS(str[57], "");        //USR3
      TS_ASSERT_EQUALS(str[58], "0");       //TXT_CNT
      TS_ASSERT_EQUALS(str[59], "");        //USER_TXT
    }
    void testConstructor1()
    {
      STR stdfRec;
      stdfRec.setContflg("10100101"); //CONT_FLG
      stdfRec.setTestnum(123456);     //TEST_NUM
      stdfRec.setHeadnum(255);        //HEAD_NUM
      stdfRec.setSitenum(0);          //SITE_NUM
      stdfRec.setPsrref( 65535);      //PSR_REF
      stdfRec.setTestflg("00011000"); //TEST_FLG
      stdfRec.setLogtyp( "LOG_TYP");  //LOG_TYP
      stdfRec.setTesttxt("TEST_TXT"); //TEST_TXT
      stdfRec.setAlarmid("ALARM_ID"); //ALARM_ID
      stdfRec.setProgtxt("PROG_TXT"); //PROG_TXT
      stdfRec.setRslttxt("RSLT_TXT"); //RSLT_TXT
      stdfRec.setZval(   255);        //Z_VAL
      stdfRec.setFmuflg( "00000101"); //FMU_FLG
      stdfRec.setMaskmap("111");      //CYC_CNT
      stdfRec.setFalmap( "1111");     //TOTF_CNT
      stdfRec.setCyccnt( 123456);     //TOTL_CNT
      stdfRec.settotfcnt(123456);     //CYC_BASE
      stdfRec.settotlcnt(123456);     //BIT_BASE
      stdfRec.setCycbase(5);          //COND_CNT
      stdfRec.setBitbase(3);          //LIM_CNT
      stdfRec.setCondcnt(5);          //CYC_SIZE
      stdfRec.setLimcnt(3);           //CYC_SIZE
      stdfRec.setCycsize(2);          //CYC_SIZE
      stdfRec.setPmrsize(2);          //PMR_SIZE
      stdfRec.setChnsize(2);          //CHN_SIZE
      stdfRec.setPatsize(2);          //PAT_SIZE
      stdfRec.setBitsize(2);          //BIT_SIZE
      stdfRec.setU1size (2);          //U1_SIZE
      stdfRec.setU2size (2);          //U2_SIZE
      stdfRec.setU3size (2);          //U3_SIZE
      stdfRec.setUtxsize(5);          //UTX_SIZE
      stdfRec.setCapbgn (65535);      //CAP_BGN
      stdfRec.setLimindx(0,0);        //LIM_INDX
      stdfRec.setLimindx(1,1);        //LIM_INDX
      stdfRec.setLimindx(2,2);        //LIM_INDX
      stdfRec.setLimspec(0,0);        //LIM_SPEC
      stdfRec.setLimspec(1,1);        //LIM_SPEC
      stdfRec.setLimspec(2,2);        //LIM_SPEC
      stdfRec.setCondlst(0,"0");      //COND_LST
      stdfRec.setCondlst(1,"1");      //COND_LST
      stdfRec.setCondlst(2,"2");      //COND_LST
      stdfRec.setCondlst(3,"3");      //COND_LST
      stdfRec.setCondlst(4,"4");      //COND_LST
      stdfRec.setCycocnt(2);          //CYCO_CNT
      stdfRec.setCycofst(0,0);        //CYC_OFST
      stdfRec.setCycofst(1,1);        //CYC_OFST
      stdfRec.setPmrcnt (2);          //PMR_CNT
      stdfRec.setPmrindx(0,0);        //PMR_INDX
      stdfRec.setPmrindx(1,1);        //PMR_INDX
      stdfRec.setChncnt (2);          //CHN_CNT
      stdfRec.setChnnum (0,0);        //CHN_NUM
      stdfRec.setChnnum (1,1);        //CHN_NUM
      stdfRec.setExpcnt (2);          //EXP_CNT
      stdfRec.setExpdata(0,0);        //EXP_DATA
      stdfRec.setExpdata(1,1);        //EXP_DATA
      stdfRec.setCapcnt (2);          //CAP_CNT
      stdfRec.setCapdata(0,0);        //CAP_DATA
      stdfRec.setCapdata(1,1);        //CAP_DATA
      stdfRec.setNewcnt (2);          //NEW_CNT
      stdfRec.setNewdata(0,0);        //NEW_DATA
      stdfRec.setNewdata(1,1);        //NEW_DATA
      stdfRec.setPatcnt (2);          //PAT_CNT
      stdfRec.setPatnum (0,0);        //PAT_NUM
      stdfRec.setPatnum (1,1);        //PAT_NUM
      stdfRec.setBposcnt(2);          //BPOS_CNT
      stdfRec.setBitpos (0,0);        //BIT_POS
      stdfRec.setBitpos (1,1);        //BIT_POS
      stdfRec.setUsr1cnt(2);          //USR1_CNT
      stdfRec.setUsr1   (0,0);        //USR1
      stdfRec.setUsr1   (1,1);        //USR1
      stdfRec.setUsr2cnt(2);          //USR2_CNT
      stdfRec.setUsr2   (0,0);        //USR2
      stdfRec.setUsr2   (1,1);        //USR2
      stdfRec.setUsr3cnt(2);          //USR3_CNT
      stdfRec.setUsr3   (0,0);        //USR3
      stdfRec.setUsr3   (1,1);        //USR3
      stdfRec.setTxtcnt (3);          //TXT_CNT
      stdfRec.setUsertxt(0,"cn1");    //USER_TXT
      stdfRec.setUsertxt(1,"cn2");    //USER_TXT
      stdfRec.setUsertxt(2,"cn3");    //USER_TXT

      TS_ASSERT_EQUALS(stdfRec.storage(), 210u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "210");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "10100101");          //CONT_FLG
      TS_ASSERT_EQUALS(str[4], "123456");            //TEST_NUM
      TS_ASSERT_EQUALS(str[5], "255");               //HEAD_NUM
      TS_ASSERT_EQUALS(str[6], "0");                 //SITE_NUM
      TS_ASSERT_EQUALS(str[7], "65535");             //PSR_REF
      TS_ASSERT_EQUALS(str[8], "00011000");          //TEST_FLG
      TS_ASSERT_EQUALS(str[9], "LOG_TYP");           //LOG_TYP
      TS_ASSERT_EQUALS(str[10], "TEST_TXT");         //TEST_TXT
      TS_ASSERT_EQUALS(str[11], "ALARM_ID");         //ALARM_ID
      TS_ASSERT_EQUALS(str[12], "PROG_TXT");         //PROG_TXT
      TS_ASSERT_EQUALS(str[13], "RSLT_TXT");         //RSLT_TXT
      TS_ASSERT_EQUALS(str[14], "255");              //Z_VAL
      TS_ASSERT_EQUALS(str[15], "00000101");         //FMU_FLG
      TS_ASSERT_EQUALS(str[16], "111");              //MASK_MAP
      TS_ASSERT_EQUALS(str[17], "1111");             //FAL_MAP
      TS_ASSERT_EQUALS(str[18], "123456");           //CYC_CNT
      TS_ASSERT_EQUALS(str[19], "123456");           //TOTF_CNT
      TS_ASSERT_EQUALS(str[20], "123456");           //TOTL_CNT
      TS_ASSERT_EQUALS(str[21], "5");                //CYC_BASE
      TS_ASSERT_EQUALS(str[22], "3");                //BIT_BASE
      TS_ASSERT_EQUALS(str[23], "5");                //COND_CNT
      TS_ASSERT_EQUALS(str[24], "3");                //LIM_CNT
      TS_ASSERT_EQUALS(str[25], "2");                //CYC_SIZE
      TS_ASSERT_EQUALS(str[26], "2");                //PMR_SIZE
      TS_ASSERT_EQUALS(str[27], "2");                //CHN_SIZE
      TS_ASSERT_EQUALS(str[28], "2");                //PAT_SIZE
      TS_ASSERT_EQUALS(str[29], "2");                //BIT_SIZE
      TS_ASSERT_EQUALS(str[30], "2");                //U1_SIZE
      TS_ASSERT_EQUALS(str[31], "2");                //U2_SIZE
      TS_ASSERT_EQUALS(str[32], "2");                //U3_SIZE
      TS_ASSERT_EQUALS(str[33], "5");                //UTX_SIZE
      TS_ASSERT_EQUALS(str[34], "65535");            //CAP_BGN
      TS_ASSERT_EQUALS(str[35], "0,1,2");            //LIM_INDX
      TS_ASSERT_EQUALS(str[36], "0,1,2");            //LIM_SPEC
      TS_ASSERT_EQUALS(str[37], "0,1,2,3,4");        //COND_LST
      TS_ASSERT_EQUALS(str[38], "2");                //CYCO_CNT
      TS_ASSERT_EQUALS(str[39], "0,1");              //CYC_OFST
      TS_ASSERT_EQUALS(str[40], "2");                //PMR_CNT
      TS_ASSERT_EQUALS(str[41], "0,1");              //PMR_INDX
      TS_ASSERT_EQUALS(str[42], "2");                //CHN_CNT
      TS_ASSERT_EQUALS(str[43], "0,1");              //CHN_NUM
      TS_ASSERT_EQUALS(str[44], "2");                //EXP_CNT
      TS_ASSERT_EQUALS(str[45], "0,1");              //EXP_DATA
      TS_ASSERT_EQUALS(str[46], "2");                //CAP_CNT
      TS_ASSERT_EQUALS(str[47], "0,1");              //CAP_DATA
      TS_ASSERT_EQUALS(str[48], "2");                //NEW_CNT
      TS_ASSERT_EQUALS(str[49], "0,1");              //NEW_DATA
      TS_ASSERT_EQUALS(str[50], "2");                //PAT_CNT
      TS_ASSERT_EQUALS(str[51], "0,1");              //PAT_NUM
      TS_ASSERT_EQUALS(str[52], "2");                //BPOS_CNT
      TS_ASSERT_EQUALS(str[53], "0,1");              //BIT_POS
      TS_ASSERT_EQUALS(str[54], "2");                //USR1_CNT
      TS_ASSERT_EQUALS(str[55], "0,1");              //USR1
      TS_ASSERT_EQUALS(str[56], "2");                //USR2_CNT
      TS_ASSERT_EQUALS(str[57], "0,1");              //USR2
      TS_ASSERT_EQUALS(str[58], "2");                //USR3_CNT
      TS_ASSERT_EQUALS(str[59], "0,1");              //USR3
      TS_ASSERT_EQUALS(str[60], "3");                //TXT_CNT
      TS_ASSERT_EQUALS(str[61], "cn1  ,cn2  ,cn3  ");//USER_TXT

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "88");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "00000000"); //CONT_FLG
      TS_ASSERT_EQUALS(str[4], "0");        //TEST_NUM
      TS_ASSERT_EQUALS(str[5], "0");        //HEAD_NUM
      TS_ASSERT_EQUALS(str[6], "0");        //SITE_NUM
      TS_ASSERT_EQUALS(str[7], "0");        //PSR_REF
      TS_ASSERT_EQUALS(str[8], "00000000"); //TEST_FLG
      TS_ASSERT_EQUALS(str[9], "");         //LOG_TYP
      TS_ASSERT_EQUALS(str[10], "");        //TEST_TXT
      TS_ASSERT_EQUALS(str[11], "");        //ALARM_ID
      TS_ASSERT_EQUALS(str[12], "");        //PROG_TXT
      TS_ASSERT_EQUALS(str[13], "");        //RSLT_TXT
      TS_ASSERT_EQUALS(str[14], "0");       //Z_VAL
      TS_ASSERT_EQUALS(str[15], "00000101");//FMU_FLG
      TS_ASSERT_EQUALS(str[16], "");        //MASK_MAP
      TS_ASSERT_EQUALS(str[17], "");        //FAL_MAP
      TS_ASSERT_EQUALS(str[18], "0");       //CYC_CNT
      TS_ASSERT_EQUALS(str[19], "0");       //TOTF_CNT
      TS_ASSERT_EQUALS(str[20], "0");       //TOTL_CNT
      TS_ASSERT_EQUALS(str[21], "0");       //CYC_BASE
      TS_ASSERT_EQUALS(str[22], "0");       //BIT_BASE
      TS_ASSERT_EQUALS(str[23], "0");       //COND_CNT
      TS_ASSERT_EQUALS(str[24], "0");       //LIM_CNT
      TS_ASSERT_EQUALS(str[25], "0");       //CYC_SIZE
      TS_ASSERT_EQUALS(str[26], "0");       //PMR_SIZE
      TS_ASSERT_EQUALS(str[27], "0");       //CHN_SIZE
      TS_ASSERT_EQUALS(str[28], "0");       //PAT_SIZE
      TS_ASSERT_EQUALS(str[29], "0");       //BIT_SIZE
      TS_ASSERT_EQUALS(str[30], "0");       //U1_SIZE
      TS_ASSERT_EQUALS(str[31], "0");       //U2_SIZE
      TS_ASSERT_EQUALS(str[32], "0");       //U3_SIZE
      TS_ASSERT_EQUALS(str[33], "0");       //UTX_SIZE
      TS_ASSERT_EQUALS(str[34], "0");       //CAP_BGN
      TS_ASSERT_EQUALS(str[35], "");        //LIM_INDX
      TS_ASSERT_EQUALS(str[36], "");        //LIM_SPEC
      TS_ASSERT_EQUALS(str[37], "");        //COND_LST
      TS_ASSERT_EQUALS(str[38], "0");       //CYCO_CNT
      TS_ASSERT_EQUALS(str[39], "");        //CYC_OFST
      TS_ASSERT_EQUALS(str[40], "0");       //PMR_CNT
      TS_ASSERT_EQUALS(str[41], "");        //PMR_INDX
      TS_ASSERT_EQUALS(str[42], "0");       //CHN_CNT
      TS_ASSERT_EQUALS(str[43], "");        //CHN_NUM
      TS_ASSERT_EQUALS(str[44], "0");       //EXP_CNT
      TS_ASSERT_EQUALS(str[45], "");        //EXP_DATA
      TS_ASSERT_EQUALS(str[46], "0");       //CAP_CNT
      TS_ASSERT_EQUALS(str[47], "");        //CAP_DATA
      TS_ASSERT_EQUALS(str[48], "0");       //NEW_CNT
      TS_ASSERT_EQUALS(str[49], "");        //NEW_DATA
      TS_ASSERT_EQUALS(str[50], "0");       //PAT_CNT
      TS_ASSERT_EQUALS(str[51], "");        //PAT_NUM
      TS_ASSERT_EQUALS(str[52], "0");       //BPOS_CNT
      TS_ASSERT_EQUALS(str[53], "");        //BIT_POS
      TS_ASSERT_EQUALS(str[54], "0");       //USR1_CNT
      TS_ASSERT_EQUALS(str[55], "");        //USR1
      TS_ASSERT_EQUALS(str[56], "0");       //USR2_CNT
      TS_ASSERT_EQUALS(str[57], "");        //USR2
      TS_ASSERT_EQUALS(str[58], "0");       //USR3_CNT
      TS_ASSERT_EQUALS(str[59], "");        //USR3
      TS_ASSERT_EQUALS(str[60], "0");       //TXT_CNT
      TS_ASSERT_EQUALS(str[61], "");        //USER_TXT
    }

    void testWriteRead1()
    {
      const char *filename = "TestSTR.testWriteRead1.txt";

      STR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      STR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "88");
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "00000000"); //CONT_FLG
      TS_ASSERT_EQUALS(str[4], "0");        //TEST_NUM
      TS_ASSERT_EQUALS(str[5], "0");        //HEAD_NUM
      TS_ASSERT_EQUALS(str[6], "0");        //SITE_NUM
      TS_ASSERT_EQUALS(str[7], "0");        //PSR_REF
      TS_ASSERT_EQUALS(str[8], "00000000"); //TEST_FLG
      TS_ASSERT_EQUALS(str[9], "");         //LOG_TYP
      TS_ASSERT_EQUALS(str[10], "");        //TEST_TXT
      TS_ASSERT_EQUALS(str[11], "");        //ALARM_ID
      TS_ASSERT_EQUALS(str[12], "");        //PROG_TXT
      TS_ASSERT_EQUALS(str[13], "");        //RSLT_TXT
      TS_ASSERT_EQUALS(str[14], "0");       //Z_VAL
      TS_ASSERT_EQUALS(str[15], "00000101");//FMU_FLG
      TS_ASSERT_EQUALS(str[16], "");        //MASK_MAP
      TS_ASSERT_EQUALS(str[17], "");        //FAL_MAP
      TS_ASSERT_EQUALS(str[18], "0");       //CYC_CNT
      TS_ASSERT_EQUALS(str[19], "0");       //TOTF_CNT
      TS_ASSERT_EQUALS(str[20], "0");       //TOTL_CNT
      TS_ASSERT_EQUALS(str[21], "0");       //CYC_BASE
      TS_ASSERT_EQUALS(str[22], "0");       //BIT_BASE
      TS_ASSERT_EQUALS(str[23], "0");       //COND_CNT
      TS_ASSERT_EQUALS(str[24], "0");       //LIM_CNT
      TS_ASSERT_EQUALS(str[25], "0");       //CYC_SIZE
      TS_ASSERT_EQUALS(str[26], "0");       //PMR_SIZE
      TS_ASSERT_EQUALS(str[27], "0");       //CHN_SIZE
      TS_ASSERT_EQUALS(str[28], "0");       //PAT_SIZE
      TS_ASSERT_EQUALS(str[29], "0");       //BIT_SIZE
      TS_ASSERT_EQUALS(str[30], "0");       //U1_SIZE
      TS_ASSERT_EQUALS(str[31], "0");       //U2_SIZE
      TS_ASSERT_EQUALS(str[32], "0");       //U3_SIZE
      TS_ASSERT_EQUALS(str[33], "0");       //UTX_SIZE
      TS_ASSERT_EQUALS(str[34], "0");       //CAP_BGN
      TS_ASSERT_EQUALS(str[35], "");        //LIM_INDX
      TS_ASSERT_EQUALS(str[36], "");        //LIM_SPEC
      TS_ASSERT_EQUALS(str[37], "");        //COND_LST
      TS_ASSERT_EQUALS(str[38], "0");       //CYCO_CNT
      TS_ASSERT_EQUALS(str[39], "");        //CYC_OFST
      TS_ASSERT_EQUALS(str[40], "0");       //PMR_CNT
      TS_ASSERT_EQUALS(str[41], "");        //PMR_INDX
      TS_ASSERT_EQUALS(str[42], "0");       //CHN_CNT
      TS_ASSERT_EQUALS(str[43], "");        //CHN_NUM
      TS_ASSERT_EQUALS(str[44], "0");       //EXP_CNT
      TS_ASSERT_EQUALS(str[45], "");        //EXP_DATA
      TS_ASSERT_EQUALS(str[46], "0");       //CAP_CNT
      TS_ASSERT_EQUALS(str[47], "");        //CAP_DATA
      TS_ASSERT_EQUALS(str[48], "0");       //NEW_CNT
      TS_ASSERT_EQUALS(str[49], "");        //NEW_DATA
      TS_ASSERT_EQUALS(str[50], "0");       //PAT_CNT
      TS_ASSERT_EQUALS(str[51], "");        //PAT_NUM
      TS_ASSERT_EQUALS(str[52], "0");       //BPOS_CNT
      TS_ASSERT_EQUALS(str[53], "");        //BIT_POS
      TS_ASSERT_EQUALS(str[54], "0");       //USR1_CNT
      TS_ASSERT_EQUALS(str[55], "");        //USR1
      TS_ASSERT_EQUALS(str[56], "0");       //USR2_CNT
      TS_ASSERT_EQUALS(str[57], "");        //USR2
      TS_ASSERT_EQUALS(str[58], "0");       //USR3_CNT
      TS_ASSERT_EQUALS(str[59], "");        //USR3
      TS_ASSERT_EQUALS(str[60], "0");       //TXT_CNT
      TS_ASSERT_EQUALS(str[61], "");        //USER_TXT
    }

    void testWriteRead2()
    {
      const char *filename = "TestSTR.testWriteRead2.txt";

      STR stdfRecIn;
      stdfRecIn.setContflg("10100101"); //CONT_FLG
      stdfRecIn.setTestnum(123456);     //TEST_NUM
      stdfRecIn.setHeadnum(255);        //HEAD_NUM
      stdfRecIn.setSitenum(0);          //SITE_NUM
      stdfRecIn.setPsrref( 65535);      //PSR_REF
      stdfRecIn.setTestflg("00011000"); //TEST_FLG
      stdfRecIn.setLogtyp( "LOG_TYP");  //LOG_TYP
      stdfRecIn.setTesttxt("TEST_TXT"); //TEST_TXT
      stdfRecIn.setAlarmid("ALARM_ID"); //ALARM_ID
      stdfRecIn.setProgtxt("PROG_TXT"); //PROG_TXT
      stdfRecIn.setRslttxt("RSLT_TXT"); //RSLT_TXT
      stdfRecIn.setZval(   255);        //Z_VAL
      stdfRecIn.setFmuflg( "00010101"); //FMU_FLG
      stdfRecIn.setMaskmap("111");      //MASK_MAP
      stdfRecIn.setFalmap( "1111");     //FAL_MAP
      stdfRecIn.setCyccnt( 123456);     //CYC_CNT 
      stdfRecIn.settotfcnt(123456);     //TOTF_CNT
      stdfRecIn.settotlcnt(123456);     //TOTL_CNT
      stdfRecIn.setCycbase(5);          //CYC_BASE
      stdfRecIn.setBitbase(3);          //BIT_BASE
      stdfRecIn.setCondcnt(5);          //COND_CNT
      stdfRecIn.setLimcnt(3);           //LIM_CNT 
      stdfRecIn.setCycsize(2);          //CYC_SIZE
      stdfRecIn.setPmrsize(2);          //PMR_SIZE
      stdfRecIn.setChnsize(2);          //CHN_SIZE
      stdfRecIn.setPatsize(2);          //PAT_SIZE
      stdfRecIn.setBitsize(2);          //BIT_SIZE
      stdfRecIn.setU1size (2);          //U1_SIZE
      stdfRecIn.setU2size (2);          //U2_SIZE
      stdfRecIn.setU3size (2);          //U3_SIZE
      stdfRecIn.setUtxsize(3);          //UTX_SIZE
      stdfRecIn.setCapbgn (65535);      //CAP_BGN
      stdfRecIn.setLimindx(0,0);        //LIM_INDX
      stdfRecIn.setLimindx(1,1);        //LIM_INDX
      stdfRecIn.setLimindx(2,2);        //LIM_INDX
      stdfRecIn.setLimspec(0,0);        //LIM_SPEC
      stdfRecIn.setLimspec(1,1);        //LIM_SPEC
      stdfRecIn.setLimspec(2,2);        //LIM_SPEC
      stdfRecIn.setCondlst(0,"a");      //COND_LST
      stdfRecIn.setCondlst(1,"b");      //COND_LST
      stdfRecIn.setCondlst(2,"c");      //COND_LST
      stdfRecIn.setCondlst(3,"d");      //COND_LST
      stdfRecIn.setCondlst(4,"e");      //COND_LST
      stdfRecIn.setCycocnt(2);          //CYCO_CNT
      stdfRecIn.setCycofst(0,0);        //CYC_OFST
      stdfRecIn.setCycofst(1,1);        //CYC_OFST
      stdfRecIn.setPmrcnt (2);          //PMR_CNT
      stdfRecIn.setPmrindx(0,0);        //PMR_INDX
      stdfRecIn.setPmrindx(1,1);        //PMR_INDX
      stdfRecIn.setChncnt (2);          //CHN_CNT
      stdfRecIn.setChnnum (0,0);        //CHN_NUM
      stdfRecIn.setChnnum (1,1);        //CHN_NUM
      stdfRecIn.setExpcnt (2);          //EXP_CNT
      stdfRecIn.setExpdata(0,0);        //EXP_DATA
      stdfRecIn.setExpdata(1,1);        //EXP_DATA
      stdfRecIn.setCapcnt (2);          //CAP_CNT
      stdfRecIn.setCapdata(0,0);        //CAP_DATA
      stdfRecIn.setCapdata(1,1);        //CAP_DATA
      stdfRecIn.setNewcnt (2);          //NEW_CNT
      stdfRecIn.setNewdata(0,0);        //NEW_DATA
      stdfRecIn.setNewdata(1,1);        //NEW_DATA
      stdfRecIn.setPatcnt (2);          //PAT_CNT
      stdfRecIn.setPatnum (0,0);        //PAT_NUM
      stdfRecIn.setPatnum (1,1);        //PAT_NUM
      stdfRecIn.setBposcnt(2);          //BPOS_CNT
      stdfRecIn.setBitpos (0,0);        //BIT_POS
      stdfRecIn.setBitpos (1,1);        //BIT_POS
      stdfRecIn.setUsr1cnt(2);          //USR1_CNT
      stdfRecIn.setUsr1   (0,0);        //USR1
      stdfRecIn.setUsr1   (1,1);        //USR1
      stdfRecIn.setUsr2cnt(2);          //USR2_CNT
      stdfRecIn.setUsr2   (0,0);        //USR2
      stdfRecIn.setUsr2   (1,1);        //USR2
      stdfRecIn.setUsr3cnt(2);          //USR3_CNT
      stdfRecIn.setUsr3   (0,0);        //USR3
      stdfRecIn.setUsr3   (1,1);        //USR3
      stdfRecIn.setTxtcnt (3);          //TXT_CNT
      stdfRecIn.setUsertxt(0,"cn11111");//USER_TXT
      stdfRecIn.setUsertxt(1,"cn22222");//USER_TXT
      stdfRecIn.setUsertxt(2,"cn33333");//USER_TXT
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 204u)

      STR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "204");              
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "10100101");    //CONT_FLG
      TS_ASSERT_EQUALS(str[4], "123456");      //TEST_NUM
      TS_ASSERT_EQUALS(str[5], "255");         //HEAD_NUM
      TS_ASSERT_EQUALS(str[6], "0");           //SITE_NUM
      TS_ASSERT_EQUALS(str[7], "65535");       //PSR_REF
      TS_ASSERT_EQUALS(str[8], "00011000");    //TEST_FLG
      TS_ASSERT_EQUALS(str[9], "LOG_TYP");     //LOG_TYP
      TS_ASSERT_EQUALS(str[10], "TEST_TXT");   //TEST_TXT
      TS_ASSERT_EQUALS(str[11], "ALARM_ID");   //ALARM_ID
      TS_ASSERT_EQUALS(str[12], "PROG_TXT");   //PROG_TXT
      TS_ASSERT_EQUALS(str[13], "RSLT_TXT");   //RSLT_TXT
      TS_ASSERT_EQUALS(str[14], "255");        //Z_VAL
      TS_ASSERT_EQUALS(str[15], "00010101");   //FMU_FLG
      TS_ASSERT_EQUALS(str[16], "111");        //MASK_MAP
      TS_ASSERT_EQUALS(str[17], "1111");       //FAL_MAP
      TS_ASSERT_EQUALS(str[18], "123456");     //CYC_CNT
      TS_ASSERT_EQUALS(str[19], "123456");     //TOTF_CNT
      TS_ASSERT_EQUALS(str[20], "123456");     //TOTL_CNT
      TS_ASSERT_EQUALS(str[21], "5");          //CYC_BASE
      TS_ASSERT_EQUALS(str[22], "3");          //BIT_BASE
      TS_ASSERT_EQUALS(str[23], "5");          //COND_CNT
      TS_ASSERT_EQUALS(str[24], "3");          //LIM_CNT
      TS_ASSERT_EQUALS(str[25], "2");          //CYC_SIZE
      TS_ASSERT_EQUALS(str[26], "2");          //PMR_SIZE
      TS_ASSERT_EQUALS(str[27], "2");          //CHN_SIZE
      TS_ASSERT_EQUALS(str[28], "2");          //PAT_SIZE
      TS_ASSERT_EQUALS(str[29], "2");          //BIT_SIZE
      TS_ASSERT_EQUALS(str[30], "2");          //U1_SIZE
      TS_ASSERT_EQUALS(str[31], "2");          //U2_SIZE
      TS_ASSERT_EQUALS(str[32], "2");          //U3_SIZE
      TS_ASSERT_EQUALS(str[33], "3");          //UTX_SIZE
      TS_ASSERT_EQUALS(str[34], "65535");      //CAP_BGN
      TS_ASSERT_EQUALS(str[35], "0,1,2");      //LIM_INDX
      TS_ASSERT_EQUALS(str[36], "0,1,2");      //LIM_SPEC
      TS_ASSERT_EQUALS(str[37], "a,b,c,d,e");  //COND_LST
      TS_ASSERT_EQUALS(str[38], "2");          //CYCO_CNT
      TS_ASSERT_EQUALS(str[39], "0,1");        //CYC_OFST
      TS_ASSERT_EQUALS(str[40], "2");          //PMR_CNT
      TS_ASSERT_EQUALS(str[41], "0,1");        //PMR_INDX
      TS_ASSERT_EQUALS(str[42], "2");          //CHN_CNT
      TS_ASSERT_EQUALS(str[43], "0,1");        //CHN_NUM
      TS_ASSERT_EQUALS(str[44], "2");          //EXP_CNT
      TS_ASSERT_EQUALS(str[45], "0,1");        //EXP_DATA
      TS_ASSERT_EQUALS(str[46], "2");          //CAP_CNT
      TS_ASSERT_EQUALS(str[47], "0,1");        //CAP_DATA
      TS_ASSERT_EQUALS(str[48], "2");          //NEW_CNT
      TS_ASSERT_EQUALS(str[49], "0,1");        //NEW_DATA
      TS_ASSERT_EQUALS(str[50], "2");          //PAT_CNT
      TS_ASSERT_EQUALS(str[51], "0,1");        //PAT_NUM
      TS_ASSERT_EQUALS(str[52], "2");          //BPOS_CNT
      TS_ASSERT_EQUALS(str[53], "0,1");        //BIT_POS
      TS_ASSERT_EQUALS(str[54], "2");          //USR1_CNT
      TS_ASSERT_EQUALS(str[55], "0,1");        //USR1
      TS_ASSERT_EQUALS(str[56], "2");          //USR2_CNT
      TS_ASSERT_EQUALS(str[57], "0,1");        //USR2
      TS_ASSERT_EQUALS(str[58], "2");          //USR3_CNT
      TS_ASSERT_EQUALS(str[59], "0,1");        //USR3
      TS_ASSERT_EQUALS(str[60], "3");          //TXT_CNT
      TS_ASSERT_EQUALS(str[61], "cn1,cn2,cn3");//USER_TXT

    }

    void testWriteRead3()
    {
      const char *filename = "TestSTR.testWriteRead3.txt";

      STR stdfRecIn;
      stdfRecIn.setContflg("10100101"); //CONT_FLG
      stdfRecIn.setTestnum(123456);     //TEST_NUM
      stdfRecIn.setHeadnum(255);        //HEAD_NUM
      stdfRecIn.setSitenum(0);          //SITE_NUM
      stdfRecIn.setPsrref( 65535);      //PSR_REF
      stdfRecIn.setTestflg("00011000"); //TEST_FLG
      stdfRecIn.setLogtyp( "LOG_TYP");  //LOG_TYP
      stdfRecIn.setTesttxt("TEST_TXT"); //TEST_TXT
      stdfRecIn.setAlarmid("ALARM_ID"); //ALARM_ID
      stdfRecIn.setProgtxt("PROG_TXT"); //PROG_TXT
      stdfRecIn.setRslttxt("RSLT_TXT"); //RSLT_TXT
      stdfRecIn.setZval(   255);        //Z_VAL
      stdfRecIn.setFmuflg( "00000000"); //FMU_FLG: If the bit is set means the field is considered missing or not.
      stdfRecIn.setMaskmap("111");      //MASK_MAP
      stdfRecIn.setFalmap( "1111");     //FAL_MAP
      stdfRecIn.setCyccnt( 123456);     //CYC_CNT 
      stdfRecIn.settotfcnt(123456);     //TOTF_CNT
      stdfRecIn.settotlcnt(123456);     //TOTL_CNT
      stdfRecIn.setCycbase(5);          //CYC_BASE
      stdfRecIn.setBitbase(3);          //BIT_BASE
      stdfRecIn.setCondcnt(5);          //COND_CNT
      stdfRecIn.setLimcnt(3);           //LIM_CNT 
      stdfRecIn.setCycsize(2);          //CYC_SIZE
      stdfRecIn.setPmrsize(2);          //PMR_SIZE
      stdfRecIn.setChnsize(2);          //CHN_SIZE
      stdfRecIn.setPatsize(2);          //PAT_SIZE
      stdfRecIn.setBitsize(2);          //BIT_SIZE
      stdfRecIn.setU1size (2);          //U1_SIZE
      stdfRecIn.setU2size (2);          //U2_SIZE
      stdfRecIn.setU3size (2);          //U3_SIZE
      stdfRecIn.setUtxsize(3);          //UTX_SIZE
      stdfRecIn.setCapbgn (65535);      //CAP_BGN
      stdfRecIn.setLimindx(0,0);        //LIM_INDX
      stdfRecIn.setLimindx(1,1);        //LIM_INDX
      stdfRecIn.setLimindx(2,2);        //LIM_INDX
      stdfRecIn.setLimspec(0,0);        //LIM_SPEC
      stdfRecIn.setLimspec(1,1);        //LIM_SPEC
      stdfRecIn.setLimspec(2,2);        //LIM_SPEC
      stdfRecIn.setCondlst(0,"a");      //COND_LST
      stdfRecIn.setCondlst(1,"b");      //COND_LST
      stdfRecIn.setCondlst(2,"c");      //COND_LST
      stdfRecIn.setCondlst(3,"d");      //COND_LST
      stdfRecIn.setCondlst(4,"e");      //COND_LST
      stdfRecIn.setCycocnt(2);          //CYCO_CNT
      stdfRecIn.setCycofst(0,0);        //CYC_OFST
      stdfRecIn.setCycofst(1,1);        //CYC_OFST
      stdfRecIn.setPmrcnt (2);          //PMR_CNT
      stdfRecIn.setPmrindx(0,0);        //PMR_INDX
      stdfRecIn.setPmrindx(1,1);        //PMR_INDX
      stdfRecIn.setChncnt (2);          //CHN_CNT
      stdfRecIn.setChnnum (0,0);        //CHN_NUM
      stdfRecIn.setChnnum (1,1);        //CHN_NUM
      stdfRecIn.setExpcnt (2);          //EXP_CNT
      stdfRecIn.setExpdata(0,0);        //EXP_DATA
      stdfRecIn.setExpdata(1,1);        //EXP_DATA
      stdfRecIn.setCapcnt (2);          //CAP_CNT
      stdfRecIn.setCapdata(0,0);        //CAP_DATA
      stdfRecIn.setCapdata(1,1);        //CAP_DATA
      stdfRecIn.setNewcnt (2);          //NEW_CNT
      stdfRecIn.setNewdata(0,0);        //NEW_DATA
      stdfRecIn.setNewdata(1,1);        //NEW_DATA
      stdfRecIn.setPatcnt (2);          //PAT_CNT
      stdfRecIn.setPatnum (0,0);        //PAT_NUM
      stdfRecIn.setPatnum (1,1);        //PAT_NUM
      stdfRecIn.setBposcnt(2);          //BPOS_CNT
      stdfRecIn.setBitpos (0,0);        //BIT_POS
      stdfRecIn.setBitpos (1,1);        //BIT_POS
      stdfRecIn.setUsr1cnt(2);          //USR1_CNT
      stdfRecIn.setUsr1   (0,0);        //USR1
      stdfRecIn.setUsr1   (1,1);        //USR1
      stdfRecIn.setUsr2cnt(2);          //USR2_CNT
      stdfRecIn.setUsr2   (0,0);        //USR2
      stdfRecIn.setUsr2   (1,1);        //USR2
      stdfRecIn.setUsr3cnt(2);          //USR3_CNT
      stdfRecIn.setUsr3   (0,0);        //USR3
      stdfRecIn.setUsr3   (1,1);        //USR3
      stdfRecIn.setTxtcnt (3);          //TXT_CNT
      stdfRecIn.setUsertxt(0,"cn11111");//USER_TXT
      stdfRecIn.setUsertxt(1,"cn22222");//USER_TXT
      stdfRecIn.setUsertxt(2,"cn33333");//USER_TXT
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 198u)

      STR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "198");              
      TS_ASSERT_EQUALS(str[1], "15");
      TS_ASSERT_EQUALS(str[2], "30");
      TS_ASSERT_EQUALS(str[3], "10100101");    //CONT_FLG
      TS_ASSERT_EQUALS(str[4], "123456");      //TEST_NUM
      TS_ASSERT_EQUALS(str[5], "255");         //HEAD_NUM
      TS_ASSERT_EQUALS(str[6], "0");           //SITE_NUM
      TS_ASSERT_EQUALS(str[7], "65535");       //PSR_REF
      TS_ASSERT_EQUALS(str[8], "00011000");    //TEST_FLG
      TS_ASSERT_EQUALS(str[9], "LOG_TYP");     //LOG_TYP
      TS_ASSERT_EQUALS(str[10], "TEST_TXT");   //TEST_TXT
      TS_ASSERT_EQUALS(str[11], "ALARM_ID");   //ALARM_ID
      TS_ASSERT_EQUALS(str[12], "PROG_TXT");   //PROG_TXT
      TS_ASSERT_EQUALS(str[13], "RSLT_TXT");   //RSLT_TXT
      TS_ASSERT_EQUALS(str[14], "255");        //Z_VAL
      TS_ASSERT_EQUALS(str[15], "00000000");   //FMU_FLG
      //TS_ASSERT_EQUALS(str[16], "111");        //MASK_MAP
      //TS_ASSERT_EQUALS(str[17], "1111");       //FAL_MAP
      TS_ASSERT_EQUALS(str[16], "123456");     //CYC_CNT
      TS_ASSERT_EQUALS(str[17], "123456");     //TOTF_CNT
      TS_ASSERT_EQUALS(str[18], "123456");     //TOTL_CNT
      TS_ASSERT_EQUALS(str[19], "5");          //CYC_BASE
      TS_ASSERT_EQUALS(str[20], "3");          //BIT_BASE
      TS_ASSERT_EQUALS(str[21], "5");          //COND_CNT
      TS_ASSERT_EQUALS(str[22], "3");          //LIM_CNT
      TS_ASSERT_EQUALS(str[23], "2");          //CYC_SIZE
      TS_ASSERT_EQUALS(str[24], "2");          //PMR_SIZE
      TS_ASSERT_EQUALS(str[25], "2");          //CHN_SIZE
      TS_ASSERT_EQUALS(str[26], "2");          //PAT_SIZE
      TS_ASSERT_EQUALS(str[27], "2");          //BIT_SIZE
      TS_ASSERT_EQUALS(str[28], "2");          //U1_SIZE
      TS_ASSERT_EQUALS(str[29], "2");          //U2_SIZE
      TS_ASSERT_EQUALS(str[30], "2");          //U3_SIZE
      TS_ASSERT_EQUALS(str[31], "3");          //UTX_SIZE
      TS_ASSERT_EQUALS(str[32], "65535");      //CAP_BGN
      TS_ASSERT_EQUALS(str[33], "0,1,2");      //LIM_INDX
      TS_ASSERT_EQUALS(str[34], "0,1,2");      //LIM_SPEC
      TS_ASSERT_EQUALS(str[35], "a,b,c,d,e");  //COND_LST
      TS_ASSERT_EQUALS(str[36], "2");          //CYCO_CNT
      TS_ASSERT_EQUALS(str[37], "0,1");        //CYC_OFST
      TS_ASSERT_EQUALS(str[38], "2");          //PMR_CNT
      TS_ASSERT_EQUALS(str[39], "0,1");        //PMR_INDX
      TS_ASSERT_EQUALS(str[40], "2");          //CHN_CNT
      TS_ASSERT_EQUALS(str[41], "0,1");        //CHN_NUM
      TS_ASSERT_EQUALS(str[42], "2");          //EXP_CNT
      TS_ASSERT_EQUALS(str[43], "0,1");        //EXP_DATA
      TS_ASSERT_EQUALS(str[44], "2");          //CAP_CNT
      TS_ASSERT_EQUALS(str[45], "0,1");        //CAP_DATA
      TS_ASSERT_EQUALS(str[46], "2");          //NEW_CNT
      TS_ASSERT_EQUALS(str[47], "0,1");        //NEW_DATA
      TS_ASSERT_EQUALS(str[48], "2");          //PAT_CNT
      TS_ASSERT_EQUALS(str[49], "0,1");        //PAT_NUM
      TS_ASSERT_EQUALS(str[50], "2");          //BPOS_CNT
      TS_ASSERT_EQUALS(str[51], "0,1");        //BIT_POS
      TS_ASSERT_EQUALS(str[52], "2");          //USR1_CNT
      TS_ASSERT_EQUALS(str[53], "0,1");        //USR1
      TS_ASSERT_EQUALS(str[54], "2");          //USR2_CNT
      TS_ASSERT_EQUALS(str[55], "0,1");        //USR2
      TS_ASSERT_EQUALS(str[56], "2");          //USR3_CNT
      TS_ASSERT_EQUALS(str[57], "0,1");        //USR3
      TS_ASSERT_EQUALS(str[58], "3");          //TXT_CNT
      TS_ASSERT_EQUALS(str[59], "cn1,cn2,cn3");//USER_TXT

    }

};
