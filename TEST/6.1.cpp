#include "pch.h"

template <typename T>
class Array
{
public:
	// Список операций:


	/// <summary>
	/// конструктор класса, который создает
	/// Array, заполненный значениями value типа T.
	/// Считайте что у типа T есть конструктор, который можно вызвать без
	/// без параметров, либо он ему не нужен.
	/// </summary>
	/// <param name="size">размер</param>
	/// <param name="value">значения</param>
	explicit Array(size_t size = 0, const T& value = T()) : data_(new T[size]), size_(size)
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] = value;
	}

	/// <summary>
	/// конструктор копирования, который создает
	/// копию параметра. Считайте, что для типа
	/// T определен оператор присваивания.
	/// </summary>
	/// <param name=""></param>
	Array(const Array& array) : size_(array.size()), data_(new T[size_])
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] = array[i];
	}

	///деструктор
	~Array()
	{
		delete[] data_;
	}

	/// <summary>
	/// оператор присваивания.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	Array& operator=(const Array& array)
	{
		if(this != &array)
		{
			delete[] data_;
			size_ = array.size();
			data_ = new T[size_];
			for (size_t i = 0; i < size_; ++i)
				data_[i] = array[i];
		}		
		return *this;
	}

	/// <summary>
	/// возвращает размер массива 
	/// </summary>
	/// <returns> количество элементов</returns>
	size_t size() const { return size_; }

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	T& operator[](size_t i) const
	{
		return data_[i];
	}
	//   две версии оператора доступа по индексу.

private:
	T* data_;
	size_t size_;
};


TEST(ThemeSix, TestSixOne)
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