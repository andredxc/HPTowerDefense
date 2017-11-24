#include <SDL2/SDL.h>

#include "TroopList.h"

template <class TipoGenerico>
TroopList<TipoGenerico>::TroopList()
{
    _listPtr = new TipoGenerico[100];
    _maxLen = 99;
    _fim = -1;
};

template <class TipoGenerico>
TroopList<TipoGenerico>::TroopList(int size)
{
    _listPtr = new TipoGenerico[size];
    _maxLen = size - 1;
    _fim = -1;
};

template <class TipoGenerico>
TroopList<TipoGenerico>::~TroopList()
{
    if(_listPtr){
        //TODO: Consertar
        //delete _listPtr;
    }
};

template <class TipoGenerico>
void TroopList<TipoGenerico>::append(TipoGenerico unit)
{
    if (_fim == _maxLen)
    {
        std::cerr << "TroopList is full" << std::endl;
    }
    else
    {
        _fim = _fim + 1;
        _listPtr[_fim] = unit;
    }
};

template <class TipoGenerico>
void TroopList<TipoGenerico>::remove()
{
    if (_fim == -1)
    {
        std::cerr << "Fila vazia" << std::endl;
    }
    else
    {
        _fim = _fim - 1;
    }
};

template <class TipoGenerico>
TipoGenerico TroopList<TipoGenerico>::last()
{
    if (isEmpty())
    {
        std::cerr << "TroopList is empty" << std::endl;
        return _listPtr[0];
    }
    else
    {
        return _listPtr[_fim];
    }
};

template <class TipoGenerico>
int TroopList<TipoGenerico>::isEmpty()
{
    return _fim == -1;
};

template <class TipoGenerico>
void TroopList<TipoGenerico>::print()
{
    int i = 0;
    for (i = 0; i <= _fim; i++)
    {
        //printf("%d\n",i);
        printf ("pos[%d]:%u\n", i, _listPtr[i].getHealth());
    }
};

template <class TipoGenerico>
int TroopList<TipoGenerico>::size()
{
    return _fim+1;
}

template <class TipoGenerico>
TipoGenerico TroopList<TipoGenerico>::at(int i)
{
    if(i < 0 || i >= size())
    {
        printf("TroopList: index %d is out of bounds\n", i);
    }
    return _listPtr[i];
}
