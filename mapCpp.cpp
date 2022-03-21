#include <iostream>

namespace whoamifk_map {
    template<typename _Key, typename _Ty, typename _Alloc = std::allocator<std::pair<const _Key, _Ty>>>
    class Map {
    public:
        typedef Map<_Key, _Ty,_Alloc> _MyMap;
        typedef _Key key_type;
        typedef _Ty mapped_type;
        typedef _Alloc allocator_type;
        typedef std::pair<const key_type, mapped_type> value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type* iterator;
        typedef const value_type* const_iterator;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        Map()
            : _data(_Alloc().allocate(20)), _size(0), _capacity(20) {}
        ~Map() {
            if (!empty()) {
                for (iterator i = begin(); i != end(); ++i) {
                    _Alloc().destroy(i);
                }
                _Alloc().deallocate(_data, _capacity);
            }
        }

        iterator begin() {
            return &_data[0];
        }
        iterator end() {
            return &_data[_size];
        }
        bool empty() const {
            return _size == 0;
         }
        _MyMap& insert(const value_type& _val) {
            if (++_size >= _capacity) {
                reserve(_capacity * 2);
            }
            _Alloc().construct(&_data[_size - 1], _val);
            return *this;
        }
        _MyMap& reserve(size_type _cap) {
            int count = 0;
            if (_cap < _capacity) return *this;
            pointer buff = _Alloc().allocate(_cap);
            for (iterator i = begin(); i != end(); ++i, ++count)
                _Alloc().construct(&buff[count], *i);
            std::swap(_data, buff);
            for (iterator i = &buff[0]; i != &buff[_size]; ++i)
                _Alloc().destroy(i);
            _Alloc().deallocate(buff, _capacity);
            _capacity = _cap;
            return *this;
        }
        bool has_key(const key_type& _k) {
            for (iterator i = begin(); i != end(); ++i) {
                if (i->first == _k) return true;
            }
            return false;
        }
        mapped_type& operator[](const key_type& _k) {
            if (has_key(_k)) {
                for (iterator i = begin(); i != end(); ++i) {
                    if (i->first == _k) return i->second;
                }
            }
            size_type op = _size;
            insert(value_type(_k, mapped_type()));
            return _data[op].second; // def type val
        }
        Map(const _MyMap& _mp)
            :_size(_mp._size), _capacity(_mp._size + 20), _data(_Alloc().allocate(_mp.size))
        {
            if (_mp != nullptr) {
                int count = 0;
                for (iterator i = &_mp._data[0]; i != &_mp._data[_mp._size]; ++i, ++count)
                {
                    _Alloc().construct(&_data[count], *i);
                }
            }
            else throw std::invalid_argument("Nullptr passed as an argument...");
        }
    private:
        pointer _data;
        size_type _size, _capacity;

    };
};

int main()
{
    try {
        whoamifk_map::Map<std::string, int> mp;
    }
    catch (std::exception e) {
        system("cls");
        std::cout << e.what() << std::endl;
    }
}
