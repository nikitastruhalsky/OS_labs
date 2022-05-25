#include <iostream>
#include <vector>
#include <pthread.h>
#include <ctime>


struct ThreadParams
{
    std::vector<std::vector<int>>& _first;
    std::vector<std::vector<int>>& _second;
    std::vector<std::vector<int>>& _third;
    int start1, start2, mul_st, count;
    ThreadParams(std::vector<std::vector<int>>& a,
                 std::vector<std::vector<int>>& b,
                 std::vector<std::vector<int>>& d,
                 int i, int j, int k, int count) :
            _first(a), _second(b), _third(d), start1(i), start2(j), mul_st(k), count(count) {}
};

std::vector<std::vector<int>> CreateMatrix(int size)
{
    std::vector<std::vector<int>> newMatrix(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            newMatrix[i].push_back(rand() % 10);
        }
    }

    return newMatrix;
}

std::vector<std::vector<int>> CreateNullMatrix(int size)
{
    std::vector<std::vector<int>> newMatrix(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            newMatrix[i].push_back(0);
        }
    }

    return newMatrix;
}


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void* MultBlocks(void* params)
{
    ThreadParams threadParams = *(ThreadParams*)params;
    for (int i = threadParams.start1; i < threadParams.start1 + threadParams.count; i++)
    {
        for (int j = threadParams.start2; j < threadParams.start2 + threadParams.count; j++)
        {
            int current_element = 0;
            for (int k = 0; k < threadParams.count; k++)
            {
                current_element += threadParams._first[i][threadParams.mul_st + k] * threadParams._second[threadParams.mul_st + k][j];
            }

            pthread_mutex_lock(&mutex);
            threadParams._third[i][j] += current_element;
            pthread_mutex_unlock(&mutex);
        }
    }

    return nullptr;
}


void MultMatrixUsingThreads(std::vector<std::vector<int>> &first_matrix,
                            std::vector<std::vector<int>> &second_matrix,
                            int number_of_blocks, std::vector<std::vector<int>> &result_matrix)
{
    int block_size = first_matrix.size() / number_of_blocks;
    std::vector<pthread_t> all_threads;
    for (int i = 0; i < first_matrix.size(); i += block_size)
    {
        for (int j = 0; j < first_matrix.size(); j += block_size)
        {
            for (int k = 0; k < first_matrix.size(); k += block_size)
            {
                ThreadParams* params = new ThreadParams(first_matrix, second_matrix, result_matrix, i, j, k, block_size);
                pthread_t pthr;
                pthread_create(&pthr, nullptr, &MultBlocks, (void*)params);
                all_threads.push_back(pthr);
            }
        }
    }

    for (int i = 0; i < all_threads.size(); i++)
    {
        pthread_join(all_threads[i], nullptr);
    }

    std::cout << "Number of threads: " << all_threads.size() << std::endl;
}




int main()
{
    int matrix_size[] = { 3, 5, 8, 10, 15};

    for (int j = 0; j < 5; j++)
    {
        std::cout << "MATRIX SIZE: " << matrix_size[j] << std::endl;
        std::vector<std::vector<int>> matrix_1 = CreateMatrix(matrix_size[j]);
        std::vector<std::vector<int>> matrix_2 = CreateMatrix(matrix_size[j]);

        std::vector<std::vector<int>> matrix_final_1 = CreateNullMatrix(matrix_size[j]);
        int a = clock();
        MultBlocks;
        int b = clock();
        std::cout << "Simple matrix multiplication time: " << b - a << std::endl;

        std::cout << std::endl;

        for (int i = 1; i <= matrix_size[j]; i++)
        {
            if (matrix_size[j] % i == 0)
            {
                std::vector<std::vector<int>> matrix_final_2 = CreateNullMatrix(matrix_size[j]);
                std::cout << i << " blocks" << std::endl;
                a = clock();
                MultMatrixUsingThreads(matrix_1, matrix_2, i, matrix_final_2);
                b = clock();
                std::cout << "Time: " << b - a << std::endl;
                std::cout << std::endl;
            }
        }

        std::cout << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
