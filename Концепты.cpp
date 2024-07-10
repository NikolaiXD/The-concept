#include <iostream>
#include <concepts>
#include <string>
#include <type_traits>

// ����������� �������� ComplexConcept
template<typename T>
concept ComplexConcept = requires(T a) {
    // �������� ������� ������ hash, ������������� ���, �������������� � long
    { a.hash() } -> std::convertible_to<long>;

    // �������� ������� ������ toString, ������������� std::string
    { a.toString() } -> std::same_as<std::string>;

    // �������� ���������� ������������ �����������
        requires !std::has_virtual_destructor_v<T>;
};

// �����, ��������������� �������� ComplexConcept
class ValidClass {
public:
    long hash() const { return 12345; }
    std::string toString() const { return "ValidClass"; }
};

// �����, �� ��������������� �������� ComplexConcept ��-�� ������� ������������ �����������
class InvalidClass {
public:
    virtual ~InvalidClass() = default; // ������� ������������ ����������� ������ ���� ����� ����������
    long hash() const { return 12345; }
    std::string toString() const { return "InvalidClass"; }
};

// ��������, ��� ValidClass ������������� �������� ComplexConcept
static_assert(ComplexConcept<ValidClass>, "ValidClass ������ ������������� ComplexConcept");

// ��������, ��� InvalidClass �� ������������� �������� ComplexConcept
static_assert(!ComplexConcept<InvalidClass>, "InvalidClass �� ������ ������������� ComplexConcept");

int main()
{
    setlocale(LC_ALL, "RUS");

    std::cout << "��� �������� ������ �������!\n";
    return 0;
}