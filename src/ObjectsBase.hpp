#ifndef OBJECTSBASE_HPP_INCLUDED
#define OBJECTSBASE_HPP_INCLUDED

namespace GameObject {
    class Base {
    public:
        unsigned int x;
        unsigned int y;
        int displayCharacter;
    protected:
        virtual ~Base() = 0;
    };

    // Objects that remain fixed
    class Static : public Base {
    protected:
        virtual ~Static() = 0;
    };

    // Objects that can move
    class Dynamic : public Base {
    protected:
        virtual ~Dynamic() = 0;
    };
}
#endif // OBJECTSBASE_HPP_INCLUDED
