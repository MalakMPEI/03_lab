#include <iostream>
#include <vector>

using namespace std;


const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;


vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    max=numbers[0];
    min=numbers[0];

    for(double elem:numbers)
    {
        if (elem<min)
            min=elem;
        if (elem>max)

            max=elem;
    }
}

vector<size_t> make_histogram(vector<double> numbers, size_t bin_count, double max, double min,size_t& bins_max)
{
    size_t number_count=numbers.size();
    vector<size_t> bins(bin_count);
    bins_max = 0;
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < number_count; i++)
    {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        // ���� �� numbers �� ����������!

        if (!found)
        {
            bins[bin_count - 1]++;
        }

    } // ����� ����� �� numbers

    for (size_t i=0; i<bin_count; i++)
        {
             if (bins[i] > bins_max) bins_max = bins[i];
        }

    return bins;
}


void show_histogram_text(vector<size_t> bins, size_t bins_max)
{
    size_t bin_count = bins.size();
    size_t height;
    for (size_t i=0; i<bin_count; i++)
    {
        if (bins_max > MAX_ASTERISK)

            height = MAX_ASTERISK*(static_cast<double>(bins[i]) / bins_max);
       else height = bins[i];
       for (size_t j=0; j<(MAX_ASTERISK-height); j++)
        {
            cout<<" ";
        }
    for(size_t j=0; j < height; j++)
        {
            cout<<"*";
        }
        cout<<"|";
        if (bins[i]<100) cout<<" ";
        if (bins[i]<10) cout<<" ";
        cout<<bins [i];


        cout<<endl;

    }
}



int main()
{

    size_t number_count;
    size_t bin_count;

    cerr << "Enter numbers count: ";
    cin >> number_count;

    const auto numbers = input_numbers(number_count);
    double max;
    double min;
    find_minmax(numbers, min, max);

    cerr << "Enter bin count: ";
    cin >> bin_count;

    size_t bins_max;
    const auto bins = make_histogram(numbers,bin_count,max,min,bins_max);
    show_histogram_text(bins,bins_max);

    return 0;
}
