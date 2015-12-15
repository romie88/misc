#include <iostream>
#include "6.frequency.h"

void print_vector( const std::vector< int > & result ) {
    for ( const auto r : result )
        std::cout << r << " ";
    std::cout << std::endl;
}

void test_driver_July( unsigned int n ) {
    std::cout << "test for n = " << n << std::endl;
    SolutionJuly sln( n );
    print_vector( sln.getResult() );
}

void test_driver_BF( const std::vector< int > & nums ) {
    print_vector( nums );
    SolutionBF sln( nums );
    print_vector( sln.getResult() );
}

int main()
{
    for( unsigned int i = 7; i < 20; ++i )
    {
        test_driver_July( i );
    }
    
    test_driver_BF( std::vector< int >( { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } ) );
    
    test_driver_BF( std::vector< int >( { 0, -1, 1, 2, -2, 3, 4, 5, 7, 8, 10 } ) );
    
    test_driver_BF( std::vector< int >( { 1, 2, 3 } ) );
    
    return 0;
}
