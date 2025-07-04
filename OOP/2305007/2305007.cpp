#include <iostream>
#include <cmath>
using namespace std;

class Fraction {
    int numerator;
    int denominator;
public:
    void reduce() {
        int a = numerator, b = denominator;
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        numerator /= a;
        denominator /= a;
        if(denominator < 0) {
            denominator *= -1;
            numerator *= -1;
        }
    }

    Fraction(int numerator = 0, int denominator = 1) : numerator(numerator), denominator(denominator) {
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }
        reduce();
    }

    explicit Fraction(float f) {
        const int precision = 1e2;
        numerator = round(f*precision);
        denominator = precision;
        reduce();
    }

    void setNumerator(int numerator) { this->numerator = numerator; }
    void setDenominator(int denominator) { this->denominator = denominator; }
    int getNumerator() { return numerator; }
    int getDenominator() { return denominator; }

    Fraction operator+(const Fraction &f) const {
        int temp_numerator = numerator*f.denominator + f.numerator*denominator;
        int temp_denominator = denominator*f.denominator;
        return {temp_numerator, temp_denominator};
    }

    Fraction operator+(float f) {
        return *this + Fraction(f);
    }

    friend Fraction operator+(float f, const Fraction& fraction) {
        return Fraction(f) + fraction;
    }

    Fraction operator-(const Fraction &f) const {
        int temp_numerator = numerator*f.denominator - f.numerator*denominator;
        int temp_denominator = denominator*f.denominator;
        return {temp_numerator, temp_denominator};
    }

    Fraction operator-(float f) {
        return *this - Fraction(f);
    }

    friend Fraction operator-(float f, const Fraction& fraction) {
        return Fraction(f) - fraction;
    }

    Fraction operator*(const Fraction &f) const {
        return {numerator*f.numerator, denominator*f.denominator};
    }

    Fraction operator*(float f) {
        return *this * Fraction(f);
    }

    friend Fraction operator*(float f, const Fraction& fraction) {
        return Fraction(f)*fraction;
    }

    Fraction operator/(const Fraction &f) const {
        return {numerator*f.denominator, denominator*f.numerator};
    }

    Fraction operator/(float f) {
        return *this / Fraction(f);
    }

    friend Fraction operator/(float f, const Fraction& fraction) {
        return Fraction(f)/fraction;
    }

    Fraction& operator+=(const Fraction &f) {
        *this = *this + f;
        reduce();
        return *this;
    }

    Fraction& operator+=(float f) {
        *this += Fraction(f);
        return *this;
    }

    friend Fraction& operator+=(float f, Fraction& fraction) {
        Fraction *temp = new Fraction(Fraction(f));
        *temp += fraction;
        return *temp;
    }

    Fraction& operator-=(const Fraction &f) {
        *this = *this - f;
        reduce();
        return *this;
    }

    Fraction& operator-=(float f) {
        *this -= Fraction(f);
        return *this;
    }

    friend Fraction& operator-=(float f, Fraction& fraction) {
        Fraction *temp = new Fraction(Fraction(f));
        *temp -= fraction;
        return *temp;
    }

    Fraction& operator*=(const Fraction& f) {
        *this = *this * f;
        reduce();
        return *this;
    }

    Fraction& operator*=(float f) {
        *this *= Fraction(f);
        return *this;
    }

    friend Fraction& operator*=(float f, Fraction& fraction) {
        Fraction *temp = new Fraction(Fraction(f));
        *temp *= fraction;
        return *temp;
    }

    Fraction& operator/=(const Fraction& f) {
        *this = *this / f;
        reduce();
        return *this;
    }

    Fraction& operator/=(float f) {
        *this /= Fraction(f);
        return *this;
    }

    friend Fraction& operator/=(float f, Fraction& fraction) {
        Fraction *temp = new Fraction(Fraction(f));
        *temp /= fraction;
        return *temp;
    }

    bool operator==(const Fraction& f) {
        return (numerator == f.numerator && denominator == f.denominator);
    }

    bool operator==(float f) {
        return (numerator == Fraction(f).numerator && denominator == Fraction(f).denominator);
    }

    bool operator!=(const Fraction& f) {
        return !(numerator == f.numerator && denominator == f.denominator);
    }

    bool operator!=(float f) {
        return !(numerator == Fraction(f).numerator && denominator == Fraction(f).denominator);
    }

    friend ostream& operator<<(ostream &os, const Fraction &f) {
        os << f.numerator << "/" << f.denominator;
        return os;
    }
};

