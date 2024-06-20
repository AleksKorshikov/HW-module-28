#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <algorithm>

void merge(std::vector<int>& numbers, size_t left, size_t midpoint, size_t right) {
    size_t i = left;
    size_t j = midpoint + 1;

    if (numbers[midpoint] <= numbers[j]) {
        return;
    }

    while (i <= midpoint && j <= right) {
        if (numbers[i] <= numbers[j]) {
            i++;
        }
        else {
            int temp = numbers[j];
            for (size_t k = j; k > i; k--) {
                numbers[k] = numbers[k - 1];
            }
            numbers[i] = temp;

            midpoint++;
            i++;
            j++;
        }
    }
}

void mergeSort(std::vector<int>& numbers, size_t left, size_t right) {
    if (left >= right) {
        return;
    }

    size_t midpoint = left + (right - left) / 2;

    std::future<void> future;

    if (right - left < 100) {
        mergeSort(numbers, left, midpoint);
        mergeSort(numbers, midpoint + 1, right);
    }
    else {
        future = std::async(std::launch::async, mergeSort, std::ref(numbers), left, midpoint);
        mergeSort(numbers, midpoint + 1, right);
        future.get();
    }

    merge(numbers, left, midpoint, right);
}

int main() {
    std::vector<int> numbers = { 38, 27, 43, 3, 9, 82, 10 };

    mergeSort(numbers, 0, numbers.size() - 1);

    std::cout << "Sorted array: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}