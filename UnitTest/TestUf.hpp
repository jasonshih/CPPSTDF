#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestUf : public CxxTest::TestSuite 
{
  private:
    typedef Uf<1> Uf1;
    typedef Uf<2> Uf2;
    typedef Uf<4> Uf4;
    typedef Uf<8> Uf8;

  public:
    void setUp()
    {
    }
    void tearDown()
    {
    }

    void testConstructor11()
    {
      Uf1 stdfStr;
      TS_ASSERT(stdfStr.getValue() == 0);
      stdfStr = 123;
      TS_ASSERT(stdfStr.getValue() == 123);
      stdfStr.clear();
      TS_ASSERT(stdfStr.getValue() == 0);
    }

    void testConstructor12()
    {
      Uf1 stdfStr = 123;
      TS_ASSERT(stdfStr.getValue() == 123);
      stdfStr.clear();
      TS_ASSERT(stdfStr.getValue() == 0);
    }

    void testConstructor21()
    {
      Uf2 stdfStr = 0;
      TS_ASSERT(stdfStr.getValue() == 0);
      stdfStr = 12345;
      TS_ASSERT(stdfStr.getValue() == 12345);
      stdfStr.clear();
      TS_ASSERT(stdfStr.getValue() == 0);
    }

    void testConstructor22()
    {
      Uf2 stdfStr = 12345;
      TS_ASSERT(stdfStr.getValue() == 12345);
      stdfStr.clear();
      TS_ASSERT(stdfStr.getValue() == 0);
    }

    void testConstructor41()
    {
      Uf4 stdfStr = 0;
      TS_ASSERT(stdfStr.getValue() == 0);
      stdfStr = 123456789;
      TS_ASSERT(stdfStr.getValue() == 123456789);
      stdfStr.clear();
      TS_ASSERT(stdfStr.getValue() == 0);
    }

    void testConstructor42()
    {
      Uf4 stdfStr = 123456789;
      TS_ASSERT(stdfStr.getValue() == 123456789);
      stdfStr.clear();
      TS_ASSERT(stdfStr.getValue() == 0);
    }

    void testConstructor81()
    {
      Uf8 stdfStr = 0;
      TS_ASSERT(stdfStr.getValue() == 0);
      stdfStr = 123456789;
      TS_ASSERT(stdfStr.getValue() == 123456789);
      stdfStr.clear();
      TS_ASSERT(stdfStr.getValue() == 0);
    }

    void testConstructor82()
    {
      Uf8 stdfStr = 123456789;
      TS_ASSERT(stdfStr.getValue() == 123456789);
      stdfStr.clear();
      TS_ASSERT(stdfStr.getValue() == 0);
    }

    void testWriteRead11()
    {
      const char *filename = "TestUf.testWriteRead11.txt";

      Uf1 stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Uf1 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.getValue() == stdfStrOut.getValue());
    }

    void testWriteRead21()
    {
      const char *filename = "TestUf.testWriteRead21.txt";

      Uf2 stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Uf2 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.getValue() == stdfStrOut.getValue());
    }

    void testWriteRead41()
    {
      const char *filename = "TestUf.testWriteRead41.txt";

      Uf4 stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Uf4 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.getValue() == stdfStrOut.getValue());
    }

    void testWriteRead81()
    {
      const char *filename = "TestUf.testWriteRead81.txt";

      Uf8 stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Uf8 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.getValue() == stdfStrOut.getValue());
    }

    void testWriteRead12()
    {
      const char *filename = "TestUf.testWriteRead12.txt";

      Uf1 stdfStrIn = 0xFEDCBA98;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();
      stdfStrIn = 0x98;

      Uf1 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.getValue() == stdfStrOut.getValue());
      TS_ASSERT(stdfStrIn.getValue() == 152);
      TS_ASSERT(stdfStrOut.getValue() == 152);
      TS_ASSERT(stdfStrIn.getValue() == 152);
      TS_ASSERT(stdfStrOut.getValue() == 152);
      TS_ASSERT(stdfStrIn.to_string() == "152");
      TS_ASSERT(stdfStrOut.to_string() == "152");
      TS_ASSERT(stdfStrIn.storage() == 1);
      TS_ASSERT(stdfStrOut.storage() == 1);
    }

    void testWriteRead22()
    {
      const char *filename = "TestUf.testWriteRead22.txt";

      Uf2 stdfStrIn = 0xFEDCBA98;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();
      stdfStrIn = 0xBA98;

      Uf2 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.getValue() == stdfStrOut.getValue());
      TS_ASSERT(stdfStrIn.getValue() == 47768);
      TS_ASSERT(stdfStrOut.getValue() == 47768);
      TS_ASSERT(stdfStrIn.getValue() == 47768);
      TS_ASSERT(stdfStrOut.getValue() == 47768);
      TS_ASSERT(stdfStrIn.to_string() == "47768");
      TS_ASSERT(stdfStrOut.to_string() == "47768");
      TS_ASSERT(stdfStrIn.storage() == 2);
      TS_ASSERT(stdfStrOut.storage() == 2);
    }

    void testWriteRead42()
    {
      const char *filename = "TestUf.testWriteRead42.txt";

      Uf4 stdfStrIn = 0xFEDCBA98;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Uf4 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.getValue() == stdfStrOut.getValue());
      TS_ASSERT(stdfStrIn.getValue() == 4275878552);
      TS_ASSERT(stdfStrOut.getValue() == 4275878552);
      TS_ASSERT(stdfStrIn.getValue() == 4275878552);
      TS_ASSERT(stdfStrOut.getValue() == 4275878552);
      TS_ASSERT(stdfStrIn.to_string() == "4275878552");
      TS_ASSERT(stdfStrOut.to_string() == "4275878552");
      TS_ASSERT(stdfStrIn.storage() == 4);
      TS_ASSERT(stdfStrOut.storage() == 4);
    }

    void testWriteRead82()
    {
      const char *filename = "TestUf.testWriteRead82.txt";

      Uf8 stdfStrIn = 0xFEDCBA9876543210;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Uf8 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.getValue() == stdfStrOut.getValue());
      TS_ASSERT(stdfStrIn.getValue() == 0xFEDCBA9876543210);
      TS_ASSERT(stdfStrOut.getValue() == 0xFEDCBA9876543210);
      TS_ASSERT(stdfStrIn.getValue() == 18364758544493064720ull);
      TS_ASSERT(stdfStrOut.getValue() == 18364758544493064720ull);
      TS_ASSERT(stdfStrIn.to_string() == "18364758544493064720");
      TS_ASSERT(stdfStrOut.to_string() == "18364758544493064720");
      TS_ASSERT(stdfStrIn.storage() == 8);
      TS_ASSERT(stdfStrOut.storage() == 8);
    }
};
