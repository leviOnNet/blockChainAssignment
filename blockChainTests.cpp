
#include <iostream>
#include "blockChain.h"

using namespace std;
using namespace blockChain;

void printArray(float* arr, int size) {
    for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    float **block = nullptr;

    // Test insertion
    insert(block, 3.0f);
    insert(block, 1.0f);
    insert(block, 4.0f);
    insert(block, 2.0f);
    insert(block, 5.0f);
    insert(block, 6.0f);  // Should create a new block

    // Test toArray
    float *array = toArray(block);
    int size = numberOfFloats(block);
    cout << "Array after insertion: ";
    printArray(array, size);
    delete[] array;

    // Test search
    cout << "Searching for 4.0: " << (search(block, 4.0f) ? "Found" : "Not Found") << endl;
    cout << "Searching for 9.0: " << (search(block, 9.0f) ? "Found" : "Not Found") << endl;

    // Test sort
    sort(block);
    array = toArray(block);
    cout << "Sorted array: ";
    printArray(array, size);
    delete[] array;

    // Test remove
    remove(block, 3.0f);
    array = toArray(block);
    size = numberOfFloats(block);
    cout << "Array after removing 3.0: ";
    printArray(array, size);
    delete[] array;

    // Test repack
    repack(block);
    array = toArray(block);
    cout << "Array after repack: ";
    printArray(array, size);
    delete[] array;

    // Test adjust
    adjust(block, 1.0f);
    array = toArray(block);
    cout << "Array after adjusting by +1.0: ";
    printArray(array, size);
    delete[] array;

    // Test stats
    cout << "Total: " << total(block) << endl;
    cout << "Average: " << average(block) << endl;
    cout << "Number of floats: " << numberOfFloats(block) << endl;
    cout << "Number of blocks: " << numberOfBlocks(block) << endl;
    cout << "Max possible floats: " << maxPossibleFloats(block) << endl;

    // Test destroy
    destroy(block);
    cout << "After destroy, is empty? " << (isEmpty(block) ? "Yes" : "No") << endl;

    return 0;
}
