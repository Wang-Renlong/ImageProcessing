#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>

#define NULL_NODE 0xFFFFFFFF

template <class T>
class Quadtree{
private:
    //T *data;
    //unsigned int *p; //指向父节点
    //unsigned int *a1;//指向第一个子节点
    //unsigned int *a2;//指向第二个子节点
    //unsigned int *a3;//指向第三个子节点
    //unsigned int *a4;//指向第四个子节点
    std::vector<T> data;
    std::vector<unsigned int> p; //指向父节点
    std::vector<unsigned int> a1;//指向第一个子节点
    std::vector<unsigned int> a2;//指向第二个子节点
    std::vector<unsigned int> a3;//指向第三个子节点
    std::vector<unsigned int> a4;//指向第四个子节点

    unsigned int lenth;//总长度
    unsigned int used;//已用节点数量, 指向第一个未使用的空间

public:
    Quadtree(unsigned int max_len);
    ~Quadtree();

    unsigned int add(unsigned int super, unsigned char c, T& t);
    unsigned int add(unsigned int super, T& t);
    T& getById(unsigned int index);
    unsigned int getChildIndex(unsigned int index, unsigned char c);
    unsigned int getSuperIndex(unsigned int index);
    unsigned char getPosInSuper(unsigned int index);
    void deleteChild(unsigned int index, unsigned char c);
    bool isLeaf(unsigned int index);
    T* getPtrById(unsigned int index);
    unsigned int sum();
    void printTree();
};

template <class T>
Quadtree<T>::Quadtree(unsigned int max_lenth)
              :lenth(max_lenth), used(0)
{
    data = std::vector<T>(max_lenth);
    p = std::vector<unsigned int>(max_lenth);
    a1 = std::vector<unsigned int>(max_lenth);
    a2 = std::vector<unsigned int>(max_lenth);
    a3 = std::vector<unsigned int>(max_lenth);
    a4 = std::vector<unsigned int>(max_lenth);

}//end func

template <class T>
Quadtree<T>::~Quadtree()
{
    data.clear();
    p.clear();
    a1.clear();
    a2.clear();
    a3.clear();
    a4.clear();
}//end func

template <class T>
unsigned int Quadtree<T>::add(unsigned int super, unsigned char c, T& t)
{
    bool success = true;
    //没有多余空间
    if(used >= lenth)
        return NULL_NODE;
    //if(used != 0 && a1[super]>0 && a2[super]>0 && a3[super]>0 && a4[super]>0)
    //    return FALSE;
    //节点赋值
    data[used] = t;
    //父节点指向
    p[used] = super;
    //初始化子节点指向
    a1[used] = NULL_NODE;
    a2[used] = NULL_NODE;
    a3[used] = NULL_NODE;
    a4[used] = NULL_NODE;
    if(used == 0)//头节点
    {
        p[used] = NULL_NODE;
    }
    else if(super < used)//加入父节点
    {
        switch(c)
        {
        case 1:
            if(a1[super] == NULL_NODE)
                a1[super] = used;
            else
                success = false;
            break;
        case 2:
            if(a2[super] == NULL_NODE)
                a2[super] = used;
            else
                success = false;
            break;
        case 3:
            if(a3[super] == NULL_NODE)
                a3[super] = used;
            else
                success = false;
            break;
        case 4:
            if(a4[super] == NULL_NODE)
                a4[super] = used;
            else
                success = false;
            break;
        default:
            success = false;
            break;
        }//end switch
    }
    else
        success = false;

    if(success)
    {
        //log
        //printf("Quadtree.add: used=%d\n", used+1);

        used++;
        return used-1;
    }
    else
        return NULL_NODE;
}

template <class T>
unsigned int Quadtree<T>::add(unsigned int super, T& t)
{
    unsigned int result = NULL_NODE;
    if(used >= lenth || super >= used)
        return NULL_NODE;
    if(used == 0)
        result = add(super, 1, t);
    else if(a1[super] == NULL_NODE)
        result = add(super, 1, t);
    else if(a2[super] == NULL_NODE)
        result = add(super, 2, t);
    else if(a3[super] == NULL_NODE)
        result = add(super, 3, t);
    else if(a4[super] == NULL_NODE)
        result = add(super, 4, t);
    return result;
}

template <class T>
T& Quadtree<T>::getById(unsigned int index)
{
    if(index < used)
        return data[index];
    else
        return data[0];
}

template <class T>
unsigned int Quadtree<T>::getChildIndex(unsigned int index, unsigned char c)
{
    if(index > used)
        return NULL_NODE;
    if(c == 1)
        return a1[index];
    else if(c == 2)
        return a2[index];
    else if(c == 3)
        return a3[index];
    else if(c == 4)
        return a4[index];
    else
        return NULL_NODE;
}

template <class T>
unsigned int Quadtree<T>::getSuperIndex(unsigned int index)
{
    if(index >= used)
        return NULL_NODE;
    else
        return p[index];
}

template <class T>
unsigned char Quadtree<T>::getPosInSuper(unsigned int index)
{
    unsigned int super = getSuperIndex(index);
    if(super == NULL_NODE)
        return 0;
    else if(a1[super] == index)
        return 1;
    else if(a2[super] == index)
        return 2;
    else if(a3[super] == index)
        return 3;
    else if(a4[super] == index)
        return 4;
    else
        return 0;
}

template <class T>
void Quadtree<T>::printTree()
{
    for(int i = 0; i < used; i++)
        printf("ind: %d sup: %d chd: %d %d %d %d\n", i, p[i], a1[i], a2[i], a3[i], a4[i]);
    printf("\n");
}

template <class T>
bool Quadtree<T>::isLeaf(unsigned int index)
 {
     if(index >= used)
        return true;
     else if(a1[index] == NULL_NODE && a2[index] == NULL_NODE &&
             a3[index] == NULL_NODE && a4[index] == NULL_NODE)
        return true;
     else
        return false;
 }

template <class T>
void Quadtree<T>::deleteChild(unsigned int index, unsigned char c)
{
    unsigned int temp = NULL_NODE;
    if(c == 1)
    {
        temp = a1[index];
        a1[index] = NULL_NODE;
    }
    else if(c == 2)
    {
        temp = a2[index];
        a2[index] = NULL_NODE;
    }
    else if(c == 3)
    {
        temp = a3[index];
        a3[index] = NULL_NODE;
    }
    else if(c == 4)
    {
        temp = a4[index];
        a4[index] = NULL_NODE;
    }
    if(temp != NULL_NODE)
        p[temp] = NULL_NODE;
}

template <class T>
T* Quadtree<T>::getPtrById(unsigned int index)
{
    if(index >= used)
        return NULL;
    else
        return &(data[index]);
}

template <class T>
unsigned int Quadtree<T>::sum()
{
    return used;
}

#endif // QUADTREE_H
