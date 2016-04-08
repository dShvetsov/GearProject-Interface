#include "diversed_object.h"


Diversed_object::Diversed_object(Matrix<uint> &binpic):pic(binpic.deep_copy()), equal(2, 0), obj()
{
    Diver();
    perfom();
}

void Diversed_object::perfom(){
    for (uint i = 2; i < next_obj_number; i++){
        if (equal[i] != i){
            equal[i] = equal[equal[i]]; // каждое элемент массива будет содеражть номер истинного объекта пиксела
            obj[equal[i] - 2].merge(obj[i - 2]);
        }
        else
        {
            uint xstart, xend, ystart, yend;
            tie(xstart, xend, ystart, yend) = obj[i - 2].get_bound();
            if (xend - xstart + yend - ystart <= 1) continue;
            obj_count++;
            obj[i - 2].set_id(i);
        }
    }

    for (auto i = obj.begin(); i != obj.end();){
        if (! (*i).validable()){
                obj.erase(i);
        }
        else
        {
                i++;
        }
    }
    for (uint i = 0; i < pic.n_rows; ++i)
        for (uint j = 0; j < pic.n_cols; ++j)
            pic(i,j) = equal[pic(i,j)];

}

void Diversed_object::connect(uint n, uint m)
{
    if( n != equal[n]){
        connect(equal[n], m);
    }
    if ( m != equal[m]){
        connect(equal[m], n);
    }
    if ( equal[m] == equal[n] )
        return;
    if (m > n){
        equal[m] = equal[n];
    }
    else{
        equal[n] = equal[m];
    }
}

uint Diversed_object::add_complies(uint n, uint m, uint newx, uint newy)
{ //добавим, что n и m обозначают одну и ту же область
    pic(newx, newy) = n;
    if ( n == m ){
         return n;
    }
    connect(n,m);
    return n;
}

uint Diversed_object::add_obj(uint x, uint y)
{
    equal.push_back(next_obj_number);
    obj.push_back(Object(next_obj_number ,x, y));
    pic(x, y) = next_obj_number++;
    return next_obj_number;
}

uint Diversed_object::perfom_obj(uint obj_number, uint newx, uint newy)
{
    pic(newx,newy) = obj_number;
    obj[obj_number - 2].update_axis(newx, newy);
    return obj_number;
}

void Diversed_object::Diver()
{
    next_obj_number = 2;
    if (pic(0,0) != 0) {
        add_obj(0,0);
    }
    for (uint j = 1; j < pic.n_cols; j++)
    { // пройдем по первой строчке и выделим объекты
        if (pic(0, j) != 0)
        {
            pic(0, j - 1) != 0 ? perfom_obj(pic(0, j - 1), 0, j) : add_obj(0, j); // продолжается предыдущий объект или начинается новый
        }
    }
    for (uint i = 1; i < pic.n_rows; i++)
    {
        if (pic(i, 0) != 0) // отдельно обработать первый столбец
        {
            (pic(i - 1, 0) != 0) ? perfom_obj(pic(i - 1, 0), i, 0) : add_obj(i, 0);
        }
        for (uint j = 1; j < pic.n_cols; j++)
        {
            if (pic(i, j) != 0)
            {
                if (pic(i - 1, j) == 0 && pic(i, j - 1) == 0)
                {
                    add_obj(i ,j);
                    continue;
                }
                if (pic(i - 1,j) != pic(i, j - 1) && pic(i - 1, j) != 0 && pic(i, j - 1) != 0)
                {
                    add_complies(pic(i - 1, j), pic(i, j - 1), i, j);
                    continue;
                }
                 // остался случай, когда один из pic() равен нулю, а другой нет

                 if (pic(i, j - 1) != 0 && pic(i - 1, j) == 0){
                    perfom_obj(pic(i, j - 1), i, j);
                    continue;
                }
                if (pic(i - 1, j) != 0 && pic(i, j - 1) == 0){
                    perfom_obj(pic(i - 1, j), i, j);
                    continue;
                }
                perfom_obj(pic(i - 1, j), i , j);
            }
        }
    }
}

