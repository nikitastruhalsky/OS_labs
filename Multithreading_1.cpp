#include <iostream>
#include <vector>
#include <windows.h>
#include <mutex>
#include <ctime>
#include <map>


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

DWORD WINAPI multiply_blocks(LPVOID params)
{
	ThreadParams p = *(ThreadParams*)params;
	for (int i = p.start1; i < p.start1 + p.count; i++)
	{
		for (int j = p.start2; j < p.start2 + p.count; j++)
		{
			int sum = 0;
			for (int k = 0; k < p.count; k++)
			{
				sum += p._first[i][p.mul_st + k] * p._second[p.mul_st + k][j];
			}
			HANDLE mutex = CreateMutex(NULL, TRUE, NULL);
			p._third[i][j] += sum;
			ReleaseMutex(mutex);
		}
	}
	return 0;
}

std::vector<std::vector<int>> MultMatrixUsingThreads(std::vector<std::vector<int>>& first_matrix,
							std::vector<std::vector<int>>& second_matrix,
							int number_of_blocks, std::vector<std::vector<int>>& result_matrix)
{
	int block_size = first_matrix.size() / number_of_blocks;
	std::vector<HANDLE> all_threads;
	for (int i = 0; i < first_matrix.size(); i += block_size)
	{
		for (int j = 0; j < first_matrix.size(); j += block_size)
		{
			for (int k = 0; k < first_matrix.size(); k += block_size)
			{
				ThreadParams* p = new ThreadParams(first_matrix, second_matrix, result_matrix, i, j, k, block_size);
				HANDLE thread = CreateThread(nullptr, 0, multiply_blocks, p, 0, nullptr);
				all_threads.push_back(thread);
			}
		}
	}

	WaitForMultipleObjects(all_threads.size(), all_threads.data(), TRUE, INFINITE);

	std::cout << "Number of threads: " << all_threads.size() << std::endl;

	return result_matrix;
}

int main()
{
	int matrixSize;
	std::cout << "Insert matrix size:" << std::endl;
	std::cin >> matrixSize;

	std::vector<std::vector<int>> A, B, C;

	A = CreateMatrix(matrixSize);
	B = CreateMatrix(matrixSize);
	C = CreateNullMatrix(matrixSize);

	int a = clock();

	for (int i = 1; i <= matrixSize; ++i)
	{
		if (matrixSize % i == 0)
		{
			std::cout << "Number of blocks: " << i << std::endl << "Time: ";
			a = clock();
			C = MultMatrixUsingThreads(A, B, i, C);
			std::cout << clock() - a << "ms" << std::endl << std::endl;
		}
	}

	return 0;
}