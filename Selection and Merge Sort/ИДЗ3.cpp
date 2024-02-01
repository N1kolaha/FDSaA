#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <chrono>
//первый ключ фио второй номер телефона
//оба ключа сортировать по убыванию, первая сорт простой выбор, вторая сортировка простое слияние рекурсивная реализация
struct Key {
    std::string name;
    std::string familia;
    std::string otchestvo;
    long long int number;
    int stroke;
};

void input(std::vector<Key>& vector,  std::ifstream& file) {
    Key cur;
    std::string str;
    int current=1;
    //std::getline(file, str);
    while (!file.eof()) {
        std::getline(file, str, ' ');
        if (str != "") {
            cur.name = str;
            std::getline(file, str, ' ');
            cur.familia = str;
            std::getline(file, str, ' ');
            cur.otchestvo = str;


            std::getline(file, str, '\n');
            cur.number = std::stoll(str);
            cur.stroke = current;
            vector.push_back(cur);
            current++;


        }
    }

}


void output(std::vector<Key>& vector, std::ofstream& file) {


    for (size_t i = 0; i < vector.size(); ++i) {
        file << vector[i].name << " " << vector[i].familia << " " << vector[i].otchestvo << "  " << vector[i].number << "  " << vector[i].stroke << std::endl;
    }
}

void selectionsort(std::vector<Key>& arr, int start) {
    Key c;
    long long int n;
    if (start < arr.size() - 1) {
        int max = start;
        for (int i = start + 1; i < arr.size(); ++i) {
            if ((arr[i].name > arr[max].name) ||
                ((arr[i].name == arr[max].name) && (arr[i].familia > arr[max].familia)) ||
                ((arr[i].name == arr[max].name) && (arr[i].familia == arr[max].familia) && (arr[i].otchestvo > arr[max].otchestvo)) ||
                ((arr[i].name == arr[max].name) && (arr[i].familia == arr[max].familia) && (arr[i].otchestvo == arr[max].otchestvo) && (arr[i].number > arr[max].number))) {
                max = i;
            }
        }
        c = arr[start];
        arr[start] = arr[max];
        arr[max] = c;
        selectionsort(arr, start + 1);
    }
}

void SelectionSortirovka(std::vector<Key>& arr, int start, std::ofstream& file) {
    auto begin = std::chrono::high_resolution_clock::now();
    selectionsort(arr, start);
    auto end = std::chrono::high_resolution_clock::now();
    output(arr, file);
    
    file << "\nSelection sort time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;
}





void merge(std::vector<Key>& vector, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<Key> leftArray(n1);
    std::vector<Key> rightArray(n2);

    for (int i = 0; i < n1; ++i)
        leftArray[i] = vector[left + i];
    for (int j = 0; j < n2; ++j)
        rightArray[j] = vector[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if ((leftArray[i].name >= rightArray[j].name) ||
            ((leftArray[i].name == rightArray[j].name) && (leftArray[i].familia >= rightArray[j].familia)) ||
            ((leftArray[i].name == rightArray[j].name) && (leftArray[i].familia == rightArray[j].familia) && (leftArray[i].otchestvo >= rightArray[j].otchestvo)) ||
            ((leftArray[i].name == rightArray[j].name) && (leftArray[i].familia == rightArray[j].familia) && (leftArray[i].otchestvo == rightArray[j].otchestvo) && (leftArray[i].number >= rightArray[j].number))) {
            vector[k] = leftArray[i];
            ++i;
        }
        else {
            vector[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        vector[k] = leftArray[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        vector[k] = rightArray[j];
        ++j;
        ++k;
    }
}

void MergeSort(std::vector<Key>& vector, int left, int right, std::ofstream& file) {
 
    if (left < right) {
        int middle = (right + left) / 2;

        MergeSort(vector, left, middle,file);
        MergeSort(vector, middle + 1, right,file);

        merge(vector, left, middle, right);
    }
    
   
}
void MergeSortirovka(std::vector<Key>& vector, int left, int right, std::ofstream& file) {

    auto  begin = std::chrono::high_resolution_clock::now();

    MergeSort(vector, left, right, file);
    auto end = std::chrono::high_resolution_clock::now();
    output(vector, file);

    file << "\nMerge sort time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;

}


int main() {
    setlocale(LC_ALL, "");
    std::ifstream iFile("input.txt");
    std::ofstream oFile("output.txt");
    std::ofstream oFile1("output1.txt");
    std::vector<Key> Array;
    std::vector<Key> Array1;
    input(Array,iFile);
    Array1 = Array;
    iFile.close();
    SelectionSortirovka(Array,0,oFile);
    MergeSortirovka(Array, 0, Array.size() - 1,oFile1);
    
    oFile.close();
    oFile1.close();

  
    
    return 0;
}
