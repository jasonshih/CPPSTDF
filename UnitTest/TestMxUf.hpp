#include <cxxtest/TestSuite.h>

#include "DataTypes.hpp"

class TestMxUf : public CxxTest::TestSuite 
{
  private:
    typedef Uf<1> Uf1;
    typedef Uf<2> Uf2;
    typedef Uf<4> Uf4;
    typedef Uf<8> Uf8;

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
      MxUf stdfStr(size);
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor1()
    {
      const size_t size = 10;
      MxUf stdfStr(size);
      TS_ASSERT_EQUALS(stdfStr.byte_size(), 1u);
      stdfStr.byte_size(stdfStr.byte_size());
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), size);
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << "0,"; ss << "0";
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());
    }

    void testConstructor2()
    {
      const size_t size = 100;
      MxUf stdfStr(size);
      Uf1 data[size];
      for(size_t i = 0; i < size; i++)
      {
        stdfStr[i] = data[i] = i;
      }

      TS_ASSERT_EQUALS(stdfStr.byte_size(), 1u);
      stdfStr.byte_size(stdfStr.byte_size());
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), size);
      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStr[i], data[i].getValue());
      }
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i << ','; ss << size-1;
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());
      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor3()
    {
      const size_t size = 100;
      MxUf stdfStr(size);
      Uf4 data[size];
      for(size_t i = 0; i < size; i++)
      {
        stdfStr[i] = data[i] = i+0xFFFF;
      }

      TS_ASSERT_EQUALS(stdfStr.byte_size(), 4u);
      stdfStr.byte_size(stdfStr.byte_size());
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), 4u*size);
      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStr[i], data[i].getValue());
      }
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i+0xFFFF << ','; ss << size-1+0xFFFF;
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());
      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testCopyConstructor1()
    {
      const size_t size = 100;
      MxUf source(size);
      Uf1 data[size];
      for(size_t i = 0; i < size; i++)
      {
        source[i] = data[i] = i;
      }
      MxUf stdfStr(source);

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStr[i], data[i].getValue());
      }
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i << ','; ss << size-1;
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());
      TS_ASSERT_EQUALS(source.to_string(), ss.str());
      stdfStr.clear();
      TS_ASSERT_EQUALS(source.to_string(), ss.str());
      source = stdfStr;
      ss.str("");
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());
      TS_ASSERT_EQUALS(source.to_string(), ss.str());
    }

    void testClone1()
    {
      const size_t size = 100;
      MxUf source(size);
      Uf1 data[size];
      for(size_t i = 0; i < size; i++)
      {
        source[i] = data[i] = i;
      }
      DataType::DataTypeSharedPtr stdfStr = source.clone();

      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i << ','; ss << size-1;
      TS_ASSERT_EQUALS(stdfStr->to_string(), ss.str());
      TS_ASSERT_EQUALS(source.to_string(), ss.str());
      stdfStr->clear();
      TS_ASSERT_EQUALS(source.to_string(), ss.str());
      source = *(boost::dynamic_pointer_cast<MxUf, DataType>(stdfStr));
      ss.str("");
      TS_ASSERT_EQUALS(stdfStr->to_string(), ss.str());
      TS_ASSERT_EQUALS(source.to_string(), ss.str());
    }

    void testWriteRead11()
    {
      const char *filename = "TestMxUf.testWriteRead11.txt";

      const size_t size = 1;

      MxUf stdfStrIn(size);
      TS_ASSERT_EQUALS(stdfStrIn.byte_size(), 1u);
      stdfStrIn.byte_size(stdfStrIn.byte_size());
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      MxUf stdfStrOut;
      stdfStrOut.byte_size(1u);
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i], stdfStrOut[i]);
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrIn.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead21()
    {
      const char *filename = "TestMxUf.testWriteRead21.txt";

      const size_t size = 2;

      MxUf stdfStrIn(size);
      stdfStrIn[0] = 2;
      stdfStrIn[1] = 257;
      stdfStrIn.byte_size(stdfStrIn.byte_size());
      TS_ASSERT_EQUALS(stdfStrIn.byte_size(), 2u);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      MxUf stdfStrOut;
      stdfStrOut.byte_size(2u);
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i], stdfStrOut[i]);
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead41()
    {
      const char *filename = "TestMxUf.testWriteRead41.txt";

      const size_t size = 2;

      MxUf stdfStrIn(size);
      stdfStrIn[0] = 2;
      stdfStrIn[1] = 65539;
      stdfStrIn.byte_size(stdfStrIn.byte_size());
      TS_ASSERT_EQUALS(stdfStrIn.byte_size(), 4u);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      MxUf stdfStrOut;
      stdfStrOut.byte_size(4u);
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i], stdfStrOut[i]);
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead81()
    {
      const char *filename = "TestMxUf.testWriteRead81.txt";

      const size_t size = 2;

      MxUf stdfStrIn(size);
      stdfStrIn[0] = 2;
      stdfStrIn[1] = 9llu + 0xFFFFFFFF;
      stdfStrIn.byte_size(stdfStrIn.byte_size());
      TS_ASSERT_EQUALS(stdfStrIn.byte_size(), 8u);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      MxUf stdfStrOut;
      stdfStrOut.byte_size(8u);
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i], stdfStrOut[i]);
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead12()
    {
      const char *filename = "TestMxUf.testWriteRead12.txt";

      const size_t size = 10;

      MxUf stdfStrIn(size);
      stdfStrIn[0] = 2;
      stdfStrIn[1] = 1;
      stdfStrIn.byte_size(stdfStrIn.byte_size());
      TS_ASSERT_EQUALS(stdfStrIn.byte_size(), 1u);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      MxUf stdfStrOut;
      stdfStrOut.byte_size(1u);
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i], stdfStrOut[i]);
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead22()
    {
      const char *filename = "TestMxUf.testWriteRead22.txt";

      const size_t size = 10;

      MxUf stdfStrIn(size);
      stdfStrIn[5] = 1u << 9;
      stdfStrIn.byte_size(stdfStrIn.byte_size());
      TS_ASSERT_EQUALS(stdfStrIn.byte_size(), 2u);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      MxUf stdfStrOut;
      stdfStrOut.byte_size(2u);
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i], stdfStrOut[i]);
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead42()
    {
      const char *filename = "TestMxUf.testWriteRead42.txt";

      const size_t size = 10;

      MxUf stdfStrIn(size);
      stdfStrIn[5] = 1u << 17;
      stdfStrIn.byte_size(stdfStrIn.byte_size());
      TS_ASSERT_EQUALS(stdfStrIn.byte_size(), 4u);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      MxUf stdfStrOut;
      stdfStrOut.byte_size(4u);
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i], stdfStrOut[i]);
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead82()
    {
      const char *filename = "TestMxUf.testWriteRead82.txt";

      const size_t size = 10;

      MxUf stdfStrIn(size);
      stdfStrIn[5] = 9llu+0xFFFFFFFF;
      stdfStrIn.byte_size(stdfStrIn.byte_size());
      TS_ASSERT_EQUALS(stdfStrIn.byte_size(), 8u);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      MxUf stdfStrOut;
      stdfStrOut.byte_size(8u);
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i], stdfStrOut[i]);
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead13()
    {
      const char *filename = "TestMxUf.testWriteRead13.txt";

      const size_t size = 20;
      Uf1 data[size];

      MxUf stdfStrIn(size);
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i;
      }
      stdfStrIn.byte_size(stdfStrIn.byte_size());
      TS_ASSERT_EQUALS(stdfStrIn.byte_size(), 1u);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      MxUf stdfStrOut;
      stdfStrOut.byte_size(1u);
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i], data[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i], stdfStrOut[i]);
      }
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.storage(), size);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i << ','; ss << size-1;
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), ss.str());
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), ss.str());
    }

    void testWriteRead23()
    {
      const char *filename = "TestMxUf.testWriteRead23.txt";

      const size_t size = 20;
      Uf2 data[size];

      MxUf stdfStrIn(size);
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i+0xFF;
      }
      stdfStrIn.byte_size(stdfStrIn.byte_size());
      TS_ASSERT_EQUALS(stdfStrIn.byte_size(), 2u);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      MxUf stdfStrOut;
      stdfStrOut.byte_size(2u);
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i], data[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i], stdfStrOut[i]);
      }
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 2*size);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 2*size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i+0xFF << ','; ss << size-1+0xFF;
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), ss.str());
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), ss.str());
    }

    void testWriteRead43()
    {
      const char *filename = "TestMxUf.testWriteRead43.txt";

      const size_t size = 20;
      Uf4 data[size];

      MxUf stdfStrIn(size);
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i+0xFFFF;
      }
      stdfStrIn.byte_size(stdfStrIn.byte_size());
      TS_ASSERT_EQUALS(stdfStrIn.byte_size(), 4u);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      MxUf stdfStrOut;
      stdfStrOut.byte_size(4u);
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i], data[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i], stdfStrOut[i]);
      }
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 4*size);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 4*size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i+0xFFFF << ','; ss << size-1+0xFFFF;
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), ss.str());
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), ss.str());
    }

    void testWriteRead83()
    {
      const char *filename = "TestMxUf.testWriteRead83.txt";

      const size_t size = 20;
      Uf8 data[size];

      MxUf stdfStrIn(size);
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i+0xFFFFFFFF;
      }
      stdfStrIn.byte_size(stdfStrIn.byte_size());
      TS_ASSERT_EQUALS(stdfStrIn.byte_size(), 8u);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      MxUf stdfStrOut;
      stdfStrOut.byte_size(8u);
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i], data[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i], stdfStrOut[i]);
      }
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 8*size);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 8*size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i+0xFFFFFFFF << ','; ss << size-1+0xFFFFFFFF;
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), ss.str());
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), ss.str());
    }

    void testWriteReadxx()
    {
      const char *filename = "TestMxUf.testWriteReadxx.txt";

      const size_t size = 20;
      Uf4 data[size];

      MxUf stdfStrIn(size);
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i+0xFFFF;
      }
      stdfStrIn.byte_size(stdfStrIn.byte_size());
      TS_ASSERT_EQUALS(stdfStrIn.byte_size(), 4u);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      MxUf stdfStrOut;
      stdfStrOut.byte_size(4u);
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i], data[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i], stdfStrOut[i]);
      }
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i+0xFFFF << ','; ss << size-1+0xFFFF;
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), ss.str());
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), ss.str());
    }

};