class FractionVector {
    Fraction *fractions;
    int size;
    int capacity;
public:
    FractionVector(int size = 0) : size(size) {
        capacity = size ? 2*size : 2;
        fractions = new Fraction[capacity];
    }
    
    FractionVector(const FractionVector& vec) {
        size = vec.size;
        capacity = vec.capacity;
        fractions = new Fraction[capacity];
        for(int i = 0; i < size; i++) {
            fractions[i] = vec.fractions[i];
        }
    }

    void increaseCapacity() {
        if(2*size >= capacity) {
            capacity *= 2;
            Fraction *temp = new Fraction[capacity];
            for(int i = 0; i < size; i++) {
                temp[i] = fractions[i];
            }
            delete[] fractions;
            fractions = temp;
        }
    }

    void decreaseCapacity() {
        if(4*size <= capacity) {
            capacity /= 2;
            Fraction *temp = new Fraction[capacity];
            for(int i = 0; i < size; i++) {
                temp[i] = fractions[i];
            }
            delete[] fractions;
            fractions = temp;
        }
    }

    void addFraction(const Fraction& f) {
        fractions[size++] = f;
        increaseCapacity();
    }

    void addFraction(float f) {
        addFraction(Fraction(f));
    }

    void deleteFraction(const Fraction& f) {
        for(int i = 0; i < size; i++) {
            if(fractions[i] == f) {
                for(int j = i; j < size-1; j++) {
                    fractions[j] = fractions[j+1];
                }
                size--;
                decreaseCapacity();
                return;
            }
        }
    }

    void deleteFraction(int idx) {
        if(idx < size) {
            for(int j = idx; j < size-1; j++) {
                fractions[j] = fractions[j+1];
            }
            size--;
            decreaseCapacity();
        }
    }

    void clear() {
        size = 0;
    }

    Fraction& operator[](int idx) {
        if(idx < 0 || idx >= size) {
            throw out_of_range("Index out of range");
        }
        return fractions[idx];
    }

    FractionVector operator+(const FractionVector& vec) const {
        if(size != vec.size) {
            throw invalid_argument("vector size mismatch in addition");
        }
        FractionVector temp(size);
        for(int i = 0; i < size; i++) {
            temp.fractions[i] = fractions[i] + vec.fractions[i];
        }
        return temp;
    }

    FractionVector operator-(const FractionVector& vec) const {
        if(size != vec.size) {
            throw invalid_argument("vector size mismatch in subtraction");
        }
        FractionVector temp(size);
        for(int i = 0; i < size; i++) {
            temp.fractions[i] = fractions[i] - vec.fractions[i];
        }
        return temp;
    }

    FractionVector operator*(Fraction& f) {
        FractionVector temp(size);
        for(int i = 0; i < size; i++) {
            temp.fractions[i] = fractions[i]*f;
        }
        return temp;
    }

    FractionVector operator*(float f) {
        FractionVector temp(size);
        for(int i = 0; i < size; i++) {
            temp.fractions[i] = fractions[i]*Fraction(f);
        }
        return temp;
    }

    friend FractionVector operator*(Fraction& f,  FractionVector& vec) {
        FractionVector temp(vec.size);
        for(int i = 0; i < vec.size; i++) {
            temp.fractions[i] *= f;
        }
        return temp;
    }

    friend FractionVector operator*(float f,  FractionVector& vec) {
        FractionVector temp(vec.size);
        Fraction fraction(f);
        for(int i = 0; i < vec.size; i++) {
            temp.fractions[i] = vec.fractions[i]*fraction;
        }
        return temp;
    }

    FractionVector operator/(Fraction& f) {
        FractionVector temp(size);
        for(int i = 0; i < size; i++) {
            temp.fractions[i] = fractions[i]/f;
        }
        return temp;
    }

    FractionVector operator/(float f) {
        FractionVector temp(size);
        for(int i = 0; i < size; i++) {
            temp.fractions[i] = fractions[i]/Fraction(f);
        }
        return temp;
    }

    Fraction operator*(FractionVector& vec) {
        if(size != vec.size) {
            throw invalid_argument("vector size mismatch in dot product");
        }
        Fraction temp;
        for(int i = 0; i < size; i++) {
            Fraction product = fractions[i] * vec[i];
            temp += (fractions[i] * vec[i]);
        }
        return temp;
    }

