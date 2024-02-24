#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <ctime>

namespace azh
{
    class Timer
    {
        private:
            clock_t m_Start;

        public:
            Timer() {  }
            ~Timer() {  }

            void start() { m_Start=clock(); }
            double end()
            {
                clock_t end=clock();
                return (end-m_Start)/1.0/CLOCKS_PER_SEC;
            }
    };
};

#endif /* TIMER_H */