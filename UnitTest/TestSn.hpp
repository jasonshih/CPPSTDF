#include <cxxtest/TestSuite.h>

#include "DataTypes.hpp"

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
      TS_ASSERT_EQUALS(stdfStr.storage(), 2u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535u);
    }

    void testConstructor2()
    {
      Sn stdfStr;
      TS_ASSERT_SAME_DATA(stdfStr.mData, "", 1);
      TS_ASSERT_EQUALS(stdfStr.storage(), 2u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535u);
      stdfStr += "";
      TS_ASSERT_SAME_DATA(stdfStr.mData, "", 1);
      TS_ASSERT_EQUALS(stdfStr.storage(), 2u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535u);
    }

    void testCopyConstructor1()
    {
      Sn stdfStr("ABC");
      TS_ASSERT_SAME_DATA(stdfStr.mData+2, "ABC", 3);
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535u);
      Sn stdfStrC (stdfStr);
      TS_ASSERT_SAME_DATA(stdfStrC.mData+2, "ABC", 3);
      TS_ASSERT_EQUALS(stdfStrC.storage(), 5u);
      TS_ASSERT_EQUALS(stdfStrC.max_size(), 65535u);
    }

    void testAssigner1()
    {
      Sn stdfStr("ABC");
      TS_ASSERT_SAME_DATA(stdfStr.mData+2, "ABC", 3);
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535u);
      Sn stdfStrC;
      stdfStrC = stdfStr;
      TS_ASSERT_SAME_DATA(stdfStrC.mData+2, "ABC", 3);
      TS_ASSERT_EQUALS(stdfStrC.storage(), 5u);
      TS_ASSERT_EQUALS(stdfStrC.max_size(), 65535u);
    }

    void testClone1()
    {
      Sn stdfStr("ABC");
      TS_ASSERT_SAME_DATA(stdfStr.mData+2, "ABC", 3);
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535u);
      DataType::DataTypeSharedPtr stdfStrP = stdfStr.clone();
      TS_ASSERT(stdfStrP->to_string() == "ABC");
      TS_ASSERT_EQUALS(stdfStrP->storage(), 5u);
      TS_ASSERT_DIFFERS(stdfStrP.get(), &stdfStr);
    }

    void testMergedSize()
    {
      std::basic_string<char> str;
      Sn stdfStr;

      str.assign(stdfStr.max_size(), 'A');
      TS_ASSERT(stdfStr.merged_size(str.size()) == stdfStr.max_size());

      str.assign(stdfStr.max_size()+1, 'A');
      TS_ASSERT(stdfStr.merged_size(str.size()) == stdfStr.max_size());

      str.assign(0, 'A');
      TS_ASSERT(stdfStr.merged_size(str.size()) == 0);
    }

    void testMerge()
    {
      Sn stdfStr;
      std::basic_string<char> str;

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
      std::basic_string<char> str1 = "123456789";
      stdfStr += str1;
      str[0] = 0xFF;
      str += str1;
      TS_ASSERT_SAME_DATA(stdfStr.mData, str.data(), stdfStr.max_size()+1);
    }

    void testWriteRead1()
    {
      const char *filename = "TestSn.testWriteRead1.txt";

      Sn stdfStr;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStr.write(outfile);
      outfile.close();

      std::ifstream infile(filename, std::ifstream::binary);
      stdfStr.clear();
      stdfStr.read(infile);
      outfile.close();

      TS_ASSERT(stdfStr.to_string() == "");
      TS_ASSERT_EQUALS(stdfStr.storage(), 2u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535u);
    }

    void testWriteRead2()
    {
      const char *filename = "TestSn.testWriteRead2.txt";

      Sn stdfStr("123456789");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStr.write(outfile);
      outfile.close();

      std::ifstream infile(filename,std::ifstream::binary);
      stdfStr.clear();
      stdfStr.read(infile);
      outfile.close();

      TS_ASSERT(stdfStr.to_string() == "123456789");
      TS_ASSERT_EQUALS(stdfStr.storage(), 11u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 65535u);
    }

    void testWriteRead3()
    {
      const char *filename = "TestSn.testWriteRead3.txt";

      std::basic_string<char> str;
      str.assign(70000, 'A');
      Sn stdfStrIn(str);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Sn stdfStrOut;
      std::ifstream infile(filename,std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      str.assign(stdfStrIn.max_size(), 'A');
      TS_ASSERT(stdfStrIn.to_string() == str);
      TS_ASSERT(stdfStrOut.to_string() == str);
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 65537u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 65537u);
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 65535u);
      TS_ASSERT_EQUALS(stdfStrOut.max_size(), 65535u);

      stdfStrIn.clear();
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 2u);
      TS_ASSERT_EQUALS(stdfStrIn.max_size(), 65535u);
    }
};
