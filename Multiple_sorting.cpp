#include <iostream>
#include "sort.h"

#include <vector>
#include <utility>
using std::make_pair;
using std::pair;


using std::cout;
using std::vector;
using std::endl;


int insertionSort(Container & arr, Iter start, Iter end)
{
    int comparisons = 0;
    for (Iter i = start+1; i < end; i++)
    {
        Val cur = arr[i];
        Iter j = i - 1;
        while (j >= start && arr[j] > cur)
        {
            arr[j + 1] = arr[j];
            j--;
            comparisons++;
        }
        arr[j + 1] = cur;
        comparisons++; // the last comparison takes place when cur is greater than arr[j]
    }
    return comparisons;
}


// mrege sort

void merge(Container & arr1, Container & arr2, Iter start, Iter mid, Iter midplus1, Iter end, int & compare)
{
    int i = start;
    int j = midplus1;
	int k = start;

	//arr2 = Container(arr1.size(), 0);
	//Container arr2(arr1.size(), 0);

    while (i <= mid && j <= end)
    {
        compare++;
        if (arr1[i] < arr1[j]) {
            arr2[k++] = arr1[i++];
        }
        else {
            arr2[k++] = arr1[j++];
        }
    }
    while (i <= mid)
    {
        arr2[k++] = arr1[i++];
    }
    while (j <= end)
    {
        arr2[k++] = arr1[j++];
    }


    for (Iter count = start; count < k; count++)
    {
        arr1[count] = arr2[count];
    }
}


int mergesort(Container & arr1, Container & arr2, Iter first, Iter last, int & count)
{
	if (first < last)
	{
		auto mid = (first + last) / 2;
		mergesort(arr1, arr2, first, mid, count);
		mergesort(arr1, arr2, mid + 1, last, count);
		merge(arr1, arr2, first, mid, mid + 1, last, count);
	}
	return 0;
}


int mergeSort(Container & arr, Iter start, Iter end)
{
    end --;
    int comparisons = 0;
    Container sort(arr.size(), 0);
    if (start == end)
    {
        return comparisons;
    }
    else
    {
        mergesort(arr, sort, start, end, comparisons);
		cout << "comparison = " << comparisons << endl;
        return comparisons;
    }

}
// quick sort
void quickSortRec( Container& a, Iter l, Iter r, int & comparison) {
   int pivot, i, j, t;

   if (l < r)
   {
	   pivot = l;
	   i = l;
	   j = r;

	   while (i < j)
	   {
		   while (a[i] <= a[pivot] && i < r)
		   {
			   i++;
			   comparison++;
		   }
		   while (a[j] > a[pivot])
		   {
			   j--;
			   comparison++;
		   }

		   if (i < j)
		   {
			   t = a[i];
			   a[i] = a[j];
			   a[j] = t;
		   }

	   }

	   t = a[pivot];
	   a[pivot] = a[j];
	   a[j] = t;

	   quickSortRec(a, l, j - 1, comparison);
	   quickSortRec(a, j + 1, r, comparison);

   }

   return;
}


int quickSort(Container & arr, Iter start, Iter end)
{

	if( start < end )
	{
		int comparison = 0;
   		// divide and conquer
		quickSortRec(arr, start, end - 1, comparison);
		return comparison;
	}
   return 0;
}

int shellSort(Container & arr, Iter start, Iter end)
{
//source: http://www.cplusplus.com/forum/general/123961/
    int n = end - start;
    int gap, i, j, temp;

    int comparison = 0;

    for (gap = n/2; gap > 0; gap /= 2)
    {
        for (i = start+gap; i < end; i++)
        {
        	comparison++;
            for (j= i-gap; j>=start && arr[j]>arr[j+gap]; j-=gap)
            {

            	comparison ++;

                temp = arr[j];

                arr[j] = arr[j+gap];

                arr[j+gap] = temp;
            }
        }
    }
    return comparison;
}

