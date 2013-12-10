#ifndef _CM_VECTOR_H_
#define _CM_VECTOR_H_

//
//  Trade secret of ATI Technologies, Inc.
//  Copyright 2004, ATI Technologies, Inc., (unpublished)
//
//  All rights reserved.  This notice is intended as a precaution against
//  inadvertent publication and does not imply publication or any waiver
//  of confidentiality.  The year included in the foregoing notice is the
//  year of creation of the work.
//

//
/// @file  cm_vector.h
/// @brief C++ dynamically allocated fixed size array
//


/// Templatized vector class
//
#include <assert.h>
#include <string.h>
template <typename T>
class cmVector
{
public:
    /// A type that counts the number of elements in a vector
    typedef size_t size_type;
    /// A type that provides a random-access iterator that can read or modify any element in a vector
    typedef T* iterator;

    /// @brief Constructor
    cmVector() : _data(0), _size(0), _allocated(0) {}

    /// @brief Fill constructor
    cmVector(size_type size) : _data(0), _size(0), _allocated(0)
    {
        reserve(size);

        // initialize new items
        for(size_type i = 0; i < size; i++)
            _data[i] = T();

        _size = size;
    }

    /// @brief Copy constructor
    cmVector(const cmVector<T>& rhs) : _data(0), _size(0), _allocated(0)
    {
        reserve(rhs.size());
        cmCopy(_data, &rhs[0], rhs.size());
        _size = rhs.size();
    }

    /// @brief Destructor
    ~cmVector() 
    {
        clear();
    }

    /// @brief Copy assignment
    inline cmVector& operator=(const cmVector& rhs) 
    {
        clear();
        reserve(rhs.size());
        cmCopy(_data, &rhs[0], rhs.size());
        _size = rhs.size();

        return *this;
    }

    /// @brief Return the number of elements in the vector
    ///
    /// @return the number of elements in the vector
    inline size_type size() const
    { 
        return _size;
    }

    /// @brief Specifies a new size for a vector
    ///
    /// @param newSize (in) The new size of the vector
    void resize(size_type newSize)
    {
        if(newSize < _size)
        {
            size_type itemsToCopy;
            size_type oldSize = _size;
            T* tmp = new T [newSize];

            _allocated = _size = newSize;

            itemsToCopy = oldSize;
            if (newSize < oldSize)
                itemsToCopy = newSize;

            cmCopy(tmp, _data, itemsToCopy);

            delete [ ] _data;

            _data = tmp;
            return;
        }
        if (newSize > _allocated) {
            reserve(newReserveSZ(newSize));
        }
        _size = newSize;
    }

    /// @brief Reserves a minimum length of storage for a vector object, allocating space if necessary
    ///
    /// @param minSize (in) The minimum length of storage to be allocated for the vector
    void reserve(size_type minSize)
    {
        if(minSize > _allocated)
        {
            // For sizeof(T) == 1 (i.e. char, unsigned char), round up to 16 byte increments
            const size_t roundedSize = sizeof(T) == 1 ? ((minSize + 15) & ~15) : minSize;
            T* tmp = new T [roundedSize];

            if (_data != 0)
            {
                memcpy(tmp, _data, _size*sizeof(void*));

                delete [ ] _data;
            }

            _allocated = roundedSize;
            _data = tmp;
        }
    }

    /// @brief Erases the elements of the vector
    void clear()
    {
        // prevents double deletion
        if (_allocated != 0)
        {
            delete [ ] _data;
            _data = 0;
            _allocated = 0;
            _size = 0;
        }
        
    }

    /// @brief Tests if the vector is empty
    ///
    /// @return true if the vector is empty; false if the vector is not empty
    inline bool empty() const
    {
        return (_size == 0);
    }

    /// @brief Adds an element to the end of the vector
    ///
    /// @param value (in) The element added to the end of the vector
    inline void push_back(const T& value)
    {
        check_alloc();
        _data[_size++] = value;
    }

    /// @brief Adds an element to the end of the vector
    ///
    /// @param value (in) The element added to the end of the vector
    inline void push_back(T& value)
    {
        check_alloc();
        _data[_size++] = value;
    }

    /// @brief Adds several elements to the end of the vector
    ///
    /// @param value (in) The element array added to the end of the vector
    /// @param size (in) Amount of elements to add
    inline void push_back(const T *data, size_type size)
    {
        reserve(_size + size);
        cmCopy(&_data[_size], data, size);
        _size += size;
    }

