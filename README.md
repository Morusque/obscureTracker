obscureTracker<br/>
==============

Minimalist Hackvision tracker

http://nurykabe.com/visit/programming/hardware/obscure%20tracker/

live menu :
FIRE+UP = go to the beauty menu
FIRE+DOWN = go to the notes menu
FIRE+UP+DOWN = reset all effects
line 1 :
LEFT/RIGHT = choose slot
FIRE+RIGHT = save
FIRE+LEFT = load
line 2 : sync mode
LEFT/RIGHT = choose mode
line 3 : tempo
LEFT/RIGHT = modify number of frames
FIRE+LEFT/RIGHT = modify swing
line 4 : frame length
LEFT/RIGHT = modify number of milliseconds
FIRE+LEFT/RIGHT = convert frames and frame time
line 5 :
LEFT/RIGHT = shift notes sequence
FIRE+RIGHT = commit notes sequence shifting
line 6 :
LEFT/RIGHT = shift durations sequence
FIRE+RIGHT = commit durations sequence shifting
line 7 :
LEFT/RIGHT = shift commands sequence
FIRE+RIGHT = commit commands sequence shifting
line 8 :
LEFT/RIGHT = shift values sequence
FIRE+RIGHT = commit values sequence shifting
line 9 :
LEFT/RIGHT = choose global effect
FIRE+RIGHT = enable global effect
FIRE+LEFT = disable global effect
line 10 :
LEFT/RIGHT = modify alternate sequence length
FIRE+RIGHT = enable alternate sequence
FIRE+LEFT = disable alternate sequence
line 11 :
LEFT/RIGHT = choose special effect
FIRE+RIGHT = enable special effect
FIRE+LEFT = disable special effect
line 12 :
LEFT/RIGHT = choose randomizer
FIRE+RIGHT = enable randomizer
FIRE+LEFT = disable randomizer
line 13 :
LEFT/RIGHT = shift notes pitch by one semitone
FIRE+LEFT/RIGHT = shift notes pitch by one octave
line 14 :
LEFT/RIGHT = select note
FIRE+LEFT = copy
FIRE+RIGHT = paste
line 15 (hidden)

notes menu :
FIRE+UP = go to the live menu
FIRE+DOWN = go to the durations menu
UP/DOWN = select beat
RIGHT/LEFT = transpose note by one semitone
DOWN+LEFT = transpose all notes down
DOWN+RIGHT = transpose all notes up
FIRE+RIGHT/LEFT = transpose note by one octave
FIRE+UP+DOWN = decrease pitch range

durations menu :
FIRE+UP = go to the notes menu
FIRE+DOWN = go to the commands menu
UP/DOWN = select beat
RIGHT/LEFT = modify duration by one frame
FIRE+RIGHT = set duration to frame duration
FIRE+LEFT = set duration to zero
FIRE+UP+DOWN = limit all durations to frame duration

commands menu :
FIRE+UP = go to the durations menu
FIRE+DOWN = go to the beauty menu
UP/DOWN = select beat
RIGHT/LEFT = modify value
FIRE+RIGHT/LEFT = select command

beauty menu :
beauty

sync modes :
0 = stop
1 = play
2 = stop
3 = stop

commands :
0 =   nothing
1 = P pitch to (starting)
2 = U tune (fine)
3 = O octaver (shift)
4 = L legato (time)
5 = C chord (first/second)
6 = V vibrato (time/amp)
7 = T trill (place/note)
8 = ~ tremolo (time)
9 = N noise (amount)
A = D delay (frames)
B = > goto (beat)
C = - repeat (random)
D = . random (value)

special effects :
0 - freeze beat and set volume on
1 - limit range to the current octave
2 - invert durations
3 - play sequence backwards

randomizer :
0 = radomize notes
1 = radomize durations
2 = radomize commands
3 = radomize global params
4 = radomize everything

