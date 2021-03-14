/*
MIT License

Copyright (c) 2018 José Puga

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef RANDOM_HPP
#define RANDOM_HPP
#define RANDOM_HPP_VERSION "1.0.1"

#include <type_traits>
#include <limits>
#include <random>
#include <chrono>
#ifndef NDEBUG
#include <iostream> //FOR DEBUG ONLY
#endif

template <typename T>
using uniform_distribution =
    typename std::conditional<
            std::is_integral<T>::value,
            std::uniform_int_distribution<T>,
        typename std::conditional<
            std::is_floating_point<T>::value,
            std::uniform_real_distribution<T>,
            void
        >::type
    >::type;


template <typename T>
class Random {
static_assert( //"using = uniform_distribution" above, overwrites the use of this assert
    std::is_integral<T>::value ||
    std::is_floating_point<T>::value,  
    "Random class requires integral of floating point type.");

    public:
        Random();
        Random(const T min, const T max);

        /**
         * @brief Set Min and Max Range for random numbers.
         * @param min (optional) default = std::numeric_limits::min()
         * @param max (optional) default = std::numeric_limits::max()
         * */       
        void SetRange(
            const T min = std::numeric_limits<T>::min(), 
            const T max = std::numeric_limits<T>::max());

        /**
         * @brief Set the seed for the generator. 
         * If the seed is not set. then std::mt19937::default_seed is used.
         * @param min (optional) default = std::numeric_limits::min()
         * @param max (optional) default = std::numeric_limits::max()
         * */          
        void SetSeed(unsigned int seed);

        /**
         * @brief Set a Random Seed based on system clock.
         * */       
        void SetRandomSeed();

        unsigned int GetSeed() const {return m_seed;}

        /**
         * @brief Get a random number between min and max
         * @param min
         * @param max
         * @return Random number.
         * */
        T Get(const T min, const T max) {return _Get(min, max);}

        /**
         * @brief Get a random number. 
         * If range was not set creating the object or with SetRange() then 
         * the range will be std::numeric_limits::min() and std::numeric_limits::max() 
         * @return Random number.
         * */
        T Get() {return _Get(m_min, m_max);}

        /**
         * @brief Get the random engine. For use as param in std::suffle
         * @return Random engine.
         * */
        inline std::mt19937 GetEngine() {return m_engine;}

    private:
        T _Get(const T min, const T max);
        T m_min;
        T m_max;
        unsigned int m_seed {std::mt19937::default_seed};
        std::mt19937 m_engine;

#ifndef NDEBUG
    public:
        void DEBUG() {
            std::cout << "(" << m_seed << "): " << m_min << ", " << m_max << " - " << Get() << "\n";
        }
#endif

};

template <typename T>
Random<T>::Random() 
{
    SetRange();
}

template <typename T>
Random<T>::Random(const T min, const T max) 
{
    SetRange(min, max);
}

template <typename T>
void Random<T>::SetRange(const T min, const T max)
{
    m_min = min;
    m_max = max;
}

template <typename T>
void Random<T>::SetRandomSeed() 
{
    SetSeed(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));

}

template <typename T>
void Random<T>::SetSeed(const unsigned int seed)
{
    m_seed = seed;
    m_engine.seed(m_seed);
} 

template <typename T>

T Random<T>::_Get(const T min, const T max) {

    uniform_distribution<T> dist(min, max);
    return dist(m_engine);
}

#endif // RANDOM_HPP