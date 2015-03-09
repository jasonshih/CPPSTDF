#include <cxxtest/TestSuite.h>

#include "DataTypes.hpp"

class TestVn : public CxxTest::TestSuite 
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
      const size_t size = 0;
      Vn stdfStr;
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535u);
      TS_ASSERT_EQUALS(stdfStr.storage(), size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor1()
    {
      Vn stdfStr;
      U1 u1;
      U2 u2;
      U4 u4;
      I1 i1;
      I2 i2;
      I4 i4;
      R4 r4;
      R8 r8;
      Cn cn;
      Bn bn;
      Dn dn;
      KxN1<1> n1;
      stdfStr.addU1(u1).addU2(u2).addU4(u4).addI1(i1).addI2(i2).addI4(i4).addR4(r4).addR8(r8).addCn(cn).addBn(bn).addDn(dn).addN1(n1);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535u);
      TS_ASSERT_EQUALS(stdfStr.storage(), 49u);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "U1,0,B0,U2,0,B0,U4,0,I1,0,B0,I2,0,B0,I4,0,B0,R4,0,B0,R8,0,Cn,,Bn,,Dn,,N1,0");
    }

    void testConstructor2()
    {
      Vn stdfStr;
      U1 u1 = 255;
      I2 i2 = 510;
      Cn cn = "AB";
      stdfStr.addCn(cn).addU1(u1).addI2(i2);
      TS_ASSERT_EQUALS(stdfStr.storage(), 10u);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "Cn,AB,U1,255,B0,I2,510");
      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testCopyConstructor1()
    {
      Vn stdfStr;
      U1 u1 = 255;
      I2 i2 = 510;
      Cn cn = "AB";
      stdfStr.addCn(cn).addU1(u1).addI2(i2);
      TS_ASSERT_EQUALS(stdfStr.storage(), 10u);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "Cn,AB,U1,255,B0,I2,510");
      Vn stdfStrC(stdfStr);
      TS_ASSERT_EQUALS(stdfStrC.size(), 3u);
      TS_ASSERT_EQUALS(stdfStrC.storage(), 10u);
      TS_ASSERT_EQUALS(stdfStrC.to_string(), "Cn,AB,U1,255,B0,I2,510");
    }

    void testAssignCopy1()
    {
      Vn stdfStr;
      stdfStr.addCn(Cn("AB")).addU1(U1(255)).addI2(I2(510));
      TS_ASSERT_EQUALS(stdfStr.storage(), 10u);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "Cn,AB,U1,255,B0,I2,510");
      Vn stdfStrC;
      stdfStrC = stdfStr;
      TS_ASSERT_EQUALS(stdfStrC.size(), 3u);
      TS_ASSERT_EQUALS(stdfStrC.storage(), 10u);
      TS_ASSERT_EQUALS(stdfStrC.to_string(), "Cn,AB,U1,255,B0,I2,510");
    }

    void testClone1()
    {
      Vn stdfStr;
      stdfStr.addCn(Cn("AB")).addU1(U1(255)).addI2(I2(510));
      TS_ASSERT_EQUALS(stdfStr.storage(), 10u);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "Cn,AB,U1,255,B0,I2,510");
      DataType::DataTypeSharedPtr stdfStrP = stdfStr.clone();
      stdfStr.addCn(Cn("CC"));
      TS_ASSERT_EQUALS(stdfStrP->storage(), 10u);
      TS_ASSERT_EQUALS(stdfStrP->to_string(), "Cn,AB,U1,255,B0,I2,510");
    }

    void testWriteRead1()
    {
      const char *filename = "TestVn.testWriteRead1.txt";

      U1 u1;
      U2 u2;
      U4 u4;
      I1 i1;
      I2 i2;
      I4 i4;
      R4 r4;
      R8 r8;
      Cn cn;
      Bn bn;
      Dn dn;
      KxN1<1> n1;

      Vn stdfStrIn;
      stdfStrIn.addU1(u1).addU2(u2).addU4(u4).addI1(i1).addI2(i2).addI4(i4).addR4(r4).addR8(r8).addCn(cn).addBn(bn).addDn(dn).addN1(n1);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 49u)

      Vn stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, 49);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.storage(), stdfStrOut.storage())
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead2()
    {
      const char *filename = "TestVn.testWriteRead2.txt";

      U1 u1 = 0xFF;
      U2 u2 = 0xFFFF;
      U4 u4 = 0xFFFFFFFF;
      I1 i1 = -1;
      I2 i2 = -2;
      I4 i4 = -3;
      R4 r4 = 1.23456;
      R8 r8 = 1.23456789;
      Cn cn = "ABC";
      Bn bn = "01001001";
      Dn dn = "01001000100001000001";
      KxN1<1> n1 = "F";

      Vn stdfStrIn;
      stdfStrIn.addU1(u1).addU2(u2).addU4(u4).addI1(i1).addI2(i2).addI4(i4).addR4(r4).addR8(r8).addCn(cn).addBn(bn).addDn(dn).addN1(n1);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 56u)

      Vn stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, stdfStrIn.storage());
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.storage(), stdfStrOut.storage())
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead3()
    {
      const char *filename = "TestVn.testWriteRead3.txt";

      Vn stdfStrIn;
      U1 u1 = 255;
      I2 i2 = 510;
      Cn cn = "AB";
      stdfStrIn.addCn(cn).addU1(u1).addI2(i2);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Vn stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, stdfStrIn.storage());
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.storage(), stdfStrOut.storage())
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "Cn,AB,U1,255,B0,I2,510");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "Cn,AB,U1,255,B0,I2,510");
    }

};