    Fraction value() {
        Fraction res;
        for(int i = 0; i < size; i++) {
            res += (fractions[i]*fractions[i]);
        }
        float ans = sqrt(res.getNumerator() * 1.0 / res.getDenominator());
        return Fraction(ans);
    }

    bool operator==(const FractionVector& vec) {
        if (size != vec.size) return false;
        for (int i = 0; i < size; i++) {
            if (!(fractions[i] == vec.fractions[i])) return false;
        }
        return true;    
    }

    FractionVector& operator=(const FractionVector& vec) {
        if(*this == vec) return *this;
        delete[] fractions;
        size = vec.size;
        capacity = vec.capacity;
        fractions = new Fraction[capacity];
        for(int i = 0; i < size; i++) {
            fractions[i] = vec.fractions[i];
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const FractionVector& vec) {
        // cout << "size: " << vec.size << " capacity: " << vec.capacity << endl;
        os << "[ " ;
        for(int i = 0; i < vec.size; i++) {
            os << vec.fractions[i];
            if(i != vec.size-1) cout << ", ";
        }
        os << " ]" << endl;
        return os;
    }

    ~FractionVector() {
        delete[] fractions;
    }
};

class FractionMatrix {
    FractionVector* rows;
    FractionVector* cols;
    int row;
    int col;
public:
    FractionMatrix(int row = 0, int col = 0) : row(row), col(col) {
        rows = new FractionVector[row];
        for(int i = 0; i < row; i++) {
            rows[i] = FractionVector(col);
        }
        cols = new FractionVector[col];
        for(int i = 0; i < col; i++) {
            cols[i] = FractionVector(row);
        }
    }

    FractionMatrix(const FractionMatrix& other) {
        row = other.row;
        col = other.col;
        rows = new FractionVector[row];
        for(int i = 0; i < row; i++) {
            rows[i] = other.rows[i];
        }
        cols = new FractionVector[col];
        for(int i = 0; i < col; i++) {
            cols[i] = other.cols[i];
        }
    }
    ~FractionMatrix() {
        delete[] rows;
        delete[] cols;
    }

    // void sync() {
    //     for(int i = 0; i < row; i++) {
    //         for(int j = 0; j < col; j++) {
    //             Fraction f = rows[i][j];
    //             cols[j][i] = f;
    //         }
    //     }
    // }

    FractionMatrix& operator=(const FractionMatrix& other) {
        if(this == &other) return *this;
        delete[] rows;
        delete[] cols;
        row = other.row;
        col = other.col;
        rows = new FractionVector[row];
        for(int i = 0; i < row; i++) {
            rows[i] = other.rows[i];
        }
        cols = new FractionVector[col];
        for(int i = 0; i < col; i++) {
            cols[i] = other.cols[i];
        }
        return *this;
    }

    bool operator==(const FractionMatrix& other) {
        if (row != other.row || col != other.col) return false;
        for (int i = 0; i < row; i++) {
            if (!(rows[i] == other.rows[i])) return false;
        }
        for (int j = 0; j < col; j++) {
            if (!(cols[j] == other.cols[j])) return false;
        }
        return true;
    }

    void setElement(int i, int j, const Fraction& f) {
        if (i >= row || j >= col) {
            throw out_of_range("Matrix index out of range");
        }
        rows[i][j] = f;
        cols[j][i] = f;
    }

    FractionVector& operator[](int idx) {
        if(idx < 0 || idx >= row) {
            throw out_of_range("Matrix index out of range");
        }
        return rows[idx];
    }

