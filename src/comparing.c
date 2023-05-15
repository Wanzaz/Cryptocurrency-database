/* 
 * Comparing Functions
 * */

#include "comparing.h"
#include "types.h"
#include <string.h>

/* 
 * Comparing Functions
 * */
int compare(TCryptocurrency x, TCryptocurrency y, CompareType type)
{
    switch (type) {
        case ById:
            return x.id - y.id;
        case ByFoundationYear:
            return x.foundation_year - y.foundation_year;
        case ByName:
            return strcmp(x.name, y.name);
        case ByFounderName:
            return strcmp(x.founder_name, y.founder_name);
        case ByPrice:
            return x.price - y.price;
        case ByCentralization:
            return x.centralized - y.centralized;
  }
}

