# Sampling Algorithm
A simple sampling algorithm. Two versions are provided:
* sampling.c
* sampling_corrected.c
 
## Build
```
gcc sampling.c -o sampling -Wall

gcc sampling_corrected.c -o sampling_corrected -Wall
```

## Run
```
./sampling T dt

./sampling_corrected T dt
```
* __T__, is the sampling duratiom
* __dt__, is the sampling interval
