#include <iostream>
#include <concepts>
#include <string>
#include <type_traits>

// Определение концепта ComplexConcept
template<typename T>
concept ComplexConcept = requires(T a) {
    // Проверка наличия метода hash, возвращающего тип, конвертируемый в long
    { a.hash() } -> std::convertible_to<long>;

    // Проверка наличия метода toString, возвращающего std::string
    { a.toString() } -> std::same_as<std::string>;

    // Проверка отсутствия виртуального деструктора
        requires !std::has_virtual_destructor_v<T>;
};

// Класс, соответствующий концепту ComplexConcept
class ValidClass {
public:
    long hash() const { return 12345; }
    std::string toString() const { return "ValidClass"; }
};

// Класс, не соответствующий концепту ComplexConcept из-за наличия виртуального деструктора
class InvalidClass {
public:
    virtual ~InvalidClass() = default; // Наличие виртуального деструктора делает этот класс невалидным
    long hash() const { return 12345; }
    std::string toString() const { return "InvalidClass"; }
};

// Проверка, что ValidClass удовлетворяет концепту ComplexConcept
static_assert(ComplexConcept<ValidClass>, "ValidClass должен удовлетворять ComplexConcept");

// Проверка, что InvalidClass не удовлетворяет концепту ComplexConcept
static_assert(!ComplexConcept<InvalidClass>, "InvalidClass не должен удовлетворять ComplexConcept");

int main()
{
    setlocale(LC_ALL, "RUS");

    std::cout << "Все проверки прошли успешно!\n";
    return 0;
}