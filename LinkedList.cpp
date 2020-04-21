#include <iostream>
#include <string>
using namespace std;
// Linked List Node
template <class T>
class Node
{
public:
    T data; //Node가 가지고 있는 데이터
    Node<T> *link; //다음 Node을 연결시키는 포인터
    Node(T element)
    {
        data = element;
        link = NULL;
    }
};
// Linked List Class
template <class T>
class LinkedList
{
protected:
    Node<T> *first;
    int current_size;

public:
    LinkedList()
    {
        first = 0;
        current_size = 0;
    };
    int GetSize() { return current_size; }; // 리스트의 노드 개수를 리턴
    void Insert(T element);                 // 맨 앞에 원소를 삽입
    virtual bool Delete(T &element);                // 맨 뒤의 원소를 삭제
    void Print();                           // 리스트를 출력
};

template <class T>
class Stack : public LinkedList<T>
{
using LinkedList<T>::first;
using LinkedList<T>::current_size;
public:
    bool Delete(T &element); //Stack에 맞게 맨 앞의 있는 원소를 삭제
};

template <class T>
void LinkedList<T>::Insert(T element)
{
    Node<T> *newnode = new Node<T>(element); //추가할 Node구현
    newnode->link = first; //맨 앞에 있던 Node을 newnode의 링크로 설정
    first = newnode; // newnode가 새로운 맨 앞의 node으로 설정
    current_size++; //LinkedList 크기 증가
    return;
}

template <class T>
bool LinkedList<T>::Delete(T &element)
{
    if (first == 0)
        return false;
    Node<T> *current = first;
    Node<T> *previous = NULL;
    while (1)
    {
        if (current->link == 0) // find end node
        {
            if (previous)
                previous->link = current->link;
            else
                first = first->link;
            break;
        }
        previous = current;
        current = current->link;
    }
    //LinkedList을 차래대로 traverse하면서 마지막 Node을 찾는 while loop
    element = current->data; //element에 마지막 Node의 정보를 복사
    delete current; //마지막 Node의 매모리를 지우는 과정
    current_size--; //LinkedList의 크기를 줄이기
    return true;
}
template <class T>
void LinkedList<T>::Print()
{
    if (current_size == 0)
        return;
    Node<T> *temp = first; //맨 앞 Node을 임시적으로 저장을 할 Node구현
    for (int i = 0; i < current_size; i++)
    {
        cout << "[" << i + 1 << "|" << first->data << "]";
        if (i != current_size - 1)
            cout << "->";
        first = first->link;
        //LinkedList을 traverse하면서 모든 값을 출력하기 
    }
    cout << endl;
    first = temp;//first을 다시 temp으로 설정하기
}

template <class T>
bool Stack<T>::Delete(T &element)
{
    if (current_size == 0)
        return false;
    Node<T> *del = first; //맨 앞 Node을 가르키는 Node포인터 구현
    first = first->link; //맨 앞 Node을 다음 Node으로 이동하기
    element = del->data; //element에 맨 앞 Node의 정보를 복사
    delete del; //맨 앞 Node의 메모리 지우기
    current_size--; //Stack의 크기를 줄이기
    return true;
}
