#include <iostream>
using namespace std;

template <typename T>
class SmartArray {
private:
    T* arr;       
    int size;      

public:
    //  Constructor
    SmartArray(int initialSize = 10) {
        size = initialSize;
        arr = new T[size];
        for (int i = 0; i < size; ++i) arr[i] = 0;

        
    }

    //  Destructor
    ~SmartArray() {
        delete[] arr;
    }

    
    void resize(int newSize) {
        T* newArr = new T[newSize];
        for (int i = 0; i < (newSize < size ? newSize : size); ++i)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
        size = newSize;
    }

    //  Insert at specific position
    void insertAt(int index, T value) {
        if (index < -1 || index > size) {
            cout << " Invalid index!\n";
            return;
        }

        int newSize = size + 1;
        T* newArr = new T[newSize];

        if (index == 0) {
            // Insert at head
            newArr[0] = value;
            for (int i = 0; i < size; ++i)
                newArr[i + 1] = arr[i];
        }
        else if (index == -1 || index == size) {
            // Insert at tail
            for (int i = 0; i < size; ++i)
                newArr[i] = arr[i];
            newArr[newSize - 1] = value;
        }
        else {
            // Insert at middle
            for (int i = 0; i < index; ++i)
                newArr[i] = arr[i];
            newArr[index] = value;
            for (int i = index; i < size; ++i)
                newArr[i + 1] = arr[i];
        }

        delete[] arr;
        arr = newArr;
        size = newSize;

        cout << " Value inserted successfully!\n";
    }

    //  Delete at specific position
    void deleteAt(int index) {
        if (size == 0) {
            cout << " Array is empty!\n";
            return;
        }

        if (index < -1 || index >= size) {
            cout << " Invalid index!\n";
            return;
        }

        int newSize = size - 1;
        T* newArr = new T[newSize];

        if (index == 0) {
            // Delete head
            for (int i = 1; i < size; ++i)
                newArr[i - 1] = arr[i];
        }
        else if (index == -1 || index == size - 1) {
            // Delete tail
            for (int i = 0; i < newSize; ++i)
                newArr[i] = arr[i];
        }
        else {
            // Delete middle
            for (int i = 0; i < index; ++i)
                newArr[i] = arr[i];
            for (int i = index + 1; i < size; ++i)
                newArr[i - 1] = arr[i];
        }

        delete[] arr;
        arr = newArr;
        size = newSize;

        cout << " Value deleted successfully!\n";
    }

    //  Access element by index
    void accessByIndex(int index) {
        if (index == -1)
            index = size - 1; 
        if (index < 0 || index >= size) {
            cout << " Invalid index!\n";
            return;
        }
        cout << " Element at index " << index << " = " << arr[index] << "\n";
    }

    //  Display full array
    void display() {
        if (size == 0) {
            cout << " Array is empty!\n";
            return;
        }
        cout << "\nCurrent Array Elements: ";
        for (int i = 0; i < size; ++i)
            cout << arr[i] << " ";
        cout << "\n";
    }

    //  Show current size
    int getSize() const { return size; }
};


int main() {
    cout << " Welcome to SmartArray System (by MAFA )\n";

    SmartArray<int> arr(10);

    int choice, index, value;
    bool running = true;

    while (running) {
        cout << "\n Choose an Operation:\n";
        cout << "1️ Insert Element\n";
        cout << "2️  Delete Element\n";
        cout << "3️  Display Array\n";
        cout << "4️  Access by Index\n";
        cout << "5️  Exit\n";
        cout << " Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter index (0=head, -1=tail, or any middle position): ";
            cin >> index;
            cout << "Enter value: ";
            cin >> value;
            arr.insertAt(index, value);
            break;

        case 2:
            cout << "Enter index (0=head, -1=tail, or any middle position): ";
            cin >> index;
            arr.deleteAt(index);
            break;

        case 3:
            arr.display();
            break;

        case 4:
            cout << "Enter index (use -1 for last element): ";
            cin >> index;
            arr.accessByIndex(index);
            break;

        case 5:
            running = false;
            cout << " Exiting program... Goodbye!\n";
            break;

        default:
            cout << " Invalid choice! Try again.\n";
        }
    }

    return 0;
}

