#include <iostream>
#include <cmath>
#include <string>

class Triangle {
private:
    double a, b, c;
    std::string color;

    // Перевірка, чи сторони утворюють коректний трикутник
    bool isValidTriangle(double a, double b, double c) {
        return (a + b > c) && (a + c > b) && (b + c > a);
    }

public:
    // Конструктор за замовчуванням
    Triangle() : a(1), b(1), c(1), color("white") {}

    // Конструктор з параметрами
    Triangle(double a, double b, double c, std::string color) {
        if (isValidTriangle(a, b, c)) {
            this->a = a;
            this->b = b;
            this->c = c;
        } else {
            std::cerr << "nekorektni storony trikytnika!Vstanovlenno znachennya za zamovchyvannyam.\n";
            this->a = this->b = this->c = 1;
        }
        this->color = color;
    }

    // Сетери з перевіркою коректності
    void setSides(double a, double b, double c) {
        if (isValidTriangle(a, b, c)) {
            this->a = a;
            this->b = b;
            this->c = c;
        } else {
            std::cerr << "error: nekorektni znachennya trikutnyka.\n";
        }
    }

    // Сетер для кольору
    void setColor(std::string color) {
        this->color = color;
    }

    // Гетери
    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
    std::string getColor() const { return color; }

    // Обчислення периметра
    double perimeter() const {
        return a + b + c;
    }

    // Обчислення площі за формулою Герона
    double area() const {
        double s = perimeter() / 2;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }

    // Виведення інформації про трикутник
    void print() const {
        std::cout << "Triangle: sides = (" << a << ", " << b << ", " << c 
                  << "), color = " << color 
                  << ", perimeter = " << perimeter() 
                  << ", area = " << area() << "\n";
    }
};

// Тестування всіх можливостей класу
int main() {
    std::cout << "Testing Triangle class:\n";

    // Тест конструктора за замовчуванням
    Triangle t1;
    t1.print();

    // Тест конструктора з параметрами
    Triangle t2(3, 4, 5, "blue");
    t2.print();

    // Спроба встановити некоректні сторони
    t2.setSides(1, 2, 10); // не утворює трикутник
    t2.print();

    // Встановлення коректних сторін і кольору
    t2.setSides(5, 5, 6);
    t2.setColor("red");
    t2.print();

    return 0;
}
