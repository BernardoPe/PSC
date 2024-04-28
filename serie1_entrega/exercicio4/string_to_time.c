#include <stdio.h>
#include <time.h>

#define FIELDS 6

const int field_lengths[] = {2, 2, 4, 2, 2, 2};

int string_to_time(const char *string, struct tm *tm) {
    int i = 0;
    int value = 0;
    int digit_count = 0;
    int field = 0;

    while (string[i] != '\0') {
        //check if char is a number and add it to value
        if (string[i] >= '0' && string[i] <= '9') {
            value = value * 10 + (string[i] - '0');
            digit_count++;
        } else if (string[i] == '-' || string[i] == ' ' || string[i] == ':') {

            //check if the field length is valid
            if(field_lengths[field] != digit_count) return 0;
            //set time property based on the current field
            switch (field) {
                case 0:
                    tm->tm_mday = value;
                    break;
                case 1:
                    tm->tm_mon = value - 1; 
                    break;
                case 2:
                    tm->tm_year = value - 1900; 
                    break;
                case 3:
                    tm->tm_hour = value;
                    break;
                case 4:
                    tm->tm_min = value;
                    break;
                case 5:
                    tm->tm_sec = value;
                    break;
                default:
                    return 0;
            }
            value = 0;
            digit_count = 0;
            field++;
        } else return 0;
        i++;
    }
    //set last property, string might not contain separator at the end
    if (field == FIELDS - 1) tm->tm_sec = value;
    else return 0;
    
    tm->tm_wday = 0;
    tm->tm_yday = 0;
    tm->tm_isdst = 0;

    return 1; 
}
