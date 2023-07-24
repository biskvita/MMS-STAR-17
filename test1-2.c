#include <stdio.h>
#include <stdint.h>

unsigned countSetBits(uint64_t num)
{
    unsigned count = 0;

    while (num) 
    {
        count += num & 1;
        num >>= 1;
    }

    return count;
}

unsigned onesCount(uint64_t mask1, uint32_t mask2, uint16_t mask3, uint8_t mask4)
{
    return countSetBits(mask1) + countSetBits(mask2) + countSetBits(mask3) + countSetBits(mask4);
}

void flipOddBits(uint64_t* mask)
{
    int count = 0;
    uint64_t temp = *mask;

    while (temp)
    {
        if (count % 2 != 0)
        {
            
        }

        temp >>= 1;
        ++count; 
    }
}

void mirrorBits(uint16_t* mask)
{
    uint16_t rev = 0;
    uint16_t copy = *mask; 
 
    while (copy) 
    {
        rev <<= 1;
 
        if (copy & 1 == 1)
        {
            rev ^= 1;
        }
            
        copy >>= 1;
    }

    *mask = rev; 
}

int main()
{
    // 00010111
    uint64_t x = 23;
    uint16_t y = 10; 
    
    mirrorBits(&y);
    printf("%d", y);

    return 0; 
}