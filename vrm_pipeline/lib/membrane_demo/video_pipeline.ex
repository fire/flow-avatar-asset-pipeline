defmodule Membrane.Demo.VideoPipeline do
  @moduledoc """
  Sample Membrane pipeline that will play an `.mp4` file.
  """

  use Membrane.Pipeline

  alias Membrane.H264.FFmpeg.{Parser, Decoder}
  alias Membrane.Hackney
  alias Membrane.SDL

  @impl true
  def handle_init(_) do
    children = [
      hackney: %Hackney.Source{
        location: "https://membraneframework.github.io/static/video-samples/test-video.h264"
      },
      parser: %Parser{framerate: {30, 1}},
      decoder: Decoder,
      sdl: SDL.Player
    ]

    links = [
      link(:hackney)
      |> to(:parser)
      |> to(:decoder)
      |> to(:sdl)
    ]

    {{:ok, spec: %ParentSpec{children: children, links: links}}, %{}}
  end
end
