#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestKxU2 : public CxxTest::TestSuite 
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
      const int size = 0;
      KxTYPE<U2, size> stdfStr;
      U2 data[size];
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor1()
    {
      const int size = 10;
      KxTYPE<U2, size> stdfStr;
      U2 data[size];
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), 2*size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0,0,0,0,0,0,0,0,0,0");
    }

    void testConstructor2()
    {
      const int size = 100;
      KxTYPE<U2, size> stdfStr;
      U2 data[size];
      for(size_t i = 0; i < size; i++)
      {
        stdfStr[i] = data[i] = i;
      }
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(), 2*size);
      U2 data88 = stdfStr[88];
      TS_ASSERT_EQUALS(data88.getValue(), 88);
      TS_ASSERT_EQUALS(data88.to_string(), data[88].to_string());
      U2 data99 = stdfStr[99];
      TS_ASSERT_EQUALS(data99.getValue(), 99);
      TS_ASSERT_EQUALS(data99.to_string(), data[99].to_string());
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99");
      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");
    }

    void testWriteRead1()
    {
      const char *filename = "TestKxU2.testWriteRead1.txt";

      const int size = 1;
      U2 data[size];

      KxTYPE<U2, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<U2, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead2()
    {
      const char *filename = "TestKxU2.testWriteRead2.txt";

      const int size = 10;
      U2 data[size];

      KxTYPE<U2, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<U2, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead3()
    {
      const char *filename = "TestKxU2.testWriteRead3.txt";

      const int size = 20;
      U2 data[size];

      KxTYPE<U2, size> stdfStrIn;
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i;
      }
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<U2, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");
    }

};
