#ifndef SORT_CASE_H
#define SORT_CASE_H

#include <functional>
#include <simpleDS/vector.hpp>

namespace azh
{
    /* T1 为排序示例的数据类型，T2 为生成数据的种子类型，T3为用于生成数据的函数容器类型 */
    template<class T1,class T2=int,class T3=std::function<T1(T2)>>
    class sortCase
    {
        private:
            size_t m_Sum;
            T2 m_LowerLimit;
            T2 m_UpperLimit;
            T3 m_FuncOfRand;

        public:
            explicit sortCase(size_t n,const T2& lowerLimit,const T2& upperLimit)
                : m_Sum(n), m_LowerLimit(lowerLimit), m_UpperLimit(upperLimit) {  }

            inline void setRandFunction(T3 funcOfRand) { m_FuncOfRand=funcOfRand; }
            
            Vector<T1> getNoRepeat();
            Vector<T1> getNoRepeatByCount(size_t refreshCount);

            static bool verify(Vector<T1> vec,std::function<int(const T1&,const T1&)> comparision);

        private:
            Vector<T1> getNoRepeatData();
    };

    template<class T1,class T2,class T3>
    Vector<T1> sortCase<T1,T2,T3>::getNoRepeat()
    {
        if(!m_FuncOfRand)
            throw "sortCase:not call setRandFunction!";
        return getNoRepeatData();
    }

    template<class T1,class T2,class T3>
    Vector<T1> sortCase<T1,T2,T3>::getNoRepeatByCount(size_t refreshCount)
    {
        if(!m_FuncOfRand)
            throw "sortCase:not call setRandFunction!";
        static Vector<T1> vec;
        static size_t count=0;
        if(count==0||count>=refreshCount)
        {
            vec=getNoRepeatData();
            count++;
            if(count>=refreshCount)
                count=0;
        }
        return vec;
    }

    template<class T1,class T2,class T3>
    Vector<T1> sortCase<T1,T2,T3>::getNoRepeatData()
    {
        Vector<T1> vec;
        auto seed=m_UpperLimit-m_LowerLimit;
        if(seed<m_Sum)
            throw "sortCase:seed is smaller than n!";
        for(T2 i=m_LowerLimit;i<m_UpperLimit;)
        {
            T1 data=m_FuncOfRand(i);
            bool isVaild=true;
            for(size_t j=0;j<vec.size();j++)
            {
                if(data==vec[j])
                {
                    isVaild=false;
                    break;
                }
            }
            if(isVaild)
            {
                vec.push_back(data);
                i++;
            }
        }
        return vec;
    }

    template<class T1,class T2,class T3>
    bool sortCase<T1,T2,T3>::verify(Vector<T1> vec,std::function<int(const T1&,const T1&)> comparision)
    {
        for(auto i=vec.begin();i!=vec.end()-1;i++)
        {
            if(comparision(*i,*(i+1))>0)
                return false;
        }
        return true;
    }
}

#endif /* SORT_CASE_H */
