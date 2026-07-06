#include<bits/stdc++.h> 
using namespace std;

void ALU_decimal_into_binary(int n) {
    if (n == 0) 
    {
        cout << 0 << "\n";
        return;
    }

    // Treating the number as raw bits
    // so that it works for right-shifting negative numbers too 
    unsigned int u = n; 

    // This flag helps us ignore leading zeros for positive numbers
    bool skip_leading_zeros = true;

    // int is 32 bits. Read them from left (31) to right (0).
    for (int i = 31; i >= 0; i--) {
        // to get ith bit we shift i times and use &1 to get it 
        int current_bit = (u >> i) & 1;

        // Once we hit our first '1', we can start printing the bits 
        if (current_bit == 1) {
            skip_leading_zeros = false;
        }

        // Print the bits from now on 
        // would print 32 bits represenation if the sent number is negative 
        if (!skip_leading_zeros) {
            cout << current_bit;
        }
    }
    cout << "\n";
}

int ALU_binary_to_decimal ( string binary )
{ 
    int decimal = 0 ;

    if (binary[0] == '1') {
        while (binary.length() < 32) {
            binary = "1" + binary;
        }
    }

    for ( int i = 0 ; i <binary.length() ; i++)
    { 
        // following bitwise we shift bits to left so there would be 0 in the rightmost position
        decimal <<=1 ; 
        if ( binary[i]=='1')
        { 
            // since doing xor with 1 would just add 1 if binary string had 1 or else the 0 would be the as it was 
            decimal^=1 ; 
        }
    }

    return decimal ;  
}

int ALU_bitwise_addition(int a , int b )
// this is the exact logic for bitwise half adder 
{ 
    while(a!=0)
    { 
        // finding out the carrying we need to do later on 
        int carry = a&b ; 
        // the total sum without carries
        b = a^b ; 
        // change 'a' into left shift of carries so when loop runs again we add the carries 
        a = (unsigned int) carry << 1 ;
    }
    return b ;
}

int ALU_bitwise_subtraction ( int a , int b )
{ 
    // since ALU does not have the concept of substraction it looks at a-b as a + (-b) 
    // we need to do two's complement to b 

    // doing two's complement 
    int negative_b = ~b ; // this inverts the bits ( ~ is the NOT function )
    int add_one = 1 ; 
    while ( add_one != 0 )
    { 
        int carry = negative_b&add_one ; 
        negative_b = negative_b^add_one ; 
        add_one = (unsigned int )carry << 1 ; 
    }

    // doing the normal addtion

    return ALU_bitwise_addition(negative_b , a ) ; 
}

int ALU_bitwise_multiplication ( int a , int b ) 
{ 
    int result = 0 ; 
    while ( b!= 0 )
    { 
        if (b&1) 
        { 
            result = ALU_bitwise_addition(result,a); 
        }
        a <<= 1 ; 
        b = (unsigned int) b >> 1 ; 
    }

    return result ; 
}

// there is no need to write code for logic gates or shift operations since u can directly do AND(&) , OR (|) , XOR (^), NOT (~) , left shift ( << ) , right shift ( >> ) 

// This represents the physical output bus of the ALU
struct ALU_Output {
    LL result;
    bool Z; // Zero Flag
    bool S; // Sign Flag (Negative)
    bool O; // Overflow Flag
};

ALU_Output ALU_flags_calculate ( int a , int b ) 
{ 
    ALU_Output output ; 
    output.result = ALU_bitwise_addition(a , b ) ; 

    output.Z = ( output.result == 0 ) ; 
    output.S = (output.result>>31)&1  ; 

    // checking signs of a and b by doing ^ with output since if a is +ve and output is negative it would result in 1 
    // we do & just to be safe from false alarms like in case of  3 + -2 
    int overflow_check = (a^output.result)&(b^output.result);

    output.O = (overflow_check>>31)&1 ; 

    return output;

}

int main () 
{   
    // Testing arithmetic functions
    cout << ALU_bitwise_subtraction(5,4) << "\n" ; 
    
    cout << ALU_bitwise_addition(2,3) << "\n" ; 

    cout << ALU_bitwise_addition(-2,-3) << "\n" ; 
    
    cout << ALU_bitwise_addition(-3,2) << "\n" ; 

    // Testing Decimal To Binary conversions
    
    ALU_decimal_into_binary(5) ; 

    ALU_decimal_into_binary(-5) ; 

    // testing Binary to Decimal conversions

    // 101 is 5 in decimal 
    cout << ALU_binary_to_decimal("101") << "\n"; 

    // 1011 is 4 bit representation of -5 
    cout << ALU_binary_to_decimal("1011") << "\n" ; 

    // Testing Multiplcation function

    cout << ALU_bitwise_multiplication(3 , 3 ) ; 

    // Testing Hardware Status Flags

    int two_billion = 2000000000 ; 
    int another_two_billion = 2000000000; 
    // taking 2 2 billions to adding them to see if out ALU flags are working 

    ALU_Output check = ALU_flags_calculate(two_billion , another_two_billion) ;
    cout << " ALU flags check result " << "\n" ;
    cout << check.result << "\n"; 
    cout << check.Z << "\n" ; 
    cout << check.S << "\n" ; 
    cout << check.O << "\n"; 
}
