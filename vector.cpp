class vector {
private:
    int *data;
    int last;
    int capacity;

public:
    explicit vector(int capacity = 1): capacity(capacity), last(0), data(new int[capacity]()) {}

    ~vector() { delete[] data; }

    // adds element to the last avaialable position,
    // resizes vector if current capacity is reached
    void push_back(int num) {
        if (last == capacity) resize(2 * capacity);
        data[last++] = num;
    }

    // resizes vector to given capacity
    void resize(int new_capacity) {
        if (new_capacity <= capacity) return;

        int *new_data = new int[new_capacity]();
        for (int i = 0; i < last; i++) new_data[i] = data[i];

        capacity = new_capacity;
        delete[] data;
        data = new_data;
    }

    int size() { return this->last; }

    void set(int num, int idx) {
        data[idx] = num;
    }
    
    int at(int idx) {
        return data[idx];
    }
};

int main(int argc, char **argv) {
    return 0;
}
