#!/bin/sh

./lapic -o stdout "$@" | aplay --format=FLOAT --rate=44100
