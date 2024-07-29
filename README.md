# kws_cli

[![build](https://github.com/mryndzionek/kws_cli/actions/workflows/build.yml/badge.svg)](https://github.com/mryndzionek/kws_cli/actions/workflows/build.yml)

## About

Speech recognition in ~300kB of code.

Small footprint, standalone, zero dependency, offline
keyword spotting (KWS) CLI tool. Might be useful in
some automation task. Accepts audio on stdin a and recognizes
following words: `up`, `down`, `left`, `right`, `stop`.

Here is an example invocation:

```
rec -q -t raw -c1 -e signed -b 16 -r16k - | ./kws_cli
```

Make sure you have decent microphone and the system audio
is on a decent level.

Individual WAV files can piped (e.g. for testing) using:

```
sox -S ../untitled.wav -t raw -c1 -e signed -b 16 -r16k - | ./kws_cli
```
## Demo

In the demo subdirectory there is a Python script showing how to
use `kws_cli` for simple automation.

https://github.com/user-attachments/assets/2a9eaa90-a0b9-4423-91c8-fd4df6bbc459

## More details

Speech recognition is based on [this](https://github.com/microsoft/EdgeML/blob/master/docs/publications/Sha-RNN.pdf)
model and examples from the same repository.
This simple model with three layers: 2x LSTM + 1x fully connected.
The model is trained in PyTorch and exported to ONNX.
Then [onnx2c](https://github.com/kraiskil/onnx2c)
is used to convert the model to a bunch of C code.
The LSTM layers had become mainstream in recent years and are well
supported in different frameworks. ~~The model is small, so it might
be possible to run it on Cortex-M4/M7, or ESP32 (future work).~~
See below.

## Building

The usual CMake routine:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release
make
```

## Running in embedded systems context (TinyML/EdgeML)

This model was run on RP2040 and ESP32-S3.

On RP2040 the inference alone takes ~2.4s with 240MHz clock, so
it's not possible to run real-time. The feature extraction also
takes significant time. A smaller ("narrower") model was also
tested and still the inference took ~1.2s. This is still impressive
taking into account that RP2040 is a Cortex-M0+ without FPU.

On ESP32-S3 running at 240MHz inference with feature extraction
takes ~0.5s, so running real-time is possible (e.g. every 750ms
with 250ms overlap gives good results).


