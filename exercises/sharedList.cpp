#include <iostream>
#include <memory>

using namespace std;

class Node
{
public:
    Node(const int v) :
        next(nullptr),
        value(v)
    {}

    //Node* next;
    std::shared_ptr<Node> next;
    int value;
    // ~Node()
    // {
    //     std::cout << "      value: " << value << '\n';
    //     delete next;
    // }
};

class List
{
public:
    List();
    void add(std::shared_ptr<Node> node);
    std::shared_ptr<Node> get(const int value);

private:
    std::shared_ptr<Node> first;
};

List::List() :
    first(nullptr)
{}

void List::add(std::shared_ptr<Node> node)
{
    if(!first)
    {
        first = node;
    }
    else
    {
        std::shared_ptr<Node> current = first;
        while(current->next)
        {
            current = current->next;
        }
        current->next = node;
    }
}

std::shared_ptr<Node> List::get(const int value)
{
    if(!first)
    {
        cout << "List is empty!" << endl;
        return nullptr;
    }
    else
    {
        std::shared_ptr<Node> current = std::move(first);
        do
        {
            if(current->value == value)
            {
                cout << "Found value " << current->value << endl;
                return current;
            }
            else
            {
                cout << "Going through " << current->value << endl;
                current = current->next;
            }
        } while(current);
        cout << "Not found: value " << value << endl;
        return nullptr;
    }
}

int main()
{
    List lista;
    //Node* node4 = new Node(4);
    auto node4 = std::make_shared<Node>(4);
    auto node7 = std::make_shared<Node>(4);
    //Node* node7 = new Node(7);

    lista.add(std::move(node4));
    lista.add(std::make_shared<Node>(2));
    lista.add(std::move(node7));
    lista.add(std::make_shared<Node>(9));
    auto node = lista.get(1);

    if (node)
        cout << node->value << '\n';

    //delete node4;
    // delete node7;
    return 0;
}