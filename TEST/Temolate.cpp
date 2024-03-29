#include "pch.h"

template<class T>
class Array
{
	T* data_;
public:
	
};

/// <summary>
/// ����������� ��������� �� ������
/// </summary>
template<>
class Array<bool>
{
	size_t size_;
	int* data_; // � ������� int !!!
public:
	static int const INTBITS = 8 * sizeof(int); // ������� ������� ����� ������� � ��� = 32
	/// <summary>
	///	����������� ������, ������� �������� ���-�� bool, ����� �������� ������ � ���� int !!!
	///	����� ������ ��� ��� ��������� ������ ������������ ��������� � ������������� 1 ��� ������
	///	��� ��� �� ������ ������� �������� �� ���� ��� �������, � �������� ���� ��� !!!
	/// </summary>
	/// <param name="size"></param>
	explicit Array(size_t size) : size_(size_), data_(new int[size_/ INTBITS + 1])
	{ }
	
	/// <summary>
	/// �����!!! �������� �����������, �� ����� �� ����� ������� bool �� ��������. ���� �������� �� ����������
	/// �� ����� ������� ������, �� ������ ������� ������ �.�. �� ����� ������� �� �� �������� ������� � ������
	/// ��� �� ���������, � ������ ������ ��� ���� � ������ �� ���������. ������ ������� ������ ��
	/// ���������� ���.
	/// </summary>
	/// <param name="i">���������� ����� bool. ��� ���� ��� �� ������ � ����� ���� �� ���������� ���� ���������
	/// ���������� ����� �� ���������� ��� � ����, � ����� ���� ��� ����. ����� ������� �� ������� i �� ���-�� ����� � ����.
	/// ��� �������� ������� ���� �������� 1 � ������� ������������� � ����������� �� ����������� ���-�� � ����
	/// ����� ����� �� ����������� ��� ����� �� �������� �� �������, ������� ���� ��� 0 - false
	/// ���� ����� 0 � ���� 1  - true</param>
	/// <returns>True ��� False</returns>
	bool operator[](size_t i) const
	{
		return data_[i / INTBITS] & (1 << (i % INTBITS));
	}
};


template<class T>
void swap(T& a, T & b)
{
	T tmp(a);
	a = b;
	b = tmp;
}

template<class T>
void swap(Array<T> & a, Array<T> & b)
{
	a.swap(b);
}
