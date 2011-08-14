#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestSn : public CxxTest::TestSuite 
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
      Sn stdfStr;
      TS_ASSERT_SAME_DATA(stdfStr.mData, "", 1);
      TS_ASSERT_EQUALS(stdfStr.size(), 2);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535);
    }

    void testConstructor2()
    {
      Sn stdfStr;
      TS_ASSERT_SAME_DATA(stdfStr.mData, "", 1);
      TS_ASSERT_EQUALS(stdfStr.size(), 2);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535);
      stdfStr += "";
      TS_ASSERT_SAME_DATA(stdfStr.mData, "", 1);
      TS_ASSERT_EQUALS(stdfStr.size(), 2);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535);
    }

    void testMergedSize()
    {
      string str;
      Sn stdfStr;

      str.assign(stdfStr.max_size(), 'A');
      TS_ASSERT(stdfStr.merged_size(str) == stdfStr.max_size());

      str.assign(stdfStr.max_size()+1, 'A');
      TS_ASSERT(stdfStr.merged_size(str) == stdfStr.max_size());

      str.assign(0, 'A');
      TS_ASSERT(stdfStr.merged_size(str) == 0);
    }

    void testMerge()
    {
      Sn stdfStr;
      string str;

      str = "";
      stdfStr.clear();
      stdfStr += str;
      TS_ASSERT(stdfStr.to_string() == str);
      TS_ASSERT_SAME_DATA(stdfStr.mData, "", 1);

      str.clear();
      str.assign(stdfStr.max_size()+1, 'A');
      stdfStr.clear();
      stdfStr += str;
      str[0] = 0xFF;
      str[1] = 0xFF;
      TS_ASSERT_SAME_DATA(stdfStr.mData, str.data(), stdfStr.max_size()+1);

      str = "123456789";
      stdfStr.clear();
      stdfStr += str;
      TS_ASSERT(stdfStr.to_string() == str);
      str.insert(0, 2, 0x0);
      str[0] = 0x09;
      str[1] = 0x00;
      TS_ASSERT_SAME_DATA(stdfStr.mData, str.data(), str.size()+1);

      str.clear();
      str.assign(stdfStr.max_size()-5, 'A');
      stdfStr.clear();
      stdfStr += str;
      TS_ASSERT(stdfStr.to_string() == str);
      str.insert(0, 2, 0x0);
      str[0] = 0xFF-5;
      str[1] = 0xFF;
      TS_ASSERT_SAME_DATA(stdfStr.mData, str.data(), stdfStr.max_size()-4);
      string str1 = "123456789";
      stdfStr += str1;
      str[0] = 0xFF;
      str += str1;
      TS_ASSERT_SAME_DATA(stdfStr.mData, str.data(), stdfStr.max_size()+1);
    }

    void testWriteRead1()
    {
      const char *filename = "TestSn.testWriteRead1.txt";

      Sn stdfStr;
      ofstream outfile(filename, ofstream::binary);
      stdfStr.write(outfile);
      outfile.close();

      ifstream infile(filename, ifstream::binary);
      stdfStr.clear();
      stdfStr.read(infile);
      outfile.close();

      TS_ASSERT(stdfStr.to_string() == "");
      TS_ASSERT_EQUALS(stdfStr.size(), 2);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535);
    }

    void testWriteRead2()
    {
      const char *filename = "TestSn.testWriteRead2.txt";

      Sn stdfStr("123456789");
      ofstream outfile(filename, ofstream::binary);
      stdfStr.write(outfile);
      outfile.close();

      ifstream infile(filename,ifstream::binary);
      stdfStr.clear();
      stdfStr.read(infile);
      outfile.close();

      TS_ASSERT(stdfStr.to_string() == "123456789");
      TS_ASSERT_EQUALS(stdfStr.size(), 11);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535);
    }

    void testWriteRead3()
    {
      const char *filename = "TestSn.testWriteRead3.txt";

      string str;
      str.assign(70000, 'A');
      Sn stdfStrIn(str);
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Sn stdfStrOut;
      ifstream infile(filename,ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      str.assign(stdfStrIn.max_size(), 'A');
      TS_ASSERT(stdfStrIn.to_string() == str);
      TS_ASSERT(stdfStrOut.to_string() == str);
      TS_ASSERT_EQUALS(stdfStrIn.size(), 65537);
      TS_ASSERT_EQUALS(stdfStrOut.size(), 65537);
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 65535);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 65535);

      stdfStrIn.clear();
      TS_ASSERT_EQUALS(stdfStrIn.size(), 2);
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 65535);
    }
};
