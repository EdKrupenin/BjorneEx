#include "pch.h"

template <typename T>
class Array
{
	T** data_;
	size_t size_;
public:

	/*
	 * Рекомендую решать не через извратные конструкции, а через указатель на указатель.
	 * Тогда за основу берется решение прошлого задания и доделки будут минимальными, а главное общая идея будет той же.
	 * идея T **data  состоит в том, что мы храним не массив значений типа T,
	 * а массив указателей на тип T, для которых operator= определен.
	 * Следовательно копию каждого элемента создаем на куче через копирующий конструктор и сохраняем указатель на эту копию.
	 * Меня подловили только на том, что в прошлом задании было explicit Array(size_t size = 0, const T& value = T()),
	 * а здесь написали explicit Array(size_t size, const T& value = T()) и отдельно дописали Array(), хотя прошлый вариант покрывал все ситуации.
	 * У меня в коде остался конструктор от прошлого задания и я, не посмотрев, добавил конструктор без параметров,
	 * который будет конфликтовать с explicit Array(size_t size = 0, const T& value = T()),
	 * если в коде будет обращение к конструктору без параметров :).
	 */

	 /// <summary>
	 /// конструктор класса, который можно вызвать
	 /// без параметров. Должен создавать пустой
	 /// Array.
	 /// </summary>
	Array() : data_(nullptr), size_(0)
	{
	}

	/// <summary>
	///  конструктор класса, который создает
	///  Array размера size, заполненный значениями
	///  value типа T. Если у класса нет конструктора
	///  по умолчанию, то второй аргумент этого конструктора
	///  обязателен.
	/// </summary>
	/// <param name="size"></param>
	/// <param name="value"></param>
	explicit Array(size_t size, const T& value = T()) : size_(size), data_(new T*[size])
	{
		for (size_t i = 0; i < size_; ++i)
			data_[i] = new T(value);
	}


	/// <summary>
	/// конструктор копирования, который создает
	/// копию параметра. Для типа T оператор
	/// присваивания не определен.
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
	//   деструктор, если он вам необходим.
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
	//   оператор присваивания.
	//
	size_t size() const { return size_; }
	//   возвращает размер массива (количество 
	//                              элементов).
	//
	T& operator[](size_t i) const
	{
		return *data_[i];
	}
	//   две версии оператора доступа по индексу.
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