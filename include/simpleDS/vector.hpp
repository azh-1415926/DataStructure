#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>

namespace azh
{
    template<class T>
    class vector
    {
        private:
            T* m_Data;
            size_t m_Size;
            size_t m_Capacity;
            size_t m_Increments;

        public:
            explicit vector(size_t capacity=10)
                : m_Size(0), m_Capacity(10), m_Increments(20) { m_Data=new T[m_Capacity]; }

            vector(std::initializer_list<T> list)
                : m_Size(0), m_Capacity(list.size()), m_Increments(20)
                {
                    m_Data=new T[m_Capacity];
                    size_t i=0;
                    for(auto it=list.begin();it!=list.end();it++)
                    {
                        m_Data[i]=*it;
                        i++;
                    }
                    m_Size=m_Capacity;
                }

            vector(const vector& vec)
                : m_Size(vec.m_Size), m_Capacity(vec.m_Capacity), m_Increments(vec.m_Increments)
            {
                m_Data=new T[m_Size];
                for(size_t i=0;i<m_Size;i++)
                    m_Data[i]=vec.m_Data[i];
            }
            
            ~vector() { delete[] m_Data; }

            inline bool empty() const { return m_Size==0; }
            inline size_t size() const { return m_Size; }
            inline size_t capacity() const { return m_Capacity; }
            inline size_t increments() const { return m_Increments; }
            
            inline void setIncrements(size_t increments) { m_Increments=increments; }

            void reserve(size_t n);
            
            inline void push_back(const T& data)
            {
                if(m_Size==m_Capacity)
                    reserve(m_Capacity+m_Increments);
                m_Data[m_Size++]=data;
            }

            inline void pop_back() { m_Size--; }

            T& operator[](size_t i) { return m_Data[i]; }
            const T& operator[](size_t i) const { return m_Data[i]; }

            vector& operator=(const vector& vec)
            {
                m_Size=vec.m_Size;
                m_Capacity=vec.m_Capacity;
                m_Increments=vec.m_Increments;
                delete[] m_Data;
                m_Data=new T[m_Size];
                for(size_t i=0;i<m_Size;i++)
                    m_Data[i]=vec.m_Data[i];
            }
            
            class iterator
            {
                private:
                    vector* m_Vector;
                    size_t m_Index;
                
                public:
                    iterator(vector* vec=nullptr,size_t i=0)
                        : m_Vector(vec), m_Index(i) {  }

                    iterator(const iterator& it)
                        : m_Vector(it.m_Vector), m_Index(it.m_Index) {  }

                    iterator& operator=(const iterator& it)
                    {
                        m_Vector=it.m_Vector;
                        m_Index=it.m_Index;
                    }

                    iterator& operator++() { m_Index++; return *this; }

                    iterator operator++(int)
                    {
                        iterator it=*this;
                        m_Index++;
                        return it;
                    }

                    iterator& operator--() { m_Index--; return *this; }
                    
                    iterator operator--(int)
                    {
                        iterator it=*this;
                        m_Index--;
                        return it;
                    }

                    bool operator!=(const iterator& it) { return !(m_Vector==it.m_Vector&&m_Index==it.m_Index); }

                    T& operator*() { return (*m_Vector)[m_Index]; }

                    int operator-(const iterator& it)
                    {
                        if(m_Vector!=it.m_Vector)
                            throw std::invalid_argument("vector iterator error!");
                        return m_Index-it.m_Index;
                    }
                    
                    iterator operator-(int i) { return iterator(m_Vector,m_Index-i); }
                    iterator operator+(int i) { return iterator(m_Vector,m_Index+i); }
            };

            inline iterator begin() { return iterator(this,0); }
            inline iterator end() { return iterator(this,m_Size); }
    };

    template <class T>
    void vector<T>::reserve(size_t n)
    {
        if(n<m_Size)
            return;
        T* temp=new T[n];
        for(size_t i=0;i<m_Size;i++)
            temp[i]=m_Data[i];
        delete[] m_Data;
        m_Data=temp;
        m_Capacity=n;
    }
}

#endif /* VECTOR_H */