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
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#include "../include/synth.h"

void process_text(char *src, wchar_t **dest);
void err_exit(const char *message);

int fdout, save = 0, out = 0;

const char *usage = "Usage: synth -s \"text\" -o out.wav\n"
		   "	-s <text>\n"
		   "	-o <path>: PCM output to file\n"
		   "	-t <tempo value>\n"
		   "	-p <pitch value>\n"
		   "	-g <gain value>\n"
		   "	-a <aspiration value>\n"
		   "	-v <vibrato value> (100-10000)\n"
		   "	-h: print help";

int main(int argc, char *argv[])
{
	if (argc == 1)
		err_exit(usage);

	setlocale(LC_ALL, "");

	wchar_t *text_buf;

	int pitch = -1, vibrato = 0;
	float asp = 1, gain = 0, tempo = 1;

	int opt;
	while ((opt = getopt(argc, argv, "s:t:o:p:t:g:a:v:h")) != -1) {
		switch (opt) {
		case 's':
			process_text(optarg, &text_buf);
			break;

		case 'o':
			if (strcmp(optarg, "stdout") == 0) {
				out = 1;
			} else {
				fdout = open(optarg, O_WRONLY | O_CREAT, 0644);
				save = 1;
			}
			break;

		case 'p':
			pitch = atoi(optarg);
			break;

		case 't':
			tempo = atof(optarg);
			break;

		case 'g':
			gain = atof(optarg);
			break;

		case 'a':
			asp = atof(optarg);
			break;

		case 'v':
			vibrato = atoi(optarg);
			break;

		case 'h':
			err_exit(usage);

		default:
			err_exit(usage);
		}
	}

	if (wcslen(text_buf) <= 0)
		err_exit("Nothing to synthesize. Use -s <string>");

	if (!(save || out))
		err_exit("No output method specified. Use -o <path> or stdout");

	synth(text_buf, pitch, tempo, gain, asp, vibrato);

	exit(EXIT_SUCCESS);
}

#define append(x)	wd = wcscpy(wd, x);\
			wd += wcslen(x)

void process_text(char *src, wchar_t **dest)
{
	size_t mbslen = mbstowcs(NULL, src, 0);
	*dest = calloc(mbslen + 128, sizeof(wchar_t));

	wchar_t *wcs = calloc(mbslen + 1, sizeof(wchar_t));
	mbstowcs(wcs, src, mbslen + 1);

	wchar_t *digits[] = {L"sıfır", L"bir", L"iki", L"üç", L"dört", L"beş",
		L"altı", L"yedi", L"sekiz", L"dokuz"};

	wchar_t *wp = wcs, *wd = *dest;
	for (; *wp != 0; wp++) {
		if (iswalpha(*wp)) {
			if (iswupper(*wp)) *wd++ = towlower(*wp);
			else *wd++ = *wp;
		} else if (iswdigit(*wp)) {
			append(digits[*wp - '0']);
		} else {
			switch(*wp) {
			case L'+':
				append(L"artı");
				break;
			case L'-':
				append(L"eksi");
				break;
			case L'*':
				append(L"çarpı");
				break;
			case L'/':
				append(L"bölü");
				break;
			case L'>':
				append(L"büyüktür");
				break;
			case L'<':
				append(L"küçüktür");
				break;
			case L'%':
				append(L"yüzde");
				break;
			case L'=':
				append(L"eşittir");
				break;
			default:
				*wd++ = L'_';
				break;
			}
		}
	}
	*wd = L'\0';
	free(wcs);
}

void err_exit(const char *message)
{
	puts(message);
	exit(EXIT_FAILURE);
}
