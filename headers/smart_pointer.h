#ifndef BANQUE_SMART_POINTER
#define BANQUE_SMART_POINTER

template<typename T> class SP {
    private:
        T* ptr;
    public:
        SP(T* ptr): ptr(ptr) {};
        ~SP() {
            std::cout << "Smart Pointer is destroyed" << std::endl;
            if (ptr) {
                delete this->ptr;
            }
            
        }



        T* get() {
            return this->ptr;
        }

        T* operator->() {
            return this->ptr;
        }

        T& operator*() {
            return this->ptr;
        }

        int operator==(SP sp){
            if(*this == sp){
                return 1;
            }
            return 0;
        }
};

#endif