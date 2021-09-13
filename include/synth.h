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

#ifndef SYNTH_H
#define SYNTH_H

extern int fdout;
extern int out;
extern int save;

int synth(wchar_t *text, int pitch, float tempo, float gain,
		float aspiration, int vibrato);

#endif
