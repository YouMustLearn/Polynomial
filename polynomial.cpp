//User inputs two polynomials and program performs arithmetic operations on them

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Polynomial
{
public:
    Polynomial();
    Polynomial(vector<int> coeffs);
    
    void print() const;
    int Degree() const;
    int Coefficient(int k) const;

    void constantMultiply(int x);
    void Transform();
	double evaluateAt(double x);

	Polynomial& operator++();
	Polynomial operator++(int post);
	Polynomial& operator--();
	Polynomial operator--(int unused);
	Polynomial& operator+=(const Polynomial& right);
	Polynomial& operator-=(const Polynomial& right);
	Polynomial& operator*=(const Polynomial& right);

private:
    vector<int> coefficient;
};

//Polynomial operators
Polynomial Add(Polynomial pol1, Polynomial pol2);
Polynomial Subtract(Polynomial pol1, Polynomial pol2);
Polynomial Multiply(Polynomial pol1, Polynomial pol2);

int main()
{
    vector<int> polynomial1;
    vector<int> polynomial2;

    cout << "Welcome! Please input the coefficients of the first polynomial." << endl;
    cout << "When you are finished, enter -123456789." << endl;

    //user input for polynomial1:
    int r;
    int count1 = 0;
    bool more1 = true;
    while (more1)
    {
        cin >> r;
        if (r == -123456789)
            more1 = false;
        else
            polynomial1.push_back(r);
        count1++;
    }

    cout <<"\nPlease input the coefficients of the second polynomial." << endl;

    int s;
    int count2 = 0;
    bool more2 = true;
    while (more2)
    {
        cin >> s;
        if (s == -123456789)
            more2 = false;
        else
            polynomial2.push_back(s);
        count2++;
    }

    //setting Degree() equal for both polynomials entered, with coefficients of 0 for lesser polynomial
    if (count1 != count2)
    {
        if (count1 < count2)
        {
            int a = count2 - count1;
            while (a != 0)
            {
                polynomial1.push_back(0);
                a--;
            }
        }
        else
        {
            int a = count1 - count2;
            while (a != 0)
            {
                polynomial2.push_back(0);
                a--;
            }
        }
    }

    Polynomial poly1(polynomial1);
    cout << "\nYour first polynomial is p(x) ";
    poly1.print();

    Polynomial poly2(polynomial2);
    cout << "\n\nYour second polynomial is q(x) ";
    poly2.print();

    cout << "\n\np(x)+q(x) = ";
    Polynomial Sum = Add(poly1, poly2);
    Sum.print();

    cout << "\n\np(x)-q(x) = ";
    Polynomial Difference = Subtract(poly1, poly2);
    Difference.print();

	cout << "\n\np(x)*q(x) = ";
	Polynomial Product = Multiply(poly1, poly2);
	Product.print();

	cout << endl << endl;

    return 0;
}

Polynomial::Polynomial()
{
    coefficient;
}

Polynomial::Polynomial(vector<int> coeffs)
{
    coefficient = coeffs;
}

/**Multiplies vector by a constant x
@param a Multiplies vector by x
*/
void Polynomial::constantMultiply(int x)
{
    for (int t = 0; t < coefficient.size(); t++)
        coefficient[t] *= x;
}

void Polynomial::print() const
{
    for (int i = 0; i < coefficient.size(); i++)
    {
        if (i == 0 && coefficient[i] == 0)            //case: degree 0 | coefficient 0
            cout << "";                                
        else if (i == 0 && coefficient[i] != 0)        //case: degree 0 | coefficient !=0
            cout << coefficient[i];
        else if (i == 1 && coefficient[i] > 0)        //case: degree 1 | coefficent > 0
            cout << "+" << coefficient[i] << "x";
        else if (i == 1 && coefficient[i] < 0)        //case: degree 1 | coefficient < 0
            cout << coefficient[i] << "x";
        else if (i > 1 && coefficient[i] == 1)        //case: degree > 1 | coefficient 1
            cout << "+x^" << i;
        else if (i > 1 && coefficient[i] == -1)        //case: degree > 1 | coefficient -1
            cout << "-x^" << i;
        else if (i == 1 && coefficient[i] == 1)        //case: degree 1 | coefficient 1
            cout << "+x";
        else if (i > 0 && coefficient[i] == 0)        //case: degree > 0 | coefficient 0
            cout << "";
        else if (i > 0 && coefficient[i] > 0)        //case: degree > 0 | coefficient > 0
            cout << "+" << coefficient[i] << "x^" << i;
        else if (i > 0 && coefficient[i] < 0)        //case: degree > 0 | coefficient < 0
            cout << coefficient[i] << "x^" << i;
        else if (i == coefficient.size() - 1 && coefficient[i] > 0)        //case: highest degree | coefficient > 0
            cout << "+" << coefficient[i] << "x^" << i;
        else if (i == coefficient.size() - 1 && coefficient[i] < 0)        //case: highest degree | coefficient < 0
            cout << coefficient[i] << "x^" << i;
    }
}

//Returns degree of polynomial
int Polynomial::Degree() const
{
    return coefficient.size() - 1;
}

//Returns coefficient of vector at k
int Polynomial::Coefficient(int k) const
{
    int n = coefficient[k];
    return n;
}

//Evaluates polynomial by plugging in x
double Polynomial::evaluateAt(double x)
{
	double input = x;
	double evaluate = 0;
	for (int i = 0; i < coefficient.size(); i++)
	{
		evaluate += coefficient[i] * (pow(input, i));
	}
	
	return evaluate;
}

/**Addition, adds two polynomials together
@param a is a polynomial
@param b is a polynomial
@return c is the sum of the two polynomials
*/
Polynomial Add(Polynomial pol1, Polynomial pol2)
{
    vector<int> initAdd;

    for (int x = 0; x <= pol1.Degree(); x++)
    {
        initAdd.push_back(pol1.Coefficient(x));
        initAdd[x] += pol2.Coefficient(x);
    }

    Polynomial sum(initAdd);
    return sum;
}

/** Subtracts two polynomials
@param a is a polynomial 
@param b is a polynomial
@return c is the difference between the polynomials
*/
Polynomial Subtract(Polynomial pol3, Polynomial pol4)
{
    vector<int> initSub;

    for (int y = 0; y <= pol3.Degree(); y++)
    {
        initSub.push_back(pol3.Coefficient(y));
        initSub[y] -= pol4.Coefficient(y);
    }

    Polynomial difference(initSub);
    return difference;
}

/**Multiplies two polynomials
@param a is a polynomial
@param b is a polynomial
@return c returns the product of the two polynomials
*/
Polynomial Multiply(Polynomial pol5, Polynomial pol6)
{
	vector<int> initMult(100);

	for (int g = 0; g <= pol5.Degree(); g++)
	{
		for (int h = 0; h <= pol6.Degree(); h++)
		{
			initMult[g + h] += pol5.Coefficient(g) * pol6.Coefficient(h);
		}
	}

	Polynomial product(initMult);
	return product;
}

//Transform takes the derivative of the polynomial
void Polynomial::Transform()
{
	for (int w = 0; w < coefficient.size(); w++)
	{
		coefficient[w] *= w;
	}
}
