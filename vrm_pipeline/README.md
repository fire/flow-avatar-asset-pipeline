# Membrane simple pipeline demo

This demo shows how to create a pipeline that plays an mp3 file.

## Prerequisites

1. Make sure you have following libraries installed on your OS:
   * clang-format, 
   * portaudio19-dev, 
   * ffmpeg, 
   * libavutil-dev, 
   * libswresample-dev, 
   * libmad0-dev
   
    One-liner for Ubuntu
    ```bash
    apt install clang-format portaudio19-dev ffmpeg libavutil-dev libswresample-dev libmad0-dev
    ```
    One-liner for Rocky Linux
    ```bash
    yum install portaudio-devel ffmpeg-devel libresample-devel libmad-devel SDL2-devel libav-devel
    ```
    One-liner for MacOS
    ```bash
    brew install clang-format portaudio ffmpeg libmad
    ```
1. Make sure you have Elixir installed on your machine. See: https://elixir-lang.org/install.html
1. Fetch the required dependencies by running `mix deps.get`

### How to run

To start the demo pipeline run `mix run --no-halt run.exs` or type the following commands into an IEx shell (started by `iex -S mix`):

```elixir
alias Membrane.Demo.VideoPipeline
{:ok, pid} = VideoPipeline.start_link()
VideoPipeline.play(pid)
```

## Copyright and License

Copyright 2018, [Software Mansion](https://swmansion.com/?utm_source=git&utm_medium=readme&utm_campaign=membrane)

[![Software Mansion](https://membraneframework.github.io/static/logo/swm_logo_readme.png)](https://swmansion.com/?utm_source=git&utm_medium=readme&utm_campaign=membrane)

Licensed under the [Apache License, Version 2.0](LICENSE)
