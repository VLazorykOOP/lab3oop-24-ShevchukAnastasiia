#include <iostream>
#include <stdexcept>

class Vector {
private:
    long* data;
    size_t size;
    int state; // 0 - OK, 1 - out of bounds, 2 - memory allocation error
    static int object_count;

public:
    // Getters
    size_t getSize() const { return size; }
    int getState() const { return state; }
    static int getObjectCount() { return object_count; }

    // Default constructor
    Vector() : size(1), state(0) {
        try {
            data = new long[1]{0};
        } catch (...) {
            state = 2;
            data = nullptr;
        }
        object_count++;
    }

    // Constructor with size
    Vector(size_t n) : size(n), state(0) {
        try {
            data = new long[n]{};
        } catch (...) {
            state = 2;
            data = nullptr;
        }
        object_count++;
    }

    // Constructor with size and initial value
    Vector(size_t n, long value) : size(n), state(0) {
        try {
            data = new long[n];
            for (size_t i = 0; i < n; ++i)
                data[i] = value;
        } catch (...) {
            state = 2;
            data = nullptr;
        }
        object_count++;
    }

    // Copy constructor
    Vector(const Vector& other) : size(other.size), state(other.state) {
        try {
            data = new long[size];
            for (size_t i = 0; i < size; ++i)
                data[i] = other.data[i];
        } catch (...) {
            state = 2;
            data = nullptr;
        }
        object_count++;
    }

    // Assignment operator
    Vector& operator=(const Vector& other) {
        if (this == &other)
            return *this;

        delete[] data;
        size = other.size;
        state = other.state;

        try {
            data = new long[size];
            for (size_t i = 0; i < size; ++i)
                data[i] = other.data[i];
        } catch (...) {
            state = 2;
            data = nullptr;
        }

        return *this;
    }

    // Destructor
    ~Vector() {
        delete[] data;
        object_count--;
    }

    // Assign value to an element
    void setElement(size_t index, long value = 0) {
        if (index >= size) {
            state = 1;
            return;
        }
        data[index] = value;
        state = 0;
    }

    // Get value from an element
    long getElement(size_t index) {
        if (index >= size) {
            state = 1;
            return 0;
        }
        state = 0;
        return data[index];
    }

    // Print vector
    void print() const {
        if (data == nullptr) {
            std::cout << "[invalid vector]\n";
            return;
        }
        std::cout << "[ ";
        for (size_t i = 0; i < size; ++i)
            std::cout << data[i] << " ";
        std::cout << "]\n";
    }

    // Addition
    Vector operator+(const Vector& other) const {
        size_t n = (size < other.size) ? size : other.size;
        Vector result(n);
        for (size_t i = 0; i < n; ++i)
            result.data[i] = this->data[i] + other.data[i];
        return result;
    }

    // Subtraction
    Vector operator-(const Vector& other) const {
        size_t n = (size < other.size) ? size : other.size;
        Vector result(n);
        for (size_t i = 0; i < n; ++i)
            result.data[i] = this->data[i] - other.data[i];
        return result;
    }

    // Multiplication by unsigned int
    Vector operator*(unsigned int multiplier) const {
        Vector result(size);
        for (size_t i = 0; i < size; ++i)
            result.data[i] = this->data[i] * multiplier;
        return result;
    }

    // Comparisons
    bool operator==(const Vector& other) const {
        if (size != other.size)
            return false;
        for (size_t i = 0; i < size; ++i)
            if (data[i] != other.data[i])
                return false;
        return true;
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    bool operator<(const Vector& other) const {
        size_t n = (size < other.size) ? size : other.size;
        for (size_t i = 0; i < n; ++i) {
            if (data[i] < other.data[i])
                return true;
            else if (data[i] > other.data[i])
                return false;
        }
        return size < other.size;
    }
};

// Initialize static object counter
int Vector::object_count = 0;

// ==========================
// Testing program
// ==========================

int main() {
    Vector v1;              // Default constructor
    Vector v2(5);           // Constructor with size
    Vector v3(5, 3);        // Constructor with size and initial value

    std::cout << "v1 = "; v1.print();
    std::cout << "v2 = "; v2.print();
    std::cout << "v3 = "; v3.print();

    v2.setElement(2, 10);
    std::cout << "v2 after setting v2[2] = 10: "; v2.print();

    std::cout << "v2[2] = " << v2.getElement(2) << "\n";

    Vector v4 = v2 + v3;
    std::cout << "v2 + v3 = "; v4.print();

    Vector v5 = v3 - v2;
    std::cout << "v3 - v2 = "; v5.print();

    Vector v6 = v3 * 2;
    std::cout << "v3 * 2 = "; v6.print();

    std::cout << "v2 == v3? " << (v2 == v3 ? "yes" : "no") << "\n";
    std::cout << "v2 != v3? " << (v2 != v3 ? "yes" : "no") << "\n";
    std::cout << "v2 < v3? "  << (v2 < v3 ? "yes" : "no") << "\n";

    std::cout << "Number of Vector objects: " << Vector::getObjectCount() << "\n";

    return 0;
}
