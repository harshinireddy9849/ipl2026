#include <stdio.h>

// Define the structure with precise bit allocations
struct DeviceRegister {
    unsigned int power_on   : 1;  // Allocate 1 bit
    unsigned int boot_mode  : 2;  // Allocate 2 bits
    unsigned int error_code : 3;  // Allocate 3 bits
    unsigned int volume     : 4;  // Allocate 4 bits
};

int main() {
    // 1. Check the memory size footprint
    printf("--- Memory Footprint Analysis ---\n");
    printf("Total memory size of struct DeviceRegister: %zu bytes\n\n", sizeof(struct DeviceRegister));

    // 2. Instantiate and assign valid values (Within Limits)
    struct DeviceRegister myDevice;
    
    myDevice.power_on = 1;     // Valid (Fits in 1 bit)
    myDevice.boot_mode = 2;    // Valid (Fits in 2 bits: binary 10)
    myDevice.error_code = 5;   // Valid (Fits in 3 bits: binary 101)
    myDevice.volume = 12;      // Valid (Fits in 4 bits: binary 1100)

    printf("--- Testing Normal Value Assignments ---\n");
    printf("Power Status : %u\n", myDevice.power_on);
    printf("Boot Mode    : %u\n", myDevice.boot_mode);
    printf("Error Code   : %u\n", myDevice.error_code);
    printf("Volume Level : %u\n\n", myDevice.volume);

    // 3. Testing Bound Overflow (What happens if we give too much?)
    printf("--- Testing Bitfield Overflow Behavior ---\n");
    
    // We are trying to force '3' (binary 11) into a 1-bit slot.
    // The compiler will truncate it, keeping only the lowest 1 bit.
    myDevice.power_on = 3; 
    
    // We are trying to force '19' (binary 10011) into a 4-bit slot (max 15).
    // The lowest 4 bits are 0011, which equals decimal 3.
    myDevice.volume = 19; 

    printf("Power Status (assigned 3) truncated to: %u\n", myDevice.power_on);
    printf("Volume Level (assigned 19) truncated to: %u\n", myDevice.volume);

    return 0;
}