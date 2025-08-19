#include <iostream>
#include <conio.h>

#include "hello.h"
#include "lib.h"

int main() { 
    hello::greetings(std::cout);
    std::cout<<"\nversion:"<< version()<<std::endl;
    getch();
 }
