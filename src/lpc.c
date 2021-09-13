/*
 * Copyright (C) 2021 İrem Kuyucu <siren@kernal.eu>
 *
 * This file is part of Lapic.
 *
 * Lapic is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lapic is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lapic.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <math.h>

#include "../include/lpc.h"

#define SAMPLE_RATE 44100
#define ORDER 48
#define BUFFER_ORDER 256
#define DX 0.15f

static float temp[BUFFER_ORDER] = {0};
static unsigned offset = 0, x = 0;

void lpc_decode(frame_t p, int pitch, float tempo, float gain, float asp,
                int vibrato, float (*vibr_expr)(int), void (*callback)(float))
{
        double v, y, f, sum;
        float period, sample;
        unsigned samples_per_frame = DX * SAMPLE_RATE / tempo;

        for (int i = 0; i < samples_per_frame; ++i) {
                x++;

                v = pitch;
                /* Vibrato if enabled */
                if (vibrato)
                        v += vibr_expr(vibrato);

                /* Triangle wave source */
                period = SAMPLE_RATE / v;
                x = fmodf(x, period);
                y = 0.005f * abs(x - period);

                f = 0.05f * drand48() + exp2(y) * asp;

                /* Apply coefficients and overlap */
                sum = f;
                for (unsigned j = 0; j < ORDER; ++j)
                        sum -= p.a[j] * temp[(offset + BUFFER_ORDER-j) % BUFFER_ORDER];

                offset++;
                /* Bisqwit's magic */
		temp[offset %= BUFFER_ORDER] = sum;

                sample = sum * sqrt(p.gain + gain);
                callback(sample);
        }
}
