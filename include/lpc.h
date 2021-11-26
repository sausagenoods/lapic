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

#ifndef LPC_H
#define LPC_H

typedef struct {
        float a[48];
        float gain;
} frame_t;

typedef struct {
        int sound_count;
	wchar_t *sounds;
	int pitch;
        frame_t frames[30];
} voice_bank_t;

void lpc_decode(frame_t p, int pitch, float tempo, float gain, float asp,
                int vibrato, float (*vibr_expr)(int), void (*callback)(float));

#endif
