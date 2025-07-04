#include <iostream>
#include <cstring>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
	  int t = a % b;
	  a = b;
	  b = t;
	}
    return a;
}

class Fraction {
    int numerator;
    int denominator;
public:
    Fraction() : numerator(0), denominator(1) {}

    Fraction(int numerator) {
        this->numerator = numerator;
        this->denominator = 1;  
    }

    Fraction(int numerator, int denominator) {
        if(denominator == 0) {
            cout << "0 can not be denominator." << endl;
            exit(-1);
        }
        this->numerator = numerator;
        this->denominator = denominator;
    }

    ~Fraction() {

    }

    bool operator > (Fraction &f) {
        return (numerator*f.denominator > denominator*f.numerator);
    }

    bool operator < (Fraction &f) {
        return (numerator*f.denominator < denominator*f.numerator);
    }

    bool operator == (Fraction &f) {
        return (numerator*f.denominator == denominator*f.numerator);
    }

    int getNumerator() {
        return numerator;
    }

    int getDenominator() {
        return denominator;
    }

    Fraction add(Fraction &f) {
        int newNumerator = this->numerator*f.denominator + f.numerator*this->denominator;
        int newDenominator = this->denominator*f.denominator;

        return Fraction(newNumerator, newDenominator);
    }

    Fraction add(int n) {
        int newNumerator = numerator + denominator*n;
        return Fraction(newNumerator, denominator);
    }

