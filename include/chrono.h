/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-20-2019
* Chrono Header
*/

#ifndef __CHRONO_H__
#define __CHRONO_H__

namespace Suffer {

    class Chrono {

    public:

        Chrono();
        ~Chrono();

        /**
         * @brief: returns the current time
         */
        double Now();

        /**
         * @brief: calculates the difference between two time values.
         */
        double Difference(const double end, const double start);

        // Converters
        double ToSeconds(const double value);
        double ToNanoseconds(const double value);
        double ToMilliseconds(const double value);
        double ToMicroseconds(const double value);

    };

}

#endif // __CHRONO_H__