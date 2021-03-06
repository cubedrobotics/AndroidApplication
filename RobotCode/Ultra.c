//Get the distance from the front of the robot using the ultrasonic sensor

#include <roboticscape.h>
#include <rc_usefulincludes.h> 
#define TRIGGER BLUE_GP0_PIN_3

int main()
{
    /*
    Send pulse
    Wait for rising edge
    Get start time
    Wait for falling edge
    Get stop edge
    Calculate difference (amount of time pin was high)
    */
    rc_initialize();
    //rc_set_cpu_freq(FREQ_1000MHZ);
    rc_set_state(RUNNING);
    rc_gpio_export(TRIGGER);
    rc_gpio_set_dir(TRIGGER, OUTPUT_PIN);
    rc_gpio_set_value_mmap(TRIGGER, LOW);
    //const unsigned long timeout = 20000000;
    //while(rc_get_state()!=EXITING)
   //{
    rc_gpio_set_value(TRIGGER, HIGH);
    rc_usleep(500);
    rc_gpio_set_value(TRIGGER, LOW);
    rc_gpio_set_dir(TRIGGER, INPUT_PIN);
    
    while(rc_gpio_get_value(TRIGGER) == LOW);
    long startTime = rc_nanos_since_epoch();
    //long start = rc_nanos_since_epoch();
    
    while(rc_gpio_get_value(TRIGGER) == HIGH);
    //long startTime = rc_nanos_since_epoch();
    long travelTime = rc_nanos_since_epoch() - startTime;
    printf("%6d\n", rc_gpio_get_value(TRIGGER));
    
    float distance = travelTime / 148;
    //printf("%6d\n", travelTime);
    printf("%6d\n", distance);
    //} 
    rc_gpio_set_value(TRIGGER, LOW);
    rc_gpio_unexport(TRIGGER);
    rc_cleanup();
    return -1;
}
