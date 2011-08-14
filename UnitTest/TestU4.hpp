#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestU4 : public CxxTest::TestSuite 
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
      U4 stdfStr;
      TS_ASSERT(stdfStr.mData == 0);
    }

    void testConstructor2()
    {
      U4 stdfStr = 0;
      TS_ASSERT(stdfStr.mData == 0);
    }

    void testConstructor3()
    {
      U4 stdfStr;
      TS_ASSERT(stdfStr.mData == 0);
      stdfStr = 0xFEDCBA98;
      TS_ASSERT(stdfStr.mData == 0xFEDCBA98);
    }

    void testConstructor4()
    {
      U4 stdfStr = 0xFFFFFFFF;
      TS_ASSERT(stdfStr.mData == 0xFFFFFFFF);
    }

    void testWriteRead1()
    {
      const char *filename = "TestU4.testWriteRead1.txt";

      U4 stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U4 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0);
      TS_ASSERT(stdfStrOut.mData == 0);
      TS_ASSERT(stdfStrIn.getValue() == 0);
      TS_ASSERT(stdfStrOut.getValue() == 0);
      TS_ASSERT(stdfStrIn.to_string() == "0");
      TS_ASSERT(stdfStrOut.to_string() == "0");
    }

    void testWriteRead2()
    {
      const char *filename = "TestU4.testWriteRead2.txt";

      U4 stdfStrIn = 1000;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U4 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0x3E8);
      TS_ASSERT(stdfStrOut.mData == 0x3E8);
      TS_ASSERT(stdfStrIn.getValue() == 1000);
      TS_ASSERT(stdfStrOut.getValue() == 1000);
      TS_ASSERT(stdfStrIn.to_string() == "1000");
      TS_ASSERT(stdfStrOut.to_string() == "1000");
      TS_ASSERT(stdfStrIn.size() == 4);
      TS_ASSERT(stdfStrOut.size() == 4);
    }

    void testWriteRead3()
    {
      const char *filename = "TestU4.testWriteRead3.txt";

      U4 stdfStrIn = 4294967295;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U4 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0xFFFFFFFF);
      TS_ASSERT(stdfStrOut.mData == 0xFFFFFFFF);
      TS_ASSERT(stdfStrIn.getValue() == 4294967295);
      TS_ASSERT(stdfStrOut.getValue() == 4294967295);
      TS_ASSERT(stdfStrIn.to_string() == "4294967295");
      TS_ASSERT(stdfStrOut.to_string() == "4294967295");
      TS_ASSERT(stdfStrIn.size() == 4);
      TS_ASSERT(stdfStrOut.size() == 4);
    }

    void testWriteRead4()
    {
      const char *filename = "TestU4.testWriteRead4.txt";

      U4 stdfStrIn = 4275878552;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      U4 stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT(stdfStrIn.mData == 0xFEDCBA98);
      TS_ASSERT(stdfStrOut.mData == 0xFEDCBA98);
      TS_ASSERT(stdfStrIn.getValue() == 4275878552);
      TS_ASSERT(stdfStrOut.getValue() == 4275878552);
      TS_ASSERT(stdfStrIn.to_string() == "4275878552");
      TS_ASSERT(stdfStrOut.to_string() == "4275878552");
      TS_ASSERT(stdfStrIn.size() == 4);
      TS_ASSERT(stdfStrOut.size() == 4);
    }


};
