#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestCn : public CxxTest::TestSuite 
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
      Cn stdfStr;
      TS_ASSERT_SAME_DATA(stdfStr.mData, "", 1);
      TS_ASSERT_EQUALS(stdfStr.size(), 1);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255);
    }

    void testConstructor2()
    {
      Cn stdfStr;
      TS_ASSERT_SAME_DATA(stdfStr.mData, "", 1);
      TS_ASSERT_EQUALS(stdfStr.size(), 1);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255);
      stdfStr += "";
      TS_ASSERT_SAME_DATA(stdfStr.mData, "", 1);
      TS_ASSERT_EQUALS(stdfStr.size(), 1);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255);
    }

    void testMergedSize()
    {
      string str;
      Cn stdfStr;

      str.assign(stdfStr.max_size(), 'A');
      TS_ASSERT(stdfStr.merged_size(str) == stdfStr.max_size());

      str.assign(stdfStr.max_size()+1, 'A');
      TS_ASSERT(stdfStr.merged_size(str) == stdfStr.max_size());

      str.assign(0, 'A');
      TS_ASSERT(stdfStr.merged_size(str) == 0);
    }

    void testMerge()
    {
      Cn stdfStr;
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
      TS_ASSERT_SAME_DATA(stdfStr.mData, str.data(), stdfStr.max_size()+1);

      str = "123456789";
      stdfStr.clear();
      stdfStr += str;
      TS_ASSERT(stdfStr.to_string() == str);
      str.insert(0, 1, 0x0);
      str[0] = 0x09;
      TS_ASSERT_SAME_DATA(stdfStr.mData, str.data(), str.size()+1);

      str.clear();
      str.assign(stdfStr.max_size()-5, 'A');
      stdfStr.clear();
      stdfStr += str;
      TS_ASSERT(stdfStr.to_string() == str);
      str.insert(0, 1, 0x0);
      str[0] = 0xFF-5;
      TS_ASSERT_SAME_DATA(stdfStr.mData, str.data(), stdfStr.max_size()-4);
      string str1 = "123456789";
      stdfStr += str1;
      str[0] = 0xFF;
      str += str1;
      TS_ASSERT_SAME_DATA(stdfStr.mData, str.data(), stdfStr.max_size()+1);
    }

    void testWriteRead1()
    {
      const char *filename = "TestCn.testWriteRead1.txt";

      Cn stdfStr;
      ofstream outfile(filename, ofstream::binary);
      stdfStr.write(outfile);
      outfile.close();

      ifstream infile(filename, ifstream::binary);
      stdfStr.clear();
      stdfStr.read(infile);
      outfile.close();

      TS_ASSERT(stdfStr.to_string() == "");
      TS_ASSERT_EQUALS(stdfStr.size(), 1);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255);
    }

    void testWriteRead2()
    {
      const char *filename = "TestCn.testWriteRead2.txt";

      Cn stdfStr("123456789");
      ofstream outfile(filename, ofstream::binary);
      stdfStr.write(outfile);
      outfile.close();

      ifstream infile(filename,ifstream::binary);
      stdfStr.clear();
      stdfStr.read(infile);
      outfile.close();

      TS_ASSERT(stdfStr.to_string() == "123456789");
      TS_ASSERT_EQUALS(stdfStr.size(), 10);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255);
    }

    void testWriteRead3()
    {
      const char *filename = "TestCn.testWriteRead3.txt";

      string str;
      str.assign(300, 'A');
      Cn stdfStr(str);
      ofstream outfile(filename, ofstream::binary);
      stdfStr.write(outfile);
      outfile.close();

      ifstream infile(filename,ifstream::binary);
      stdfStr.clear();
      stdfStr.read(infile);
      outfile.close();

      str.assign(stdfStr.max_size(), 'A');
      TS_ASSERT(stdfStr.to_string() == str);
      TS_ASSERT_EQUALS(stdfStr.size(), 256);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255);
    }
};
