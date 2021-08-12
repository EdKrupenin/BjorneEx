struct Rational
{
    Rational(int numerator_ = 0, int denominator_ = 1);

    void add(Rational rational);
    void sub(Rational rational);
    void mul(Rational rational);
    void div(Rational rational);

    void neg();
    void inv();
    double to_double() const;

    Rational& operator+=(Rational rational);
    Rational& operator-=(Rational rational);
    Rational& operator*=(Rational rational);
    Rational& operator/=(Rational rational);

    Rational operator-() const;
    Rational operator+() const;
	friend bool operator == (const Rational& f1, const Rational& f2);
	friend bool operator == (int num, const Rational& f2);
	friend bool operator == (const Rational& f1, int num);
	friend bool operator != (const Rational& f1, const Rational& f2);
	friend bool operator != (int num, const Rational& f2);
	friend bool operator != (const Rational& f1, int num);
	friend bool operator != (const Rational& f1, const Rational& f2);
	friend bool operator != (int num, const Rational& f2);
	friend bool operator != (const Rational& f1, int num);
	friend bool operator >= (const Rational& f1, const Rational& f2);
	friend bool operator >= (int num, const Rational& f2);
	friend bool operator >= (const Rational& f1, int num);
	friend bool operator <= (const Rational& f1, const Rational& f2);
	friend bool operator <= (int num, const Rational& f2);
	friend bool operator <= (const Rational& f1, int num);
	friend bool operator > (const Rational& f1, const Rational& f2);
	friend bool operator > (int num, const Rational& f2);
	friend bool operator > (const Rational& f1, int num);
	friend bool operator < (const Rational& f1, const Rational& f2);
	friend bool operator < (int num, const Rational& f2);
	friend bool operator < (const Rational& f1, int num);
	explicit operator double() const
	{
		Rational r(*this);
		return r.to_double();
	}
private:
    int numerator_;
    int denominator_;
};

Rational operator+(Rational lhs, Rational rhs);
Rational operator-(Rational lhs, Rational rhs);
Rational operator*(Rational lhs, Rational rhs);
Rational operator/(Rational lhs, Rational rhs);

bool operator==(const Rational& f1, const Rational& f2)
{
	bool f_equal = ((f1.numerator_ * f2.denominator_) == (f2.numerator_ * f1.denominator_)) ? true : false;
	return f_equal;
}


bool operator==(int num, const Rational& f2)
{
	return Rational(num, 1) == f2;
}

bool operator==(const Rational& f1, int num)
{
	return f1 == Rational(num, 1);
}

bool operator!=(const Rational& f1, const Rational& f2)
{
	return ((f1 == f2) ? false : true);
}

bool operator!=(int num, const Rational& f2)
{
	return Rational(num, 1) != f2;
}

bool operator!=(const Rational& f1, int num)
{
	return f1 != Rational(num, 1);
}

bool operator>=(const Rational& f1, const Rational& f2)
{
	return ((f1 < f2) ? false : true);
}

bool operator>=(int num, const Rational& f2)
{
	return Rational(num, 1) >= f2;
}

bool operator>=(const Rational& f1, int num)
{
	return f1 >= Rational(num, 1);
}

bool operator<=(const Rational& f1, const Rational& f2)
{
	return ((f1 > f2) ? false : true);
}

bool operator<=(int num, const Rational& f2)
{
	return Rational(num, 1) <= f2;
}

bool operator<=(const Rational& f1, int num)
{
	return f1 <= Rational(num, 1);
}

bool operator>(const Rational& f1, const Rational& f2)
{
	
	bool f_equal = ((f1.numerator_ * f2.denominator_) > (f2.numerator_ * f1.denominator_)) ? true : false;
	return f_equal;
}

bool operator>(int num, const Rational& f2)
{
	return Rational(num, 1) > f2;
}

bool operator>(const Rational& f1, int num)
{
	return f1 > Rational(num, 1);
}

bool operator<(const Rational& f1, const Rational& f2)
{
	bool f_equal = ((f1.numerator_ * f2.denominator_) < (f2.numerator_ * f1.denominator_)) ? true : false;
	return f_equal;
}

bool operator<(int num, const Rational& f2)
{
	return Rational(num, 1) < f2;
}

bool operator<(const Rational& f1, int num)
{
	return f1 < Rational(num, 1);
}

