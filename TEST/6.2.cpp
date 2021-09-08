#include "pch.h"

template <typename T>
class Array
{
	T** data_;
	size_t size_;
public:

	/*
	 * ���������� ������ �� ����� ��������� �����������, � ����� ��������� �� ���������.
	 * ����� �� ������ ������� ������� �������� ������� � ������� ����� ������������, � ������� ����� ���� ����� ��� ��.
	 * ���� T **data  ������� � ���, ��� �� ������ �� ������ �������� ���� T,
	 * � ������ ���������� �� ��� T, ��� ������� operator= ���������.
	 * ������������� ����� ������� �������� ������� �� ���� ����� ���������� ����������� � ��������� ��������� �� ��� �����.
	 * ���� ��������� ������ �� ���, ��� � ������� ������� ���� explicit Array(size_t size = 0, const T& value = T()),
	 * � ����� �������� explicit Array(size_t size, const T& value = T()) � �������� �������� Array(), ���� ������� ������� �������� ��� ��������.
	 * � ���� � ���� ������� ����������� �� �������� ������� � �, �� ���������, ������� ����������� ��� ����������,
	 * ������� ����� ������������� � explicit Array(size_t size = 0, const T& value = T()),
	 * ���� � ���� ����� ��������� � ������������ ��� ���������� :).
	 */

	 /// <summary>
	 /// ����������� ������, ������� ����� �������
	 /// ��� ����������. ������ ��������� ������
	 /// Array.
	 /// </summary>
	Array() : data_(nullptr), size_(0)
	{
	}

	/// <summary>
	///  ����������� ������, ������� �������
	///  Array ������� size, ����������� ����������
	///  value ���� T. ���� � ������ ��� ������������
	///  �� ���������, �� ������ �������� ����� ������������
	///  ����������.
	/// </summary>
	/// <param name="size"></param>
	/// <param name="value"></param>
	explicit Array(size_t size, const T& value = T()) : size_(size), data_(new T*[size])
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] = new T(value);
	}


	/// <summary>
	/// ����������� �����������, ������� �������
	/// ����� ���������. ��� ���� T ��������
	/// ������������ �� ���������.
	/// </summary>
	/// <param name="array"></param>
	Array(const Array& array) : size_(array.size()), data_(new T*[size_])
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] = new T(&array[i]);
	}
	
	~Array()
	{
		delete[] data_;
	}
	//   ����������, ���� �� ��� ���������.
	//
	Array& operator=(const Array& array)
	{
		if (this != &array)
		{
			delete[] data_;
			size_ = array.size();
			data_ = new T*[size_];
			for (size_t i = 0; i < size_; ++i)
				data_[i] = new T(&array[i]);
		}
		return *this;
	}
	//   �������� ������������.
	//
	size_t size() const { return size_; }
	//   ���������� ������ ������� (���������� 
	//                              ���������).
	//
	T& operator[](size_t i) const
	{
		return *data_[i];
	}
	//   ��� ������ ��������� ������� �� �������.
};


TEST(ThemeSix, TestSixTwo)
{
	typedef Array<double> ArrayF;
	typedef Array<ArrayF> AArrayF;

	ArrayF a0(1, 3.14);
	std::cout << "a0 created" << std::endl;
	std::cout << a0[0] << std::endl << std::endl;

	AArrayF a(5, a0); // default constructor
	std::cout << "a created" << std::endl;
	std::cout << a[0][0] << std::endl << std::endl;

	AArrayF b(a); // copy constructor
	std::cout << "b created" << std::endl << std::endl;

	AArrayF c; // default constructor
	std::cout << "c created" << std::endl << std::endl;
	c = b; // assignment (calls copy constructor and swap)
	std::cout << "c changed" << std::endl << std::endl;
}