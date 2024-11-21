#ifndef SINGLETON_H
#define SINGLETON_H

// Generic Singleton based on Singleton from game programming patterns
// https://gameprogrammingpatterns.com/singleton.html

// Originally implemented in Julgen
// https://github.com/JulianRijken/Julgen

namespace bin
{
    template<typename T>
    class Singleton
    {
    public:
        static T& GetInstance()
        {
            static T s_Instance{};
            return s_Instance;
        }

        virtual ~Singleton() = default;

        Singleton(Singleton&& other) = delete;
        Singleton(const Singleton& other) = delete;
        Singleton& operator=(Singleton&& other) = delete;
        Singleton& operator=(const Singleton& other) = delete;

    protected:
        Singleton() = default;
    };
}  // namespace bin
#endif  // SINGLETON_H
