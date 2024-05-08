//
// Created by jvanz on 5/1/2024.
//

// Julia set function: z = x + yi where -2 <= (x,y) <= 2 then iterate Z = Z(n-1)^2 + C
// Page 211 textbook
// Z^2 = sqrt(x(n-1)^2 + y(n-1)^2) ^ 2 which = x^2 + y^2

// First test Q(-1.75)

#include <iostream>
#include <valarray>
#include "JuliaSet.hpp"
#include "SFML/System/Vector2.hpp"

/**
 * iterates the given pixel coordinates (x,y) until either it reaches max iterations or escapes to infinity
 * @param zi (x,y) coordinates for initial conditions
 * const_c arbitrary complex number that the entire image is based on.
 * @return number of iterations computing took (used for gradient)
 */
float JuliaSet::iterate_coordinate(sf::Vector2f zi) {
        float zx = zi.x;
        float zy = zi.y;
        float mod = zx * zx + zy * zy;
        int curr_iter = 0;
        while (mod < 4.0f && (curr_iter < MAX_ITERATIONS)) {
            const float tmp = zx;
            // x coord = x^2 - y^2 + const_x
            zx = zx * zx - zy * zy + const_c.x;
            // y coord = 2.0 (radius of circle to fold) * y * x + const_y
            zy = 2.0f * zy * tmp + const_c.y;
            // modulus or norm of complex number is sqrt(x^2 + y^2), or simpler we check x^2 + y^2 < upper_bound^2 (2^2 = 4.0)
            mod = zx * zx + zy * zy;
            ++curr_iter;
        }
        return static_cast<float>(curr_iter);

}

float JuliaSet::smooth_iterate(sf::Vector2f zi) {
    float zx = zi.x;
    float zy = zi.y;
    float mod = zx * zx + zy * zy;
    int curr_iter = 0;
    while (mod < 4.0f && (curr_iter < MAX_ITERATIONS)) {
        const float tmp = zx;
        // x coord = x^2 - y^2 + const_x
        zx = zx * zx - zy * zy + const_c.x;
        // y coord = 2.0 (radius of circle to fold) * y * x + const_y
        zy = 2.0f * zy * tmp + const_c.y;
        // modulus or norm of complex number is sqrt(x^2 + y^2), or simpler we check x^2 + y^2 < upper_bound^2 (2^2 = 4.0)
        mod = zx * zx + zy * zy;
        ++curr_iter;
    }
    const float final_mod = std::sqrt(mod);
    const float smooth_iters = float(curr_iter) - std::log2(std::max(1.0f, std::log2(final_mod)));
    return smooth_iters;
}

