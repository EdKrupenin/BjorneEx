#include "pch.h"
struct Number;
struct BinaryOperation;

/// <summary>
/// Интерфейс посетителей должен содержать методы посещения
/// каждого элемента. Важно, чтобы иерархия элементов менялась
/// редко, так как при добавлении нового элемента придётся менять
/// всех существующих посетителей.
/// </summary>
struct IVisitor {
	virtual void visitNumber(Number const* number) = 0;
	virtual void visitBinaryOperation(BinaryOperation const* operation) = 0;
	virtual ~IVisitor() { }
};

/// <summary>
/// Интерфейс "Кон­крет­ный посе­ти­те­ль"
/// реа­ли­зу­ют какое-то осо­бен­ное пове­де­ние для всех типов эле­мен­тов,
/// кото­рые можно подать через мето­ды интер­фей­са посетителя.
/// Сложная иерархия элементов. Обязан иметь вирутуальный метод visit
/// </summary>
struct Expression
{
	//virtual double evaluate() const = 0;
	virtual void visit(IVisitor* vistitor) const = 0;
	virtual ~Expression() { }
};

/// <summary>
// Метод принятия посетителя должен быть реализован в каждом
/// элементе, а не только в базовом классе. Это поможет программе
/// определить, какой метод посетителя нужно вызвать, если вы не
/// знаете тип элемента.
/// </summary>
struct Number : Expression
{
	Number(double value) : value(value) {}
	//double evaluate() const;

	double get_value() const { return value; }

	void visit(IVisitor* visitor) const { visitor->visitNumber(this); }

private:
	double value{};
};

struct BinaryOperation : Expression
{
	BinaryOperation(Expression const* left, char op, Expression const* right) : left(left), op(op), right(right)
	{}
	~BinaryOperation() {}
	//double evaluate() const;

	Expression const* get_left() const { return left; }
	Expression const* get_right() const { return right; }
	char get_op() const { return op; }

	void visit(IVisitor* visitor) const { visitor->visitBinaryOperation(this); }

private:
	/// <summary>
	/// Несмотря на то что мы в сигнатуре ожидаем указатель на базовый класс
	/// мы с легкостью можем вернуть указатель на производный класс и промзодет преобразование
	/// иными словами left может быть как Number так и BinaryOperation
	/// </summary>
	Expression const* left;

	/// <summary>
	/// Несмотря на то что мы в сигнатуре ожидаем указатель на базовый класс
	/// мы с легкостью можем вернуть указатель на производный класс и промзодет преобразование
	/// иными словами right может быть как Number так и BinaryOperation
	/// </summary>
	Expression const* right;
	char op;
};


#include <iostream>

/* Этот класс вам нужно реализовать */



/// <summary>
/// Конкретный посетитель реализует одну операцию для всей
/// иерархии элементов. Новая операция = новый посетитель.
/// Посетитель выгодно применять, когда новые элементы
/// добавляются очень редко, а новые операции — часто.
/// </summary>
struct PrintVisitor : IVisitor {
	void visitNumber(Number const* number)
	{
		std::cout << number->get_value();
		/* ... */
	}

	void visitBinaryOperation(BinaryOperation const* bop)
	{
		std::cout << '(';
		bop->get_left()->visit(this);
		std::cout << bop->get_op();/* ... */
		bop->get_right()->visit(this);
		std::cout << ')';
	}
};

struct Expression;

struct ScopedPtr
{
	/// <summary>
	/// Конструктор умного указателя
	/// </summary>
	/// <param name="ptr">Принимает на вход указатель</param>
	explicit ScopedPtr(Expression* ptr = 0) : ptr_(ptr) { }

	~ScopedPtr() { delete ptr_; }

	/// <summary>
	/// возвращает указатель, сохраненный внутри ScopedPtr (например, чтобы передать его в какую-то функцию); 
	/// </summary>
	/// <returns> указатель, сохраненный внутри ScopedPtr </returns>
	Expression* get() const
	{
		return ptr_;
	}

	/// <summary>
	/// забирает указатель у ScopedPtr и возвращает значение этого указателя,
	/// после вызова release ScopedPtr не должен освобождать память
	/// (например, чтобы вернуть этот указатель из функции);
	/// </summary>
	/// <returns> возвращает значение указателя</returns>
	Expression* release()
	{
		Expression* ptr = ptr_;
		ptr_ = nullptr;
		return ptr;
	}

	/// <summary>
	/// заставляет ScopedPtr освободить старый указатель,
	/// а вместо него захватить новый (например, чтобы переиспользовать ScopedPtr,
	/// так как оператор присваивания запрещен). 
	/// </summary>
	/// <param name="ptr">Новый указатель</param>
	void reset(Expression* ptr = 0)
	{
		delete ptr_;
		ptr_ = ptr;
	}

	Expression& operator*() const {
		return *ptr_;
	}

	Expression* operator->() const {
		return ptr_;
	}


private:
	// запрещаем копирование ScopedPtr
	ScopedPtr(const ScopedPtr&);
	ScopedPtr& operator=(const ScopedPtr&);

	Expression* ptr_;
};

struct OperatorPtr
{
	explicit OperatorPtr(Expression* ptr = nullptr) : ptr_(ptr), countPtr(ptr ? 1 : 0) { }
	~OperatorPtr() {
		delete ptr_;
	}
	int countPtr{};
	Expression* ptr_ = nullptr;
};

struct SharedPtr
{
	explicit SharedPtr(Expression* ptr = nullptr) {
		if (ptr != nullptr) {
			operator_ = new OperatorPtr(ptr);
		}
	}

	/// <summary>
	/// Конструктор копирования
	/// </summary>
	/// <param name="SharedPtr">Константная ссылка на объект копирования</param>
	SharedPtr(const SharedPtr& SharedPtr) : operator_(SharedPtr.operator_)
	{
		if (operator_ != nullptr && operator_->countPtr) {
			++(operator_->countPtr);
		}
	}

	~SharedPtr() {
		if (operator_ != nullptr)
			if (--operator_->countPtr == 0)
				delete operator_;
	}

	SharedPtr& operator=(const SharedPtr& shared_ptr) {
		if (this != &shared_ptr) {
			this->~SharedPtr();
			this->operator_ = shared_ptr.operator_;
			if (operator_ != nullptr)
				++(operator_->countPtr);
		}
	}

	/// <summary>
	/// возвращает указатель, сохраненный внутри ScopedPtr (например, чтобы передать его в какую-то функцию); 
	/// </summary>
	/// <returns> указатель, сохраненный внутри ScopedPtr </returns>
	Expression* get() const
	{
		return operator_->ptr_;
	}

	// <summary>
	/// заставляет ScopedPtr освободить старый указатель,
	/// а вместо него захватить новый (например, чтобы переиспользовать ScopedPtr,
	/// так как оператор присваивания запрещен). 
	/// </summary>
	/// <param name="ptr">Новый указатель</param>
	void reset(Expression* ptr = 0)
	{
		this->~SharedPtr();
		if (ptr != nullptr)
			operator_ = new OperatorPtr(ptr);
		else
			operator_ = nullptr;
	}

	Expression& operator*() const {
		return *operator_->ptr_;
	}

	Expression* operator->() const {
		return operator_->ptr_;
	}

private:
	OperatorPtr* operator_ = nullptr;
};

TEST(ThemeFive, TestFiveThree)
{
	Expression* sube = new BinaryOperation(new Number(4.5), '+', new Number(5));
	Expression const* expr = new BinaryOperation(new Number(3), '*', sube);
	PrintVisitor  visitor;
	expr->visit(&visitor);
	return 0;
}