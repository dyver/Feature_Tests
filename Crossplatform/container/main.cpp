#include <iostream>

using namespace std;

template<typename ItemType> class Container {
    public:
        class Iterator {
            public:
                Iterator(ItemType* p) : position(p) {}
                bool operator!=(const Iterator& sample) { return position != sample.position; }
                Iterator& operator++() { ++position; return *this; }
                ItemType& operator*() { return *position; }
            private:
                ItemType* position = nullptr;
        };
        Iterator begin() { return Iterator(data); }
        Iterator end() { return Iterator(data + sizeof(data) / sizeof(ItemType)); }
    private:
        ItemType data[3] = { 1, 2, 3 };
};

int main() {
    Container<int> c;
    for (const auto& i : c) {
        cout << i << endl;
    }
    return 0;
}
