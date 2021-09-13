# Lapic
Lapic is a simple speech synthesizer that uses LPC decoding. The default voicebank supports Turkish.

## Usage
```
Usage: ./lapic -s "text" -o out.wav
	-s <text>
	-o <path>: PCM output to file
	-t <tempo value>
	-p <pitch value>
	-g <gain value>
	-a <aspiration value>
	-v <vibrato value> (100-10000)
	-h: print help
```

### Examples
Default: `./lapic -s "Merhaba ben bir konuşma sentezleyiciyim" -o outfile.pcm`\
Whisper: `./lapic -s "uuuu spuuki" -a 0.002 -g 1 -o outfile.pcm`\
Vibrato: `./lapic -s "aaaaaaaaaa" -v 2500 -o outfile.pcm`

Playback using aplay: `./play.sh -s "alsa ile gerçek zamanlı çalma" -t 2`\
Convert PCM using ffmpeg: `ffmpeg -f f32le -ar 44100 -i outfile.pcm -acodec libmp3lame outfile.mp3`
