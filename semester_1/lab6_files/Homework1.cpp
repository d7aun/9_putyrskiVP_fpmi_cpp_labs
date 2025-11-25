#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
int stInt(std::string st) {
    if ((st[0] < '0' || st[0] > '9') && st[0] != '-')
        throw "a must be integer, b must be unsigned\n";
    int a = stoi(st);
    std::string xst = std::to_string(a);
    if (st == xst)
        return a;
    else throw "Enter fraction as a/b: a is integer, b is unsigned\n";
}
struct fraction {
    int num;
    unsigned den;
    fraction(int a = 0, unsigned b = 1) : num(a), den(b) {};
    fraction(const fraction& p) {
        num = p.num;
        den = p.den;
    }
    ~fraction() {};
    fraction operator + (const fraction& p) {
        num = p.den * num + p.num * den;
        den *= p.den;
        return *this;
    }
    fraction operator - (const fraction& p) {
        num = p.den * num - p.num * den;
        den *= p.den;
        return *this;
    }
    fraction operator -() {
        fraction tmp;
        tmp.num = -num;
        tmp.den = den;
        return tmp;
    }
    fraction operator * (const fraction& p) {
        num *= p.num;
        den *= p.den;
        return *this;
    }
    fraction operator / (const fraction& p) {
        num *= p.den;
        den *= p.num;
        return *this;
    }
    fraction& operator += (const fraction& p) {
        num = p.den * num + p.num * den;
        den *= p.den;
        return *this;
    }
    fraction& operator -= (const fraction& p) {
        num = p.den * num - p.num * den;
        den *= p.den;
        return *this;
    }
    fraction& operator *= (const fraction& p) {
        num *= p.num;
        den *= p.den;
        return *this;
    }
    fraction& operator /= (const fraction& p) {
        num *= p.den;
        den *= p.num;
        return *this;
    }
    friend bool operator == (const fraction& k, const fraction& p) {
        if (p.den * k.num == p.num * k.den)
            return true;
        return false;
    }
    friend bool operator != (const fraction& k, const fraction& p) {
        if (k == p)
            return false;
        return true;
    }
    friend bool operator > (const fraction& k, const fraction& p) {
        if (k.num * p.num > 0)
            return (p.den * k.num > p.num * k.den);
        return !(p.den * k.num > p.num * k.den);
    }
    friend bool operator < (const fraction& k, const fraction& p) {
        if (k.num * p.num > 0)
            return (p.den * k.num < p.num * k.den);
        return !(p.den * k.num < p.num * k.den);
    }
    friend bool operator >= (const fraction& k, const fraction& p) {
        return !(k < p);
    }
    friend bool operator <= (const fraction& k, const fraction& p) {
        return !(k > p);
    }
    fraction& operator ++() {
        num += den;
        return *this;
    }
    fraction operator ++(int) {
        num += den;
        return *this;
    }
    friend std::ostream& operator << (std::ostream& out, const fraction& p) {
        out << p.num << "/" << p.den;
        return out;
    }
    friend fraction& operator >> (std::istream& in, fraction& p) {
        std::string fra;
        getline(in, fra);
        size_t i = fra.find("/");
        if (i == std::string::npos) {
            throw "Enter fraction as a/b: a is integer, b is positive integer\n";
        }
        std::string stNum, stDen;
        stNum = fra.substr(0, i);
        p.num = stInt(stNum);
        stDen = fra.substr(i + 1);
        p.den = stInt(stDen);
        if (p.den == 0)
            throw "b must be positive integer\n";
        return p;
    }
};
void yourVec(const std::vector <fraction>& v, int sz) {
    for (int i = 0; i < sz; ++i) {
        std::cout << v[i] << "  ";
    }
    std::cout << "\n";
}
void swapFr(fraction& a, fraction& b) {
    std::swap(a.num, b.num);
    std::swap(a.den, b.den);
}

int main()
{
    std::cout << "Fraction is a / b: a is integer, b is positive integer\nTests:\n";
    fraction fr(3, 2), ffr(4, 5);
    fraction fffr = -fr + ffr;
    fr++;
    if (fr>=ffr)
        std::cout << fffr << "  " << fr << std::endl;
    fraction ur;
    try {
        std::cin >> ur;
        std::cout << ur << "\n";
    }
    catch (const char* s) {
        std::cerr << s;
    }
    std::cout << "End of tests.\n\n";

    std::vector <fraction> vec;
    int sz = 10,
        xsz = sz;
    std::cout << "Enter " << sz << " fractions:\n";
    fraction util;
    
    for (int i = 0; i < xsz; ++i) {
        try {
            std::cin >> util;
            vec.push_back(util);
        }
        catch (const char* s) {
            std::cerr << s;
            sz--;
        }
    }
    std::cout << "Vector of your fractions is:\n";
    yourVec(vec, sz);

    std::cout << "Increasingly sorted vector is:\n";
    for (int i = 0; i < sz; ++i)
        for (int j = 0; j < sz - i - 1; ++j)
            if (vec[j] > vec[j + 1])
                swapFr(vec[j], vec[j + 1]);
    yourVec(vec, sz);
    return 0;
}
