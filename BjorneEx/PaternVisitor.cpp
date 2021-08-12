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
struct IExpression
{
	//virtual double evaluate() const = 0;
	virtual void visit(IVisitor* vistitor) const = 0;
	virtual ~IExpression() { }
};

/// <summary>
// ����� �������� ���������� ������ ���� ���������� � ������
/// ��������, � �� ������ � ������� ������. ��� ������� ���������
/// ����������, ����� ����� ���������� ����� �������, ���� �� ��
/// ������ ��� ��������.
/// </summary>
struct Number : IExpression
{
	Number(double value) : value(value){}
	//double evaluate() const;

	double get_value() const { return value; }

	void visit(IVisitor* visitor) const { visitor->visitNumber(this); }

private:
	double value {};
};

struct BinaryOperation : IExpression
{
	BinaryOperation(IExpression const* left, char op, IExpression const* right) : left(left), op(op), right(right)
	{}
	~BinaryOperation(){}
	//double evaluate() const;

	IExpression const* get_left() const { return left; }
	IExpression const* get_right() const { return right; }
	char get_op() const { return op; }

	void visit(IVisitor* visitor) const { visitor->visitBinaryOperation(this); }

private:
	/// <summary>
	/// �������� �� �� ��� �� � ��������� ������� ��������� �� ������� �����
	/// �� � ��������� ����� ������� ��������� �� ����������� ����� � ��������� ��������������
	/// ����� ������� left ����� ���� ��� Number ��� � BinaryOperation
	/// </summary>
	IExpression const* left;
	
	/// <summary>
	/// �������� �� �� ��� �� � ��������� ������� ��������� �� ������� �����
	/// �� � ��������� ����� ������� ��������� �� ����������� ����� � ��������� ��������������
	/// ����� ������� right ����� ���� ��� Number ��� � BinaryOperation
	/// </summary>
	IExpression const* right;
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

/*
int main()
{
	IExpression* sube = new BinaryOperation(new Number(4.5), '+', new Number(5));
	IExpression const* expr = new BinaryOperation(new Number(3), '*', sube);
	PrintVisitor  visitor;
	expr->visit(&visitor);
	return 0; 
}