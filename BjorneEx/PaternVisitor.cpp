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
struct IExpression
{
	//virtual double evaluate() const = 0;
	virtual void visit(IVisitor* vistitor) const = 0;
	virtual ~IExpression() { }
};

/// <summary>
// Метод принятия посетителя должен быть реализован в каждом
/// элементе, а не только в базовом классе. Это поможет программе
/// определить, какой метод посетителя нужно вызвать, если вы не
/// знаете тип элемента.
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
	/// Несмотря на то что мы в сигнатуре ожидаем указатель на базовый класс
	/// мы с легкостью можем вернуть указатель на производный класс и промзодет преобразование
	/// иными словами left может быть как Number так и BinaryOperation
	/// </summary>
	IExpression const* left;
	
	/// <summary>
	/// Несмотря на то что мы в сигнатуре ожидаем указатель на базовый класс
	/// мы с легкостью можем вернуть указатель на производный класс и промзодет преобразование
	/// иными словами right может быть как Number так и BinaryOperation
	/// </summary>
	IExpression const* right;
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

/*
int main()
{
	IExpression* sube = new BinaryOperation(new Number(4.5), '+', new Number(5));
	IExpression const* expr = new BinaryOperation(new Number(3), '*', sube);
	PrintVisitor  visitor;
	expr->visit(&visitor);
	return 0; 
}