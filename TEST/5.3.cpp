#include "pch.h"
struct Number;
struct BinaryOperation;

/// <summary>
/// ��������� ����������� ������ ��������� ������ ���������
/// ������� ��������. �����, ����� �������� ��������� ��������
/// �����, ��� ��� ��� ���������� ������ �������� ������� ������
/// ���� ������������ �����������.
/// </summary>
struct IVisitor {
	virtual void visitNumber(Number const* number) = 0;
	virtual void visitBinaryOperation(BinaryOperation const* operation) = 0;
	virtual ~IVisitor() { }
};

/// <summary>
/// ��������� "���������� ����������"
/// ��������� �����-�� ��������� ��������� ��� ���� ����� ���������,
/// ������� ����� ������ ����� ������ ���������� ����������.
/// ������� �������� ���������. ������ ����� ������������ ����� visit
/// </summary>
struct Expression
{
	//virtual double evaluate() const = 0;
	virtual void visit(IVisitor* vistitor) const = 0;
	virtual ~Expression() { }
};

/// <summary>
// ����� �������� ���������� ������ ���� ���������� � ������
/// ��������, � �� ������ � ������� ������. ��� ������� ���������
/// ����������, ����� ����� ���������� ����� �������, ���� �� ��
/// ������ ��� ��������.
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
	/// �������� �� �� ��� �� � ��������� ������� ��������� �� ������� �����
	/// �� � ��������� ����� ������� ��������� �� ����������� ����� � ��������� ��������������
	/// ����� ������� left ����� ���� ��� Number ��� � BinaryOperation
	/// </summary>
	Expression const* left;

	/// <summary>
	/// �������� �� �� ��� �� � ��������� ������� ��������� �� ������� �����
	/// �� � ��������� ����� ������� ��������� �� ����������� ����� � ��������� ��������������
	/// ����� ������� right ����� ���� ��� Number ��� � BinaryOperation
	/// </summary>
	Expression const* right;
	char op;
};


#include <iostream>

/* ���� ����� ��� ����� ����������� */



/// <summary>
/// ���������� ���������� ��������� ���� �������� ��� ����
/// �������� ���������. ����� �������� = ����� ����������.
/// ���������� ������� ���������, ����� ����� ��������
/// ����������� ����� �����, � ����� �������� � �����.
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
	/// ����������� ������ ���������
	/// </summary>
	/// <param name="ptr">��������� �� ���� ���������</param>
	explicit ScopedPtr(Expression* ptr = 0) : ptr_(ptr) { }

	~ScopedPtr() { delete ptr_; }

	/// <summary>
	/// ���������� ���������, ����������� ������ ScopedPtr (��������, ����� �������� ��� � �����-�� �������); 
	/// </summary>
	/// <returns> ���������, ����������� ������ ScopedPtr </returns>
	Expression* get() const
	{
		return ptr_;
	}

	/// <summary>
	/// �������� ��������� � ScopedPtr � ���������� �������� ����� ���������,
	/// ����� ������ release ScopedPtr �� ������ ����������� ������
	/// (��������, ����� ������� ���� ��������� �� �������);
	/// </summary>
	/// <returns> ���������� �������� ���������</returns>
	Expression* release()
	{
		Expression* ptr = ptr_;
		ptr_ = nullptr;
		return ptr;
	}

	/// <summary>
	/// ���������� ScopedPtr ���������� ������ ���������,
	/// � ������ ���� ��������� ����� (��������, ����� ���������������� ScopedPtr,
	/// ��� ��� �������� ������������ ��������). 
	/// </summary>
	/// <param name="ptr">����� ���������</param>
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
	// ��������� ����������� ScopedPtr
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
	/// ����������� �����������
	/// </summary>
	/// <param name="SharedPtr">����������� ������ �� ������ �����������</param>
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
	/// ���������� ���������, ����������� ������ ScopedPtr (��������, ����� �������� ��� � �����-�� �������); 
	/// </summary>
	/// <returns> ���������, ����������� ������ ScopedPtr </returns>
	Expression* get() const
	{
		return operator_->ptr_;
	}

	// <summary>
	/// ���������� ScopedPtr ���������� ������ ���������,
	/// � ������ ���� ��������� ����� (��������, ����� ���������������� ScopedPtr,
	/// ��� ��� �������� ������������ ��������). 
	/// </summary>
	/// <param name="ptr">����� ���������</param>
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