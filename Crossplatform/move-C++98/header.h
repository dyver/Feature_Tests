#define TO_MOVE

namespace cmn
{
    /// Последовательный массив данных с семантикой перемещения
    template <class T> struct varray
    {
        public:
            varray(int s = 0) { size = s; buffer = new T[size]; }
            varray(const varray& sample) { /// конструктор перемещения для C++98
                size = sample.size;
#ifdef TO_MOVE
                // FIXME: MOVING SEMANTICS
                buffer = sample.buffer;
                varray& dirty_trick = const_cast<varray&>(sample);
                dirty_trick.size = 0;
                dirty_trick.buffer = 0;
#else
                buffer = new T[size];
                for (int i = 0; i < size; ++i) buffer[i] = sample.buffer[i];
#endif
            }
            varray& operator=(const varray& sample) { /// оператор перемещения для C++98
                if (buffer) delete[] buffer;
                size = sample.size;
#ifdef TO_MOVE
                // FIXME: MOVING SEMANTICS
                buffer = sample.buffer;
                varray& dirty_trick = const_cast<varray&>(sample);
                dirty_trick.size = 0;
                dirty_trick.buffer = 0;
#else
                buffer = new T[size];
                for (int i = 0; i < size; ++i) buffer[i] = sample.buffer[i];
#endif
                return *this;
            }
            ~varray() { if (buffer) delete[] buffer; }
            varray& clone() {
//                varray result(size);
//                for (int i = 0; i < size; ++i) result.buffer[i] = buffer[i];
//                return result;
                return *this;
            }

            T* getBuffer() { return buffer; }
            int getSize() { return size; }
            T& operator[](int index) { return buffer[index]; }
        private:
            T* buffer;
            int size;
    };
}
