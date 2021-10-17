#include <iostream>
#include <string>

using namespace std ;
int main(){
    char input[2] ; // attention depassement de tampon
    cin >>  input ;
    if( isdigit(input[0]) && isalpha(input[1])){
        input[1] += 'a' - 'A' ;
        cout << input[0] << input[1] << int('A');
    }

    return 0 ;
}