# command-file to pass Geant4 simulation to cluster
#condor_q -all
#condor_submit start.cmd
#condor_rm username
#ccmake ..
#make -j40
#/usr/bin/time -v ./ColliRotate run.mac
#hadd -f outputfile.root inputfile*.root*
#hadd -f Result.root ID_*.root*

# you have to use "universe = vanilla"
universe		= vanilla

# the path to your simulation
simulation_path       = /hiskp3/loepke/geant4/ColliRotate

# the path to your executable file
executable		= $(simulation_path)/build/ColliRotate

# the path to the console output -> console output is flushed to this file
output			= $(simulation_path)/sim/C26-5d_4_1_3_0_logfiles/log.out.$(Process)

# the path to the error output -> console output is flushed to this file if any errors occur
error			= $(simulation_path)/sim/C26-5d_4_1_3_0_logfiles/log.err.$(Process)

# a datapath ... unused so far
# datapath        = $(simulation_path)/sim/results

# the path to the cluster log file -> some infos about the job: CPUs, memory, size ...
log			    = condor_explora.log
getenv			= true

# be a nice user!
nice_user		= TRUE

# how much memory your simulation needs
# check this on entry2 with 
#/usr/bin/time -v <program name with cmdln options> e.g.:
#/usr/bin/time -v ./ColliRotate C26-5d_4_2_4_0.mac
request_memory  = 1000 MB

# pass down a macrofile to your simulation
arguments   = $(simulation_path)/C26-5d_4_1_3_0.mac

# Number of processes to start
queue 100
