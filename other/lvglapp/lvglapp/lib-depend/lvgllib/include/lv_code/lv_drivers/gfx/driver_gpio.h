#include "string.h"
#include "stdio.h"

int gpio_export_init(int pin);  
int gpio_unexport_deinit(int pin);  

//dir: 0-->IN, 1-->OUT
int gpio_direction_set(int pin, int dir);  

//value: 0-->LOW, 1-->HIGH
int gpio_status_write(int pin, int value); 
int gpio_status_read(int pin);  

