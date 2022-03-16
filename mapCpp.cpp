#include <iostream>
/*
namespace whoamifk_map {
    template<typename _key, typename _val, typename _cmp, typename _Alloc = std::allocator>
    class Map {
    private:

    public:
        typedef std::pair<const key_type, mapped_type> value_type;

    };
}
*/
namespace whoamifk_map {
    template<typename _Key, typename _Ty, typename _Cmp,typename _Alloc = std::allocator<std::pair<const _Key, _Ty>>>
    class Map {
    public:
        typedef Map<_Key, _Ty, _Cmp, _Alloc> _MyMap;
        typedef _Key key_type;
        typedef _Ty mapped_type;
        typedef _Cmp compare_type;
        typedef _Alloc allocator_type;
        typedef std::pair<const key_type, mapped_type> value type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type* iterator;
        typedef const value_type* const_iterator;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        Map()
            : _data(_Alloc().allocate(20)),_size(0),_capacity(20) {}
    private:
        pointer _data;
        size_type _size, _capacity;
    };
}

int main()
{
    std::allocator<int> myAllocator;
    int* arr = myAllocator.allocate(11);
    arr[3] = 10;
    arr[4] = 5;
    arr[1] = -1;
}
