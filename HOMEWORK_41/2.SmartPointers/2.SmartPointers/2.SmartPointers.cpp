//  Создайте пользовательские классы умных указателей.
//  Один из классов должен повторять функциональность
//  стандартного класса unique_ptr, а другой shared_ptr.
//  Напишите код по тестированию ваших классов

#include <iostream>

// Класс, имитирующий функциональность unique_ptr
template <typename T>
class CustomUniquePtr {
private:
    T* ptr;
public:
    explicit CustomUniquePtr(T* p = nullptr) : ptr(p) {}

    ~CustomUniquePtr() {
        if (ptr) {
            delete ptr;
        }
    }

    CustomUniquePtr(const CustomUniquePtr&) = delete;
    CustomUniquePtr& operator=(const CustomUniquePtr&) = delete;

    CustomUniquePtr(CustomUniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    CustomUniquePtr& operator=(CustomUniquePtr&& other) noexcept {
        if (this != &other) {
            if (ptr) {
                delete ptr;
            }
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T* get() const {
        return ptr;
    }

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    T* operator->() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }
};

// Класс, имитирующий функциональность shared_ptr
template <typename T>
class CustomSharedPtr {
private:
    T* ptr;
    size_t* refCount;
public:
    explicit CustomSharedPtr(T* p = nullptr) : ptr(p), refCount(new size_t(1)) {}

    ~CustomSharedPtr() {
        release();
    }

    CustomSharedPtr(const CustomSharedPtr& other) : ptr(other.ptr), refCount(other.refCount) {
        (*refCount)++;
    }

    CustomSharedPtr& operator=(const CustomSharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            (*refCount)++;
        }
        return *this;
    }

    T* get() const {
        return ptr;
    }

    void release() {
        if (ptr) {
            (*refCount)--;
            if (*refCount == 0) {
                delete ptr;
                delete refCount;
            }
            ptr = nullptr;
            refCount = nullptr;
        }
    }

    size_t use_count() const {
        return (ptr ? *refCount : 0);
    }

    T* operator->() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }
};

int main() {
    // Тестирование CustomUniquePtr
    CustomUniquePtr<int> uniquePtr(new int(10));
    std::cout << "UniquePtr: " << *uniquePtr << std::endl; // Выводим значение по умолчанию

    // Перемещаем указатель
    CustomUniquePtr<int> anotherUniquePtr = std::move(uniquePtr);
    std::cout << "Another UniquePtr: " << *anotherUniquePtr << std::endl; // Выводим перемещенное значение

    // Тестирование CustomSharedPtr
    CustomSharedPtr<int> sharedPtr(new int(20));
    std::cout << "SharedPtr: " << *sharedPtr << " (use_count: " << sharedPtr.use_count() << ")" << std::endl;

    // Создаем еще один sharedPtr с тем же указателем
    CustomSharedPtr<int> anotherSharedPtr = sharedPtr;
    std::cout << "Another SharedPtr: " << *anotherSharedPtr << " (use_count: " << anotherSharedPtr.use_count() << ")" << std::endl;

    return 0;
}