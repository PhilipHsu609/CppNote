#include <string>
#include <utility>

/*
   This is a builder pattern implementation that uses the fluent interface.

   The builder pattern is used to construct a complex object step by step.
   It separates the construction of a complex object from its representation,
   allowing the same construction process to create different representations.

   In this example, the `Person` class has multiple attributes related to address
   and employment. The `PersonBuilder` class and its derived classes
   `PersonAddressBuilder` and `PersonJobBuilder` provide a fluent interface to set these
   attributes.

   The `PersonBuilderBase` class provides the common interface for the derived builders.
   The `PersonBuilder` class initializes the `Person` object and passes it to the base
   class. The `PersonAddressBuilder` and `PersonJobBuilder` classes provide methods to set
   the address and employment details, respectively.

   The `PersonBuilder` allows switching between different builders (`PersonAddressBuilder`
   and `PersonJobBuilder`) using the `lives` and `works` methods. This enables a fluent
   interface where you can chain method calls to set different attributes of the `Person`
   object.
*/

class PersonBuilder;

class Person {
    // address
    std::string street_address;
    std::string post_code;
    std::string city;
    // employment
    std::string company_name;
    std::string position;
    int annual_income{0};

  public:
    static PersonBuilder create();

    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;
};

class PersonJobBuilder;
class PersonAddressBuilder;

class PersonBuilderBase {
  protected:
    Person &person;

  public:
    PersonBuilderBase(Person &person) : person(person) {}
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;

    operator Person() { return std::move(person); }
};

class PersonBuilder : public PersonBuilderBase {
    Person person;

  public:
    // Pass the person object to the base class
    PersonBuilder() : PersonBuilderBase(person) {}
};

class PersonAddressBuilder : public PersonBuilderBase {
    using Self = PersonAddressBuilder;

  public:
    PersonAddressBuilder(Person &person) : PersonBuilderBase(person) {}

    Self &at(std::string street_address) {
        person.street_address = street_address;
        return *this;
    }

    Self &with_post_code(std::string post_code) {
        person.post_code = post_code;
        return *this;
    }

    Self &in(std::string city) {
        person.city = city;
        return *this;
    }
};

class PersonJobBuilder : public PersonBuilderBase {
    using Self = PersonJobBuilder;

  public:
    PersonJobBuilder(Person &person) : PersonBuilderBase(person) {}

    Self &at(std::string company_name) {
        person.company_name = company_name;
        return *this;
    }

    Self &as_a(std::string position) {
        person.position = position;
        return *this;
    }

    Self &earning(int annual_income) {
        person.annual_income = annual_income;
        return *this;
    }
};

PersonBuilder Person::create() { return PersonBuilder(); }
PersonAddressBuilder PersonBuilderBase::lives() const {
    return PersonAddressBuilder(person);
}
PersonJobBuilder PersonBuilderBase::works() const { return PersonJobBuilder(person); }

int main() {
    [[maybe_unused]] auto p = Person::create()
                                  .lives()
                                  .at("123 London Road")
                                  .in("London")
                                  .with_post_code("SW12BC")
                                  .works()
                                  .at("Fabrikam")
                                  .as_a("Engineer")
                                  .earning(123000);
}