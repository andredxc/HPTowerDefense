#include "TroopList.h"

template <class TipoGenerico>
TroopList<TipoGenerico>::TroopList()
{
    _filaptr = new TipoGenerico[100];
    _maxLen = 99;
    _fim = -1;
};

template <class TipoGenerico>
TroopList<TipoGenerico>::TroopList(int size)
{
    _filaptr = new TipoGenerico[size];
    _maxLen = size - 1;
    _fim = -1;
};

template <class TipoGenerico>
TroopList<TipoGenerico>::~TroopList()
{
    if(_filaptr){
        //TODO: Consertar
        //delete _filaptr;
    }
};

template <class TipoGenerico>
void TroopList<TipoGenerico>::append(TipoGenerico number)
{
    if (_fim == _maxLen)
    {
        std::cerr << "Fila llena" << std::endl;
    }
    else
    {
        _fim = _fim + 1;
        _filaptr[_fim] = number;
        printf("Colocando no fim da lista\n");
        number.print();
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
        std::cerr << "Fila vazia" << std::endl;
        return _filaptr[0];
    }
    else
    {
        return _filaptr[_fim];
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
        printf ("pos[%d]:%u\n", i, _filaptr[i].getHealth());
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
        printf("TroopList: tentativa de acesso a um índice fora de alcance (%d)\n", i);
    }
    return _filaptr[i];
}
