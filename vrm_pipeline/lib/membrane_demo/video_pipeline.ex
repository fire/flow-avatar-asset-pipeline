defmodule Membrane.Demo.VideoPipeline do
  @moduledoc """
  Sample Membrane pipeline that will play an `.mp4` file.
  """

  use Membrane.Pipeline

  alias Membrane.H264.FFmpeg.{Parser, Decoder}
  alias Membrane.Hackney
  alias Membrane.SDL
  alias Membrane.Element.{Tee}

  @impl true
  def handle_init(_) do
    children = [
      hackney: %Hackney.Source{
        location: "https://membraneframework.github.io/static/video-samples/test-video.h264"
      },
      tee: Tee.Master,
      parser: %Parser{framerate: {60, 1}},
      decoder: Decoder,
      sdl: SDL.Player,
      debug: Membrane.Demo.VideoDebug.Sink.Buffers,
    ]

    links = [
      link(:hackney)
      |> to(:parser)
      |> to(:decoder)
      |> to(:tee),
      link(:tee) |> via_out(:master) |> to(:sdl),
      link(:tee) |> via_out(:copy) |> to(:debug)
    ]

    {{:ok, spec: %ParentSpec{children: children, links: links}}, %{}}
  end
end
