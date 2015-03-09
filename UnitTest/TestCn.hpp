#include <cxxtest/TestSuite.h>

#include "DataTypes.hpp"

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
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
    }

    void testConstructor2()
    {
      Cn stdfStr;
      TS_ASSERT_SAME_DATA(stdfStr.mData, "", 1);
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
      stdfStr += "";
      TS_ASSERT_SAME_DATA(stdfStr.mData, "", 1);
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
    }

    void testCopyConstructor1()
    {
      Cn stdfStr("ABC");
      TS_ASSERT_SAME_DATA(stdfStr.mData+1, "ABC", 3);
      TS_ASSERT_EQUALS(stdfStr.storage(), 4u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
      Cn stdfStrC (stdfStr);
      TS_ASSERT_SAME_DATA(stdfStrC.mData+1, "ABC", 3);
      TS_ASSERT_EQUALS(stdfStrC.storage(), 4u);
      TS_ASSERT_EQUALS(stdfStrC.max_size(), 255u);
    }

    void testAssigner1()
    {
      Cn stdfStr("ABC");
      TS_ASSERT_SAME_DATA(stdfStr.mData+1, "ABC", 3);
      TS_ASSERT_EQUALS(stdfStr.storage(), 4u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
      Cn stdfStrC;
      stdfStrC = stdfStr;
      TS_ASSERT_SAME_DATA(stdfStrC.mData+1, "ABC", 3);
      TS_ASSERT_EQUALS(stdfStrC.storage(), 4u);
      TS_ASSERT_EQUALS(stdfStrC.max_size(), 255u);
    }

    void testClone1()
    {
      Cn stdfStr("ABC");
      TS_ASSERT_SAME_DATA(stdfStr.mData+1, "ABC", 3);
      TS_ASSERT_EQUALS(stdfStr.storage(), 4u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
      DataType::DataTypeSharedPtr stdfStrP = stdfStr.clone();
      TS_ASSERT(stdfStrP->to_string() == "ABC");
      TS_ASSERT_EQUALS(stdfStrP->storage(), 4u);
      TS_ASSERT_DIFFERS(stdfStrP.get(), &stdfStr);
    }

    void testMergedSize()
    {
      std::basic_string<char> str;
      Cn stdfStr;

      str.assign(stdfStr.max_size(), 'A');
      TS_ASSERT(stdfStr.merged_size(str.size()) == stdfStr.max_size());

      str.assign(stdfStr.max_size()+1, 'A');
      TS_ASSERT(stdfStr.merged_size(str.size()) == stdfStr.max_size());

      str.assign(0, 'A');
      TS_ASSERT(stdfStr.merged_size(str.size()) == 0);
    }

    void testMerge()
    {
      Cn stdfStr;
      std::basic_string<char> firstlevel("http://") ;
      std::basic_string<char>  secondlevel(".com");
      std::basic_string<char> str;

      str = "";
      stdfStr.clear();
      stdfStr += str;
      TS_ASSERT(stdfStr.to_string() == str);
      TS_ASSERT_SAME_DATA(stdfStr.mData, "", 1);

      str    = " a *&^\0 CD";
      stdfStr = " a *&^\0 CD";
      TS_ASSERT(stdfStr.to_string() == str);
      stdfStr.clear();
      stdfStr += str;
      TS_ASSERT(stdfStr.to_string() == str);
      TS_ASSERT(stdfStr.to_string() == " a *&^\0 EF");
      stdfStr = firstlevel+secondlevel ;
      str.erase(0,5);
      str = "http://.com";
      str.insert(0, 1, 0x0B);
      TS_ASSERT(stdfStr.to_string() == "http://.com");
      TS_ASSERT_SAME_DATA(stdfStr.mData, str.data(), str.size()+1);
      
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
      std::basic_string<char> str1 = "123456789";
      stdfStr += str1;
      str[0] = 0xFF;
      str += str1;
      TS_ASSERT_SAME_DATA(stdfStr.mData, str.data(), stdfStr.max_size()+1);
    }

    void testWriteRead1()
    {
      const char *filename = "TestCn.testWriteRead1.txt";

      Cn stdfStr;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStr.write(outfile);
      outfile.close();

      std::ifstream infile(filename, std::ifstream::binary);
      stdfStr.clear();
      stdfStr.read(infile);
      outfile.close();

      TS_ASSERT(stdfStr.to_string() == "");
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
    }

    void testWriteRead2()
    {
      const char *filename = "TestCn.testWriteRead2.txt";

      Cn stdfStr("123456789");
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStr.write(outfile);
      outfile.close();

      std::ifstream infile(filename,std::ifstream::binary);
      stdfStr.clear();
      stdfStr.read(infile);
      outfile.close();

      TS_ASSERT(stdfStr.to_string() == "123456789");
      TS_ASSERT_EQUALS(stdfStr.storage(), 10u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
    }

    void testWriteRead3()
    {
      const char *filename = "TestCn.testWriteRead3.txt";

      std::basic_string<char> str;
      str.assign(300, 'A');
      Cn stdfStr(str);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStr.write(outfile);
      outfile.close();

      std::ifstream infile(filename,std::ifstream::binary);
      stdfStr.clear();
      stdfStr.read(infile);
      outfile.close();

      str.assign(stdfStr.max_size(), 'A');
      TS_ASSERT(stdfStr.to_string() == str);
      TS_ASSERT_EQUALS(stdfStr.storage(), 256u);
      TS_ASSERT_EQUALS(stdfStr.max_size(), 255u);
    }
};
