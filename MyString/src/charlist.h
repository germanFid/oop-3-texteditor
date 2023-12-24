#ifndef CHARLIST_H
#define CHARLIST_H

#include <stdlib.h>
#include <stdexcept>

#define EMPTY_ERR    -1
#define OUTBOUND_ERR  1
#define COMMON_ERR -100

class Node {
public:
    char data;
    Node* next;

    Node(char value) : data(value), next(NULL) {}
};

class CharList {
private:
    Node* head;

    // How AllocList WORKS //
    // AllocList is the list of spare allocated elements.
    // It helps to avoid deleting of spare nodes and 
    // reaching size reducing only in shrink_to_fit() func
    // later. You can delete every spare node using
    // allocListFree() func

    Node* allocHead;
    int length;
    int allocListLength;

    void toAllocList(Node* node)
    {
        node->next = NULL;

        if (!allocHead)
        {
            allocHead = node;
        }

        else
        {
            Node* currentNode = allocHead;

            while (currentNode->next)
            {
                currentNode = currentNode->next;
            }

            currentNode->next = node;
        }

        allocListLength++;
    }

    Node* popNewNode()
    {
        if (!allocListLength)
        {
            return NULL;
        }

        Node* node = allocHead;
        allocHead = allocHead->next;

        allocListLength--;

        return node;
    }

    Node* createNode(char value)
    {
        Node* newNode;

        if (allocListLength)
        {
            newNode = popNewNode();
            newNode->data = value;
        }

        else
        {
            newNode = new Node(value);
        }

        return newNode;
    }

public:
    CharList() : head(NULL), allocHead(NULL), length(0), allocListLength(0) {}
    ~CharList()
    {
        for (int i = 0; i < length; i++)
        {
            removeLast();
        }
        
        allocListFree();
    }

    // move semantics
    CharList (CharList&& c) noexcept
    {
        c.head = this->head;
        this->head = nullptr;

        c.allocHead = this->allocHead;
        this->allocHead = nullptr;

        c.length = this->length;
        c.allocListLength = this->allocListLength;
    }

    CharList& operator=(CharList&& c) noexcept
    {
        c.head = this->head;
        this->head = nullptr;

        c.allocHead = this->allocHead;
        this->allocHead = nullptr;

        c.length = this->length;
        c.allocListLength = this->allocListLength;

        return *this;
    }

    void allocListFree()
    {
        Node* currentNode = allocHead;
        Node* tmpNode = NULL;

        if (!currentNode)
        {
            return;
        }

        while (currentNode->next)
        {
            tmpNode = currentNode;
            currentNode = currentNode->next;

            delete tmpNode;    
        }

        if (currentNode)
        {
            delete currentNode;
        }

        allocHead = NULL;

        allocListLength = 0;
    }

    int getLength() const
    {
        return length;
    }

    int getAllocListLength() const
    {
        return allocListLength;
    }

    int getMemoryUnits() const
    {
        return length + allocListLength;
    }

    // Добавление элемента в конец списка
    void append(char value) {
        Node* newNode = createNode(value);
        if (!head) 
        {
            head = newNode;
        } 
        
        else 
        {
            Node* current = head;
            while (current->next)
            {
                current = current->next;
            }
            
            current->next = newNode;
        }

        length++;
    }

    /// @brief appends value to index
    /// @param value 
    /// @param index actual element index
    /// @return 0 if success, otherwise OUTBOUND_ERR or COMMON_ERR
    int appendAt(char value, int index)
    {
        if (index < 0 || index > length)
        {
            return OUTBOUND_ERR;
        }

        Node* newNode;

        if (index == 0)
        {
            newNode = createNode(value);
            newNode->next = head;
            head = newNode;
            length++;
        }

        else if (index == length)
        {
            append(value);
        }

        else
        {
            newNode = createNode(value);
            Node* current = head;
            Node* previous = NULL;

            for (int i = 0; i < index; i++)
            {
                previous = current;
                current = current->next;
            }

            previous->next = newNode;
            newNode->next = current;
            length++;
        }

        return 0;
    }

    /// @brief remove element by it's index
    /// @param index 
    /// @return 0, OUTBOUND_ERR, EMPTY_ERR
    int removeAt(int index) {
        if (!head) {
            return EMPTY_ERR;
        }

        if (index == 0) {
            Node* temp = head;
            head = head->next;
            
            // delete temp;
            toAllocList(temp);

            length--;
            return 0;
        }

        Node* current = head;
        Node* previous = NULL;
        int i = 0;

        while (current && i < index)
        {
            previous = current;
            current = current->next;
            i++;
        }

        if (current)
        {
            previous->next = current->next;
            // delete current;
            toAllocList(current);
        } 
        
        else 
        {
            return OUTBOUND_ERR;
        }

        length--;
        return 0;
    }

    // Удаление элемента с конца списка
    int removeLast() {
        return removeAt(length - 1);
    }

    // Операция индексации
    char operator[](int index) const {
        Node* current = head;
        int i = 0;

        while (current && i < index) {
            current = current->next;
            i++;
        }

        if (current) {
            return current->data;
        } 
        
        else {
            throw std::invalid_argument("invalid index!");
            exit(OUTBOUND_ERR);
        }
    }

    // Конвертация всего списка в null-terminated string
    char* toString() const{
        if (!head) {
            char* emptyString = new char[1];
            emptyString[0] = '\0';
            return emptyString;
        }

        int length = 0;
        Node* current = head;

        // Подсчет длины списка
        while (current) {
            length++;
            current = current->next;
        }

        char* result = new char[length + 1];
        current = head;
        int i = 0;

        // Копирование данных в строку
        while (current) {
            result[i++] = current->data;
            current = current->next;
        }

        result[length] = '\0';
        return result;
    }
};

#endif // CHARLIST_H