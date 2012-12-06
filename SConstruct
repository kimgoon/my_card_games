
#grab the current environment
env = Environment()

SConscript('LibCards/SConscript')

#set up the lib paths and include paths
env.Append(LIBPATH=['LibCards/'])
env.Append(CPPPATH=['LibCards/'])
env.Append(LIBS=['Cards'])

#compile the test applications
env.Program(target='testCardDeck_exe', source=['testCardDeck.cpp'])
env.Program(target='testDealer_exe', source=['testDealer.cpp'])
env.Program(target='testPlayer_exe', source=['testPlayer.cpp'])
env.Program(target='testBlackJackArena_exe', source=['testBlackJackArena.cpp'])

#compile the real application here.... later on, sometime
