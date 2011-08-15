#include <cxxtest/TestSuite.h>

#include "../src/DataTypes.hpp"

class TestKxUf : public CxxTest::TestSuite 
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
      KxTYPE<Uf, size> stdfStr;
      Uf data[size];
      TS_ASSERT_SAME_DATA(stdfStr.mData, data, size);
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(Uf::TYPE_1B), size);
      TS_ASSERT_EQUALS(stdfStr.size(Uf::TYPE_2B), size);
      TS_ASSERT_EQUALS(stdfStr.size(Uf::TYPE_4B), size);
      TS_ASSERT_EQUALS(stdfStr.size(Uf::TYPE_8B), size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor1()
    {
      const size_t size = 10;
      KxTYPE<Uf, size> stdfStr;
      Uf data[size];
      TS_ASSERT_SAME_DATA(stdfStr.mData, data, size);
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(Uf::TYPE_1B), size);
      TS_ASSERT_EQUALS(stdfStr.size(Uf::TYPE_2B), 2*size);
      TS_ASSERT_EQUALS(stdfStr.size(Uf::TYPE_4B), 4*size);
      TS_ASSERT_EQUALS(stdfStr.size(Uf::TYPE_8B), 8*size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0,0,0,0,0,0,0,0,0,0");
    }

    void testConstructor2()
    {
      const size_t size = 100;
      KxTYPE<Uf, size> stdfStr;
      Uf data[size];
      for(size_t i = 0; i < size; i++)
      {
        stdfStr[i] = data[i] = i;
      }
      TS_ASSERT_SAME_DATA(stdfStr.mData, data, size);
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.size(Uf::TYPE_1B), size);
      TS_ASSERT_EQUALS(stdfStr.size(Uf::TYPE_2B), 2*size);
      TS_ASSERT_EQUALS(stdfStr.size(Uf::TYPE_4B), 4*size);
      TS_ASSERT_EQUALS(stdfStr.size(Uf::TYPE_8B), 8*size);
      Uf data88 = stdfStr[88];
      TS_ASSERT_EQUALS(data88.getValue(), 88u);
      TS_ASSERT_EQUALS(data88.to_string(), data[88].to_string());
      Uf data99 = stdfStr[99];
      TS_ASSERT_EQUALS(data99.getValue(), 99u);
      TS_ASSERT_EQUALS(data99.to_string(), data[99].to_string());
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99");
      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");
    }

    void testWriteRead11()
    {
      const char *filename = "TestKxUf.testWriteRead11.txt";

      const size_t size = 1;
      Uf data[size];

      KxTYPE<Uf, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_1B);
      outfile.close();

      KxTYPE<Uf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_1B);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrOut.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead21()
    {
      const char *filename = "TestKxUf.testWriteRead21.txt";

      const size_t size = 1;
      Uf data[size];

      KxTYPE<Uf, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_2B);
      outfile.close();

      KxTYPE<Uf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_2B);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrOut.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead41()
    {
      const char *filename = "TestKxUf.testWriteRead41.txt";

      const size_t size = 1;
      Uf data[size];

      KxTYPE<Uf, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_4B);
      outfile.close();

      KxTYPE<Uf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_4B);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrOut.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead81()
    {
      const char *filename = "TestKxUf.testWriteRead81.txt";

      const size_t size = 1;
      Uf data[size];

      KxTYPE<Uf, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_8B);
      outfile.close();

      KxTYPE<Uf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_8B);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrOut.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead12()
    {
      const char *filename = "TestKxUf.testWriteRead12.txt";

      const size_t size = 10;
      Uf data[size];

      KxTYPE<Uf, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_1B);
      outfile.close();

      KxTYPE<Uf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_1B);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrOut.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead22()
    {
      const char *filename = "TestKxUf.testWriteRead22.txt";

      const size_t size = 10;
      Uf data[size];

      KxTYPE<Uf, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_2B);
      outfile.close();

      KxTYPE<Uf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_2B);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrOut.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead42()
    {
      const char *filename = "TestKxUf.testWriteRead42.txt";

      const size_t size = 10;
      Uf data[size];

      KxTYPE<Uf, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_4B);
      outfile.close();

      KxTYPE<Uf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_4B);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrOut.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead82()
    {
      const char *filename = "TestKxUf.testWriteRead82.txt";

      const size_t size = 10;
      Uf data[size];

      KxTYPE<Uf, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_8B);
      outfile.close();

      KxTYPE<Uf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_8B);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrOut.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead13()
    {
      const char *filename = "TestKxUf.testWriteRead13.txt";

      const size_t size = 20;
      Uf data[size];

      KxTYPE<Uf, size> stdfStrIn;
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i;
      }
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_1B);
      outfile.close();

      KxTYPE<Uf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_1B);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrOut.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");
    }

    void testWriteRead23()
    {
      const char *filename = "TestKxUf.testWriteRead23.txt";

      const size_t size = 20;
      Uf data[size];

      KxTYPE<Uf, size> stdfStrIn;
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i;
      }
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_2B);
      outfile.close();

      KxTYPE<Uf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_2B);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrOut.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");
    }

    void testWriteRead43()
    {
      const char *filename = "TestKxUf.testWriteRead43.txt";

      const size_t size = 20;
      Uf data[size];

      KxTYPE<Uf, size> stdfStrIn;
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i;
      }
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_4B);
      outfile.close();

      KxTYPE<Uf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_4B);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrOut.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");
    }

    void testWriteRead83()
    {
      const char *filename = "TestKxUf.testWriteRead83.txt";

      const size_t size = 20;
      Uf data[size];

      KxTYPE<Uf, size> stdfStrIn;
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i;
      }
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile, Uf::TYPE_8B);
      outfile.close();

      KxTYPE<Uf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile, Uf::TYPE_8B);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrOut.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");
    }

    void testWriteReadxx()
    {
      const char *filename = "TestKxUf.testWriteReadxx.txt";

      const size_t size = 20;
      Uf data[size];

      KxTYPE<Uf, size> stdfStrIn;
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i+0xFFFF;
      }
      ofstream outfile(filename, ofstream::binary);
      //stdfStrIn.write(outfile, Uf::TYPE_2B);
      stdfStrIn.write(outfile, Uf::TYPE_4B);
      outfile.close();

      KxTYPE<Uf, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      //stdfStrOut.read(infile, Uf::TYPE_2B);
      stdfStrOut.read(infile, Uf::TYPE_4B);
      outfile.close();

      TS_ASSERT_SAME_DATA(stdfStrIn.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrOut.mData, data, size);
      TS_ASSERT_SAME_DATA(stdfStrIn.mData, stdfStrOut.mData, size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "65535,65536,65537,65538,65539,65540,65541,65542,65543,65544,65545,65546,65547,65548,65549,65550,65551,65552,65553,65554");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "65535,65536,65537,65538,65539,65540,65541,65542,65543,65544,65545,65546,65547,65548,65549,65550,65551,65552,65553,65554");
    }

};
