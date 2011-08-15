#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestUf : public CxxTest::TestSuite 
{
  public:
    void setUp()
    {
    }
    void tearDown()
    {
    }

    void testConstructor1()
    {
      Uf stdfStr;
      TS_ASSERT(stdfStr.mData == 0);
    }

    void testConstructor2()
    {
      Uf stdfStr = 0;
      TS_ASSERT(stdfStr.mData == 0);
    }

    void testConstructor3()
    {
      Uf stdfStr;
      TS_ASSERT(stdfStr.mData == 0);
      stdfStr = 123456789;
      TS_ASSERT(stdfStr.mData == 123456789);
    }

    void testConstructor4()
    {
      Uf stdfStr = 123456789;
      TS_ASSERT(stdfStr.mData == 123456789);
    }

    void testWriteRead1()
    {
      const char *filename = "TestUf.testWriteRead1.txt";

      Uf stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_1B);
      outfile.close();

      Uf stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_1B);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
    }

    void testWriteRead2()
    {
      const char *filename = "TestUf.testWriteRead2.txt";

      Uf stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_2B);
      outfile.close();

      Uf stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_2B);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
    }

    void testWriteRead3()
    {
      const char *filename = "TestUf.testWriteRead3.txt";

      Uf stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_4B);
      outfile.close();

      Uf stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_4B);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
    }

    void testWriteRead4()
    {
      const char *filename = "TestUf.testWriteRead4.txt";

      Uf stdfStrIn = 0xFEDCBA98;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_1B);
      outfile.close();
      stdfStrIn = 0x98;

      Uf stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_1B);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 152);
      TS_ASSERT(stdfStrOut.mData == 152);
      TS_ASSERT(stdfStrIn.getValue() == 152);
      TS_ASSERT(stdfStrOut.getValue() == 152);
      TS_ASSERT(stdfStrIn.to_string() == "152");
      TS_ASSERT(stdfStrOut.to_string() == "152");
      TS_ASSERT(stdfStrIn.storage(Uf::TYPE_1B) == 1);
      TS_ASSERT(stdfStrOut.storage(Uf::TYPE_1B) == 1);
    }

    void testWriteRead5()
    {
      const char *filename = "TestUf.testWriteRead5.txt";

      Uf stdfStrIn = 0xFEDCBA98;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_2B);
      outfile.close();
      stdfStrIn = 0xBA98;

      Uf stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_2B);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 47768);
      TS_ASSERT(stdfStrOut.mData == 47768);
      TS_ASSERT(stdfStrIn.getValue() == 47768);
      TS_ASSERT(stdfStrOut.getValue() == 47768);
      TS_ASSERT(stdfStrIn.to_string() == "47768");
      TS_ASSERT(stdfStrOut.to_string() == "47768");
      TS_ASSERT(stdfStrIn.storage(Uf::TYPE_2B) == 2);
      TS_ASSERT(stdfStrOut.storage(Uf::TYPE_2B) == 2);
    }

    void testWriteRead6()
    {
      const char *filename = "TestUf.testWriteRead6.txt";

      Uf stdfStrIn = 0xFEDCBA98;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_4B);
      outfile.close();

      Uf stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_4B);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 4275878552);
      TS_ASSERT(stdfStrOut.mData == 4275878552);
      TS_ASSERT(stdfStrIn.getValue() == 4275878552);
      TS_ASSERT(stdfStrOut.getValue() == 4275878552);
      TS_ASSERT(stdfStrIn.to_string() == "4275878552");
      TS_ASSERT(stdfStrOut.to_string() == "4275878552");
      TS_ASSERT(stdfStrIn.storage(Uf::TYPE_4B) == 4);
      TS_ASSERT(stdfStrOut.storage(Uf::TYPE_4B) == 4);
    }

    void testWriteRead7()
    {
      const char *filename = "TestUf.testWriteRead7.txt";

      Uf stdfStrIn = 0xFEDCBA9876543210;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_8B);
      outfile.close();

      Uf stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_8B);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0xFEDCBA9876543210);
      TS_ASSERT(stdfStrOut.mData == 0xFEDCBA9876543210);
      TS_ASSERT(stdfStrIn.getValue() == 18364758544493064720ull);
      TS_ASSERT(stdfStrOut.getValue() == 18364758544493064720ull);
      TS_ASSERT(stdfStrIn.to_string() == "18364758544493064720");
      TS_ASSERT(stdfStrOut.to_string() == "18364758544493064720");
      TS_ASSERT(stdfStrIn.storage(Uf::TYPE_8B) == 8);
      TS_ASSERT(stdfStrOut.storage(Uf::TYPE_8B) == 8);
    }
};
