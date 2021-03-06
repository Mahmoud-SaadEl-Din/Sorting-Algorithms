// Algo_assignment1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <time.h>
#include <vector>
#include<fstream>
#include<string>
using namespace std;

// Sorting Algorithms
void selection_sort(vector<int> &vector, int size);
void insertion_sort(vector<int> &vector, int size);
void merge_sort(vector<int> &vector, int left,int right);
void quick_sort(vector<int> &vector, int low,int high);
void hybrid_sort();
// print the vector 
void print_array(vector<int> vector , int size);
// check if the data sorted correctly or not
void check(vector<int> vector);
// write the output in files
void write_output();
//read the input from files
void read_input();
// get time in seconds before excute
void get_time_before_sort();
// get time in seconds after execute
void get_time_after_sort();

vector<int> my_vector; // where the data will be stored

ifstream my_read_file; //  stream to read the input
ofstream my_out_file; // stream to write the output
ofstream my_running_file; //  stream time running file
string input_file; // name of the input
string output_file; // name of the output sorted data
string running_file; // name of the output time text
string sorted;
time_t time1; //  to get the times in seconds
time_t time2; // to get the time in seconds
int algorithm_choise; // user input to choose the Algo

int main(int argc, char** argv)
{
	 algorithm_choise = stoi(argv[1]);
	 input_file = argv[2];
	 output_file = argv[3];
	 running_file = argv[4];
	 read_input();
	 get_time_before_sort();
	switch (algorithm_choise)
	{
	case 0: // selection sort
		selection_sort(my_vector, my_vector.size());
		break;
	case 1: // insertion sort
		insertion_sort(my_vector, my_vector.size());
		break;
	case 2: // merge sort
		merge_sort(my_vector, 0, my_vector.size() - 1);
		break;
	case 3: // quick sort
		quick_sort(my_vector, 0, my_vector.size() - 1);
		break;
	case 4: // hybrid sort
		hybrid_sort();
		break;
	default:
		break;
	}
	get_time_after_sort();
	check(my_vector);
	write_output();
    return 0;
}

void selection_sort(vector<int> &vector, int size)
{
	int min_index;
	for (int i = 0; i < size - 1; ++i) {
		min_index = i;
		for (int j = i + 1; j < size; ++j) {
			if (vector.at(min_index) > vector.at(j)) min_index = j;
		}

		if (min_index != i) {
			int temp = vector[min_index];
			vector[min_index] = vector[i];
			vector[i] = temp;
		}
	}
}

void insertion_sort(vector<int> &vector, int size)
{
	for (int i = 1; i < size; ++i) {
		int inserted_value = vector[i]; // the value we are trying to insert it in the correct place
		int j = i - 1;
		while (j >= 0 && vector[j] > inserted_value) {
			vector[j + 1] = vector[j];
			--j;
		}
		vector[j+1] = inserted_value;
	}
}

void merge(vector<int> &vector_data, int left, int middle, int right) {
	 int part1 = middle - left + 1;
	 int part2 = right - middle;

	vector<int> L, R; // creat two parts to hold the values which will be compared and sorted

	for (int i = 0; i < part1; ++i) {
		L.push_back(vector_data[left + i]);
	}
	for (int i = 0; i < part2; i++)
	{
		R.push_back(vector_data[middle + 1 + i]);
	}

	int i = 0; // iterator for the first part
	int j = 0;// iterator for the second part
	int k = left; // for the main vector

	while (i < part1 && j < part2) // comparing between both parts. choose the minimum to be inserted first
	{
		if (L[i] <= R[j])
		{
			vector_data[k] = L[i];
			i++;
		}
		else
		{
			vector_data[k] = R[j];
			j++;
		}
		k++;
	}

	// 2 whiles loops are better that.. to compare both of sizes and if they are not equal,
	// check while is the greater and copy the remaining items in the main vector

    // if still have elements in part1 , add it to the main vector
	while (i < part1)
	{
		vector_data[k] = L[i];
		i++;
		k++;
	}
	// if still have elements in part2 , add it to the main vector
	while (j < part2)
	{
		vector_data[k] = R[j];
		j++;
		k++;
	}
}

void merge_sort(vector<int> &vector, int left,int right)
{
	if (left < right)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int middle = left + (right - left) / 2;

		// Sort first and second halves 
		merge_sort(vector, left, middle);
		merge_sort(vector, middle+1, right);

		merge(vector, left, middle, right);
	}
}

int partition(vector<int> &vector, int low, int high)
{
	int pivot = vector[high];    // pivot 
	int i = low-1;  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or 
		// equal to pivot 
		if (vector[j] <= pivot)
		{
			i++;    // increment index of smaller element 
			//swap
			int temp = vector[i];
			vector[i] = vector[j];
			vector[j] = temp;
		}
	}
	//swap
	int temp = vector[i+1];
	vector[i+1] = vector[high];
	vector[high] = temp;
	return i+1 ;
}

void quick_sort(vector<int> &vector, int low, int high)
{
	if (low < high)
	{
		
		int part = partition(vector,low, high);

		
		quick_sort(vector, low, part - 1);
		quick_sort(vector, part + 1, high);
	}
}

void hybrid_sort() {
	if (my_vector.size() < 50000) {
		merge_sort(my_vector, 0, my_vector.size() - 1);
	}
	else {
		quick_sort(my_vector, 0, my_vector.size() - 1);
	}
}

void print_array(vector<int> vector, int size)
{
	int i;
	for (i = 0; i < size; i++)
		cout << vector.at(i) << " - " ;
	cout << endl;
}

void check(vector<int> vector) {
	for (int i = 1; i < vector.size(); ++i) {
		if (vector[i] - vector[i - 1] < 0) cout << "error at " << i << endl;
	}
	cout << "done checking correctly" << endl;
}

void write_output() {
	my_out_file.open(output_file);
	my_running_file.open(running_file, ios_base::app);
	my_running_file << " #" << my_vector.size() << "_" << "unkown_sorted_or_not " << " : " << time2 - time1 << endl;
	for (int i = 0; i < my_vector.size(); ++i)
		my_out_file << my_vector[i] << "\n";
	my_out_file.close();
	my_running_file.close();
}

void read_input() {
	my_read_file.open(input_file);
	if (my_read_file.is_open()) {
		cout << "File opened" << endl;
		string value;
		while (getline(my_read_file, value)) {
			if (value != "")
				my_vector.push_back(stoi(value));
		}
		my_read_file.close();
	}
}

void get_time_before_sort(){ time(&time1); }

void get_time_after_sort(){ time(&time2); }