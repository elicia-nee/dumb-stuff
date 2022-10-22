#include <iostream>
void collatz(int input){
    static int counter = 0;
    if(input!=1){
        counter++;
        if (input % 2 == 0){ //Even
            input = input/2;
            return collatz(input);
        }
        input = (input*3 + 1)/2;
        return collatz(input);
    } else{
        std::cout<<"Loops: "<<counter;
    }
}
int main(){
    int input;
    std::cin>>input;
    collatz(abs(input));
    return 0;
}