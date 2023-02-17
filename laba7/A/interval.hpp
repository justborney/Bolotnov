#ifndef INTERVAL_H
#define INTERVAL_H

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

template <typename Type>
Type Min (vector<Type> arg)
{
    typename vector<Type>::iterator it = arg.begin();
    Type minElem = *it;

    for (; it != arg.end(); ++it)
    {
        minElem = minElem > *it ? *it : minElem;
    }

    return minElem;
}

template <typename Type>
Type Min (Type arg1, Type arg2)
{
	return (arg1 < arg2) ? arg1 : arg2;
}

template <typename Type>
Type Max (vector<Type> arg)
{
    typename vector<Type>::iterator it = arg.begin();
    Type minElem = *it;

    for (; it != arg.end(); ++it)
    {
        minElem = minElem < *it ? *it : minElem;
    }

    return minElem;
}

template <typename Type>
Type Max (Type arg1, Type arg2)
{
	return (arg1 > arg2) ? arg1 : arg2;
}

/*
    Класс Interval
*/

template <typename Type>
class Interval
{
private:
    /* Левая и правая границы интервала */
    Type left;
    Type right;
public:
	Interval ()
	{
		this->left  = 0;
		this->right = 0;
	}

    Interval (Type lInit, Type rInit)
    {
        this->left  = lInit;
        this->right = rInit;
    }

    /*
        Геттеры и сеттеры
    */
    Type getLeft (void)
    {
        return this->left;
    }

    Type getRight (void)
    {
        return this->right;
    }

    void setLeft (Type arg)
    {
        this->left = arg;
    }

    void setRight (Type arg)
    {
        this->right = arg;
    }

    /*
        Перегрузка операторов
    */
    Interval operator=  (Interval const& arg)
    {
        return Interval(this->left = arg.left, this->right = arg.right);
    }

    Interval operator+ (Interval const& arg)
    {
        return Interval(this->left + arg.left, this->right + arg.right);
    }
    Interval operator+ (Type arg)
	{
		return Interval(this->left + arg, this->right + arg);
	}

	Interval operator- (void)
	{
		return Interval(-this->left, -this->right);
	}
    Interval operator- (Interval const& arg)
    {
        return Interval(this->left - arg.right, this->right - arg.left);
    }
    Interval operator- (Type arg)
	{
		return Interval(this->left - arg, this->right - arg);
	}

    Interval operator* (Interval const& arg)
    {
        vector<Type> allMult = {this->left * arg.left, this->left * arg.right,
                                this->right * arg.left, this->right * arg.right};
        return Interval( Min(allMult), Max(allMult) );
    }
	Interval operator* (Type arg)
	{
		return Interval(this->left * arg, this->right * arg);
	}

    Interval operator/ (Interval const& arg)
    {
        return Interval(this->left, this->right)
                *
               Interval(1 / arg.right, 1 / arg.left);
    }

	bool operator== (Interval const& arg)
	{
		return (this->left == arg.left) and (this->right == arg.right);
	}

	bool operator> (Interval const& arg)
	{
		return (this->left > arg.right);
	}

	bool operator< (Interval const& arg)
	{
		return (this->right < arg.left);
	}

    /*
        Методы
    */
    friend bool in(Type arg, Interval inter)
    {
        return ( inter.getLeft() <= arg && arg <= inter.getRight());
    }

    friend bool in(Interval larg, Interval rarg)
    {
        return ( rarg.getLeft() <= larg.getLeft() &&
                 larg.getRight() <= rarg.getRight());
    }

	/* Ширина интервала */
	Type wid (void)
	{
		return this->right - this->left;
	}

	friend Type wid (Interval const& arg)
	{
		return arg.right - arg.left;
	}

	/* Радиус интервала */
	double rad (void)
	{
		return (this->right - this->left) / 2.0;
	}

	friend double rad (Interval const& arg)
	{
		return (arg.right - arg.left) / 2.0;
	}

	/* Середина интервала */
	double med (void)
	{
		return (this->left + this->right) / 2.0;
	}

	friend double med (Interval const& arg)
	{
		return (arg.left + arg.right) / 2.0;
	}

	/* Модуль интервала */
	Type iabs (void)
	{
		return Max( fabs(this->left), fabs(this->right) );
	}

	friend Type iabs (Interval const& arg)
	{
		return Max( fabs(arg.left), fabs(arg.right) );
	}

	/* Натур. логарифм */
	Interval<Type> ln (Interval<Type> arg)
	{
		if ( arg.getLeft() <= 0 || arg.getRight() <= 0 )
		{
			cout << "Error: Ln on negative interval" << endl;
			exit(0);
		}
		else
		{
			return Interval<Type> ( log(arg.getLeft()), log(arg.getRight()) );
		}
	}
};
/* Конец класса Interval */

template <typename Type>
Interval<Type> operator+ (Type scArg, Interval<Type> const& arg)
{
	return Interval<Type>(arg.getLeft() + scArg, arg.getRight() + scArg);
}

template <typename Type>
Interval<Type> operator- (Type scArg, Interval<Type> const& arg)
{
	return Interval<Type>(scArg - arg.getRight(), scArg - arg.getLeft());
}

template <typename Type>
Interval<Type> operator* (Type scArg, Interval<Type> const& arg)
{
	return Interval<Type>(arg.getLeft() * scArg, arg.getRight() * scArg);
}

template <typename Type>
ostream& operator<< (ostream &out, Interval<Type> const& arg)
{
	out << "[" << arg.getLeft() << ";" << arg.getRight() << "]";
	return out;
}

/* swap интервалов */
template <typename Type>
void swap (Interval<Type>* arg1, Interval<Type>* arg2)
{
	Interval<Type> tmp = *arg1;
	*arg1 = *arg2;
	*arg2 = tmp;
}

#endif
