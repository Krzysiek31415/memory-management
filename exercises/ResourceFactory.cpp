#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

struct Resource
{
    Resource(char* byte) : byte_(byte) {}
    char* byte() const { return byte_; }
    virtual string name() const = 0;
    virtual ~Resource() { delete [] byte_; }

protected:
    char* byte_ = nullptr;
};

struct ResourceA : Resource
{
    ResourceA(char* byte) : Resource(byte) {}
    string name() const override { return string("ResourceA ").append(1, *byte_); }
    ~ResourceA() override {}
};

struct ResourceB : Resource
{
    ResourceB(char* byte) : Resource(byte) {}
    string name() const override { return string("ResourceB ").append(1, *byte_); }
    ~ResourceB() override {}
};

struct ResourceFactory
{ 
    std::shared_ptr<Resource> makeResourceA(char* byte) { return std::shared_ptr<Resource>{new ResourceA{byte}}; }
    std::shared_ptr<Resource> makeResourceB(char* byte) { return std::shared_ptr<Resource>{new ResourceB{byte}}; }
};

struct ResourceCollection
{
    void add(std::shared_ptr<Resource> r) { resources.push_back(r); }
    void clear() { resources.clear(); }
    std::shared_ptr<Resource> operator[](int index) { return resources[index]; }
    void printAll()
    {
        for (const auto & res : resources)
        {
            cout << res->name() << endl;
        }
    }

private:
    vector<std::shared_ptr<Resource>> resources;
};

int main()
{
    ResourceCollection collection;
    ResourceFactory rf;
    collection.add(rf.makeResourceA(new char[2]{0x01,'\n'}));
    collection.add(rf.makeResourceB(new char[2]{0x02,0x00}));
    collection.printAll();

    //auto firstByte = collection[0]->byte();
    collection.clear();
    //cout << *firstByte << endl;

    return 0;
}

