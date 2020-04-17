#include <iostream>
#include <vector>
#include <conio.h>

using namespace std;
vector<double>
input_numbers (size_t count)
{
    vector <double> result(count);
    for (int i=0; i<count; i++)
    {
        cin>>result[i];
    }
return result;
}
void find_minmax(const vector <double> &numbers, double &max, double &min)
{
    max=numbers[0];
    min=numbers[0];
    for(size_t a:numbers)
    {
        if(a<min)
            min=a;
        if(a>max)
            max=a;
    }
}
vector<size_t>
make_histogram(const vector <double> &numbers,double &max, double &min, size_t &bin_count)
{
    vector<size_t>bins(bin_count,0); /* массив из индексов корзин */
    for(double x : numbers) /* мы каждому x присваиваем последовательно каждый элемент массива "numbers" */
    {
        size_t bin_index=(size_t)((x-min)*bin_count/(max-min));
        if (bin_index==bin_count) /* индекс корзины "bin_index"*/
        {
            bin_index=bin_index-1; /* нумирация идет с 0*/
        }
        bins[bin_index]++;
    }
    return bins;
}
void show_histogram_text(vector<size_t> bins)
{
    const size_t MAX_WIDTH=80;
    const size_t MAX_ASTERISK=76;
    unsigned max_count=0;
    for (size_t b : bins) /* мы присваиваем значение количества элементов */
    {
        if(max_count<b)
            max_count=b; /* здесь мы ищем максимальное количество элементов в массиве*/
    }
    for(size_t bin: bins)
    {
        if(bin<100)
        {
            cout<<" ";
            if (bin<10)
            {
                cout<< " ";
            }
        }
        cout<<bin<<"|";
        size_t height=76*1.0;
            if(max_count>MAX_ASTERISK) /* Если количество будет больше 76, то уменьшаем масштаб*/
                height=MAX_ASTERISK*((static_cast<double>(bin))/max_count); /* это для того,чтобы было дробное число , получаем,
используя "static_cast<double>"*/
        else
        {
            height=bin;
        }
        for(int i=0; i<height; i++)
        {
            cout<<"*";
        }
        cerr<<"\n";
    }
}
void
svg_text(double left, double baseline, string text) {
    cout << "<text x='20' y='35'>anything you want</text>";
}
void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}
void show_histogram_svg(const vector<size_t>& bins)
 {
    svg_begin(400, 300);
    svg_text(20, 20, to_string(bins[0]));
    svg_end();
}
int main()
{
    double left;
    double baseline;
    string text;
    size_t number_count, bin_count;
    double max=0, min=0;
    cerr<<"number_count=";
    cin>>number_count;
    cerr<<"Enter number count: "<<"\n";
    const auto numbers = input_numbers(number_count);/* массив из количества элементов "number_count"*/
    cerr<<"bin_count=";
    cin>> bin_count;
    find_minmax (numbers,max,min);
    const auto bins=make_histogram(numbers,max,min,bin_count);
    show_histogram_svg(bins);
    return 0;
}