    FractionMatrix operator+(const FractionMatrix& other) {
        if(row != other.row || col != other.col) {
            throw invalid_argument("Matrix size mismatch in addition");
        }
        FractionMatrix temp(row, col);
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                temp.setElement(i, j, (rows[i][j] + other.rows[i][j]));
            }
        }
        return temp;
    }

    FractionMatrix operator-(const FractionMatrix& other) {
        if(row != other.row || col != other.col) {
            throw invalid_argument("Matrix size mismatch in subtraction");
        }
        FractionMatrix temp(row, col);
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                temp.setElement(i, j, (rows[i][j] - other.rows[i][j]));
            }
        }
        return temp;
    }

    FractionMatrix operator*(const Fraction& f) {
        FractionMatrix temp(row, col);
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                temp.setElement(i, j, (rows[i][j]*f));
            }
        }
        return temp;
    }

    FractionMatrix operator*(const float f) {
        Fraction fraction(f);
        FractionMatrix temp(row, col);
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                temp.setElement(i, j, (rows[i][j]*fraction));
            }
        }
        return temp;
    }

    friend FractionMatrix operator*(const Fraction& f, const FractionMatrix& matrix) {
        FractionMatrix temp(matrix.row, matrix.col);
        for(int i = 0; i < matrix.row; i++) {
            for(int j = 0; j < matrix.col; j++) {
                temp.setElement(i, j, (matrix.rows[i][j]*f));
            }
        }
        return temp;
    }

    FractionMatrix operator/(const Fraction& f) {
        FractionMatrix temp(row, col);
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                temp.setElement(i, j, (rows[i][j]/f));
            }
        }
        return temp;
    }

    FractionMatrix operator*(const FractionMatrix& matrix) {
        if(col != matrix.row) {
            throw invalid_argument("Multiplication not possible");
        }
        FractionMatrix product(row, matrix.col);
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < matrix.col; j++) {
                product.setElement(i, j, (rows[i]*matrix.cols[j]));
            }
        }
        return product;
    }

    FractionMatrix operator%(const FractionMatrix& matrix) {
        if(col != matrix.col || row != matrix.row) {
            throw invalid_argument("Hadamard multiplication not possible");
        }
        FractionMatrix product(row, col);
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                product.setElement(i, j, (rows[i][j]*matrix.rows[i][j]));
            }
        }
        return product;
    }

    FractionMatrix transpose() {
        FractionMatrix transposed(col, row);
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                transposed.setElement(j, i, (rows[i][j]));
            }
        }
        return transposed;
    }

    FractionVector getRow(int index) {
        if(index >= row) {
            throw out_of_range("Row index out of range");
        }
        return rows[index];
    }

    FractionVector getColumn(int index) {
        if(index >= col) {
            throw out_of_range("Column index out of range");
        }
        return cols[index];
    }

    friend ostream& operator<<(ostream& os, const FractionMatrix& matrix) {
        for(int i = 0; i < matrix.row; i++) {
            os << "[ ";
            for(int j = 0; j < matrix.col; j++) {
                os << matrix.rows[i][j];
                if(j < matrix.col-1) os << ", ";
            }
            os << " ]" << endl;  
        }
        cout << endl;
        return os;
    }

};

