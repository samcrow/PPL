#ifndef VARADICCOMPILER_H
#define VARADICCOMPILER_H
#include <vector>


/**
 * @brief Provides a method that compiles
 * varadic arguments into a list
 */
class VaradicCompiler
{
public:
    
    template < typename T, typename... As >
    static std::vector<T> compile(T first, As... others) {
        std::vector<T> vector = compile(others...);
        vector.insert(vector.begin(), first);
        return vector;
    }
    
    template < typename T >
    static std::vector<T> compile(T arg) {
        std::vector<T> vector;
        vector.push_back(arg);
        return vector;
    }
    
    template < typename T >
    static std::vector<T> compile() {
        return std::vector<T>();
    }
    
    VaradicCompiler() = delete;
};

#endif // VARADICCOMPILER_H
