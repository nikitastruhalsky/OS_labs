#include <iostream>
#include <vector>
#include <mutex>
#include <thread>


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


std::mutex mutex;


void MultBlocks(std::vector<std::vector<int>> &first_matrix,
	std::vector<std::vector<int>> &second_matrix,
	int start_index_row, int start_index_column, int hz,
	int block_size, std::vector<std::vector<int>> &result_block)
{
	for (int i = start_index_row; i < start_index_row + block_size; i++)
	{
		for (int j = start_index_column; j < start_index_column + block_size; j++)
		{
			int current_element = 0;
			for (int k = 0; k < block_size; k++)
			{
				current_element += first_matrix[i][hz + k] * second_matrix[hz + k][j];
			}

			mutex.lock();
			result_block[i][j] += current_element;
			mutex.unlock();
		}
	}
}


void MultMatrixUsingThreads(std::vector<std::vector<int>> &first_matrix,
	std::vector<std::vector<int>> &second_matrix,
	int number_of_blocks, std::vector<std::vector<int>> &result_matrix)
{
	int block_size = first_matrix.size() / number_of_blocks;
	std::vector<std::thread> all_threads;
	for (int i = 0; i < first_matrix.size(); i += block_size)
	{
		for (int j = 0; j < first_matrix.size(); j += block_size)
		{
			for (int k = 0; k < first_matrix.size(); k += block_size)
			{
				std::thread thread(MultBlocks, std::ref(first_matrix), std::ref(second_matrix), i, j, k, block_size, std::ref(result_matrix));
				all_threads.push_back(std::move(thread));
			}
		}
	}

	for (int i = 0; i < all_threads.size(); i++)
	{
		all_threads[i].join();
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
		MultBlocks(matrix_1, matrix_2, 0, 0, 0, matrix_1.size(), matrix_final_1);
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