int main() {
    cout << "--- Fraction Class Test ---" << endl;
    
    Fraction a(1, 2), b(3, 4), c(2, 4), d(0.5f), e(-1, -2), f(5, -10);
    cout << "a: " << a << ", b: " << b << ", c: " << c << endl;
    cout << "d (float): " << d << ", e: " << e << ", f: " << f << endl;
    
    cout << "Arithmetic operation:" << endl;
    cout << "a + b = " << (a + b) << endl;
    cout << "b - a = " << (b - a) << endl;
    cout << "a * b = " << (a * b) << endl;
    cout << "b / a = " << (b / a) << endl;
    cout << "a + 0.5 = " << (a + 0.5) << endl;
    cout << "0.5 + a = " << (0.5 + a) << endl;
    Fraction g = a;
    g += b;
    cout << "Assignment operation:" << endl;
    cout << "a += b: " << g << endl;
    g -= b;
    cout << "g -= b: " << g << endl;
    g *= b;
    cout << "g *= b: " << g << endl;
    g /= b;
    cout << "g /= b: " << g << endl;
    
    cout << "Logical operations:" << endl;
    cout << "a == c: " << (a == c) << endl;
    cout << "a == 0.5: " << (a == 0.5) << endl;
    cout << "a != b: " << (a != b) << endl;
    
    cout << "Denominator zero case:-" << endl;
    try {
        Fraction h(1, 0);
    } catch (const invalid_argument& e) {
        cout << "Caught expected error: " << e.what() << endl;
    }

    cout << "\n--- FractionVector Class Test --" << endl;
    
    FractionVector vec1;
    vec1.addFraction(Fraction(1, 2));
    vec1.addFraction(Fraction(1, 3));
    vec1.addFraction(Fraction(1, 4));
    
    cout << "Check accessing:" << endl;
    cout << "vec1: " << vec1;
    cout << "vec1[0]: " << vec1[0] << endl;
    vec1[1] = Fraction(2, 3);
    cout << "Changed vec1: " << vec1;
    
    FractionVector vec2;
    vec2.addFraction(Fraction(1, 1));
    vec2.addFraction(Fraction(1, 2));
    vec2.addFraction(Fraction(1, 3));
    cout << "vec2: " << vec2;
    
    cout << "Vector operations:" << endl;
    cout << "vec1 + vec2: " << (vec1 + vec2);
    cout << "vec2 - vec1: " << (vec2 - vec1);
    cout << "vec1 * 2: " << (vec1 * 2);
    cout << "2 * vec1: " << (2 * vec1);
    cout << "vec1 / 2: " << (vec1 / 2);
    cout << "vec1 * vec2 (dot product): " << (vec1 * vec2) << endl;
    cout << "vec1: " << vec1;
    cout << "vec1.value(): " << vec1.value() << endl;
    
    cout << "Capacity management:" << endl;
    for (int i = 0; i < 10; i++) {
        vec1.addFraction(Fraction(i+1, i+2));
    }
    cout << "Add 10 elements: " << vec1;
    for (int i = 0; i < 5; i++) {
        vec1.deleteFraction(0);
    }
    cout << "After deleting 5 elements: " << vec1;
    
    cout << "Out of range access case:-" << endl;
    try {
        cout << vec1[20] << endl;
    } catch (const out_of_range& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }
    cout << "Size mismatch case:-" << endl;
    try {
        vec1 + vec2;
    } catch (const invalid_argument& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }
    try {
        vec1 - vec2;
    } catch (const invalid_argument& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }
    try {
        vec1 * vec2;
    } catch (const invalid_argument& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }

    cout << "\n--- FractionMatrix Class Test ---" << endl;
    
    FractionMatrix A(2, 3);
    A.setElement(0, 0, Fraction(1, 1));
    A.setElement(0, 1, Fraction(1, 2));
    A.setElement(0, 2, Fraction(1, 3));
    A.setElement(1, 0, Fraction(2, 1));
    A.setElement(1, 1, Fraction(2, 2));
    A.setElement(1, 2, Fraction(2, 3));
    cout << "Matrix A (2x3):\n" << A;
    
    cout << "Row access:" << endl;
    cout << "Row 0: " << A.getRow(0);
    cout << "Column access:" << endl;
    cout << "Column 1: " << A.getColumn(1);
    
    FractionMatrix B(2, 3);
    B.setElement(0, 0, Fraction(1, 2));
    B.setElement(0, 1, Fraction(1, 3));
    B.setElement(0, 2, Fraction(1, 4));
    B.setElement(1, 0, Fraction(1, 5));
    B.setElement(1, 1, Fraction(1, 6));
    B.setElement(1, 2, Fraction(1, 7));
    cout << "Matrix B (2x3):" << endl << B;
    
    cout << "Matrix operations:" << endl;
    cout << "A + B:\n" << (A + B);
    cout << "A - B:\n" << (A - B);
    cout << "A * 2:\n" << (A * 2);
    cout << "A / 2:\n" << (A / 2);
    
    FractionMatrix C(3, 2);
    C.setElement(0, 0, Fraction(1, 1));
    C.setElement(0, 1, Fraction(1, 2));
    C.setElement(1, 0, Fraction(1, 3));
    C.setElement(1, 1, Fraction(1, 4));
    C.setElement(2, 0, Fraction(1, 5));
    C.setElement(2, 1, Fraction(1, 6));
    cout << "Matrix C (3x2):" << endl << C;
    cout << "A * C:" << endl << (A * C);
    cout << "Hadamard product (A % B):" << endl << (A % B);
    cout << "Transpose of A:" << endl << A.transpose();
    cout << "Copy check:" << endl;
    FractionMatrix D = A;
    cout << "Matrix D (copy of A):" << endl << D;
    FractionMatrix E(1, 1);
    E = A;
    cout << "Matrix E (assigned from A):\n" << E;
    cout << "Matrix E[1][0] : " << E[1][0] << endl;
    E[1][0] = Fraction(4.5f);
    cout << "Matrix E[1][0] : " << E[1][0] << endl;
    cout << "Out of range access case:-" << endl;
    try {
        A.setElement(2, 3, Fraction(1,1));
    } catch (const out_of_range& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }
    try {
        A.getRow(3);
    } catch (const out_of_range& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }
    try {
        A.getColumn(3);
    } catch (const out_of_range& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }
    try {
        cout << A[3] << endl;
    } catch (const out_of_range& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }
    cout << "Invalid operation case:-" << endl;
    try {
        A + C;
    } catch (const invalid_argument& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }
    try {
        A - C;
    } catch (const invalid_argument& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }
    try {
        A % C;
    } catch (const invalid_argument& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }
    try {
        A * B;
    } catch (const invalid_argument& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }

    return 0;
}