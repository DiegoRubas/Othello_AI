#include <iostream>
#include <string>
#include <cmath>
using namespace std ;

pair<int, int> string_to_pos(string input){
    int xPos, yPos ;
    yPos = int(input.at(0)) - 48 - 1;
    xPos = (int(input.at(1) < 97)) ? int(input.at(1)) - 65 : int(input.at(1)) - 97;
    return pair<int, int>(xPos, yPos) ;
}
class validMove
{
public:
    int value, xPos, yPos ;
    string position ;
    validMove *Left ;
    validMove *Right ;
    validMove *Parent ;
    validMove(string pos, int val);
    ~validMove();
};

validMove::validMove(string pos, int val)
{
    position = pos ;
    value = val ;
    xPos = string_to_pos(position).first ;
    yPos = string_to_pos(position).second ;
}

validMove::~validMove()
{
}

void max_heapify(validMove *array, int size, int i){
    int left = 2*i ;
    int right = 2*i +1 ;
    int largest = 0 ;
    if(left <= size && array[left-1].value > array[i-1].value) largest = left ;
    else largest = i ;
    
    if(right <= size && array[right-1].value > array[largest-1].value) largest = right ;

    if(largest != i){
        validMove temp = array[i-1] ;
        array[i-1] = array[largest-1] ;
        array[largest-1] = temp ;
        max_heapify(array, size, largest) ;
    }

}

void build_max_heap(validMove *array, int size){
    for (int i = floor(size/2); i >= 1; i--)
    {
        max_heapify(array, size, i) ;
    }
    
}

int main(){
    validMove move1("4c", 4) ;
    validMove move2("1c", 1) ;
    validMove move3("4d", 3) ;
    validMove move4("6e", 2) ;
    validMove move5("4e", 16) ;
    validMove move6("6c", 9) ;
    validMove move7("6a", 10) ;
    validMove move8("5c", 14) ;
    validMove move9("2c", 8) ;
    validMove move10("6b", 7) ;

    validMove array[] = {move1, move2, move3, move4, move5, move6, move7, move8, move9, move10} ;
    
    build_max_heap(array, 10) ;
    for (int i = 1; i <= 10; i++)
    {
        int par, right, left ;
        par = floor(i/2) ;
        left = 2*i ;
        right = 2*i +1 ;

        if(par != 0 ) array[i-1].Parent = &array[par-1] ;
        else array[i-1].Parent = NULL ;

        if(left <= 10) array[i-1].Left = &array[left-1] ;
        else array[i-1].Left = NULL ;

        if(right <= 10) array[i-1].Right = &array[right-1] ;
        else array[i-1].Right = NULL ;
    }
    int n = 1 ;
    n--;
    cout << array[n].value << endl ;
    cout << array[n].Parent->value << endl ;
    cout << array[n].Left->value << endl ;
    cout << array[n].Right->value << endl ;
    return 0 ;
}