    /// @brief Deletes the element at the end of the vector
    inline void pop_back()
    {
        if (_size > 0)
            _size--;
    }

    void sort()
    {
        // only sort if we hold more than 1 item
        if(_size > 1)
        {
            q_sort(0, _size);
        }
    }

    /// @brief Returns a reference to the vector element at a specified position
    ///
    /// @param index (in) The position of the vector element
    ///
    /// @return If the position specified is greater than the size of the container,
    ///         the result is undefined
    inline T& operator[](size_type index)
    {
        // array bound check, special case where _size is 0, this is allowed when index is 0
        assert((index < _size) || ((_size == 0) && (index == 0)));
        return _data[index];
    }

    /// @brief Returns a reference to the vector element at a specified position
    ///
    /// @param index (in) The position of the vector element
    ///
    /// @return If the position specified is greater than the size of the container,
    ///         the result is undefined
    inline const T& operator[](size_type index) const
    {
        // array bound check, special case where _size is 0, this is allowed when index is 0
        assert((index < _size) || ((_size == 0) && (index == 0)));
        return _data[index];
    }

    /// @brief Returns a random-access iterator to the first element in the container
    ///
    /// @return A random-access iterator addressing the first element in the vector or to the
    ///         location succeeding an empty vector
    inline iterator begin()
    {
        return &_data[0];
    }

    /// @brief Returns a random-access iterator to the first element in the container
    ///
    /// @return A random-access iterator addressing the first element in the vector or to the
    ///         location succeeding an empty vector
    inline iterator begin() const
    {
        return &_data[0];
    }

    /// @brief Returns a random-access iterator that points just beyond the end of the vector
    ///
    /// @return A random-access iterator to the end of the vector object. If the vector is
    ///         empty, cmVector::end == cmVector::begin
    inline iterator end() const
    {
        return &_data[_size];
    }

    /// @brief Removes an element or a range of elements in a vector from specified positions
    ///
    /// @param element (in) Position of the element to be removed from the vector
    ///
    /// @return An iterator that designates the first element remaining beyond any elements removed,
    ///         or a pointer to the end of the vector if no such element exists
    iterator erase(iterator element)
    {
        size_type offset = element - begin();

        // realloc new array and copy elements over
        if ((int)offset >= 0 && _size > offset)
        {
            //decrease the size
            _size--; 

            memcpy(&_data[offset], &_data[offset + 1], sizeof(void *) * (_size - offset)); 

            return &_data[offset];
        }

        return end();
    }

    iterator find(const iterator element) const
    {
        size_type i=0;
        while(i < _size)
        {
            if(_data[i] == *element)
            {
                return &_data[i];
            }
            i++;
        }
        return end();
    }

    int findIndex(const T& data) const
    {
        for( int i = 0; i < _size; ++i )
            if( _data[i] == data )
                return (int)i;
        return -1;
    }

private:
    inline size_type newReserveSZ(size_type newSize)
    {
        size_type realNewSZ = _allocated * 2;
        return (realNewSZ < newSize) ? newSize : realNewSZ;
    }

    inline void check_alloc()
    {
        if ((_size + 1) > _allocated)
        {
            size_type newSize;

            if (_allocated < 16)
            {
                newSize = _allocated + 1;
            }
            else
            {
                static const size_type maxVectorIncrement = 512;
                if (_allocated < maxVectorIncrement)
                    newSize = _allocated * 2;
                else
                    newSize = _allocated + maxVectorIncrement;
            }

            reserve(newSize);
        }
    }

    inline void swap(size_type a, size_type b) 
    { 
        T t = _data[a];
        _data[a] = _data[b];
        _data[b] = t;
    }


    void q_sort(size_type beg, size_type end) 
    {
        if (end > beg + 1) 
        {          
            T piv = _data[beg];
            size_type l = beg + 1;
            size_type r = end;

            while (l < r) 
            {
                if (_data[l] <= piv) 
                {
                    l++;
                }
                else 
                {
                    swap(l, --r);
                }
            }
            swap(--l, beg);
            q_sort(beg, l);
            q_sort(r, end);
        }
    }

    T*     _data;
    size_type _size;
    size_type _allocated;
};
#endif // _CM_VECTOR_H_
