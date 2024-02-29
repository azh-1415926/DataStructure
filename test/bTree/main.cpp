#include <iostream>
#include <myDS/bTree.hpp>

class Key
{
    private:
        int m_ID;
    public:
        Key(int id=0): m_ID(id) {  }

        bool operator<(const Key& key)
        {
            return this->m_ID<key.m_ID;
        }

        bool operator>(const Key& key)
        {
            return this->m_ID>key.m_ID;
        }

        Key& operator=(const Key& key)
        {
            this->m_ID=key.m_ID;
            return *this;
        }

        bool operator==(const Key& key)
        {
            return this->m_ID==key.m_ID;
        }

        std::ostream& operator<<(std::ostream& cout)
        {
            cout<<this->m_ID;
            return cout;
        }
        friend std::ostream& operator<<(std::ostream& cout,const Key& key);
};

std::ostream& operator<<(std::ostream& cout,const Key& key)
{
    cout<<key.m_ID;
    return cout;
}

void traversal(int data)
{
    std::cout<<data;
}

int main(){
    azh::BTree<Key,int> tree;
    azh::Vector<int> keys={35,16,18,70,5,50,22,60,13,17,12,45,25,42,15,90,30,7};
    azh::Vector<azh::Pair<Key,int>> vec;
    for(int i=0;i<keys.size();i++)
    {
        vec.push_back(azh::Pair<Key,int>(keys[i],keys[i]));
    }
    tree.insert(vec);
    std::cout<<"Create bTree\n";
    std::cout<<"ShowKeys:";
    tree.show();
    tree.setTraversalFunction(traversal);
    std::cout<<"inOrderTraversal:";
    tree.inOrderTraversal();
    std::cout<<"preOrderTraversal:";
    tree.preOrderTraversal();
    std::cout<<"Delete some keys\n";
    tree.erase(45);
    tree.erase(90);
    tree.erase(50);
    tree.erase(22);
    tree.erase(42);
    std::cout<<"ShowKeys:";
    tree.show();
    std::cout<<"inOrderTraversal:";
    tree.inOrderTraversal();
    std::cout<<"preOrderTraversal:";
    tree.preOrderTraversal();
    return 0;
}