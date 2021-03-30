import inspect
from os import path
from g4epy import Geant4Eic

g4e = Geant4Eic(detector='jleic', beamline='erhic') \

g4e .output('pi0_10GeV') \
    .source('../data/cone_pgun_my.mac') \
    
g4e 

g4e.run()
