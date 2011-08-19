#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestJxCn : public CxxTest::TestSuite 
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
      JxTYPE<Cn> stdfStr;
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor1()
    {
      const size_t size = 10;
      JxTYPE<Cn> stdfStr(size);
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), ",,,,,,,,,");
    }

    void testConstructor2()
    {
      size_t size = 100;
      JxTYPE<Cn> stdfStr(size);
      Cn data[size];
      for(size_t i = 0; i < size; i++)
      {
        stdfStr[i] = data[i] = "ABCD";
      }
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), 5*size);
      TS_ASSERT_EQUALS(stdfStr[88].to_string(), data[88].to_string());
      TS_ASSERT_EQUALS(stdfStr[99].to_string(), data[99].to_string());
      std::stringstream ss;
      for(size_t i = 0; i < size-1; i++) ss << "ABCD,"; ss << "ABCD";
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());
      stdfStr.add("ABCD").add("ABCD");
      ss << ",ABCD,ABCD";
      size +=2;
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());

      for(size_t i = 0; i < size; i++) stdfStr[i].clear();
      ss.str(""); for(size_t i = 0; i < size-1; i++) ss << ",";
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());

      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestJxCn.testWriteRead1.txt";

      const size_t size = 1;

      JxTYPE<Cn> stdfStrIn(size);
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Cn> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.size(), 1u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 1u);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 1u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 1u);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead2()
    {
      const char *filename = "TestJxCn.testWriteRead2.txt";

      const size_t size = 10;

      JxTYPE<Cn> stdfStrIn(size);
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Cn> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.size(), 10u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 10u);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 10u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 10u);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead3()
    {
      const char *filename = "TestJxCn.testWriteRead3.txt";

      const size_t size = 20;
      Cn data[size];

      JxTYPE<Cn> stdfStrIn(size);
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = "ABCDEF";
      }
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Cn> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.size(), 20u);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 20u);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 140u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 140u);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string());
      string str;
      for(size_t i = 0; i < size-1; i++) str.append("ABCDEF,"); str.append("ABCDEF");
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), str);
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), str);
    }

};
