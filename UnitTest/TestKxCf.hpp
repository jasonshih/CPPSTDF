#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestKxCf : public CxxTest::TestSuite 
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
      const size_t siz1 = 0;
      const size_t siz2 = 0;
      KxCf<siz1, siz2> stdfStr;
      TS_ASSERT_EQUALS(stdfStr.max_size(), siz1);
      TS_ASSERT_EQUALS(stdfStr.storage(), 0u);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor1()
    {
      const size_t siz1 = 10;
      const size_t siz2 = 0;
      KxCf<siz1, siz2> stdfStr;
      TS_ASSERT_EQUALS(stdfStr.max_size(), siz1);
      TS_ASSERT_EQUALS(stdfStr.storage(), 0u);
      TS_ASSERT_EQUALS(stdfStr.to_string(), ",,,,,,,,,");
    }

    void testConstructor2()
    {
      string abc = "ABCD";
      const size_t siz1 = 30;
      const size_t siz2 = 4;

      KxCf<siz1, siz2> stdfStr;
      for(size_t i = 0; i < siz1; i++)
      {
        stdfStr[i] = abc;
      }
      TS_ASSERT_EQUALS(stdfStr.max_size(), siz1);
      TS_ASSERT_EQUALS(stdfStr.storage(), siz1*siz2);
      TS_ASSERT_EQUALS(stdfStr[8], abc);
      TS_ASSERT_EQUALS(stdfStr[9], abc);
      string str;
      for(size_t i =  0; i < siz1-1; i++) str.append(abc+","); str.append(abc);
      TS_ASSERT_EQUALS(stdfStr.to_string(), str);
      stdfStr.clear();
      str.clear(); str.assign(siz1-1, ',');
      TS_ASSERT_EQUALS(stdfStr.to_string(), str);
    }

    void testConstructor3()
    {
      string abc = "ABCD";
      const size_t siz1 = 394;
      const size_t siz2 = 4;

      KxCf<siz1, siz2> stdfStr;
      for(size_t i = 0; i < siz1; i++)
      {
        stdfStr[i]= abc;
      }
      TS_ASSERT_EQUALS(stdfStr.max_size(), siz1);
      TS_ASSERT_EQUALS(stdfStr.storage(), siz1*siz2);
      TS_ASSERT_EQUALS(stdfStr[8], abc);
      TS_ASSERT_EQUALS(stdfStr[9], abc);
      string str;
      for(size_t i =  0; i < siz1-1; i++) str.append(abc+","); str.append(abc);
      TS_ASSERT_EQUALS(stdfStr.to_string(), str);
      stdfStr.clear();
      str.clear(); str.assign(siz1-1, ',');
      TS_ASSERT_EQUALS(stdfStr.to_string(), str);
    }

    void testWriteRead1()
    {
      const char *filename = "TestKxCf.testWriteRead1.txt";

      const size_t siz1 = 1;
      const size_t siz2 = 0;

      KxCf<siz1, siz2> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxCf<siz1, siz2> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 1u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 1u);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 0u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 0u);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead2()
    {
      const char *filename = "TestKxCf.testWriteRead2.txt";

      const size_t siz1 = 10;
      const size_t siz2 = 0;

      KxCf<siz1, siz2> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxCf<siz1, siz2> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 10u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 10u);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 0u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 0u);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead3()
    {
      const char *filename = "TestKxCf.testWriteRead3.txt";

      string abc = "ABCDEF";
      const size_t siz1 = 20;
      const size_t siz2 = 6;

      KxCf<siz1, siz2> stdfStrIn;
      for(size_t i = 0; i < siz1; i++)
      {
        stdfStrIn[i] = abc;
      }
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxCf<siz1, siz2> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.max_size(), siz1);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), siz1);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), siz1*siz2);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), siz1*siz2);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string());
      string str;
      for(size_t i =  0; i < siz1-1; i++) str.append(abc+","); str.append(abc);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), str);
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), str);
    }

    void testWriteRead4()
    {
      const char *filename = "TestKxCf.testWriteRead4.txt";

      string abc = "ABCDEF";
      const size_t siz1 = 420;
      const size_t siz2 = 9;

      KxCf<siz1, siz2> stdfStrIn;
      for(size_t i = 0; i < siz1; i++)
      {
        stdfStrIn[i] = abc;
      }
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxCf<siz1, siz2> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.max_size(), siz1);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), siz1);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), siz1*siz2);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), siz1*siz2);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string());
      string str;
      for(size_t i =  0; i < siz1-1; i++) str.append(abc+","); str.append(abc);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), str);
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), str);
    }

};
