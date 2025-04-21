#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <sstream>
#include <iomanip>

const int MATRIX_SIZE = 3;
using Matrix3x3d = std::array<std::array<double, MATRIX_SIZE>, MATRIX_SIZE>;

struct Args
{
	std::string inputFile;
	std::string outputFile;
	bool isStdIn = false;
};

void PrintHelp()
{
	std::cout << "Use: Invert.exe [options] <input file> <output file>\n"
		<< "Options:\n"
		<< "  -h  Show this help message\n"
		<< "If no arguments are provided, input is read from stdin and output is printed to console.\n";
}

Args ParseArgs(int argc, char* argv[]) 
{
	Args result;
	if (argc == 1)
	{
		result.isStdIn = true;
		return result;
	}
	if ((argc == 2) && (std::string(argv[1]) == "-h"))
	{
		PrintHelp();
		throw std::runtime_error("");
	}
	if (argc != 3)
	{
		throw std::invalid_argument("");
	}

	result.inputFile = argv[1];
	result.outputFile = argv[2];

	return result;
}

Matrix3x3d ReadMatrix3x3(std::istream& input)
{
	Matrix3x3d matrix3x3;
	double number;
	std::string line;
	int numCount = 0; 
	size_t strCount = 0;
	while (std::getline(input, line))
	{
		if (strCount > MATRIX_SIZE - 1)
		{
			throw std::runtime_error("Invalid matrix format");
		}
		std::istringstream iss(line);

		numCount = 0;
		while (iss >> number)
		{
			if (numCount > MATRIX_SIZE - 1)
			{
				throw std::runtime_error("Invalid matrix format");
			}
			matrix3x3[strCount][numCount] = number;
			numCount++;
		}

		if (iss.fail() && !iss.eof())
		{
			throw std::runtime_error("Invalid matrix");
		}

		if (numCount != MATRIX_SIZE)
		{
			throw std::runtime_error("Invalid matrix format");
		}
		strCount++;
	}
	if (strCount != MATRIX_SIZE)
	{
		throw std::runtime_error("Invalid matrix format");
	}

	return matrix3x3;
}

double CalculateDeterminante(const Matrix3x3d& matrix)
{
	double determinant = 0;
	determinant += matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[0][2] * matrix[1][0] * matrix[2][1]
		- matrix[0][2] * matrix[1][1] * matrix[2][0]
		- matrix[0][1] * matrix[1][0] * matrix[2][2]
		- matrix[0][0] * matrix[1][2] * matrix[2][1];
	return determinant;
}

Matrix3x3d InvertMatrix3x3(const Matrix3x3d& matrix)
{
	double determinant = CalculateDeterminante(matrix);
	if (determinant == 0)
	{
		throw std::runtime_error("Non-invertible");
	}

	Matrix3x3d invertMatrix;
	invertMatrix[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) / determinant;
	invertMatrix[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) / determinant;
	invertMatrix[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) / determinant;

	invertMatrix[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) / determinant;
	invertMatrix[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) / determinant;
	invertMatrix[1][2] = (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]) / determinant;

	invertMatrix[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) / determinant;
	invertMatrix[2][1] = (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1]) / determinant;
	invertMatrix[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) / determinant;

	return invertMatrix;
}

void PrintMatrix(const Matrix3x3d& matrix, std::ostream& output)
{
	output << std::fixed << std::setprecision(3);
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			output << matrix[i][j];
			if (j != MATRIX_SIZE - 1)
			{
				output << "\t";
			}
		}
		output << "\n";
	}
}

void Invert(const Args& args)
{
	std::ifstream inputFile;
	std::ofstream outputFile;
	std::istream& input = (args.isStdIn ? std::cin : inputFile);
	std::ostream& output = (args.isStdIn ? std::cout : outputFile);

	if (!args.isStdIn)
	{
		inputFile.open(args.inputFile);
		if (!inputFile.is_open())
		{
			std::cerr << "Can`t open input file!";
			return;
		}
		outputFile.open(args.outputFile);
		if (!outputFile.is_open())
		{
			std::cerr << "Can`t open output file!";
			return;
		}
	}

	Matrix3x3d matrix = ReadMatrix3x3(input);
	Matrix3x3d invertMatrix = InvertMatrix3x3(matrix);
	PrintMatrix(invertMatrix, output);
}

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArgs(argc, argv);

		Invert(args);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what();
		return 1;
	}


	return 0;
}
