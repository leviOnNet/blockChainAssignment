#include "blockChain.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>

namespace blockChain
{
    using namespace providedFunctions;

    float **createBlock()
    {
        float **block = new float *[blockSize];
        for (int i = 0; i < blockSize; ++i)
            block[i] = NULL;
        return block;
    }

    void destroy(float **&block)
    {
        while (block != NULL)
        {
            for (int i = 0; i < blockSize - 1; ++i)
            {
                delete block[i];
                block[i] = NULL;
            }
            float **next = convert(block[blockSize - 1]);
            delete[] block;
            block = next;
        }
    }

    bool isEmpty(float **&block)
    {
        return numberOfFloats(block) == 0;
    }

    int numberOfBlocks(float **block)
    {
        int count = 0;
        while (block != NULL)
        {
            count++;
            block = convert(block[blockSize - 1]);
        }
        return count;
    }

    int numberOfFloats(float **block)
    {
        int count = 0;
        while (block != NULL)
        {
            for (int i = 0; i < blockSize - 1; ++i)
                if (block[i] != NULL)
                    count++;
            block = convert(block[blockSize - 1]);
        }
        return count;
    }

    int maxPossibleFloats(float **block)
    {
        return numberOfBlocks(block) * (blockSize - 1);
    }

    int insert(float **&block, const float value)
    {
        if (block == NULL)
        {
            block = createBlock();
            block[0] = new float(value);
            return 1;
        }

        float **curr = block;
        while (curr != NULL)
        {
            for (int i = 0; i < blockSize - 1; ++i)
            {
                if (curr[i] == NULL)
                {
                    curr[i] = new float(value);
                    return 1;
                }
            }

            float **next = convert(curr[blockSize - 1]);
            if (next == NULL)
            {
                next = createBlock();
                curr[blockSize - 1] = convert(next);
            }
            curr = next;
        }

        return 0;
    }

    int remove(float **&block, const float value)
    {
        int removed = 0;
        float **curr = block;

        while (curr != NULL)
        {
            for (int i = 0; i < blockSize - 1; ++i)
            {
                if (curr[i] != NULL && *(curr[i]) == value)
                {
                    delete curr[i];
                    curr[i] = NULL;
                    removed++;
                }
            }
            curr = convert(curr[blockSize - 1]);
        }

        return removed;
    }

    bool search(float **block, const float value)
    {
        while (block != NULL)
        {
            for (int i = 0; i < blockSize - 1; ++i)
                if (block[i] != NULL && *(block[i]) == value)
                    return true;

            block = convert(block[blockSize - 1]);
        }
        return false;
    }

    float *get(float **block, int position)
    {
        int index = 0;
        while (block != NULL)
        {
            for (int i = 0; i < blockSize - 1; ++i)
            {
                if (block[i] != NULL)
                {
                    if (index == position)
                        return block[i];
                    index++;
                }
            }
            block = convert(block[blockSize - 1]);
        }
        return NULL;
    }

    float *toArray(float **block)
    {
        int count = numberOfFloats(block);
        float *arr = new float[count];
        int index = 0;

        while (block != NULL)
        {
            for (int i = 0; i < blockSize - 1; ++i)
            {
                if (block[i] != NULL)
                    arr[index++] = *(block[i]);
            }
            block = convert(block[blockSize - 1]);
        }
        return arr;
    }

    void sort(float **block)
{
    int n = numberOfFloats(block);
    float *arr = toArray(block);
    std::sort(arr, arr + n);

    // Clear all existing float* elements, but not the block structure
    float **curr = block;
    while (curr != NULL)
    {
        for (int i = 0; i < blockSize - 1; ++i)
        {
            delete curr[i];
            curr[i] = NULL;
        }
        curr = convert(curr[blockSize - 1]);
    }

    // Reinsert sorted values
    for (int i = 0; i < n; ++i)
    {
        insert(block, arr[i]);
    }

    delete[] arr;
}


    float total(float **block)
    {
        float sum = 0;
        while (block != NULL)
        {
            for (int i = 0; i < blockSize - 1; ++i)
                if (block[i] != NULL)
                    sum += *(block[i]);
            block = convert(block[blockSize - 1]);
        }
        return sum;
    }

    float average(float **block)
    {
        int n = numberOfFloats(block);
        return n > 0 ? total(block) / n : 0.0f;
    }

    void adjust(float **block, float value)
    {
        while (block != NULL)
        {
            for (int i = 0; i < blockSize - 1; ++i)
                if (block[i] != NULL)
                    *(block[i]) += value;
            block = convert(block[blockSize - 1]);
        }
    }

    void repack(float **&block)
    {
        int count = numberOfFloats(block);
        float *arr = toArray(block);

        destroy(block);
        block = createBlock();
        for (int i = 0; i < count; ++i)
            insert(block, arr[i]);

        delete[] arr;
    }

    float **loadFromFile(std::string csvFileName)
{
    std::ifstream file(csvFileName.c_str());  // C++98 fix
    if (!file.is_open())
        return NULL;

    float **block = createBlock();
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ','))
        {
            std::stringstream valueStream(token);
            float value;
            if (valueStream >> value)
                insert(block, value);
        }
    }
    return block;
}

    // Optional: For debugging
    void debugPrint(float** block)
    {
        int blockNum = 0;
        while (block != NULL)
        {
            std::cout << "Block " << blockNum++ << ": ";
            for (int i = 0; i < blockSize - 1; ++i)
            {
                if (block[i] != NULL)
                    std::cout << *(block[i]) << " ";
                else
                    std::cout << "[null] ";
            }
            std::cout << "\n";
            block = convert(block[blockSize - 1]);
        }
    }
}
