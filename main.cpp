#include <iostream>
#include <vector>
#include "histogram.h"
#include "lab03-test/svg.h"
using namespace std;

const vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}





int
main()
{
    // Ввод данных
    cerr << "Enter number count: ";

    size_t number_count;
    cin >> number_count;
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    // Обработка данных
    const auto bins = make_histogram(numbers, bin_count);

    // Вывод данных
    show_histogram_svg_7var(bins);

    return 0;
}
