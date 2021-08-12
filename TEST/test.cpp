#include "pch.h"

class ArrayOfArrays
{

    int** arrayofarrays;

public:

    class Proxy;

    ArrayOfArrays()
    {
        arrayofarrays = new int* [10];

        for (int i = 0; i < 10; ++i)
            arrayofarrays[i] = new int[10];
    }

    Proxy operator[](int index)
    {
        return Proxy(arrayofarrays[index]);
    }

    class Proxy
    {
        int* array;

    public:

        Proxy(int* array) : array(array) { }

        int& operator[](int index)
        {
            return array[index];
        }
    };
};

TEST(TestCaseName, TestName) {
    ArrayOfArrays aoa;

    aoa[3][5] = 5;

    std::cout << aoa[3][5] << std::endl;
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}