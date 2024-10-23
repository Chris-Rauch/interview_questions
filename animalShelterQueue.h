/* Problem:
 *   An animal shelter, which holds only dogs and cats, operates on a strictly
 *   FIFO basis. nPeople must adopt either the olderst (based on arrival time)
 *   of all animals at the shelter, or they can select whether they would
 *   prefer a dog or cat. They cannot select which specific animal they want.
 *   Create a data structure to amintain this system and implement operations
 *   such as enqueue, dequeueAny, dequeueCat and dequeueDog. You may use a 
 *   built in linked list data structure
 *
*/


#include <exception>
#include <stdexcept>
#include <string>
#include <list>


enum AnimalType
{
    Dog,
    Cat,
    Unknown
};

class Animal
{
public:
    Animal(std::string name, AnimalType type) : _name(name), _type(type) {}
    Animal() : _name(""), _type(AnimalType::Unknown) {}

    std::string name() const {return _name;}
    AnimalType type() const {return _type;}
private:
    std::string _name;
    AnimalType _type;
};

class AnimalShelter
{
public:
    void enqueue(Animal animal);
    Animal dequeueAny();
    Animal dequeueDog();
    Animal dequeueCat();

public:
    int numAnimals() {return _queue.size();}
    
private:
    std::list<Animal> _queue;
};

void AnimalShelter::enqueue(Animal animal)
{
    _queue.push_front(animal);
}

Animal AnimalShelter::dequeueDog()
{
    if(_queue.size() <= 0)
    {
        throw std::exception("Animal Shelter is empty. Nothing to dequeue");
    }

    Animal animal;

    // iterate backwards through the list
    for(auto it = _queue.rbegin(); it != _queue.rend(); ++it)
    {
        if(it->type() == AnimalType::Dog)
        {
            animal = *it;
            _queue.erase(std::prev(it.base()));
            break;
        }
    }
    
    return animal;
}

Animal AnimalShelter::dequeueCat()
{
    if(_queue.size() <= 0)
    {
        throw std::runtime_error("Animal Shelter is empty. Nothing to dequeue");
    }

    Animal animal;

    // iterate backwards through the list
    for(auto it = _queue.rbegin(); it != _queue.rend(); ++it)
    {
        if(it->type() == AnimalType::Cat)
        {
            animal = *it;
            _queue.erase(std::prev(it.base()));
            break;
        }
    }
    
    return animal;
}

/**
 * @brief Return the animal at the end of the list and remove it from the queue
 * 
 * @return Animal Whatever animal is as the end of the list
 */
Animal AnimalShelter::dequeueAny()
{
    if(_queue.size() <= 0)
    {
        throw std::runtime_error("Animal Shelter is empty. Nothing to dequeue");
    }

    Animal next = _queue.back();
    _queue.pop_back();
    return next;
}

