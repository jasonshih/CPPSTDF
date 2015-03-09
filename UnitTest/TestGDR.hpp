#include <cxxtest/TestSuite.h>

#include "StdfRecord.hpp"

class TestGDR : public CxxTest::TestSuite 
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
      GDR stdfRec;
      TS_ASSERT_EQUALS(stdfRec.storage(), 2u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "2");
      TS_ASSERT_EQUALS(str[1], "50");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
    }

    void testConstructor1()
    {
      GDR stdfRec;
      stdfRec.addU1(U1(5));
      stdfRec.addU2(U2(5));
      stdfRec.addU4(U4(5));
      stdfRec.addI1(I1(5));
      stdfRec.addI2(I2(5));
      stdfRec.addI4(I4(5));
      stdfRec.addR4(R4(5));
      stdfRec.addR8(R8(5));
      stdfRec.addCn(Cn("5"));
      stdfRec.addBn(Bn("000100011000"));
      stdfRec.addDn(Dn("000110001000"));
      stdfRec.addN1(N1("a"));
      TS_ASSERT_EQUALS(stdfRec.storage(), 56u);
      std::vector<std::basic_string<char> > str;
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "56");
      TS_ASSERT_EQUALS(str[1], "50");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "12");
      TS_ASSERT_EQUALS(str[4], "U1,5,B0,U2,5,B0,U4,5,I1,5,B0,I2,5,B0,I4,5,B0,R4,5,B0,R8,5,Cn,5,Bn,000100011000,Dn,000110001000,N1,A");

      stdfRec.clear();
      str.clear();
      stdfRec.to_string(str);
      TS_ASSERT_EQUALS(str[0], "2");
      TS_ASSERT_EQUALS(str[1], "50");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestGDR.testWriteRead1.txt";

      GDR stdfRecIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();

      GDR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "2");
      TS_ASSERT_EQUALS(str[1], "50");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "0");
      TS_ASSERT_EQUALS(str[4], "");
    }

    void testWriteRead2()
    {
      const char *filename = "TestGDR.testWriteRead2.txt";

      GDR stdfRecIn;
      stdfRecIn.addU1(U1(5));
      stdfRecIn.addU2(U2(5));
      stdfRecIn.addU4(U4(5));
      stdfRecIn.addI1(I1(5));
      stdfRecIn.addI2(I2(5));
      stdfRecIn.addI4(I4(5));
      stdfRecIn.addR4(R4(5));
      stdfRecIn.addR8(R8(5));
      stdfRecIn.addCn(Cn("5"));
      stdfRecIn.addBn(Bn("000100011000"));
      stdfRecIn.addDn(Dn("000110001000"));
      stdfRecIn.addN1(N1("A"));
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfRecIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfRecIn.storage(), 56u)

      GDR stdfRecOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfRecOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfRecIn.storage(), stdfRecOut.storage())
      std::vector<std::basic_string<char> > str;
      stdfRecOut.to_string(str);
      TS_ASSERT_EQUALS(str[0], "56");
      TS_ASSERT_EQUALS(str[1], "50");
      TS_ASSERT_EQUALS(str[2], "10");
      TS_ASSERT_EQUALS(str[3], "12");
      TS_ASSERT_EQUALS(str[4], "U1,5,B0,U2,5,B0,U4,5,I1,5,B0,I2,5,B0,I4,5,B0,R4,5,B0,R8,5,Cn,5,Bn,000100011000,Dn,000110001000,N1,A");
    }

};
