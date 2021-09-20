from pygame import mixer
from sys import argv

script, first = argv

pok = mixer.init()
po = mixer.music.load(f"audio/{first}")
p = mixer.music.play()
pos = 0
while mixer.music.get_pos() > -1:
    pos = mixer.music.get_pos()