    Fraction sub(Fraction &f) {
        int newNumerator = this->numerator*f.denominator - f.numerator*this->denominator;
        int newDenominator = this->denominator*f.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction sub(int n) {
        int newNumerator = numerator - denominator*n;
        return Fraction(newNumerator, denominator);
    }

    Fraction mul(Fraction &f) {
        int newNumerator = this->numerator*f.numerator;
        int newDenominator = this->denominator*f.denominator;
        return Fraction(newNumerator, newDenominator);
    }   

    Fraction mul(int n) {
        int newNumerator = numerator * n;
        return Fraction(newNumerator, denominator);
    }

    Fraction div(Fraction &f) {
        if(f.numerator == 0) {
            cout << "Can not divide by 0" << endl;
            return *this;
        }
        int newNumerator = this->numerator*f.denominator;
        int newDenominator = this->denominator*f.numerator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction div(int n) {
        if(n == 0) {
            cout << "Can not divide by 0" << endl;
            return *this;
        }
        int newDenominator = denominator * n;
        return Fraction(numerator, newDenominator);
    }

    void print() {
        int _gcd = gcd(numerator, denominator);
        numerator /= _gcd;
        denominator /= _gcd;
        if(denominator<0) {
            numerator *= -1;
            denominator *= -1;
        }
        cout << numerator << '/' << denominator << endl;
    }
};

class FractionCollection {
    Fraction *fractions;
    int maxlength;
    int length;
public:
    FractionCollection() {
        maxlength = 10;
        length = 0;
        fractions = new Fraction[maxlength];
    }

    FractionCollection(int size) {
        maxlength = size;
        length = 0;
        fractions = new Fraction[maxlength];
    }

    ~FractionCollection() {
        delete[] fractions;
    }

    void insert(Fraction f) {
        if(length == maxlength) {
            cout << "No space left." << endl;
            return;
        }
        fractions[length] = f;
        length++;
    }

    void insert(int pos, Fraction f) {
        if(length == maxlength) {
            cout << "No space left." << endl;
            return;
        }
        for(int i = length; i > pos; i--) {
            fractions[i] = fractions[i-1];
        }
        fractions[pos] = f;
        length++;
    }

    void remove() {
        if(length>0) length--;
    }

    void remove(int pos) {
        for(int i = pos; i < length-1; i++) {
            fractions[i] = fractions[i+1];
        }
        length--;
    }

    void remove(Fraction f) {
        for(int i = 0; i < length; i++) {
            // if(fractions[i].getNumerator() == f.getNumerator() && fractions[i].getDenominator() == f.getDenominator()) {
            if(f == fractions[i]) {
                remove(i);
                return;
            }
        }
    }

    Fraction getmax() {
        // double max = fractions[0].getNumerator()*1.0/fractions[0].getDenominator();
        Fraction maxFraction = fractions[0];
        for(int i = 0; i < length; i++) {
            // double curr = fractions[i].getNumerator()*1.0/fractions[i].getDenominator();
            // if(curr >= max) {
            //     maxFraction = Fraction(fractions[i].getNumerator(), fractions[i].getDenominator());
            //     max = curr;
            // }
            if(fractions[i] > maxFraction) {
                maxFraction = fractions[i];
            }
        }
        return maxFraction;
    }

    Fraction getmin() {
        // double min = fractions[0].getNumerator()*1.0/fractions[0].getDenominator();
        Fraction minFraction = fractions[0];
        for(int i = 0; i < length; i++) {
            // double curr = fractions[i].getNumerator()*1.0/fractions[i].getDenominator();
            // if(curr <= min) {
            //     minFraction = Fraction(fractions[i].getNumerator(), fractions[i].getDenominator());
            //     min = curr;
            // }
            if(fractions[i] < minFraction) {
                minFraction = fractions[i];
            }
        }
        return minFraction;
    }

    Fraction add(int start, int end) {
        Fraction summation;
        for(int i = start; i <= end; i++) {
            summation = summation.add(fractions[i]);
        }
        return summation;
    }

    Fraction mul(int start, int end) {
        Fraction product(1, 1);
        for(int i = start; i <= end; i++) {
            product = product.mul(fractions[i]);
        }
        return product;
    }

    Fraction sub(int pos1, int pos2) {
        return fractions[pos1].sub(fractions[pos2]);
    }

    Fraction div(int pos1, int pos2) {
        return fractions[pos1].div(fractions[pos2]);
    }

    void print() {
        cout<<endl<<"Fractions"<<endl; 
        cout<<"-------------------------------"<<endl; 

        for(int i = 0; i < length; i++) {
            cout << "Fraction " << i << ": ";
            fractions[i].print();
        }
        
        cout << "Max: ";
        getmax().print();
        cout << "Min: ";
        getmin().print();
        cout << "Summation: ";
        add(0, length-1).print();
        cout << "Multiplication: ";
        mul(0, length-1).print();
    }

    int getLength() {
        return length;
    }

};


int main(){ 
    //create Fraction with numerator, denominator 
    Fraction a(5,2),b(7,2),c(9,2),d(28,5); 
    cout<<"Fraction"<<endl; 
    cout<<"-------------------------------"<<endl; 
    cout<<"A: "; 
    a.print(); 
    cout<<"B: "; 
    b.print(); 
    cout<<endl; 
 
    cout<<"Add(a,b): "; 
    a.add(b).print(); 
    cout<<"Add(a,2): "; 
    a.add(2).print(); 
     
    cout<<"Sub(a,b): "; 
    a.sub(b).print(); 
    cout<<"Sub(a,2): "; 
    a.sub(2).print(); 
     
    cout<<"Mul(a,b): "; 
    a.mul(b).print(); 
    cout<<"Mul(a,2): "; 
    a.mul(2).print(); 
     
    cout<<"Div(a,b): "; 
    a.div(b).print(); 
    cout<<"Div(a,2): "; 
    a.div(2).print(); 
    cout<<"Div(a,0): "; 
    a.div(0).print(); 

    //Collection of Fractions 
    Fraction e,f(5),g(10); 
    FractionCollection fc(10); 
    fc.insert(a); 
    fc.insert(b); 
    fc.insert(c); 
    fc.print(); 
    cout<<"Sub(Pos0, Pos1): "; 
    fc.sub(0,1).print(); //subtracts the fraction at pos1 from fraction at pos0 
    cout<<"Div(Pos0, Pos1): "; 
    fc.div(0,1).print(); //divides the fraction at pos0 by the fraction at pos1 

    fc.remove(1);  //removed 'b' 
    fc.print();  
    
    fc.remove(a); 
    fc.print();

    fc.insert(d); 
    fc.insert(0,e);  //insert at pos0 
    fc.insert(f); 
    fc.insert(g); 
    fc.print(); 
 
    fc.remove(); //removed the last fraction 
    fc.print();  //notice the output 
    return 0; 
}
