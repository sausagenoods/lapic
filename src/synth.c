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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>

#include "../include/synth.h"
#include "../include/lpc.h"
#include "../include/frames_default.h"

void write_sample(float sample) {
	if (out)
		write(1, &sample, sizeof(sample));

	if (save)
		write(fdout, &sample, sizeof(sample));
}

float apply_vibrato(int vrate) {
	static unsigned k = 0;
	return 50 * sin(k++/vrate);
}

int synth(wchar_t *text, int pitch_val, float tempo_val, float gain_val,
		float asp_val, int vibrato_val)
{
	voice_bank_t* vbank = &default_vb;

	int pitch;
	if (pitch_val < 0)
		pitch = vbank->pitch;
	else
		pitch = pitch_val;

	wchar_t sounds[30] = L"abcçdefgğhiıjklmnoöprsştuüvyz_";
	for (int i = 0; text[i] != L'\0'; i++) {
		for (int j = 0; j < 30; j++) {
			if (text[i] == sounds[j]) {
				lpc_decode(vbank->frames[j], pitch, tempo_val,
					gain_val, asp_val, vibrato_val,
					apply_vibrato, write_sample);
				break;
			}
		}
	}

	return 0;
}
