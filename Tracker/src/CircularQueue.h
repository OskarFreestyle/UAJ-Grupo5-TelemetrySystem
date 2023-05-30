#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class CircularQueue {

public:

    CircularQueue() {
        capacity = 10;
        arr.resize(capacity);
        front = -1;
        rear = -1;
        size = 0;
    }

    CircularQueue(int maxSize) {
        capacity = maxSize;
        arr.resize(capacity);
        front = -1;
        rear = -1;
        size = 0;
    }

    /*
    * Inserta un nuevo elemento en la cola circular.
    * 
    * En caso de insertar un elemento cuando la cola ya esta llena, se tiene que colocar
    * en la posicion del elemento mas antiguo por lo que se devuelve ese elemento para 
    * ser borrado desde fuera correctamente y evitar asi leaks de memoria.
    * 
    * Con esto adem�s conseguimos no utilizar gran cantidad de memoria en caso de que
    * se generen muchos eventos (cosa que podr�a pasar con los eventos peri�dicos en caso
    * de que la frencuencia de trackeo sea muy alta).
    */
    T push(const T& data) {

        T e = nullptr;

        if (isEmpty()) {
            front = 0;
            rear = 0;
        }
        else rear = (rear + 1) % capacity;

        if (isFull()) {
            e = arr[front];
            front = (front + 1) % capacity;
        }
        else
            size++;

        arr[rear] = data;

        return e;
    }

    /*
    * Elimina el elemento mas antiguo de la lista circular
    */
    void pop() {
        if (isEmpty()) {
            cout << "La cola est� vac�a. No se puede eliminar ning�n elemento." << endl;
            return;
        }

        if (front == rear) {
            front = -1;
            rear = -1;
        }
        else {
            front = (front + 1) % capacity;
        }

        size--;
    }

    /*
    * Devuelve el elementos mas antiguo de la lista circular
    */
    T frontElement() {
        if (isEmpty()) {
            cout << "La cola est� vac�a. No hay ning�n elemento para mostrar." << endl;
            return T();
        }

        return arr[front];
    }

    bool isEmpty() {
        return (front == -1 && rear == -1);
    }

    bool isFull() {
        return (size == capacity);
    }

    int currentSize() {
        return size;
    }

private:

    vector<T> arr;
    int front; // �ndice del frente de la cola
    int rear; // �ndice de la parte trasera de la cola
    int capacity; // Tama�o m�ximo de la cola
    int size; // Tama�o actual de la cola

};